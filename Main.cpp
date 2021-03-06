#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

namespace drawing {
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
                vid.retrieve(frame); // retrieve = videonun ??k?? dizisini, Mat tipindeki de?ere aktarma.
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
                vid.retrieve(frame); // retrieve = videonun ??k?? dizisini, Mat tipindeki de?ere aktarma.
                cv::imshow("Camera", frame);
                if (cv::waitKey(23) == 27) { break; }
            }
        }
        else {
            std::cout << "Ipcam can not be opened" << "\n";
        }
    }

    void createSimpleImage(const int& height, const int& width, const int& blue, const int& green, const int& red) {
        cv::Mat img(height, width, CV_8UC3); // CV_8UC3  = blue, green, red; 3 kanall? renk uzay?;
        img = cv::Scalar(blue, green, red); // Scalar, resime renk vermek i?in kullan?l?r. blue-green-red -> min=0 max=255

//      cv::Mat img(height, width, CV_8UC3, cv::Scalar(blue, green, red));
        cv::imshow("Simple Picture", img);
        cv::waitKey(0);
    }

    void drawRectImage(const std::string& imagePath, const int& x, const int& y, const int& width, const int& height) {
        cv::Mat image = cv::imread(imagePath);
        cv::Mat newImage;
        image.copyTo(newImage);
        newImage = cv::Mat(newImage, cv::Rect(x, y, width, height));
        cv::imshow("Image Window", newImage);
        cv::waitKey(0);
    }

    void drawLineToImage(const std::string& imagePath, int x1, int y1, int x2, int y2, int blue, int green, int red, int thickness) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::Mat imageLined;
        orgImage.copyTo(imageLined);
        cv::line(imageLined, cv::Point(x1,y1), cv::Point(imageLined.cols/2,imageLined.rows/2), cv::Scalar(blue,green,red), thickness, 8, 0);
        cv::line(imageLined, cv::Point(imageLined.cols, y1), cv::Point(imageLined.cols / 2, imageLined.rows / 2), cv::Scalar(blue, green, red), thickness, 8, 0);
        //imageLined.cols = resmin maximum kolon sayisini alir/ 1920
        //imageLined.rows = resmin maximum satir sayisini alir/ 1080
        cv::imshow("Line Window", imageLined);
        cv::waitKey(0);
    }
    void drawRectangleToImagePoints(const std::string& imagePath, int x1, int y1, int x2, int y2, int blue, int green, int red, int thickness) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::Point start(x1, y1);
        cv::Point finish(x2, y2);
        cv::rectangle(orgImage, start, finish, cv::Scalar(blue, green, red), thickness, 8, 0);
        cv::imshow("Rectangle Window", orgImage);
        cv::waitKey(0);

    }
    void drawRectangleToImage(const std::string& imagePath, int x, int y, int width, int height, int blue, int green, int red, int thickness) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::rectangle(orgImage, cv::Rect(x,y, width, height), cv::Scalar(blue, green, red), thickness, 8, 0);
        cv::imshow("Rectangle Window", orgImage);
        cv::waitKey(0);
    }
    void drawWriteTextToImage(const std::string& imagePath, const std::string& text, int x, int y, double sizeofText, int thickness, bool mirror=false) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::Mat imageTexted;
        orgImage.copyTo(imageTexted);
        cv::Point location(x, y); // x-y noktalarimizi, yazinin sol alt kose olarak alir
        cv::Point mirrorLocation(x, y+20);
        cv::Scalar color(100, 0, 200); // blue green, red 
        cv::putText(imageTexted, text, location, FONT_ITALIC, sizeofText, color, thickness, 8, mirror);
        cv::putText(imageTexted, text, mirrorLocation, FONT_ITALIC, sizeofText, color, thickness, 8, !mirror);
        cv::imshow("Write Window", imageTexted);
        cv::waitKey(0);
    }
    void drawCircleToImage(const std::string& imagePath, int x, int y, int radius, int thickness=3) {
        cv::Mat orgImage = cv::imread(imagePath);
        cv::Point center(x, y);
        cv::Scalar color(0, 255, 255);
        cv::circle(orgImage, center, radius, color, thickness);
        cv::imshow("Circle Window", orgImage);
        cv::waitKey(0);
    }
}

namespace matrix {

