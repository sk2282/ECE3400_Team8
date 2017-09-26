# Milestone 1: Line Following and Figure-8

## Objective:
The goal of this milestone is to implement line following and turning functionalities to our robot.

## Line Following:
* The first step was to have our robot [follow a line of black tape](https://youtu.be/ZP58UEu52JQ)
* We used 2 IR sensors to detect the black line by determining a threshold value
* If a sensor went out of line, the corresponding servo would compensate by speeding up that side of the wheel so that the robot would remain on the line  
    * If left sensor went out of line, speed up left servos  
    * If right sensor went out of line, speed up right servos  
    * Otherwise, servos rotate at same rate  

 ```c
 if(lRead<thresh){  // left side is out of line
      left.write(170);
      right.write(86);
    }
    else if(rRead<thresh){   // right side is out of line
      left.write(94);
      right.write(10);
    }
    else{     // go straight
      left.write(100);
      right.write(80);
```

* We tested the robot on a [curved line](https://youtu.be/l7fE-NlZAs8) as well

## Figure-8:
### Detecting Intersections:
* Our next step was to add two additional sensors to detect an intersection
* We added two wide sensors near the wheels, one on each side of the robot
* When either wide sensor detected black, we detect an intersection

### Figure-8 Implementation:
* We then implemented [turning](https://youtu.be/I4GyVfHf1CU)  

```c
void leftTurn(){
  while(analogRead(0)>=thresh || analogRead(1)>=thresh){
      right.write(77);
      left.write(77);
  }while(analogRead(0)<=thresh){
      right.write(77);
      left.write(77);
  }
  right.write(90);
  left.write(90);
}

void rightTurn(){
  while(analogRead(0)>=thresh || analogRead(1)>=thresh){
      right.write(103);
      left.write(103);
  }while(analogRead(1)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
}
```

* When the robot detected an intersection, we programmed it to turn until the line/inner sensors detected black again (turn is finished)
* To implement the figure 8, we programmed the robot to turn left whenever it detects an intersection 3 times, go straight at the next intersection, and turn right when it detects an intersection 3 times. This sequence is in a loop, so the robot continues to navigate a [figure 8](https://youtu.be/NztFPuQvlM0)
* To go straight we added a helper function goStraight():

```c
void goStraight(){
  while(analogRead(2)>=thresh || analogRead(3)>=thresh){
    left.write(100);
    right.write(80);  
  }
}
```

* The code below shows the first few cases that we loop through while traversing the figure 8.  Notice we used a cooldown to ensure that the robot doesn't detect the same intersection more than once.

```c
int detectCooldown = 0;
int DETECT_COOLDOWN = 50;
.
.
.
 if((lwRead >= thresh || rwRead >= thresh) && detectCooldown == 0){
    switch (intsec){
      case 0:
        Serial.println("Case0");
        intsec++;
        detectCooldown = DETECT_COOLDOWN;
        roboStop = 0;
        goStraight();
      break;
      case 1:
        Serial.println("Case1");
        intsec++;
        detectCooldown = DETECT_COOLDOWN;
        roboStop = 0;
        leftTurn();
      break;
      case 2:
        Serial.println("Case2");
        intsec++;
        detectCooldown = DETECT_COOLDOWN;
        roboStop = 0;
        leftTurn();
      break;
```

## Final Robot of Milestone 1:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone1/final.JPG?raw=true" height="300" />
