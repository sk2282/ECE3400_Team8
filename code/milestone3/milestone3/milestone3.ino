#include <Servo.h>
#include <StackArray.h>

StackArray<int> stack;
Servo left;
Servo right;
int roboStop = 0;
int leftLine = 0;     // Pin for left line detector
int rightLine = 1;    // Pin for right line detector
int leftWide = 2;     // Pin for left intersection detector
int rightWide = 3;    // Pin for right intersection detector
int thresh   = 500;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 200;

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
  stack.push(19);
}

void loop() {
  lwRead = analogRead(leftWide);
  rwRead = analogRead(rightWide);
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  // INTERSECTION DETECTION
  if ((lwRead >= thresh && rwRead >= thresh) && detectCooldown <= 0) {
    detectCooldown = DETECT_COOLDOWN;
        if (!dfs()) {
          left.write(90);
          right.write(90);
          Serial.println("done");
          while(true){}
        }
        else {
          Serial.println();
        }
  }
  else {
    detectCooldown--;
    if (detectCooldown < 0) detectCooldown = 0;
  }
  lRead = analogRead(leftLine);
  rRead = analogRead(rightLine);
  if (lRead <= thresh && rRead <= thresh || roboStop) { // stop
    left.write(90);
    right.write(90);
    }
  else if (lRead < thresh) { // left side is out of line
    left.write(170);
    right.write(87);
  }
  else if (rRead < thresh) { // right side is out of line
    left.write(93);
    right.write(10);
  }
  else {    // go straight
    left.write(100);
    right.write(80);
  }
}

