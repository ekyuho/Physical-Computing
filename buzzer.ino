int freq[5]={262, 293, 329, 349, 392};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(4, OUTPUT);
}

void on(int i) {
  tone(4, freq[i]);
  delay(1000);
}

int i=0;
void loop() {
  on(i);
  i++;
  if (i==5) i=0;
}
