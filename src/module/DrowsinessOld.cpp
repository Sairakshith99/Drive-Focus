#include <wiringPi.h>
#include <chrono>
#include <thread>
#include "DrowsinessDetector.h"

int eye_counter,yawn_counter;
const double MOUTH_AR_THRESH = 0.80;
int yawnCount = 0;
std::chrono::milliseconds timer_duration(1000); 

DrowsinessDetector::DrowsinessDetector() {
    // Load face detector and landmark detector
    faceDetector.load("/home/pi/Downloads/haar-cascade-files-master/haarcascade_frontalface_alt.xml");
    facemark = FacemarkLBF::create();
    facemark->loadModel("/home/pi/Downloads/lbfmodel.yaml");
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
        for(int i = 0; i < landmarks.size(); i++)
        {
            for(int j = 0; j < landmarks[i].size(); j++)
            {
                circle(frame, landmarks[i][j], 1, Scalar(0, 0, 255), -1);
            }
        }
        double leftEyeAspectRatio = getEyeAspectRatio({ landmarks[0][36], landmarks[0][37], landmarks[0][38], landmarks[0][39], landmarks[0][40], landmarks[0][41] });
        double rightEyeAspectRatio = getEyeAspectRatio({ landmarks[0][42], landmarks[0][43], landmarks[0][44], landmarks[0][45], landmarks[0][46], landmarks[0][47] });
     
            checkDrowsiness(frame, leftEyeAspectRatio, rightEyeAspectRatio);
            
            
            
             double mouthAR = (norm(landmarks[0][51] - landmarks[0][59]) +
                norm(landmarks[0][62] - landmarks[0][66])) /
                (2.0 * norm(landmarks[0][53] - landmarks[0][57]));
                
                cout << "mouth-ratio " <<mouthAR<< endl;  //check the MOUTH ratio
                
            // Check if the mouth aspect ratio is greater the threshold
            if (mouthAR > MOUTH_AR_THRESH)
            {
                 yawn_counter++;
                if(yawn_counter>2)
                {
                myThreadFunc(1);
                std::this_thread::sleep_for(timer_duration);
                putText(frame, "Yawn detected!", Point(10, 30),
                    FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
                }
            }
            else
            {
                yawn_counter = 0;
                 myThreadFunc(2);
             }
       }
}

void DrowsinessDetector::checkDrowsiness(Mat &frame, double leftEyeAspectRatio, double rightEyeAspectRatio) {
    
    double EAR = (leftEyeAspectRatio + rightEyeAspectRatio)/2;
    cout << "EYE-ratio "<<EAR<< endl;       //check the EYE ratio
            if(EAR>0.36)   // Check if the EYE aspect ratio is greater the threshold
            {
                eye_counter++;
                if(eye_counter>3)
                {
                    myThreadFunc(1); // enable the thread 
                    std::this_thread::sleep_for(timer_duration);  // run the timer for 1-sec
                    putText(frame, "DROWSY", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
                }
            }
            else 
            {
                eye_counter = 0;
                putText(frame, "NORMAL", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
                myThreadFunc(2);
            }
}

double DrowsinessDetector::getEyeAspectRatio(vector<Point2f> eyeLandmarks) {
    double A = norm(eyeLandmarks[1] - eyeLandmarks[5]);
    double B = norm(eyeLandmarks[2] - eyeLandmarks[4]);
    double C = norm(eyeLandmarks[0] - eyeLandmarks[3]);
    double eyeAspectRatio = (A + B) / (2.0 * C);
    return eyeAspectRatio;
    }
    
void DrowsinessDetector::myThreadFunc(int thread) {
    wiringPiSetup(); // Initialize wiringPi library
    pinMode(27, OUTPUT); // Set BUZZER pin as output
    
    if(thread==1)
        digitalWrite(27, HIGH); // Turn BUZZER on
    if(thread==2)
        digitalWrite(27, LOW); // Turn BUZZER on
}

