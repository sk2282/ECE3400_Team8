#include <Servo.h>

Servo leftServo;
Servo rightServo;

void setup() {
  leftServo.attach(5);
  rightServo.attach(6);

}

void loop() {
  leftServo.write(180); //
  rightServo.write(180); 
  delay(3000);
  leftServo.write(90);
  rightServo.write(90);
  delay(3000);
  rightServo.write(0); //
  leftServo.write(0); //
  delay(3000);
  rightServo.write(90);
  leftServo.write(90);
  delay(5000);
  rightServo.write(180);
  leftServo.write(0);
  delay(3000);
  rightServo.write(90);
  leftServo.write(90);
  delay(10000);
//  rightServo.write(90);
//  leftServo.write(90);

  // motors need to go in opposite directions to go in a straight line
  
}
