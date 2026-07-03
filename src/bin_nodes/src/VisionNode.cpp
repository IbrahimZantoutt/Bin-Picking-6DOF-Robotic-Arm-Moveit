#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <image_geometry/pinhole_camera_model.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>


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

            targets_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("targets", 10);
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

            int best = -1;
            double best_area = 50.0;  // ignore noise blobs smaller than this
            for (size_t i = 0; i < contours.size(); ++i) {
                double a = cv::contourArea(contours[i]);
                if (a > best_area) { best_area = a; best = static_cast<int>(i); }
            }

            cv::imshow("hsv", hsv);
            cv::waitKey(1);
            cv::imshow("mask", mask);
            cv::waitKey(1);
        }

    private:
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr targets_pub_;

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