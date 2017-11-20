#include <Servo.h>
#include <StackArray.h>

StackArray<int> stack;
Servo left;
Servo right;
int leftLine = 2; //10; //0;     // Pin for left line detector
int rightLine = 3; //11; //1;    // Pin for right line detector
int leftWide = 4; //12; //2;     // Pin for left intersection detector
int rightWide = 7; //13; //3;    // Pin for right intersection detector
//int thresh   = 500;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 300;

int wallSensorF = 0; //11; // front wall sensor
int wallSensorR = 1; //12; // right wall sensor
int wallSensorL = 2; //13; // left wall sensor
int frontThresh = 500; // threshold value for front wall sensor 
int sideThresh = 375; // threshold value for side wall sensor threshold

/*
int lRead;
int rRead;
int lwRead;
int rwRead;
*/

int frontRead; // for wall sensors
int leftRead;
int rightRead;


void setup() {
  Serial.begin(9600);
  /*
  pinMode(wallSensorL, INPUT);
  pinMode(wallSensorR, INPUT);
  pinMode(wallSensorF, INPUT);
  */
  pinMode(leftLine, INPUT);
  pinMode(rightLine, INPUT);
  pinMode(leftWide, INPUT);
  pinMode(rightWide, INPUT);
  left.attach(5);
  right.attach(6);
  stack.push(19);
}

void loop() {
  /*
  lwRead = analogRead(leftWide);
  rwRead = analogRead(rightWide);
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  */
  // INTERSECTION DETECTION
  if ((digitalRead(leftWide) == LOW && digitalRead(rightWide) == LOW) && detectCooldown <= 0) {
//  if ((lwRead >= thresh && rwRead >= thresh) && detectCooldown <= 0) {
    detectCooldown = DETECT_COOLDOWN;
        if (!notDone()) {
          left.write(90);
          right.write(90);
          while(true){}
        }
        else {
          dfs();
        }
  }
  else {
    detectCooldown--;
    if (detectCooldown < 0) detectCooldown = 0;
  }
  /*
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  */
  if (digitalRead(leftLine) == HIGH && digitalRead(rightLine) == HIGH) { // stop
//  if (lRead <= thresh && rRead <= thresh || roboStop) { // stop
    left.write(94);
    right.write(90);
    }
  else if (digitalRead(leftLine) == HIGH) { // left side is out of line
//  else if (lRead < thresh) { // left side is out of line
    left.write(170);
    right.write(85);
  }
  else if (digitalRead(rightLine) == HIGH) { // right side is out of line
//  else if (rRead < thresh) { // right side is out of line
    left.write(95);
    right.write(10);
  }
  else {    // go straight
    left.write(100);
    right.write(80);
  }
}

