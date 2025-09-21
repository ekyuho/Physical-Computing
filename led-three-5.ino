void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);

  digitalWrite(4, HIGH);
  delay(200);
  digitalWrite(4, LOW);

  digitalWrite(5, HIGH);
  delay(200);
  digitalWrite(5, LOW);
  delay(1000);    

  digitalWrite(5, HIGH);
  delay(200);
  digitalWrite(5, LOW);

  digitalWrite(4, HIGH);
  delay(200);
  digitalWrite(4, LOW);

  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(1000); 
}
