#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

const char* ssid = "cookie2";
const char* password = "0317137263";
String serverName = "https://api.thingspeak.com/update?api_key=use-your-own-thingspeak-apk-key";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

int cnt = 1;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 연결됨");
  Serial.println("IP: " + WiFi.localIP().toString());
}

void loop() { 
  // 16초마다 값 발행
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 16000) {
    publishValue();
    lastTime = millis();
  }
  
  // 짧은 딜레이로 루프 안정화
  delay(10);
}

void publishValue() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Disconnected");
    return;
  }

  sensors_event_t event;
  float t = 0;
  float h = 0;
  
  // 온도 읽기
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    t = event.temperature;
  }
  
  // 습도 읽기
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    h = event.relative_humidity;
  }
  
  HTTPClient http;
  String serverPath = serverName + "&field1="+String(t)+"&field2="+String(h);
  Serial.println(serverPath);
  
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
