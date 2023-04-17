# Drive Focus (Driver-Attention-Monitoring-System)

![image](https://user-images.githubusercontent.com/116390489/232624670-f5f2ffe1-5abc-4fad-802e-74d664959aa6.png)


<a href="https://github.com/Sairakshith99/Drive-Focus"><img src="https://user-images.githubusercontent.com/116390489/232041553-a4d414c6-2861-4440-b1f3-e5361ab19e28.png" alt="Link to Open Source"></a> 
<a href="https://github.com/Sairakshith99/Drive-Focus/blob/main/LICENSE"><img src="https://user-images.githubusercontent.com/116390489/232076273-c7b8169f-f780-407b-92d2-bbc4850c54df.png" alt="Link to License"></a> 
<a href="https://github.com/Sairakshith99/Drive-Focus/graphs/contributors"><img src="https://user-images.githubusercontent.com/116390489/232041367-a342a2b3-5d5f-4c64-bb29-a9ec89c1a56c.png" alt="Link to Contributors"></a>



# Social Media

[![My project](https://user-images.githubusercontent.com/116390489/231455191-8b55d2b1-5a70-43cf-8644-8beb96923488.png)](https://linktr.ee/drive_focus)

# Project Contributors

| NAME | GUID | GITHUB ID |	ROLE |
| ------------- | ------------- | ------------- | ------------- |
| Johanna Benedict |	2787431J	| <a href="https://github.com/johannab2507"> @johannab2507 </a> | Embedded Programming and Deployment |
| Sai Rakshith Arun Kumar	| 2820843A | <a href="https://github.com/Sairakshith99"> @sairakshith99 </a> | Hardware Engineering and Project Management |
| Lina Chen |	2811816C | <a href="https://github.com/aenlina"> @aenlina </a>  | Bug Tracking and Documentation |
| Yulin Xiao | 2743901X | <a href="https://github.com/xyllin995"> @xyllin995 </a>    | Debugging and Testing |
> Please send an email with any recommendations you may have for this project to sairakshith99@gmil.com.

<a href="https://github.com/Sairakshith99/Drive-Focus/pulls"><img src="https://user-images.githubusercontent.com/116390489/232042061-3ada3e1a-4fd1-4690-8efe-a2310ccd0dc2.png" alt="Link to Pull Requests"></a>
![image](https://user-images.githubusercontent.com/116390489/232042154-f0cbc836-1552-465f-a4a9-d5419c8bc841.png) 

# Demo

https://user-images.githubusercontent.com/116390489/232617475-f8083924-0559-419e-8405-cf379c836fd1.mov

https://user-images.githubusercontent.com/116390489/232617109-be87fdbd-c34c-44a3-9482-846c9eb55f07.mov




# Project Description 

Drive Focus is a project developing a Driver Attention Monitoring System (DAMS) that uses face recognition software on a Raspberry Pi and a PiCamera. By examining facial traits including the driver's eyes and mouth, the system can determine whether or not they are aware. The prominent computer vision library OpenCV is used in C++ programming. The method has the ability to lower the amount of accidents caused as a result of drowsiness and raise driving safety. The system's design, implementation, testing, and development process are all thoroughly detailed.

# Project Features

1. Real-time monitoring: The system continuously monitors the driver's behavior and alerts them when they show signs of drowsiness, fatigue, or distraction.

2. Facial recognition: The system detects the driver's face and tracks their facial expressions, specifically eye and mouth movements to assess their level of attentiveness.

3. Sound alerts: The system alerts the driver by sounding a warning alarm when they show signs of drowsiness or fatigue.

4. Customizability: The system is customizable to meet the needs of different drivers and vehicle types, with adjustable sensitivity levels and alert preferences.

# Requirements

Hardware

1. External Monitor, Keyboard and Mouse (Preferred)
2. Windows or Linux Laptop
3. RaspberryPi (version 3 or higher)
4. Raspberry Pi Camera Module 2
5. Buzzer
6. Jumper wires

Software

1. RaspberryPi OS (Legacy Version Preferred) 
2. VNC(Make sure VNC is turned On) 
3. C++ API
4. OpenCV (4.1.0 or above) and necessary dependencies
5. WiringPi Library
6. Geany Code Editor

# Guide
To run the source code:
```c++
git clone https://github.com/Sairakshith99/Drive-Focus.git
cd Drive-Focus/src
g++ main.cpp /home/pi/path_to_project/Drowsiness.cpp -o main -lwiringPi `pkg-config --cflags --libs opencv`
./main
```

# Code Explanation

This system is a C++ program that implements a drowsiness detection system using facial landmarks. It uses Haar Cascade classifier to detect faces in the video stream, and a facial landmark detector to identify the eyes and mouth in the face.

This system calculates the Eye Aspect Ratio (EAR) and Mouth Aspect Ratio (MAR) of the detected face to determine whether the user is drowsy or yawning. The EAR is calculated by measuring the ratio of the distance between the horizontal eye landmarks and the vertical eye landmarks. A threshold value is set for the EAR, and if the EAR falls below this value, the program will assume that the user is drowsy. Similarly, the MAR is calculated by measuring the ratio of the distance between the upper and lower lip to the width of the mouth. A threshold value is set for the MAR, and if the MAR is greater than this value, the program will assume that the user is yawning.

When the program detects drowsiness (sleepy - eyes closed for long or yawning), it will activate a buzzer to alert the user. The buzzer is controlled by a separate thread that is activated when drowsiness or yawning is detected.

For more details refer to <a href="https://github.com/Sairakshith99/Drive-Focus/wiki"> wiki </a>

# References
[Install Opencv on RaspberryPi](https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/)  

[How to use README file](https://www.mygreatlearning.com/blog/readme-file/)

[How to install googletest](https://github.com/google/googletest)
