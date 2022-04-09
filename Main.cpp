#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

namespace opencv {
    cv::Mat readImage(const std::string& imagePath)
    {
        cv::Mat img = cv::imread(imagePath);
        if (img.data) {
            namedWindow("Image Reading", WINDOW_AUTOSIZE);

            cv::imshow("Image Reading", img);
            cv::moveWindow("Image Reading", 150, 150);

            cv::waitKey(0);

            cv::destroyAllWindows();
            // cv::destroyWindow("Image Reading");
        }
        else {
            std::cout << "The path of the image can not be found!" << "\n";
        }
        return img;
    }

    void readVideo(const std::string& videoPath) {

        cv::VideoCapture vid;
        vid.open(videoPath);
        cv::Mat frameAtMoment;
        int fps = 23, keyListener = -1;

        if (vid.isOpened()) {
            std::cout << "Video has been able to opened" << "\n";
            cv::namedWindow("Video Reading");

            while (vid.read(frameAtMoment)) {
                cv::imshow("Video Reading", frameAtMoment);
                keyListener = cv::waitKey(fps);
                if (keyListener == 27) {
                    std::cout << "Video is stopped" << "\n";
                    break;
                }
                else if (keyListener == 43) {
                    fps++;
                    std::cout << "Fps = " << fps << "\n";
                    std::cout << "Video is slowed down" << "\n";
                }
                else if (keyListener == 45) {
                    fps = fps < 1 ? 0 : --fps;
                    std::cout << "Fps = " << fps << "\n";
                    std::cout << "Video speed up" << "\n";
                }
            }
            cv::destroyAllWindows();
        }
        else
            std::cout << "Video has been not able to opened" << "\n";
        cv::waitKey(0);
    }

    void readVideoFromWebcam(const int& channel) {

        cv::VideoCapture vid;
        cv::namedWindow("Camera");
        cv::Mat frame;

        if (vid.open(channel)) {
            while (vid.grab()) // grap = o anki frame'i alabiliyor muyuz?
            {
                vid.retrieve(frame); // retrieve = videonun çýkýþ dizisini, Mat tipindeki deðere aktarma.
                cv::imshow("Camera", frame);
                cv::moveWindow("Camera", 250, 250);
                if (cv::waitKey(23) == 27) { break; }
            }
        }
        else {
            std::cout << "Webcam can not be opened" << "\n";
        }
    }

    void readVideoFromIpcam(const std::string& ip) {

        cv::VideoCapture vid;
        cv::namedWindow("Camera");
        cv::Mat frame;

        if (vid.open(ip)) {

            while (vid.grab()) // grap = o anki frame'i alabiliyor muyuz?
            {
                vid.retrieve(frame); // retrieve = videonun çýkýþ dizisini, Mat tipindeki deðere aktarma.
                cv::imshow("Camera", frame);
                if (cv::waitKey(23) == 27) { break; }
            }
        }
        else {
            std::cout << "Ipcam can not be opened" << "\n";
        }
    }

    void createSimpleImage(const int& height, const int& width, const int& blue, const int& green, const int& red) {
        cv::Mat img(height, width, CV_8UC3); // CV_8UC3  = blue, green, red; 3 kanallý renk uzayý;
        img = cv::Scalar(blue, green, red); // Scalar, resime renk vermek için kullanýlýr. blue-green-red -> min=0 max=255

//      cv::Mat img(height, width, CV_8UC3, cv::Scalar(blue, green, red));
        cv::imshow("Simple Picture", img);
        cv::waitKey(0);
    }

    void rectImage(const std::string& imagePath, const int& x, const int& y, const int& width, const int& height) {
        cv::Mat image = cv::imread(imagePath);
        cv::Mat newImage;
        image.copyTo(newImage);
        newImage = cv::Mat(newImage, cv::Rect(x, y, width, height));
        cv::imshow("p", newImage);
        cv::waitKey(0);
    }

    void lineToImage(const std::string& imagePath, int x1, int y1, int x2, int y2, int blue, int green, int red, int thickness) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::Mat imageLined;
        orgImage.copyTo(imageLined);
        cv::line(imageLined, cv::Point(x1,y1), cv::Point(imageLined.cols/2,imageLined.rows/2), cv::Scalar(blue,green,red), thickness, 8, 0);
        cv::line(imageLined, cv::Point(imageLined.cols, y1), cv::Point(imageLined.cols / 2, imageLined.rows / 2), cv::Scalar(blue, green, red), thickness, 8, 0);
        cv::imshow("Pencere", imageLined);
        cv::waitKey(0);
    }
}

int main() {
    std::string imageOrVideoPath = "C:/Users/kerem/Desktop/Albümler/beb/beb2.png";
//  opencv::readImage(imageOrVideoPath);
//  opencv::readVideo(imageOrVideoPath);
//  opencv::readVideoFromWebcam(0); // 0 webcam belong to the pc
//  opencv::createSimpleImage(900, 1600, 200, 150, 130);
//  opencv::rectImage(imageOrVideoPath, 100, 300, 800, 350);
//  opencv::lineToImage(imageOrVideoPath,0,0,350,150,0,255,255,3);

    return 0;
}