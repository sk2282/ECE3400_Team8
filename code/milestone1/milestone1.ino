/* MILESTONE 1
 * Team 8: The Resistance
 * Monday Night Lab
 */

#include <Servo.h>

Servo left;  
Servo right;  

// GLOBAL VARIABLES //
int leftLine = 1;     // Pin for left line detector
int rightLine = 2;    // Pin for right line detector
int leftWide = 4;     // Pin for left intersection detector
int rightWide = 5;    // Pin for right intersection detector

int thresh = 800;     // Threshold for black line detection

int intsec = 0;       // Number of intersections detected

int roboStop = 0;     // robot stops moving

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  left.attach(5);     // above 90 is forward
  right.attach(6);    // below 90 is forward
}

void loop() {
  int lRead = analogRead(leftLine);
  int rRead = analogRead(rightLine);
  int lwRead = analogRead(leftWide);
  int rwRead = analogRead(rightWide);

  // INTERSECTION DETECTION
  if(lwRead >= thresh || rwRead >= thresh){
    switch (intsec){
      case 0:
        intsec++;
        roboStop = 0;
        leftTurn();
      break;
      case 1:
        intsec++;
        roboStop = 0;
      break;
      case 2:
        intsec++;
        roboStop = 0;
      break;
      case 3:
        intsec++;
        roboStop = 0;
        rightTurn();
      break;
      case 4:
        intsec++;
        roboStop = 0;
        rightTurn();
      break;
      case 5:
        intsec++;
        roboStop = 0;
        rightTurn();
      break;
      case 6:
        intsec++;
        roboStop = 0;
      break;
      case 7:
        intsec++;
        roboStop = 0;
        leftTurn();
      break;
      case 8:
        roboStop = 1;
        intsec = 0;
        rightTurn(); 
      break;
      default:
        roboStop = 0;
      break;
    } 
    left.write(100);
    right.write(80);
  }
  if(lRead<=thresh && rRead<=thresh || roboStop){     // stop
    left.write(90);
    right.write(90);
  }
  else{
    if(lRead<thresh){  // left side is out of line
      left.write(170);
      right.write(87);
    }
    else if(rRead<thresh){   // right side is out of line
      left.write(93);
      right.write(10);
    }
    else{     // go straight
      left.write(100);
      right.write(80);
    }
  }
}


