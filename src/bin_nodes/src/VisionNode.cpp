#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <image_geometry/pinhole_camera_model.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <bin_interfaces/srv/get_targets.hpp>


static constexpr char kTargetFrame[] = "robot_base";

class VisionNode: public rclcpp::Node{
    public:
        VisionNode(): Node("vision_node"){
            info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>("/camera/camera_info", 10 ,[this](sensor_msgs::msg::CameraInfo::SharedPtr info){
                camera_model_.fromCameraInfo(info);
                have_model_ = true;
            });

            image_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/camera/image_raw",10, std::bind(&VisionNode::image_callback,this,std::placeholders::_1));

            depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/camera/depth/image_raw",10, [this](sensor_msgs::msg::Image::SharedPtr depth){
                try{
                    depth_image_ = cv_bridge::toCvCopy(depth, "32FC1")->image;
                } catch (cv_bridge::Exception& e) {
                    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
                    return;
                }
            });

            tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

            targets_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("targets", 10);

            // Service: return the latest single detected cube on request.
            targets_srv_ = this->create_service<bin_interfaces::srv::GetTargets>(
                "get_targets",
                [this](const std::shared_ptr<bin_interfaces::srv::GetTargets::Request>,
                       std::shared_ptr<bin_interfaces::srv::GetTargets::Response> res){
                    res->found  = have_target_;
                    res->target = latest_target_;
                });
        }

        void image_callback(const sensor_msgs::msg::Image::SharedPtr image){
            if(!have_model_){
                RCLCPP_WARN(this->get_logger(), "No camera model yet");
                return;
            }

            cv::Mat cv_image;
            try{
                cv_image = cv_bridge::toCvCopy(image, "bgr8")->image;
            } catch (cv_bridge::Exception& e) {
                RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
                return;
            }

            cv::imshow("Camera Image", cv_image);
            cv::waitKey(1);

            // Process the image and depth data here
            cv::Mat hsv, mask;
            cv::cvtColor(cv_image, hsv, cv::COLOR_BGR2HSV);
            cv::inRange(hsv, cv::Scalar(40, 100, 40), cv::Scalar(80, 255, 255), mask);
            cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, {3, 3});
            cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
            cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            // Pick the single largest green blob -- one target, not an array.
            int best = -1;
            double best_area = 50.0;   // ignore noise blobs smaller than this (px^2)
            for (size_t i = 0; i < contours.size(); i++) {
                double a = cv::contourArea(contours[i]);
                if (a > best_area) { best_area = a; best = static_cast<int>(i); }
            }
            if (best >= 0) {
                cv::Moments m = cv::moments(contours[best]);
                if (m.m00 != 0) {
                    int u = static_cast<int>(m.m10 / m.m00);
                    int v = static_cast<int>(m.m01 / m.m00);
                    cv::drawContours(cv_image, contours, best, cv::Scalar(0, 255, 0), 2);
                    cv::circle(cv_image, {u, v}, 4, cv::Scalar(0, 0, 255), -1);
                    localize(u, v);  // deproject + transform + cache
                }
            } else {
                // No green blob in view -> nothing to pick. Clear the cached
                // target so get_targets reports "not found" and the pick loop
                // stops once the table has been cleared.
                have_target_ = false;
            }

            cv::imshow("hsv", hsv);
            cv::waitKey(1);
            cv::imshow("mask", mask);
            cv::waitKey(1);
        }

        void localize(int u, int v) {
            if (!have_model_) {
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                    "no camera_info yet");
                return;
            }
            if (depth_image_.empty() ||
                u < 0 || v < 0 || u >= depth_image_.cols || v >= depth_image_.rows) {
                return;
            }

            // --- 2. Depth at the pixel (metres along the optical axis) ---------
            float d = depth_image_.at<float>(v, u);
            if (!std::isfinite(d) || d <= 0.0f) {
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                    "no valid depth at (%d,%d)", u, v);
                return;
            }

            // --- 3. Deproject to a 3D point in the camera optical frame --------
            cv::Point3d ray = camera_model_.projectPixelTo3dRay({static_cast<double>(u),
                                                              static_cast<double>(v)});
            geometry_msgs::msg::PointStamped p_cam;
            p_cam.header.frame_id = camera_model_.tfFrame();   // camera_optical_frame
            // stamp left at 0 => tf uses the latest available (static) transform
            p_cam.point.x = ray.x * d / ray.z;
            p_cam.point.y = ray.y * d / ray.z;
            p_cam.point.z = d;

            // --- 4. Transform into the arm base frame -------------------------
            geometry_msgs::msg::PointStamped p_base;
            try {
                p_base = tf_buffer_->transform(p_cam, kTargetFrame,
                                               tf2::durationFromSec(0.2));
            } catch (const tf2::TransformException & e) {
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                    "tf %s -> %s failed: %s",
                    p_cam.header.frame_id.c_str(), kTargetFrame, e.what());
                return;
            }

            // --- 5. Cache as the latest single target (served on request) -----
            latest_target_.header.stamp = this->get_clock()->now();
            latest_target_.header.frame_id = kTargetFrame;
            latest_target_.point = p_base.point;
            have_target_ = true;

            publishTarget(p_base.point);   // keep publishing for RViz/debug
        }
        void publishTarget(const geometry_msgs::msg::Point & point) {
            const rclcpp::Time now = this->get_clock()->now();
            geometry_msgs::msg::PointStamped target;
            target.header.stamp = now;
            target.header.frame_id = kTargetFrame;
            target.point = point;
            targets_pub_->publish(target);
        }

    private:
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr targets_pub_;

    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

    rclcpp::Service<bin_interfaces::srv::GetTargets>::SharedPtr targets_srv_;
    geometry_msgs::msg::PointStamped latest_target_;
    bool have_target_ = false;

    image_geometry::PinholeCameraModel camera_model_;
    cv::Mat depth_image_;
    bool have_model_ = false;
};

int main(int argc, char** argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<VisionNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
