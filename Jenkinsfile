

pipeline{
    agent any
    parameters{
        choice(choices:["noPush","push"],name:"PushAction",description:"push or not?")
    }
    stages{
        stage("checkout"){
            steps{
                checkout scm
            }
        }
        stage("build_image"){
            when{
                allOf{
                    expression{params.PushAction == "push"};
                    expression{!fileExists("Dockerfile")};
                    changeset "Dockerfile";
                    branch 'main'
                }
            }
            steps{
                sh'''
                docker build -t binpicking .
                '''
            }
        }
        stage("parallel build stage"){
            parallel{
                stage("ros_build"){
                    agent {docker{image 'binpicking'}}
                    steps{
                        sh'''#!/bin/bash
                        source /opt/ros/humble/setup.bash
                        colcon build
                        '''
                    }
                }
                stage("python_test"){
                    agent {docker {image 'python:latest'}}
                    steps{
                        sh'''
                        python --version
                        echo "print('testing python')" > test.py
                        python test.py
                        '''

                        archiveArtifacts artifacts:"test.py", onlyIfSuccessful:true
                    }
                    
                }
            }
        }   
        stage("push_image"){
            when{
                allOf{
                    expression{params.PushAction == "push"};
                    expression{fileExists("Dockerfile")};
                    changeset "Dockerfile";
                    branch 'main'
                }
            }
            steps{
               sh'''
               docker tag binpicking myrepo/binpicking:latest
               docker push myrepo/binpicking:latest
               '''
            }
        }
    }
    post{
        always{
            echo "pipeline finished"
        }
        failure{
            echo "pipeline failed"
        }
        success{
            echo "pipeline success"
        }
    }
}