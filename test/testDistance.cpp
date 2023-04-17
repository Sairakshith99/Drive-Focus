#include <gtest/gtest.h>
#include "../src/module/drowsiness.cpp"

TEST(DrowsinessTest, DistanceTest)
{
    Point2f p1(0, 0);
    Point2f p2(3, 4);
    double expected_distance = 5.0;
    double actual_distance = distance(p1, p2);
    EXPECT_DOUBLE_EQ(expected_distance, actual_distance);
}