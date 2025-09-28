#include <WiFi.h>
#include <PubSubClient.h>

// 설정
const char* ssid = "cookie2";
const char* password = "0317137263";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
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
    // 발행할 값 (예: 센서 데이터 또는 고정값)
    String value = "Hello MQTT! "+ String(cnt);
    cnt++;
    
    // MQTT 발행
    client.publish("ewha/iot/2025", value.c_str());
    Serial.println("발행됨: " + value);
  }
}
