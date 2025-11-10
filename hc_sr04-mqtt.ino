#include <WiFi.h>
#include <PubSubClient.h>

const int TRIG_PIN = 5;   // change to any suitable GPIO
const int ECHO_PIN = 18;  // change to any suitable GPIO

const char* ssid = "cookie2";
const char* password = "0317137263";
const char* mqtt_server = "damoa.io";

long duration;      // time for echo (µs)
float distance_cm;  // calculated distance

WiFiClient espClient;
PubSubClient client(espClient);

String clientId; // 고유한 클라이언트 ID
unsigned long lastReconnectAttempt = 0;
int cnt = 1;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  clientId = "ESP32_" + String((uint32_t)ESP.getEfuseMac(), HEX);
  Serial.println("Client ID: " + clientId);
  
  // WiFi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 연결됨");
  Serial.println("IP: " + WiFi.localIP().toString());
  
  // MQTT 설정
  client.setServer(mqtt_server, 1883);
  client.setKeepAlive(60); // Keep Alive 시간 60초로 설정
  client.setSocketTimeout(30); // 소켓 타임아웃 30초
  
  digitalWrite(TRIG_PIN, LOW);
  delay(100);
}

boolean reconnect() {
  // 5초마다 재연결 시도
  if (millis() - lastReconnectAttempt < 5000) {
    return false;
  }
  
  lastReconnectAttempt = millis();
  Serial.print("MQTT 재연결 시도...");
  
  // 고유한 Client ID로 연결
  if (client.connect(clientId.c_str())) {
    Serial.println("성공!");
    return true;
  } else {
    Serial.print("실패, rc=");
    Serial.println(client.state());
    return false;
  }
}

void loop() {
  // MQTT 연결 확인 및 재연결
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop(); // 연결되어 있을 때만 loop 호출
  }
  
  // 16초마다 값 발행
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 500) {
    publishValue();
    lastTime = millis();
  }
  
  // 짧은 딜레이로 루프 안정화
  delay(10);
}

void publishValue() {
  if (!client.connected()) {
    Serial.println("MQTT 연결 안됨 - 발행 스킵");
    return;
  }
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2) Measure the length of the ECHO pulse
  //    Timeout 30,000 µs (~5 m range) so we don't block forever
  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Out of range or no echo");
  } else {
    // 3) Convert time to distance
    // Speed of sound ~343 m/s → 0.0343 cm/µs
    distance_cm = (duration * 0.0343) / 2.0;

    //Serial.print("Distance: ");
    //Serial.println(distance_cm);
    //Serial.println(" cm");
  }
  
  // JSON 메시지 생성
  String value = String("{\"distance\":") + String(distance_cm) + "}";
  //Serial.println(value);
  cnt++;
  
  // MQTT 발행 (QoS 0)
  if (client.publish("ewha/kim/0317137263", value.c_str())) {
    Serial.println(value);
  } else {
    Serial.println("발행 실패!");
  }
}
