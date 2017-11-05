
/* MILESTONE 2
 * Team 8: The Resistance
 * Monday Night Lab
 */
/*
#include <Servo.h>

Servo left;
Servo right;

// GLOBAL VARIABLES
//int wallLeftSide = 5;
int wallRightSide = 4;
//int wallFront = 2;

int threshSide = 300; // change
//int threshFront = 300; // change

int leftLine = 0; //1;
int rightLine = 1; //2;
int leftWide = 2;
int rightWide = 3;
int thresh = 800;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  left.attach(5);
  right.attach(6);
}

void loop() {
  
  // go straight when threshold has not been reached
  while (analogRead(wallRightSide) <= threshSide) {
    int lRead = analogRead(leftLine);
    int rRead = analogRead(rightLine);
    int lwRead = analogRead(leftWide);
    int rwRead = analogRead(rightWide);
    
    if(lRead<=thresh && rRead<=thresh){     // stop
      left.write(90);
      right.write(90);
    }
    else{
      if(lRead<thresh){  // left side is out of line
        left.write(170);
        right.write(89);
      }
      else if(rRead<thresh){   // right side is out of line
        left.write(91);
        right.write(10);
      }
      else{     // go straight
        left.write(100);
        right.write(80);
      }
    }
  }
  
//   else stop when wall is detected
  left.write(90);
  right.write(90);
  
}*/
