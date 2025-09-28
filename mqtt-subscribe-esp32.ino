#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 설정
const char* ssid = "cookie2";
const char* password = "0317137263";

// MQTT 브로커 설정
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* topic = "ewha/iot/2025";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("WiFi에 연결 중");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("IP 주소: ");
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  connectToMQTT();
}

void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("메시지 수신 [");
  Serial.print(topic);
  Serial.print("]: ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
}

void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("MQTT 브로커에 연결 시도 중...");
    
    // 클라이언트 ID 생성 (랜덤하게)
    String clientId = "ArduinoClient-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("연결됨!");
      
      // 토픽 구독
      client.subscribe(topic);
      Serial.print("토픽 구독: ");
      Serial.println(topic);
      
    } else {
      Serial.print("실패, rc=");
      Serial.print(client.state());
      Serial.println(" 5초 후 재시도");
      delay(5000);
    }
  }
}
