#include <Servo.h>

Servo left;
Servo right;
int roboStop = 0;     // robot stops moving
int leftLine = 0;     // Pin for left line detector
int rightLine = 1;    // Pin for right line detector
int leftWide = 2;     // Pin for left intersection detector
int rightWide = 3;    // Pin for right intersection detector
int thresh   = 800;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 50;

int wallSensorF = 11;
int wallSensorR = 12;
int wallSensorL = 13;

int lRead;
int rRead;
int lwRead;
int rwRead;

void setup() {
  Serial.begin(9600);
  pinMode(wallSensorL, INPUT);
  pinMode(wallSensorR, INPUT);
  pinMode(wallSensorF, INPUT);
  left.attach(5);
  right.attach(6);
  
}

void loop() {
  lwRead = analogRead(leftWide);
  rwRead = analogRead(rightWide);
  // INTERSECTION DETECTION
  if((lwRead >= thresh || rwRead >= thresh) && detectCooldown == 0){
    if (dfs()) {
      halt();
      return;
    }
  }
  else{
    detectCooldown--;
    if (detectCooldown < 0) detectCooldown = 0;
  }
  followLine();
}

void halt() {
  Serial.println("DONE");
  left.write(90);
  right.write(90);
}

void followLine(){
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
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

