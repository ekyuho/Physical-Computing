int port[8]={13, 14, 15, 18, 19, 21, 22, 23};

void setup() {
  Serial.begin(115200);
  for(int i=0; i<8; i++) {
    Serial.printf("%d %d\n", i, port[i]);
    pinMode(port[i], OUTPUT);
  }
  for(int i=0; i<8; i++) {
    digitalWrite(port[i], 1);
  }
}

int i=0;
void loop() {
  digitalWrite(port[i], 0);
  Serial.printf("%d port%d\n", i, port[i]);
  delay(1000);
  digitalWrite(port[i], 1);
  delay(1000);
  i++;
  if (i==8) i=0;
}
