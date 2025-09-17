#define LED_BUILTIN  2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, INPUT);
  Serial.begin(115200);
}

void loop() {
  int in = digitalRead(4);
  if (in==1)in=0;
  else in=1;
  digitalWrite(LED_BUILTIN, in);
  //delay(1000);
}
