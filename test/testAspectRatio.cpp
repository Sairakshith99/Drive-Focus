#include <gtest/gtest.h>
#include <vector>
#include "../src/module/drowsiness.cpp"

TEST(DrowsinessDetectorTest, EyeAspectRatioTest)
{
    DrowsinessDetector detector;
    std::vector<cv::Point2f> eyeLandmarks = {cv::Point2f(0, 0), cv::Point2f(1, 1), cv::Point2f(2, 2), cv::Point2f(3, 3), cv::Point2f(4, 4), cv::Point2f(5, 5)};
    double expectedAspectRatio = 1.41421356;
    double actualAspectRatio = detector.getEyeAspectRatio(eyeLandmarks);
    EXPECT_DOUBLE_EQ(expectedAspectRatio, actualAspectRatio);
}
