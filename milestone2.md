# Milestone 2: Treasure and Wall Detection

## Objective:
The goal of this milestone is to implement treasure detection at three frequencies (7kHz, 12kHz, 17kHz) and wall detection to our robot.

## Treasure Detection:
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

