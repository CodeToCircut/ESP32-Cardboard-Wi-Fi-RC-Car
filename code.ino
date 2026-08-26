#include <WiFi.h>
#include <WebServer.h>

// WiFi Access Point Configuration
const char* ssid = "ESP32-Cardboard-Car";
const char* password = "Password123";

WebServer server(80);

// Motor A (Left) Pins
const int IN1 = 26;
const int IN2 = 27;

// Motor B (Right) Pins
const int IN3 = 14;
const int IN4 = 12;

// HTML & JavaScript Web UI
const char HTML_CONTENT[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>ESP32 Car Controller</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background: #121212; color: #fff; margin:0; padding:20px; }
    h1 { margin-bottom: 20px; color: #00E676; }
    .btn { width: 90px; height: 90px; font-size: 24px; font-weight: bold; background: #1E1E1E; color: #fff; border: 2px solid #00E676; border-radius: 12px; margin: 10px; touch-action: manipulation; }
    .btn:active { background: #00E676; color: #000; }
    .grid { display: grid; grid-template-columns: repeat(3, 100px); justify-content: center; align-items: center; margin: 0 auto; }
    .empty { width: 90px; height: 90px; }
  </style>
</head>
<body>
  <h1>ESP32 RC Car</h1>
  <div class="grid">
    <div class="empty"></div>
    <button class="btn" onmousedown="sendCmd('F')" onmouseup="sendCmd('S')" ontouchstart="sendCmd('F')" ontouchend="sendCmd('S')">▲</button>
    <div class="empty"></div>
    <button class="btn" onmousedown="sendCmd('L')" onmouseup="sendCmd('S')" ontouchstart="sendCmd('L')" ontouchend="sendCmd('S')">◄</button>
    <button class="btn" onmousedown="sendCmd('S')" ontouchstart="sendCmd('S')">■</button>
    <button class="btn" onmousedown="sendCmd('R')" onmouseup="sendCmd('S')" ontouchstart="sendCmd('R')" ontouchend="sendCmd('S')">►</button>
    <div class="empty"></div>
    <button class="btn" onmousedown="sendCmd('B')" onmouseup="sendCmd('S')" ontouchstart="sendCmd('B')" ontouchend="sendCmd('S')">▼</button>
    <div class="empty"></div>
  </div>

  <script>
    function sendCmd(cmd) {
      fetch('/cmd?dir=' + cmd).catch(err => console.log(err));
    }
  </script>
</body>
</html>
)rawliteral";

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void handleCommand() {
  if (server.hasArg("dir")) {
    String dir = server.arg("dir");
    if (dir == "F") {
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    } else if (dir == "B") {
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
    } else if (dir == "L") {
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    } else if (dir == "R") {
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
    } else {
      stopMotors();
    }
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  WiFi.softAP(ssid, password);
  Serial.println("\nAccess Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", HTML_CONTENT);
  });
  server.on("/cmd", handleCommand);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}
