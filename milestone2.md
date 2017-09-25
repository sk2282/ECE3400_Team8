# Milestone 2: Treasure and Wall Detection

## Objective:
The goal of this milestone is to implement treasure detection at three frequencies (7kHz, 12kHz, 17kHz) and add wall detection to our robot by using IR sensors.

## Treasure Detection:
* To implement treasure detection, we first built a non-inverting amplifier for the phototransistor  
* We first tested the amplifier with the function generator. The results can be seen below  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/100_1_noninverting_FG.bmp?raw=true" height="300" />  

#### 7kHz From 1.5" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/7kHz_15inAway.bmp?raw=true" height="300" />  

#### 12kHz From 2" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/12kHz_2inAway.bmp?raw=true" height="300" />   

#### 17kHz From 2" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/17kHz_2inAway.bmp?raw=true" height="300" />   

* The amplifier gave us a gain of about 4  

[The final circuit with amplifier was able to detect each frequency from around 2 inches away](https://youtu.be/L_e-veB9L3M)


## Wall Detection:
* We first tested three IR sensors:  
    * Short range IR  
    * Regular IR  
    * Long range IR  
* We connected the IR sensors to an anolog pin on the Arduino and used analogRead() to obtain the data from the sensors
* We then printed readings from the sensors at three different distances from a wall: 2, 6, and 12 inches  
	* The results from this test is displayed in a table below
    * We determined which IR sensors would work best for our robot, prioritizing the best range for the distances that our robot would interact with  
    * We decided to use two short range sensors on the sides and one regular sensor on the front  

    | IR Sensor| Distance | Arduino Reading |
    | -------- | :--------: | :---------------: |
    | Long Range| 2" | 1000+ |
    | Long Range | 6" |500 - 550 |
    | Long Range | 12" |370 - 380 |
    | Regular | 2" | 620 - 630 |
    | Regular | 6" | 310 - 330 |
    | Regular | 12" | 170 - 190 |
    | Short Range | 2" | 390 - 405 |
    | Short Range |6" |130 - 170 |
    | Short Range | 12" | 60 - 90 |
  
* We wrote some code to test wall detection  
    * To test the implementation, we mounted one short range sensor on the robot's right side  
    * [The robot should follow a straight line until the sensor detects a wall and stop when the wall is detected](https://youtu.be/_vbiJvubCpY)

## Final Robot of Milestone 2:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/milestone2robot.jpg?raw=true" height="300" />
