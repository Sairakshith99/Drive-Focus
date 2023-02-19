#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//This header includes definition of 'rectangle()' function//
#include<opencv2/objdetect/objdetect.hpp>
//This header includes the definition of Cascade Classifier//
#include<string>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat video_stream;//Declaring a matrix hold frames from video stream//
    VideoCapture real_time(0);//capturing video from default webcam//
    namedWindow("Face Detection");//Declaring an window to show the result//
    string trained_classifier_location = "haarcascade_frontalface_default.xml";//Defining the location our XML Trained Classifier in a string//
    CascadeClassifier faceDetector;//Declaring an object named 'face detector' of CascadeClassifier class//
    faceDetector.load(trained_classifier_location);//loading the XML trained classifier in the object//
    vector<Rect>faces;//Declaring a rectangular vector named faces//
    while (true) {
        faceDetector.detectMultiScale(video_stream, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(30, 30));//Detecting the faces in 'image_with_humanfaces' matrix//
        real_time.read(video_stream);// reading frames from camera and loading them in 'video_stream' Matrix//
        for (int i = 0; i < faces.size(); i++) { //for locating the face
            Mat faceROI = video_stream(faces[i]);//Storing face in the matrix//
            int x = faces[i].x;//Getting the initial row value of face rectangle's starting point//
            int y = faces[i].y;//Getting the initial column value of face rectangle's starting point//
            int h = y + faces[i].height;//Calculating the height of the rectangle//
            int w = x + faces[i].width;//Calculating the width of the rectangle//
            rectangle(video_stream, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);//Drawing a rectangle using around the faces//
        }
        imshow("Face Detection", video_stream);
        //Showing the detected face//
        if (waitKey(10) == 27) { //wait time for each frame is 10 milliseconds//
            break;
        }
    }
    return 0;
}