    void readValuesOfImage(const std::string& imagePath) {
        cv::Mat img = cv::imread(imagePath);
        cv::Mat processingImg;
        img.copyTo(processingImg);
        uchar blue, green, red;
        for (int x=0; x < img.cols; x++)
        {
            for (int y = 0; y < img.rows; y++)
            {
                blue = processingImg.at<cv::Vec3b>(cv::Point(x, y))[0];
                if (blue < 255 && blue > 100) {
                    blue = 80;
                    processingImg.at<cv::Vec3b>(cv::Point(x, y))[0] = blue;
                }
                green = processingImg.at<cv::Vec3b>(cv::Point(x, y))[1];
                if (green < 255 && green > 150) {
                    green = 120;
                    processingImg.at<cv::Vec3b>(cv::Point(x, y))[1] = green;
                }
            }
        }
        cv::imshow("Image", processingImg);
        cv::waitKey(0);
    }

    void copyImg(const cv::Mat& img, cv::Mat& copyImage) {
        copyImage = cv::Mat(cv::Size(img.cols, img.rows), CV_8UC3);
        cv::Vec3b bgr;
        cv::namedWindow("Image Copy Proccessing", cv::WINDOW_NORMAL);

        for (int x = 0; x < img.cols; x++)
        {
            for (int y = 0; y < img.rows; y++)
            {
                bgr = img.at<cv::Vec3b>(cv::Point(x, y));
                copyImage.at<cv::Vec3b>(cv::Point(x, y)) = bgr;

                cv::imshow("Image Copy Proccessing", copyImage);
                cv::waitKey(1);
            }
        }
    }
    void enlargeImage(const std::string& imagePath, const int& coefficientOfEnlarging=2){
        cv::Mat img = cv::imread(imagePath);
        int newWidth = img.cols * coefficientOfEnlarging;
        int newHeigth = img.rows * coefficientOfEnlarging;
        int xStart, yStart, xFinish, yFinish;
        cv::Vec3b bgr;
        cv::Mat newImg(cv::Size(newWidth, newHeigth), CV_8UC3);
        for(int i=0; i<img.cols; i++){
            for (int j = 0; j < img.rows; j++) {
                bgr = img.at<cv::Vec3b>(cv::Point(i, j));
                xStart = i * coefficientOfEnlarging;
                yStart = j * coefficientOfEnlarging;
                xFinish = xStart + coefficientOfEnlarging;
                yFinish = yStart + coefficientOfEnlarging;
                while(xStart<xFinish)
                {
                    while (yStart < yFinish) {
                        newImg.at<cv::Vec3b>(cv::Point(xStart, yStart)) = bgr;
                        yStart++;
                    }
                    xStart++;
                }
            }
        }
        cv::namedWindow("Enlarge Image", cv::WINDOW_NORMAL);
        cv::imshow("Enlarge Image", newImg);
        cv::waitKey(0);
    }
    void miniaturizeImage(const std::string& imagePath, const int& coefficientOfMiniaturize = 2) {
        cv::Mat img = cv::imread(imagePath);
        int width, height;
        cv::Vec3b bgr;
        if (img.data && !img.empty()) {
            width = img.cols / coefficientOfMiniaturize;
            height = img.rows / coefficientOfMiniaturize;
            cv::Mat newImg(cv::Size(width, height), CV_8UC3);
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    bgr = img.at<cv::Vec3b>(cv::Point(i * coefficientOfMiniaturize, j * coefficientOfMiniaturize));
                    newImg.at<Vec3b>(cv::Point(i, j)) = bgr;
                }
            }
            cv::namedWindow("Miniaturize Image", cv::WINDOW_NORMAL);
            cv::imshow("Miniaturize Image", newImg);
            cv::waitKey(0);
        }
    }

    void blur(const std::string& imagePath, int degreeOfNghbrhd=1) {
        cv::Mat img = cv::imread(imagePath);
        cv::Mat blurImg = cv::Mat::zeros(cv::Size(img.cols, img.rows), CV_8UC3);
        unsigned int b = 0, g = 0, r = 0, counter=0;

        for (int x = 0; x < img.cols; x++) {
            for (int y = 0; y < img.rows; y++) {
                for (int xNghStart = x - degreeOfNghbrhd; xNghStart < x + degreeOfNghbrhd; xNghStart++) {
                    for (int yNghStart = y - degreeOfNghbrhd; yNghStart < y + degreeOfNghbrhd; yNghStart++) {

                        if (xNghStart >= 0 && yNghStart >= 0 && xNghStart < blurImg.cols && yNghStart < blurImg.rows) {
                            b += (int)img.at<cv::Vec3b>(cv::Point(xNghStart, yNghStart))[0];
                            g += (int)img.at<cv::Vec3b>(cv::Point(xNghStart, yNghStart))[1];
                            r += (int)img.at<cv::Vec3b>(cv::Point(xNghStart, yNghStart))[2];
                            counter++;
                        }
                    }
                }
                b /= counter;
                g /= counter;
                r /= counter;
                blurImg.at<cv::Vec3b>(cv::Point(x, y))[0] = b;
                blurImg.at<cv::Vec3b>(cv::Point(x, y))[1] = g;
                blurImg.at<cv::Vec3b>(cv::Point(x, y))[2] = r;
                b = 0; g = 0; r = 0; counter = 0;
            }
        }


        cv::namedWindow("Blur Image", cv::WINDOW_GUI_NORMAL);
        cv::imshow("Blur Image", blurImg);
        cv::waitKey(0);
    }

}

