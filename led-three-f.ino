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

void on(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
}

void loop() {
  on(2, 200);
  on(4, 200);
  on(5, 200);
  delay(500);

  on(5, 200);
  on(4, 200);
  on(2, 200);
  delay(1000);
}
