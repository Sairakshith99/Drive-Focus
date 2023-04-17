#ifndef DROWSINESS_DETECTOR_H
#define DROWSINESS_DETECTOR_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

class DrowsinessDetector {
public:
    DrowsinessDetector();
    void run();

private:
    CascadeClassifier faceDetector;
    Ptr<Facemark> facemark;
    void detect(Mat &frame);
    void checkDrowsiness(Mat &frame, double leftEyeAspectRatio, double rightEyeAspectRatio);
    double getEyeAspectRatio(vector<Point2f> eyeLandmarks);
};

#endif
