# Lab 2: Analog Circuitry and FFTs

## Objective:
The objective of this lab was to test and familiarize ourselves with the sensors and signal processing needed for our robot to detect the acoustic and optical signals. We split into two subteams, one that worked with a microphone circuit to detect a 660 Hz whistle and another to work with an IR sensor to detect a treasure blinking at different frequencies. Both subteams used the Arduino Open Music Lab FFT library to process the data given by the sensors and create a filter allowing us to analyze the data.

## Team Division:
* Audio: Serena Krech, Alice Song, Victoria Tu
* Treasure: Meghan Chen, Rohit Krishnakumar, Michael Yee

## Materials used:
# Audio Team:
* Arduino Uno
* Electret microphone
* 1 µF capacitor
* 300 Ω resistors
* ~3 kΩ resistor
# Treasure Team:
* Arduino Uno
* IR receiver
* 300 Ω resistors
* 2 kΩ resistor
* Treasure board
* Solderless breadboard

## Procedure:
1. Install the Arduino IDE
2. Test the built-in blink sketch
3. Modify the blink sketch to blink an external LED
4. Add a potentiometer to control brightness of the external LED
5. Check the duty cycle on oscilloscope
6. Use the potentiometer to control a continuous rotation servo motor
7. Assemble a robot and program it to run autonomously

### 1. Install the Arduino IDE:
Before the lab, each of us downloaded [Arduino IDE](https://www.arduino.cc/en/Main/Software) to our laptops.
We read the documentation for the [Parallax Continuous Rotation Servo](http://www.parallax.com/downloads/continuous-rotation-servo-documentation) and the [Arduino Reference pages](http://arduino.cc/en/Reference/HomePage) for additional help.

### 2. Testing the Built-in Blink Sketch:
We tested the blink example code provided by the Arduino IDE (File > Examples > 1.Basics > Blink) to [test the internal LED](https://youtu.be/fLsoTSbzcxY).

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab1/blink.JPG?raw=true" height="300" />

### 3. Testing Arduino Digital I/O Pins:
We modified the sample internal blink code to [blink the external blue LED](https://youtu.be/SOBKV8ZrKtU).

For each digital pin on the Arduino, we then connected a resistor and the blue LED in series in order to be sure that each pin was functional. The LED was connected in series with a resistor to control the current and protect the board.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab1/blue_LED.JPG?raw=true" height="300" />

### 4. Reading Potentiometer Using Serial Communication:
We tested the serial communication between the Arduino and the laptop by inserting a Serial.begin(9600) command in the setup function and multiple Serial.println commands in the loop function.

We then added a potentiometer to [control the brightness of the LED](https://youtu.be/141hdDL86oY) by reading an analog input from A0.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab1/serial_monitor.PNG?raw=true" height="300" />

### 5. Oscilloscope Reading of Potentiometer-Controlled LED Circuit:
We hooked up the circuit to an oscilloscope to see the frequency and [duty cycles](https://youtu.be/mmyfeO612Gs) of the signal as the potentiometer changed.

### 6. Potentiometer-Controlled Servo:
We then edited the code to [control the servo](https://youtu.be/uiUPPhVC5jA) with the potentiometer.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab1/Servo_setup.JPG?raw=true" height="300" />

### 7. Robot Demo:
[Our robot was programmed to turn, move forward, and move backward autonomously](https://youtu.be/NYUtKrzdNKc) (to simulate movements it would do in the maze).
Our battery pack wasn’t charged, so we had our Arduino connected to a laptop, which only served as a power source.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab1/assembled_robot.png?raw=true" height="300" />
