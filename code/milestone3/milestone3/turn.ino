void leftTurn() {
  Serial.println("left turn");
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(77);
      left.write(77);
  }
  while (digitalRead(leftLine) == HIGH) {
//  while(analogRead(leftLine)<=thresh){
      right.write(77);
      left.write(77);
  }
  right.write(90);
  left.write(90);
  dir = (dir+3) % 4;
}

void rightTurn(){
  Serial.println("right turn");
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }
  while (digitalRead(rightLine) == HIGH) {
//  while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
//  while (digitalRead(leftLine) == HIGH) {
////  while(analogRead(leftLine)<=thresh){
//      right.write(103);
//      left.write(103);
//  }
//  right.write(90);
//  left.write(90);
  dir = (dir+1) % 4;
}

void UTurn() {
  Serial.println("U turn");
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }
  while (digitalRead(rightLine) == HIGH) {
//  while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  while (digitalRead(leftLine) == LOW || digitalRead(rightLine) == LOW) {
//  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }
  while (digitalRead(rightLine) == HIGH) {
//  while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
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
  Serial.println("face new");
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



