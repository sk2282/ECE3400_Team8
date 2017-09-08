#include <Servo.h>

Servo left;   // clockwise is
Servo right;  // clockwise is

int leftLine = 1;
int rightLine = 2;
int thresh = 800;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  left.attach(5);
  right.attach(6);
}

void loop() {
  int lRead = analogRead(leftLine);
  int rRead = analogRead(rightLine);
  
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

  //Serial.println(line);
}

// threshold 500 - over this and it detects line
