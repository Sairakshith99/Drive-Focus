#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
 

using namespace cv;
using namespace std;

int main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Error opening video stream" << endl;
        return -1;
    }

    CascadeClassifier faceCascade;
    CascadeClassifier eyeCascade;
    faceCascade.load("haar-cascade-files-master/haarcascade_frontalface_alt.xml");
    eyeCascade.load("haar-cascade-files-master/haarcascade_eye.xml");
    int minRadius = 38;

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
            vector<Rect> eyes;
            eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0, Size(30, 30));

            for (int j = 0; j < eyes.size(); j++)
            {
                Point eyeCenter(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                circle(frame, eyeCenter, radius, Scalar(0, 0, 255), 2, LINE_AA);
               // cout << radius<<endl;
                if (radius > minRadius) // if radius is smaller than threshold, eyes are closed
                {
                    cout << "Driver is drowsy!" << endl;
                }
                else 
                { 
                    cout << "Driver is normal" << endl;
                }
            }
        }

        imshow("Drowsiness Detection", frame);
        if (waitKey(10) == 27)
            break;
    }

    return 0;
}
