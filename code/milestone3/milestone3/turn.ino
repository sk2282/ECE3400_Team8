void leftTurn() {
  Serial.println("left turn");
  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(77);
      left.write(77);
  }while(analogRead(leftLine)<=thresh){
      right.write(77);
      left.write(77);
  }
  right.write(90);
  left.write(90);
  dir = (dir+3) % 4;
}

void rightTurn(){
  Serial.println("right turn");
  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
  while(analogRead(leftLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
  dir = (dir+1) % 4;
}

void UTurn() {
  Serial.println("U turn");
  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  while(analogRead(leftLine)>=thresh || analogRead(rightLine)>=thresh){
      right.write(103);
      left.write(103);
  }while(analogRead(rightLine)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
  dir = (dir+2) % 4;
}

void skipIntersection(){
  while(analogRead(2)>=thresh || analogRead(3)>=thresh){
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



