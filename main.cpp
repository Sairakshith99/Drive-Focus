#include "DrowsinessDetector.h"

int main() {
  //  wiringPiSetup(); // Initialize wiringPi library

    DrowsinessDetector detector;
    detector.run();
    return 0;
}
