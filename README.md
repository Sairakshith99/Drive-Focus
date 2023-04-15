# Drive Focus (Driver-Attention-Monitoring-System)
![nwmcjnsz](https://user-images.githubusercontent.com/116390489/231007502-d6b6c26d-46c9-4469-95f9-52c7d04dec26.png)
# ![image](https://user-images.githubusercontent.com/116390489/232041553-a4d414c6-2861-4440-b1f3-e5361ab19e28.png) ![image](https://user-images.githubusercontent.com/116390489/232076273-c7b8169f-f780-407b-92d2-bbc4850c54df.png) ![image](https://user-images.githubusercontent.com/116390489/232041367-a342a2b3-5d5f-4c64-bb29-a9ec89c1a56c.png)


# Social Media

[![My project](https://user-images.githubusercontent.com/116390489/231455191-8b55d2b1-5a70-43cf-8644-8beb96923488.png)](https://linktr.ee/drive_focus)

# Project Contributors

| NAME | GUID |	ROLE |
| ------------- | ------------- | ------------- |
| Johanna Benedict |	2787431J	|
| Sai Rakshith Arun Kumar	| 2820843A |	
| Lina Chen |	2811816C |
| Yulin Xiao | 2743901X |

# ![image](https://user-images.githubusercontent.com/116390489/232042061-3ada3e1a-4fd1-4690-8efe-a2310ccd0dc2.png) ![image](https://user-images.githubusercontent.com/116390489/232042154-f0cbc836-1552-465f-a4a9-d5419c8bc841.png) 


# Project Description 

Drive Focus is a project developing a Driver Attention Monitoring System (DAMS) that uses face recognition software on a Raspberry Pi and a PiCamera. By examining facial traits including the driver's eyes and mouth, the system can determine whether or not they are aware. The prominent computer vision library OpenCV is used in C++ programming. The method has the ability to lower the amount of accidents caused as a result of drowsiness and raise driving safety. The system's design, implementation, testing, and development process are all thoroughly detailed.

# Project Features

1. Real-time monitoring: The system continuously monitors the driver's behavior and alerts them when they show signs of drowsiness, fatigue, or distraction.

2. Facial recognition: The system detects the driver's face and tracks their facial expressions, specifically eye and mouth movements to assess their level of attentiveness.

3. Audio alerts: The system alerts the driver by sounding a warning alarm when they show signs of drowsiness or fatigue.

4. Compatibility with existing technology: The system is compatible with existing in-car technology such as infotainment systems and navigation systems to provide a seamless user experience.

5. Privacy and security: The system is designed to protect the driver's privacy and data security by minimizing data collection and ensuring secure storage and transmission of data.

6. Customizability: The system is customizable to meet the needs of different drivers and vehicle types, with adjustable sensitivity levels and alert preferences.

# Requirements

Hardware

1. External Monitor, Keyboard and Mouse (Preferred)
2. Windows or Linux Laptop
3. RaspberryPi V3
4. Picamera Module 2

Software

1. RaspberryPi OS (Legacy Version Preferred) 
2. VNC(Make sure VNC is turned On) 
3. C++ API
4. OpenCV (4.1.0 or above) and necessary dependencies
5. Geany 
6. CMake

# Guide
1. Download RaspberryPi OS on a Windows or Linux laptop, burn the RaspberryPi Imager to SD card.
2. Insert the SD card into the RaspberryPi borad.
3. Install all packages that needed.(how to install opencv is shown in reference)  
install cmake: 
```
sudo apt install cmake
```

## Use monitor version
1. Link the RaspberryPi to the monitor, keyboard and mouse.
2. Open the command window in project directory and run:
```c++
g++ Drowsiness.cpp main.cpp -o main -lwiringPi `pkg-config --cflags --libs opencv`
./main
```
3. Then the interface acquired by the camera will appear and you can have the drive focus test.

## Use laptop version
1. Use LAN cable link laptop and RaspberryPi board(if your laptop doesn't have the LAN cable interface please ensure the laptop and the RaspberryPi in the same LAN). `ssh pi@raspberrypi.local` to find the IP address of RaspberryPi.
2. Enter the password of the RaspberryPi.
3. Enter `sudo raspi-config` to enable the VNC.
4. Use VNC connect the borad, then enter `raspberrypi.local` to connect.
5. Copy the code you have download, drag the file into RaspberryPi.
6. Open the command window in project directory and run:
```c++
g++ Drowsiness.cpp main.cpp -o main -lwiringPi `pkg-config --cflags --libs opencv`
./main
```
7. Then the interface acquired by the camera will appear and you can have the drive focus test.

# Code Structure


# Demo


# References
[Install Opencv on RaspberryPi](https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/)  
[How to use README file](https://www.mygreatlearning.com/blog/readme-file/)
[Install CMake on RaspberryPi](https://linuxhint.com/3-ways-install-cmake-raspberry-pi/)
