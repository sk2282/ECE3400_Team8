# Lab 1: Microcontrollers

## Objective:
The objective of this lab was to learn how to use Arduino Uno and Arduino IDE by implementing simple tasks. By the end we had a basic robot that could autonomously move back and forth and spin in place.

## Team Division:
* Meghan Chen, Serena Krech, Alice Song
* Rohit Krishnakumar, Victoria Tu, Michael Yee

## Materials used:
* 1 Arduino Uno
* 1 USB A/B cable
* 1 Continuous rotation servo
* 1 blue LED (could be any visible color)
* 1 Potentiometer
* Several resistors (kΩ range)
* 1 Solderless breadboard

## Procedure:
1. Install the Arduino IDE
2. Test the built-in blink sketch
3. Modify the blink sketch to blink an external LED
4. Add a potentiometer to control brightness of the external LED
5. Check the duty cycle on oscilloscope
6. Use the potentiometer to control a continuous rotation servo motor
7. Assemble a robot and program it to run autonomously

### 1. Install the Arduino IDE
Before the lab, each of us downloaded [Arduino IDE](https://www.arduino.cc/en/Main/Software) to our laptops.
We read the documentation for the [Parallax Continuous Rotation Servo](http://www.parallax.com/downloads/continuous-rotation-servo-documentation) and the [Arduino Reference pages](http://arduino.cc/en/Reference/HomePage) for additional help.

### 2. Test the built-in blink sketch
We tested the blink example code provided by the Arduino IDE (File > Examples > 1.Basics > Blink) to test the internal LED ([video](https://youtu.be/fLsoTSbzcxY))

### 3. Testing Arduino Digital I/O Pins:
We modified the sample internal blink code to blink the external blue LED ([video](https://youtu.be/SOBKV8ZrKtU)).

For each digital pin on the Arduino, we then connected a resistor and the blue LED in series in order to be sure that each pin was functional. The LED was connected in series with a resistor to control the current and protect the board.

### 4. Read Potentiometer using serial communication
We tested the serial communication between the Arduino and the laptop by inserting a Serial.begin(9600) command in the setup function and multiple Serial.println commands in the loop function.

We then added a potentiometer to control the brightness of the LED by reading an analog input from A0 ([video](https://youtu.be/141hdDL86oY)).

### 5. Oscilloscope reading of potentiometer-controlled LED circuit
We hooked up the circuit to an oscilloscope to see the frequency and duty cycles of the signal as the potentiometer changed. ([video](https://youtu.be/mmyfeO612Gs))

### 6. Potentiometer-controlled servo
We then edited the code to control the servo with the potentiometer. (https://youtu.be/uiUPPhVC5jA)

### 7. Robot Demo
Our robot was programmed to turn, move forward, and move backward autonomously (to simulate movements it would do in the maze).
Our battery pack wasn’t charged, so we had our Arduino connected to a laptop, which only served as a power source. ([video](https://youtu.be/NYUtKrzdNKc))

