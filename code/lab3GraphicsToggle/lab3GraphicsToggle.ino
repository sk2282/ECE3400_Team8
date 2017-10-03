/*
 * Lab 3: Graphics Team
 */

int readSwitch1 = 11;
int writeSwitch1 = 10;
int readSwitch2 = 2;
int writeSwitch2 = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(readSwitch1, INPUT);
  pinMode(writeSwitch1, OUTPUT);
  pinMode(readSwitch2, INPUT);
  pinMode(writeSwitch2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(readSwitch1) == 1) {
    digitalWrite(writeSwitch1, HIGH);
  }
  else if (digitalRead(readSwitch1) == 0) {
    digitalWrite(writeSwitch1, LOW);
  }
  if (digitalRead(readSwitch2) == 1) {
    digitalWrite(writeSwitch2, HIGH);
  }
  else if (digitalRead(readSwitch2) == 0) {
    digitalWrite(writeSwitch2, LOW);
  }

}