namespace painting {
    struct ImageData {
    private:
        cv::Vec3b color= cv::Vec3b(255,0,0);
        int colorCounter=0;
    public:
        cv::Mat img;
        string windowName = "Paint";
        bool isDrawable = false;

        void increaseColor() {
            colorCounter++;
            if (colorCounter == 4)
                colorCounter = 0;
        }
        void decreaseColor() {
            colorCounter--;
            if (colorCounter == -1)
                colorCounter = 3;
        }

        cv::Vec3b getColor() {
            switch (colorCounter)
            {
            case 0:
                return color = cv::Vec3b(255, 0, 0);
                break;
            case 1:
                return color = cv::Vec3b(0, 255, 0);
                break;
            case 2:
                return color = cv::Vec3b(0, 0, 255);
                break;
            case 3:
                return color = cv::Vec3b(128, 128, 128);
                break;
            default:
                break;
            }
        }

    };
    void mouseEvent(int event, int x, int y, int flag, void* data) {
        auto* d = (ImageData*)data;
        if (event == cv::EVENT_LBUTTONDOWN) {
            d->isDrawable = true;
        }
        else if (event == cv::EVENT_LBUTTONUP) {
            d->isDrawable = false;
        }

        else if (event == cv::EVENT_RBUTTONUP) {
            d->increaseColor();
        }
        if (d->isDrawable) {
            d->img.at<cv::Vec3b>(cv::Point(x, y)) = d->getColor();
            cv::imshow(d->windowName, d->img);
        }
    }

    void paintByMaouse() {
        ImageData data;
        data.img = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
        cv::imshow(data.windowName, data.img);

        //mouse click event
        cv::setMouseCallback(data.windowName, mouseEvent, &data);
        cv::waitKey(0);
    }
}
int main() {
    std::string imageOrVideoPath = "";
//  drawing::readImage(imageOrVideoPath);
//  drawing::readVideo(imageOrVideoPath);
//  drawing::readVideoFromWebcam(0); // 0 webcam belong to the pc
//  drawing::createSimpleImage(900, 1600, 200, 150, 130);
//  drawing::drawRectImage(imageOrVideoPath, 100, 300, 800, 350);
//  drawing::drawLineToImage(imageOrVideoPath,0,0,350,150,0,255,255,3);
//  drawing::drawRectangleToImagePoints(imageOrVideoPath, 300, 350, 800, 670, 0, 255, 255, 2);
//  drawing::drawRectangleToImage(imageOrVideoPath, 300, 350, 500, 320, 0, 255, 255, 2);
//  drawing::drawWriteTextToImage(imageOrVideoPath, "TEXT", 400, 200,4.2,3);
//  drawing::drawCircleToImage(imageOrVideoPath, 580, 490, 180);

//  matrix::readValuesOfImage(imageOrVideoPath);
/*
    cv::Mat img = cv::imread(imageOrVideoPath);
    cv::Mat copy;
    matrix::copyImg(img, copy);
*/
//  matrix::enlargeImage(imageOrVideoPath, 2);
//  matrix::miniaturizeImage(imageOrVideoPath, 3);
//  matrix::blur(imageOrVideoPath, 8);
    painting::paintByMaouse();
    return 0;
}
