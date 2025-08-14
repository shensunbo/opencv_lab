#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Global variables to store current color values
int R = 255, G = 0, B = 0;
const int width = 640;
const int height = 480;
std::vector<uint8_t> nv12Data(width* height * 3 / 2); // NV12 buffer
cv::Mat bgrImage; // BGR image for display
std::string windowName = "NV12 Color Picker";

// RGB to NV12 conversion (solid color)
void RGBToNV12_SolidColor() {
    // Calculate YUV values (using BT.601 standard conversion formulas)
    uint8_t Y = static_cast<uint8_t>(0.299f * R + 0.587f * G + 0.114f * B);
    uint8_t U = static_cast<uint8_t>(-0.169f * R - 0.331f * G + 0.500f * B + 128.0f);
    uint8_t V = static_cast<uint8_t>(0.500f * R - 0.419f * G - 0.081f * B + 128.0f);

    // Fill Y plane
    uint8_t* Y_plane = nv12Data.data();
    std::fill(Y_plane, Y_plane + width * height, Y);

    // Fill UV plane (interleaved)
    uint8_t* UV_plane = nv12Data.data() + width * height;
    for (int i = 0; i < width * height / 2; i += 2) {
        UV_plane[i] = U;
        UV_plane[i + 1] = V;
    }
}

// NV12 to BGR conversion for display
void NV12ToBGR() {
    cv::Mat yuvImage(height + height / 2, width, CV_8UC1, nv12Data.data());
    cv::cvtColor(yuvImage, bgrImage, cv::COLOR_YUV2BGR_NV12);
}

// Trackbar callback function
void onTrackbarChange(int, void*) {
    // Update NV12 data with current color values
    RGBToNV12_SolidColor();

    // Convert to BGR for display
    NV12ToBGR();

    // Update window title with current RGB values
    std::string newTitle = windowName + " - R:" + std::to_string(R) +
        " G:" + std::to_string(G) +
        " B:" + std::to_string(B);
    cv::setWindowTitle(windowName, newTitle);

    // Display the image
    cv::imshow(windowName, bgrImage);
}

int main() {
    // Create display window
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    // Create trackbars for RGB components
    cv::createTrackbar("Red", windowName, &R, 255, onTrackbarChange);
    cv::createTrackbar("Green", windowName, &G, 255, onTrackbarChange);
    cv::createTrackbar("Blue", windowName, &B, 255, onTrackbarChange);

    // Initial update
    onTrackbarChange(0, nullptr);

    std::cout << "Use trackbars to adjust RGB values. Press ESC to exit..." << std::endl;

    // Main event loop
    while (true) {
        int key = cv::waitKey(30);
        if (key == 27) { // ESC key to exit
            break;
        }
    }

    return 0;
}