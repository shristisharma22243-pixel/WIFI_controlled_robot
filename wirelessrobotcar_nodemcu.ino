#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

ESP8266WebServer server(80);

const char* ssid = "ESP_Robot";
const char* password = "12345678";

// Function Prototypes
void handleRoot();
void forward();
void backward();
void left();
void right();
void stopMotor();

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  WiFi.softAP(ssid, password);

  Serial.println("WiFi Robot Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/F", forward);
  server.on("/B", backward);
  server.on("/L", left);
  server.on("/R", right);
  server.on("/S", stopMotor);

  server.begin();
}

void loop() {
  server.handleClient();
}

// ================= Web Page =================
void handleRoot() {
  String page = R"====(
<!DOCTYPE html>
<html>
<head>
<title>ESP8266 Robot</title>
<style>
body{
  background:#444;
  color:white;
  text-align:center;
  font-family:Arial;
}
button{
  width:90px;
  height:90px;
  font-size:20px;
  margin:8px;
}
</style>
</head>

<body>
<h1>ESP8266 WiFi Robot</h1>

<button onclick="send('F')">FORWARD</button><br>
<button onclick="send('L')">LEFT</button>
<button onclick="send('S')">STOP</button>
<button onclick="send('R')">RIGHT</button><br>
<button onclick="send('B')">BACK</button>

<script>
function send(cmd){
  fetch('/'+cmd);
}

document.addEventListener('keydown', function(event){
  switch(event.key){
    case 'ArrowUp':
      send('F');
      break;
    case 'ArrowDown':
      send('B');
      break;
    case 'ArrowLeft':
      send('L');
      break;
    case 'ArrowRight':
      send('R');
      break;
  }
});

document.addEventListener('keyup', function(){
  send('S');
});
</script>

</body>
</html>
)====";

  server.send(200, "text/html", page);
}

// ================= Motor Functions =================

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  server.send(200, "text/plain", "Forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  server.send(200, "text/plain", "Backward");
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  server.send(200, "text/plain", "Left");
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  server.send(200, "text/plain", "Right");
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  server.send(200, "text/plain", "Stop");
}
