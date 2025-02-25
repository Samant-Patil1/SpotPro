# SPOTPRO
## 💀WORK IN PROGRESS💀

### References/Bibliography
First of, instead of researching on this private project, I would like to request you to look into the resources I looked up into, 

1. https://sites.google.com/view/senior-tech-project/   (I chose these guys, mainly because they listed down all their steps, with perfect details)
2. https://spotmicroai.readthedocs.io/en/latest/        (The official ones)
3. https://novaspotmicro.com/                           (They extended the original design, and added some rc features, and, umm-what not. They even added the holes for ports for robotic arms, I think)
4. https://github.com/michaelkubina/SpotMicroESP32      (He editted the 3d models, to accomodate ESP32 DEVKITC)


But, if you are just like me, and do not trust the makes of the other users as well, you are more that free to follow this repository. I will try to privide each and every detail possible, while making this project.
#
## Sections:-
1. Electronics
2. 3D Parts
3. Code
4. Next-
#

### Step 1 - Electronics

First, The reason many people edited the original stl files, is because they wanted to use the best ttechnology available- First it was 
1. Arduino Mega, the original model
2. and then RPi and NVIDIA Jetson Nano
3. and then ESP32 series
Second, I thought of using my favorite *ESP32 S3 DEVKITC N8R8 1 BOARD*, but, it only has basic capability, like face recognition, server creation, 802.11, and BLE.(But still, overwhelmingly strong than most esp32, and arduino board, no, all arduino boards).
Third, What I did, for the first steps, I will be using esp32, but, later, I will be using RPi 0/3/4/5 b+ for the AI and automated control part(much later on, patience) Why not Jetson Nano? Because I dont trust it. It would be the first time I will be using it. I will still be listing all the options in the below table. ALL THE CAPS-LOCKED ITEMS ARE OPTIONAL, AND NOT INCLUDED IN MY DESIGN.


| Item                    | Quantity | Description                                                                                                                   | Tested? | Current Price    |
|-------------------------|----------|-------------------------------------------------------------------------------------------------------------------------------|---------|:-----------------|
| **ESP32-S3 DevKitC-1 N8R8**	| 1x  | A powerful MCU with WiFi + BLE, 47 GPIOs, and 14 capacitive touch sensors, ideal for IoT, robotics, and wireless projects.  | Yes     | ₹1460            |
| **NVIDIA JETSON NANO**      | 1x  | A compact AI development board with a 128-core GPU, great for deep learning, robotics, and edge computing.                   | No      | ₹6000            |
| **Raspberry Pi 0W/3/4/5**   | 1x  | A versatile SBC with WiFi + Bluetooth, GPIO support, and a quad-core processor, perfect for IoT and automation.              | Yes     | ₹6200            |
| **ARDUINO MEGA ORIGINAL**   | 1x  | A microcontroller with 54 digital I/O pins, ideal for hardware-focused projects, robotics, and automation, but lacks WiFi/BLE. | No      | ₹3200            |
| **PCA9685 Servo Controller** | 2x  | A PWM driver that controls up to 16 servos using I2C, ideal for robotic arms and motion control applications.                | Yes     | 2 x ₹228 = ₹456   |
| **MG996R Servo Motor**      | 12x | A high-torque servo motor with metal gears, commonly used in robotics, RC cars, and precise movement applications.           | Yes     | 12 x ₹309 = ₹3708 |
| **LCD1602 16X2 Display**    | 1x  | A 16x2 character LCD module for displaying text, often used in embedded systems and Arduino projects.                         | No      | ₹160             |
| **3.7V 2800mAh Battery**    | 2x  | A rechargeable lithium-ion battery suitable for powering small electronics, IoT devices, and DIY projects.                    | No      | 2 x ₹681 = ₹1362  |
| **Rocker Switch**           | 1x  | A simple on/off switch used to control power supply in circuits and electronic devices.                                      | Yes     | ₹20              |
| **SSD1306 0.96 inch Display** | 1x  | A small OLED display with I2C/SPI interface, ideal for compact projects requiring graphical output.                           | No      | ₹165             |
| **RPi Camera Module**       | 1x  | A high-resolution camera module compatible with Raspberry Pi, used for computer vision, surveillance, and photography.       | No      | ₹1280            |
| **ESP32 Camera Module**     | 1x  | A camera module based on ESP32 with WiFi support, suitable for IoT-based surveillance and image processing.                   | No      | ₹725             |
| **HC-SR04 Ultrasonic Sensor** | 2x  | A distance measurement sensor using ultrasonic waves, commonly used in robotics and obstacle detection.                      | Yes     | 2 x ₹59 = ₹118    |
| **MPU-6050 Gyro Sensor**    | 1x  | A 6-axis IMU sensor with accelerometer and gyroscope for motion tracking and stabilization applications.                     | No      | ₹200             |
| **HC-05 Bluetooth Module**  | 1x  | A Bluetooth module for wireless serial communication, commonly used in Arduino and IoT projects.                             | Yes     | ₹257             |
| **PIR Motion Sensor**       | 2x  | A passive infrared sensor used to detect motion, commonly implemented in security and automation systems.                    | No      | 2 x ₹59 = ₹118    |
| **RCWL-0516 Microwave Radar Sensor** | 2x | A motion detection sensor that uses **Doppler radar** instead of infrared, ideal for smart lighting and security systems.   | No      | 2 x ₹35 = ₹70     |


### Step 2 - 3D Parts and bolts.

Fourthly, that's it! And then, we need the screws and the 3d printing parts:
Screws:
|Type      |Quantity      |
|----------|--------------|
| M5 x 15 |8|
| M4 x 15 |40|
| M4 x 15 |8|
| M4 x 15 |48|
| M3 x 15 |4|
| M3 x 15 |28|
| M3 x 15 |16|
| F625ZZ Flange ball Bearings |8|
Totally, they cot some 500 rupees.


3d Prints:
|Type      |Quantity      |
|----------|--------------|
| Left Sidewall |1|
| Right Sidewall |1|
| Inner Shoulder |2|
| Outer Shoulder |2|
| Top Cover |1|
| Bottom Cover |1|
| Head |1|
| Headquarters |1|
| Computer Slab |1|


###Step 3 - Code
Pending...
