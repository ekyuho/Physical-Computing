int port[8]={13, 14, 15, 18, 19, 21, 22, 23};
int digit0[8]={1,0,0,0,0,0,0,0};
int digit1[8]={1,1,1,0,1,1,0,0};
int digit2[8]={0,1,0,0,0,0,0,1};

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

void loop() {
  for(int i=0; i<8; i++) digitalWrite(port[i], digit0[i]);
  delay(2000);
  for(int i=0; i<8; i++) digitalWrite(port[i], digit1[i]);
  delay(2000);
  for(int i=0; i<8; i++) digitalWrite(port[i], digit2[i]);
  delay(2000);
}
