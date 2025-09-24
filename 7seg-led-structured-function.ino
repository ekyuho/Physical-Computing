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

on(int d) {
  if (d==0) 
    for(int i=0; i<8; i++) digitalWrite(port[i], didit0[i]);
  if (d==1) 
    for(int i=0; i<8; i++) digitalWrite(port[i], didit1[i]);
  if (d==2) 
    for(int i=0; i<8; i++) digitalWrite(port[i], didit2[i]);
  delay(2000);
}

void loop() {
  on(0);
  on(1);
  on(2);
}
