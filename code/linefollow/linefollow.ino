#include <Servo.h>



Servo left;
Servo right;
int roboStop = 0;
int leftLine = 10; //0;     // Pin for left line detector
int rightLine = 11; //1;    // Pin for right line detector
int leftWide = 12; //2;     // Pin for left intersection detector
int rightWide = 13; //3;    // Pin for right intersection detector
//int thresh   = 500;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 200;

int wallSensorF = 0; //11; // front wall sensor
int wallSensorR = 1; //12; // right wall sensor
int wallSensorL = 2; //13; // left wall sensor
int frontThresh = 500; // threshold value for front wall sensor 
int sideThresh = 325; // threshold value for side wall sensor threshold

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

}

void loop() {
  /*
  lwRead = analogRead(leftWide);
  rwRead = analogRead(rightWide);
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  */
  /*
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  */
  if (digitalRead(leftLine) == HIGH && digitalRead(rightLine) == HIGH || roboStop) { // stop
//  if (lRead <= thresh && rRead <= thresh || roboStop) { // stop
    left.write(90);
    right.write(90);
    }
  else if (digitalRead(leftLine) == HIGH) { // left side is out of line
//  else if (lRead < thresh) { // left side is out of line
    left.write(170);
    right.write(83);
  }
  else if (digitalRead(rightLine) == HIGH) { // right side is out of line
//  else if (rRead < thresh) { // right side is out of line
    left.write(97);
    right.write(10);
  }
  else {    // go straight
    left.write(100);
    right.write(80);
  }
}

