void followLine(){
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

void halt() {
  left.write(90);
  right.write(90);
  while (true) {}
}

void leftTurn() {
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
<<<<<<< HEAD
      right.write(77);
      left.write(77);
  }
  while (digitalRead(leftLine) == HIGH) {
      right.write(77);
      left.write(77);
=======
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(74);
      left.write(81);
  }
  while (digitalRead(leftLine) == HIGH) {
//  while(analogRead(leftLine)<=thresh){
      right.write(74);
      left.write(81);
>>>>>>> 10c7c796ade168400e137fbb1e500722d16f6b72
  }
  right.write(90);
  left.write(90);
  dir = (dir+3) % 4;
}

void rightTurn(){
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
<<<<<<< HEAD
      right.write(103);
      left.write(103);
  }
  while (digitalRead(rightLine) == HIGH) {
      right.write(103);
      left.write(103);
=======
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(100);
      left.write(107);
  }
  while (digitalRead(rightLine) == HIGH) {
//  while(analogRead(rightLine)<=thresh){
      right.write(100);
      left.write(107);
>>>>>>> 10c7c796ade168400e137fbb1e500722d16f6b72
  }
  right.write(90);
  left.write(90);
  dir = (dir+1) % 4;
}

void UTurn() {
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
<<<<<<< HEAD
      right.write(110);
      left.write(110);
  }
  while (digitalRead(rightLine) == HIGH || digitalRead(leftLine) == HIGH) {
      right.write(110);
      left.write(110);
  }
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
      right.write(110);
      left.write(110);
  }
  while (digitalRead(rightLine) == HIGH || digitalRead(leftLine) == HIGH) {
      right.write(110);
      left.write(110);
  }
  right.write(90);
  left.write(90);
  while (digitalRead(rightLine) == LOW) {
      right.write(94);
      left.write(94);
=======
      right.write(100);
      left.write(107);
  }
  while (digitalRead(rightLine) == HIGH || digitalRead(leftLine) == HIGH) {
      right.write(100);
      left.write(107);
  }
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
      right.write(100);
      left.write(107);
  }
  while (digitalRead(rightLine) == HIGH || digitalRead(leftLine) == HIGH) {
      right.write(100);
      left.write(107);
>>>>>>> 10c7c796ade168400e137fbb1e500722d16f6b72
  }
  right.write(90);
  left.write(90);
  dir = (dir+2) % 4;
}

void skipIntersection(){
  while (digitalRead(leftWide) == LOW || digitalRead(rightWide) == LOW) {
//  while(analogRead(2)>=thresh || analogRead(3)>=thresh){
    left.write(100);
    right.write(80);  
  }
}

void faceRobot(int dir0) {
<<<<<<< HEAD
//  Serial.print("face");
//  Serial.println(dir0);
=======
>>>>>>> 10c7c796ade168400e137fbb1e500722d16f6b72
  if (dir0 == dir) {
    skipIntersection();
  }
  else if (abs(dir-dir0) == 2) {
    UTurn();
  }
  else if ((dir0 - dir + 4) % 4 == 1) {
    rightTurn();
  }
  else {
    leftTurn();
  }
}



