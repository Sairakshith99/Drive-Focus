#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load cascade classifier
    CascadeClassifier face_cascade;
    face_cascade.load("haar-cascade-files-master/haarcascade_frontalface_default.xml");

    // Load mouth cascade classifier
    CascadeClassifier mouth_cascade;
    mouth_cascade.load("haar-cascade-files-master/haarcascade_mcs_mouth.xml");

    // Open default camera
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Could not open camera" << std::endl;
        return -1;
    }

    // Main loop
    while (true)
    {
        // Read frame from camera
        Mat frame;
        cap.read(frame);

        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Detect faces
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Loop through detected faces
        for (const auto& face : faces)
        {
            // Crop face region
            Mat face_roi = gray(face);

            // Detect mouth
            std::vector<Rect> mouths;
            mouth_cascade.detectMultiScale(face_roi, mouths);

            // If mouth is detected and its height is larger than 30 pixels, yawn is detected
            if (!mouths.empty() && mouths[0].height > 30)
            {
                std::cout << "Yawn detected!" << std::endl;
            }
                
            }

        // Display frame
        imshow("Yawn detection", frame);

        // Wait for key press
        int key = waitKey(1);
        if (key == 27) // Press Esc to exit
        {
            break;
        }
    }

    // Release camera
    cap.release();

    return 0;
}
