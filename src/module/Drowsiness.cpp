// This code includes the necessary libraries for the program to run
#include <wiringPi.h>  // This library provides a way to access the GPIO pins on a Raspberry Pi
#include <chrono>      // This library provides functions for measuring time intervals
#include <thread>      // This library provides functions for creating and managing threads
#include "DrowsinessDetector.h"  // This is a user-defined header file that likely contains the DrowsinessDetector class definition

// The following code is commented out since it does not contain any actual code.
// It is likely just a comment that provides a brief description of what the program does.
// It may also contain authorship and version information.
// ----------------------------------------------------------------------------------------
// Main program for the Drowsiness Detector
// Authors: [Johanna, Sairakshith, Lina, Yulin]
// Version: [V1.0]
// Description: This program uses a camera to monitor a person's eyes and detect signs of drowsiness
// ----------------------------------------------------------------------------------------

int eye_counter, yawn_counter;	// The following code declares and initializes two integer variables
const double MOUTH_AR_THRESH = 0.80;// The following code declares and initializes a constant double variable
int yawnCount = 0;		// The following code declares and initializes an integer variable
std::chrono::milliseconds timer_duration(1000); // The following code declares and initializes a chrono duration object with a duration of 1000 milliseconds (1 second)

// This is the constructor for the DrowsinessDetector class
DrowsinessDetector::DrowsinessDetector() {
   
    faceDetector.load("/resources/haarcascade_frontalface_alt.xml"); // The following code loads a face detector using a pre-trained XML file
    facemark = FacemarkLBF::create();// The following code creates a FacemarkLBF object and loads a pre-trained model from a YAML file
    facemark->loadModel("/resources/lbfmodel.yaml");
}
// This is a function that takes two Point2f objects as arguments and returns a double value
double distance(Point2f p1, Point2f p2)
{
    // calculates the distance between the two points using the distance formula
    // It subtracts the x-coordinates and y-coordinates of the two points, squares the differences, adds the results, and takes the square root of the sum
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// This is a member function of the DrowsinessDetector class
void DrowsinessDetector::run() {
   
    // Open video capture device
    VideoCapture cap(0);

    // checks if the video capture device was opened successfully
    if (!cap.isOpened()) {
        cerr << "Error: Could not open video capture device." << endl;
        return;
    }

    while (true) {
        // reads a frame from the video capture device
        Mat frame;
        bool success = cap.read(frame);

        // checks if the frame was read successfully
        if (!success) {
            cerr << "Error: Could not read frame from video stream." << endl;
            break;
        }

        //calls the detect() function with the current frame as the argument
        detect(frame);
        
        //displays the current frame in a window with the title "Drowsiness Detection"
        imshow("Drowsiness Detection", frame);

        // It waits for 1 millisecond for a key to be pressed
        // If the 'q' key is pressed, the loop breaks
        if (waitKey(1) == 'q') {
            break;
        }
    }

    // releases the video capture device
    cap.release();
}
// This is a member function of the DrowsinessDetector class
void DrowsinessDetector::detect(Mat &frame) {
    // Detect faces in the input frame using a Haar Cascade classifier
    vector<Rect> faces;
    faceDetector.detectMultiScale(frame, faces);

    // Detect facial landmarks using the loaded landmark detector
    vector<vector<Point2f>> landmarks;
    bool success = facemark->fit(frame, faces, landmarks);
    
    // If facial landmarks were detected successfully
    if (success) {
        // Draw the detected facial landmarks on the frame
        for(int i = 0; i < landmarks.size(); i++)
        {
            for(int j = 0; j < landmarks[i].size(); j++)
            {
                circle(frame, landmarks[i][j], 1, Scalar(0, 0, 255), -1);
            }
        }
        
        // Calculate the eye aspect ratio (EAR) for both eyes using the detected landmarks
        double leftEyeAspectRatio = getEyeAspectRatio({ landmarks[0][36], landmarks[0][37], landmarks[0][38], landmarks[0][39], landmarks[0][40], landmarks[0][41] });
        double rightEyeAspectRatio = getEyeAspectRatio({ landmarks[0][42], landmarks[0][43], landmarks[0][44], landmarks[0][45], landmarks[0][46], landmarks[0][47] });
     
        // Check if the person's eyes are closed or almost closed
        checkDrowsiness(frame, leftEyeAspectRatio, rightEyeAspectRatio);
        
        
        
        // Calculate the mouth aspect ratio (MAR) using the detected landmarks
        double mouthAR = (norm(landmarks[0][51] - landmarks[0][59]) +
            norm(landmarks[0][62] - landmarks[0][66])) /
            (2.0 * norm(landmarks[0][53] - landmarks[0][57]));
        
        // Print the calculated mouth aspect ratio to the console for debugging purposes
        cout << "mouth-ratio " << mouthAR << endl;
        
        // Check if the mouth aspect ratio is greater than the threshold (indicating a yawn)
        if (mouthAR > MOUTH_AR_THRESH)
        {
            myThreadFunc(1);// Enable the thread 
            std::this_thread::sleep_for(timer_duration);
            //Display to terminal
            cout << "Yawn Detected " << endl;
            // Display "Yawn detected!" on the frame
            putText(frame, "Yawn detected!", Point(10, 30),
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
        }
        else
        {
            myThreadFunc(2);// Disable the thread
        }
    }
}

void DrowsinessDetector::checkDrowsiness(Mat &frame, double leftEyeAspectRatio, double rightEyeAspectRatio) {
    
    // Calculate the average eye aspect ratio
    double EAR = (leftEyeAspectRatio + rightEyeAspectRatio)/2;
    // Print the calculated eye aspect ratio to the console for debugging purposes
        cout << "EYE-ratio " << EAR << endl;
    // Check if the eye aspect ratio is greater than the threshold
    if(EAR>0.36)
    {
        eye_counter++; // Increment the eye counter
        
        // If the eye has been closed for more than three frames, trigger the alarm
        if(eye_counter>3)
        {
            myThreadFunc(1); // Enable the thread 
            std::this_thread::sleep_for(timer_duration); // Wait for one second
            //Display to terminal
            cout << "Eyes closed for more than 3 seconds " << endl;
            putText(frame, "DROWSY", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2); // Display the warning on the frame
        }
    }
    else 
    {
        eye_counter = 0; // Reset the eye counter
        putText(frame, "NORMAL", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2); // Display normal status on the frame
        myThreadFunc(2); // Disable the thread
    }
}

// This function calculates the Eye Aspect Ratio (EAR) using the formula
// EAR = (A + B) / (2C) where A, B, C are distances between the landmarks of the eye
double DrowsinessDetector::getEyeAspectRatio(vector<Point2f> eyeLandmarks) {
double A = norm(eyeLandmarks[1] - eyeLandmarks[5]); // distance between landmarks 1 and 5
double B = norm(eyeLandmarks[2] - eyeLandmarks[4]); // distance between landmarks 2 and 4
double C = norm(eyeLandmarks[0] - eyeLandmarks[3]); // distance between landmarks 0 and 3
double eyeAspectRatio = (A + B) / (2.0 * C); // calculate the EAR
return eyeAspectRatio; // return the calculated EAR
}
void DrowsinessDetector::myThreadFunc(int thread) {
    wiringPiSetup(); // Initialize wiringPi library
    pinMode(27, OUTPUT); // Set BUZZER pin as output
    
    if(thread==1)
        digitalWrite(27, HIGH); // Turn BUZZER on
        std::this_thread::sleep_for(timer_duration);
        digitalWrite(27, LOW);
    if(thread==2)
        digitalWrite(27, LOW); // Turn BUZZER off
}

