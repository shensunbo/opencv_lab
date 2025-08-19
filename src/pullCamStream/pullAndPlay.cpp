#include <opencv2/opencv.hpp>
#include <iostream>
#include "log.h"
int main() {

    std::string stream_url = "tcp://192.168.56.1:1234";
    std::string opencv_url = "ffmpeg://tcp://192.168.56.1:1234?listen";

    cv::VideoCapture cap(opencv_url, cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        mylog(MyLogLevel::E, "open stream failed");
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("TCP Stream", cv::WINDOW_NORMAL);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            mylog(MyLogLevel::E, "receive empty frame, maybe stream is over");
            break;
        }

        cv::imshow("TCP Stream", frame);
        if (cv::waitKey(1) == 27) { // ESC键退出
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}