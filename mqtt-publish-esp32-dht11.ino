#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// 설정
const char* ssid = "cookie2";
const char* password = "0317137263";
const char* mqtt_server = "damoa.io";

#define DHTPIN 4     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

WiFiClient espClient;
PubSubClient client(espClient);
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  
  // WiFi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi 연결됨");
  
  // MQTT 설정
  client.setServer(mqtt_server, 1883);
}

void loop() {
  // MQTT 연결 확인
  if (!client.connected()) {
    if (client.connect("ArduinoPublisher")) {
      Serial.println("MQTT 연결됨");
    }
  }
  client.loop();
  
  // 5초마다 값 발행
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 5000) {
    publishValue();
    lastTime = millis();
  }
}

int cnt=1;
void publishValue() {
  if (client.connected()) {
    sensors_event_t event;
    float t=0;
    float h=0;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
      t=event.temperature;
    }
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
      h=event.relative_humidity;
    }


    // 발행할 값 (예: 센서 데이터 또는 고정값)
    String value = Strig("온도: ")+ String(t) + String(", 습도: ") + String(h);
    
    // MQTT 발행
    client.publish("ewha/0317137263", value.c_str());
    Serial.println("발행됨: " + value);
  }
}
