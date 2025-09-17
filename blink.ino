#define LED_BUILTIN  2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("high");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("low");
  delay(1000);
}
