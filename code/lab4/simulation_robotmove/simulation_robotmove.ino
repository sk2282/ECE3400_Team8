void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT); // data lsb
  pinMode(2, OUTPUT); // data msb
  pinMode(3, OUTPUT); // y lsb
  pinMode(4, OUTPUT); // y 
  pinMode(5, OUTPUT); // y msb
  pinMode(6, OUTPUT); // x lsb
  pinMode(7, OUTPUT); // x msb
  pinMode(8, INPUT);
}

void loop() {

  while(!digitalRead(8));
  
  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  // 0,0
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, HIGH);//d
  digitalWrite(1, HIGH);//d   -> treasure  
  //0,1
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //0,2
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //0,3
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, HIGH);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//0,4
  delay(1000);
  
  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, HIGH);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //1,4
  delay(1000);
  
  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //1,3
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//1,2
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//1,1
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//1,0
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  // 2,0
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, HIGH);//d
  digitalWrite(1, HIGH);//d   -> treasure  
  //2,1
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //2,2
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //2,3
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, HIGH);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//2,4
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, HIGH);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //3,4
  delay(1000);
  
  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
  //3,3
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, HIGH);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//3,2
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, HIGH);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//3,1
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//3,0
  
  delay(1000);

  digitalWrite(7, HIGH);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//2,0
  
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, HIGH);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//1,0
  
  delay(1000);

  digitalWrite(7, LOW);//x msb
  digitalWrite(6, LOW);//x lsb
  digitalWrite(5, LOW);//y msb
  digitalWrite(4, LOW);//y
  digitalWrite(3, LOW);//y lsb
  digitalWrite(2, LOW);//d
  digitalWrite(1, HIGH);//d   -> visited
//0,0

  while(1);
}

