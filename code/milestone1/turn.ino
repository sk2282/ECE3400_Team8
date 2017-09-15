void leftTurn(){
  right.write(87);
  left.write(87);
  delay(50);
  while(analogRead(leftWide)<=thresh || analogRead(rightWide)<=thresh){
      right.write(87);
      left.write(87);
  }
}

void rightTurn(){
  right.write(93);
  left.write(93);
  delay(50);
  while(analogRead(leftWide)<=thresh || analogRead(rightWide)<=thresh){
      right.write(93);
      left.write(93);
  }
}

