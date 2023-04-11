#include "DrowsinessDetector.h"



DrowsinessDetector::DrowsinessDetector() {
    // Load face detector and landmark detector
    faceDetector.load("haar-cascade-files-master/haarcascade_frontalface_alt.xml");
    facemark = FacemarkLBF::create();
    facemark->loadModel("lbfmodel.yaml");
}

double distance(Point2f p1, Point2f p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void DrowsinessDetector::run() {
    // Open video capture device
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open video capture device." << endl;
        return;
    }

    while (true) {
        Mat frame;
        bool success = cap.read(frame);

        if (!success) {
            cerr << "Error: Could not read frame from video stream." << endl;
            break;
        }

        detect(frame);

        imshow("Drowsiness Detection", frame);

        if (waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
}

void DrowsinessDetector::detect(Mat &frame) {
    vector<Rect> faces;
    faceDetector.detectMultiScale(frame, faces);

    vector<vector<Point2f>> landmarks;
    bool success = facemark->fit(frame, faces, landmarks);

    if (success) {
        double leftEyeAspectRatio = getEyeAspectRatio({ landmarks[0][36], landmarks[0][37], landmarks[0][38], landmarks[0][39], landmarks[0][40], landmarks[0][41] });
        double rightEyeAspectRatio = getEyeAspectRatio({ landmarks[0][42], landmarks[0][43], landmarks[0][44], landmarks[0][45], landmarks[0][46], landmarks[0][47] });
       // cout << leftEyeAspectRatio << endl;
       // cout << rightEyeAspectRatio << endl;
       
        checkDrowsiness(frame, leftEyeAspectRatio, rightEyeAspectRatio);
            
            vector<Point2f> mouth(6);
            mouth[0] = landmarks[0][48];
            mouth[1] = landmarks[0][49];
            mouth[2] = landmarks[0][50];
            mouth[3] = landmarks[0][51];
            mouth[4] = landmarks[0][52];
            mouth[5] = landmarks[0][53];

            // Calculate distance between top and bottom lip
            double topToBottomDistance = distance(mouth[2], mouth[5]);

            // Calculate distance between corners of mouth
            double cornerToCornerDistance = distance(mouth[0], mouth[4]);

            // Calculate ratio between top-to-bottom distance and corner-to-corner distance
            double ratio = topToBottomDistance / cornerToCornerDistance;
               // cout << ratio << endl;
            // Check if the mouth is open wider than the threshold
            if (ratio > 0.60) {        
                   // turnLedOn();
                    cout << "Yawn detected!" << endl;
                }
              
       }
       
       for(int i = 0; i < landmarks.size(); i++)
        {
            for(int j = 0; j < landmarks[i].size(); j++)
            {
                circle(frame, landmarks[i][j], 1, Scalar(0, 0, 255), -1);
            }
        }
}

void DrowsinessDetector::checkDrowsiness(Mat &frame, double leftEyeAspectRatio, double rightEyeAspectRatio) {
    if (leftEyeAspectRatio < 0.25 || rightEyeAspectRatio < 0.25) {
        putText(frame, "Drowsy", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
    }
    else {
        
        putText(frame, "Awake", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }
}

double DrowsinessDetector::getEyeAspectRatio(vector<Point2f> eyeLandmarks) {
    double A = norm(eyeLandmarks[1] - eyeLandmarks[5]);
    double B = norm(eyeLandmarks[2] - eyeLandmarks[4]);
    double C = norm(eyeLandmarks[0] - eyeLandmarks[3]);
    double eyeAspectRatio = (A + B) / (2.0 * C);
    return eyeAspectRatio;
    }

