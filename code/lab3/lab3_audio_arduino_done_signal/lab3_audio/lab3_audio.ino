void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(2,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  Serial.println("done");
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  Serial.println("done signal off");
}
