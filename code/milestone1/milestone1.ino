/* MILESTONE 1
 * Team 8: The Resistance
 * Monday Night Lab
 */

#include <Servo.h>

Servo left;  
Servo right;  

// GLOBAL VARIABLES //
int leftLine = 0;     // Pin for left line detector
int rightLine = 1;    // Pin for right line detector
int leftWide = 2;     // Pin for left intersection detector
int rightWide = 3;    // Pin for right intersection detector

int thresh = 800;     // Threshold for black line detection

int intsec = 0;       // Number of intersections detected

int roboStop = 0;     // robot stops moving

int detectCooldown = 0;

void leftTurn(){
  right.write(87);
  left.write(87);
  delay(50);
  while(analogRead(0)<=thresh || analogRead(1)<=thresh){
      right.write(87);
      left.write(87);
  }
  left.write(100);
  right.write(80);
  //detect = 0;
}

void rightTurn(){
  right.write(103);
  left.write(103);
  delay(50);
  while(analogRead(0)<=thresh || analogRead(1)<=thresh){
      right.write(93);
      left.write(93);
  }
  left.write(100);
  right.write(80);
  //detect = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  left.attach(5);     // above 90 is forward - THESE ARE DIGITAL PINS
  right.attach(6);    // below 90 is forward
}

void loop() {
  int lRead = analogRead(leftLine);
  int rRead = analogRead(rightLine);
  int lwRead = analogRead(leftWide);
  int rwRead = analogRead(rightWide);

  // INTERSECTION DETECTION
  if((lwRead >= thresh || rwRead >= thresh) && detectCooldown == 0){
    switch (intsec){
      case 0:
        Serial.println("Case0");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
        leftTurn();
      break;
      case 1:
        Serial.println("Case1");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
      break;
      case 2:
        Serial.println("Case2");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
      break;
      case 3:
        Serial.println("Case3");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
        rightTurn();
      break;
      case 4:
        Serial.println("Case4");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
        rightTurn();
      break;
      case 5:
        Serial.println("Case5");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
        rightTurn();
      break;
      case 6:
        Serial.println("Case6");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
      break;
      case 7:
        Serial.println("Case7");
        intsec++;
        detectCooldown = 10;
        roboStop = 0;
        leftTurn();
      break;
      case 8:
        Serial.println("Case8");
        roboStop = 1;
        intsec = 0;
        detectCooldown = 10;
        leftTurn(); 
      break;
      default:
        Serial.println("Default");
        roboStop = 0;
      break;
    }
  }
    else{
      detectCooldown--;
      if (detectCooldown < 0) detectCooldown = 0;
    }
    left.write(100);
    right.write(80);
  
  if(lRead<=thresh && rRead<=thresh || roboStop){     // stop
    left.write(90);
    right.write(90);
  }
  else{
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
    }
  }
}


