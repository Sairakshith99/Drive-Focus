#include <wiringPi.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

// Define global variables for LED pin and minimum eye radius
const int buzzer = 27;
const int MIN_RADIUS = 38;

// Define callback function to turn LED on
void turnOn()
{
    digitalWrite(buzzer, HIGH);
    delay(1000);
}

// Define callback function to turn LED off
void turnOff()
{
    digitalWrite(buzzer, LOW);
}

int main()
{
    wiringPiSetup(); // Initialize wiringPi library
    pinMode(buzzer, OUTPUT); // Set LED pin as output

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Error opening video stream" << endl;
        return -1;
    }
    CascadeClassifier faceCascade;
    CascadeClassifier eyeCascade;
    CascadeClassifier mouth_cascade;

    faceCascade.load("haar-cascade-files-master/haarcascade_frontalface_alt.xml");
    eyeCascade.load("haar-cascade-files-master/haarcascade_eye.xml");
    mouth_cascade.load("haar-cascade-files-master/haarcascade_mcs_mouth.xml");

    while (true)
    {
        Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(100, 100));

        for (int i = 0; i < faces.size(); i++)
        {
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2);

            Mat faceROI = gray(faces[i]);
            
            std::vector<Rect> mouths;
                
            mouth_cascade.detectMultiScale(faceROI, mouths);
            if (!mouths.empty() && mouths[0].height > 30)
            {
                cout << "yawn!" << endl;
                turnOn(); // Turn on LED if driver is drowsy
            }
           else
            {
                cout << "Driver is normal" << endl;
                turnOff(); // Turn off LED if driver is not drowsy
            }
                
            vector<Rect> eyes;
            eyeCascade.detectMultiScale(faceROI, eyes, 1.3, 5, 0, Size(30, 30));

            for (int j = 0; j < eyes.size(); j++)
            {
                Point eyeCenter(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                circle(frame, eyeCenter, radius, Scalar(0, 0, 255), 2, LINE_AA);
                
                if (radius > MIN_RADIUS)
                {
                    cout << "eye!" << endl;
                    turnOn(); // Turn off LED if driver is not drowsy
                }

               
                else
                {
                    cout << "Driver is normal" << endl;
                    turnOff(); // Turn off LED if driver is not drowsy
                }
            }
        }

        imshow("Drowsiness Detection", frame);
        if (waitKey(10) == 27)
            break;
    }

    return 0;
}
