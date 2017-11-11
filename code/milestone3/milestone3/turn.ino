void leftTurn() {
  Serial.println("left turn");
  while(analogRead(0)>=thresh || analogRead(1)>=thresh){
      right.write(77);
      left.write(77);
  }while(analogRead(0)<=thresh){
      right.write(77);
      left.write(77);
  }
  right.write(90);
  left.write(90);
  direction = (direction-1) % 4;
}

void rightTurn(){
  Serial.println("right turn");
  while(analogRead(0)>=thresh || analogRead(1)>=thresh){
      right.write(103);
      left.write(103);
  }while(analogRead(1)<=thresh){
      right.write(103);
      left.write(103);
  }
  right.write(90);
  left.write(90);
  direction = (direction+1) % 4;
}

void UTurn() {
  Serial.println("U turn");
  rightTurn();
  rightTurn();
}

void skipIntersection(){
  while(analogRead(2)>=thresh || analogRead(3)>=thresh){
    left.write(100);
    right.write(80);  
  }
}

void faceRobot(int dir) {
  Serial.println("face new");
  if (dir == direction) {
    return;
  }
  else if (abs(direction-dir) == 2) {
    rightTurn();
    rightTurn();
  }
  else if (dir - direction == 1) {
    rightTurn();
  }
  else {
    leftTurn();
  }
}



