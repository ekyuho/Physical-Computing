#define LED_BUILTIN 2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

int i=6;
int n=0;
int t[10]={10,25,50,100,200,500,1000};

void loop() {
  if (n==0) {
    n=5;
    for (int k=0;k<10;k++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(20);
      digitalWrite(LED_BUILTIN, LOW);
      delay(20);
    }
    i++;
    if (i==7) i=0;
  }
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.println(t[i]);
  delay(t[i]);  
  digitalWrite(LED_BUILTIN, LOW);  
  delay(2000);  
  n--;
}
