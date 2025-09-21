#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
// 각자 본인의 폰에서 테더링 설정하고 사용하세요
// iphone의 겨우 데이타 속도를 '저속' 으로 설정해야 합니다.  2.4GHz 만 가능.
const char *ssid = "cookie2";
const char *password = "0317137263"; 

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
void handle_root();

// HTML 페이지
#if 1
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>ESP32 Simple Web Server - &#128522;</h1>
</center>
</body>
</html>
)rawliteral";
#endif


//페이지 요청이 들어 오면 처리 하는 함수
void handle_root()
{
  server.send(200, "text/html", index_html);
}

void on()
{
	digitalWrite(2, 1); 
	server.send(200, "text/html", "turned on");
}

void off()
{
	digitalWrite(2, 0);
	server.send(200, "text/html", "turned off");
}


void InitWebServer() 
{
	//페이지 요청 처리 함수 등록
	server.on("/", handle_root);
	server.on("/on", on);
	server.on("/off", off);

    server.begin();
}

void setup() {
	Serial.begin(115200);
	Serial.println("ESP32 Simple web Start");
	Serial.println(ssid);
	pinMode(2, OUTPUT);

	//WiFi 접속
	WiFi.begin(ssid, password);

	//접속 완료 하면
	while (WiFi.status() != WL_CONNECTED) {
	delay(1000);
	Serial.print(".");
	}
    
	Serial.print("Wifi IP: ");
	Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

	InitWebServer(); 
    
	Serial.println("HTTP server started");
	delay(100); 
}

void loop() {
  server.handleClient();
}
