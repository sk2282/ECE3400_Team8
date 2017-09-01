#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(3);

}

void loop() {
// Test servo direction
  servo.write(90);    // stopped
  delay(2000);
  servo.write(0);     // clockwise
  delay(2000);
  servo.write(90);    // stopped
  delay(2000);
  servo.write(180);   // counter clockwise
  delay(2000);

// Using potentiometer to control servo
// Comment above portion out to use.
int v = analogRead(0);    // read pot value
analogWrite(3, v/4);      // divide pot value by 4 to get value between 0 and 255. Then write to servo.
}
