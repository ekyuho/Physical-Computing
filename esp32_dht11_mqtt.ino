#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// 설정
const char* ssid = "cookie2";
const char* password = "0317137263";
const char* mqtt_server = "damoa.io";

#define DHTPIN 4
#define DHTTYPE DHT11

WiFiClient espClient;
PubSubClient client(espClient);
DHT_Unified dht(DHTPIN, DHTTYPE);

String clientId; // 고유한 클라이언트 ID
unsigned long lastReconnectAttempt = 0;
int cnt = 1;

void setup() {
  Serial.begin(115200);
  dht.begin();

  delay(1000);
  Serial.println(__FILE__);
  Serial.println(__DATE__);
  
  // 고유한 Client ID 생성 (MAC 주소 기반)
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
    // rc 값 의미:
    // -4: 서버 연결 실패
    // -3: 네트워크 연결 끊김
    // -2: 네트워크 연결 실패
    // -1: 타임아웃
    //  0: 연결됨
    //  1: 잘못된 프로토콜 버전
    //  2: 식별자 거부됨
    //  3: 서버 사용 불가
    //  4: 잘못된 사용자명/비밀번호
    //  5: 권한 없음
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
  if (millis() - lastTime > 10000) {
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
  
  // JSON 메시지 생성
  String value = String("{\"cnt\":") + String(cnt) + 
                 String(", \"temperature\": ") + String(t) + 
                 String(", \"humidity\": ") + String(h) + "}";
  Serial.println(value);
  cnt++;
  
  // MQTT 발행 (QoS 0)
  if (client.publish("ewha/0317137263", value.c_str())) {
    Serial.println("발행 성공: " + value);
  } else {
    Serial.println("발행 실패!");
  }
}
