#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

// Some variables we will need along the way
const char* ssid     = "Fablab";
const char* password = "Fabricationlab1"; 
const char* PARAM_MESSAGE = "message"; 
int webServerPort = 80;
int ledPin = D0;
int motPin = D2;

// Setting up our webserver
AsyncWebServer server(webServerPort);

void notFound(AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(404, "text/plain", "Not found");
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void sendResponse(AsyncWebServerRequest *request, String message){
  AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", message);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(motPin, OUTPUT);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(motPin, LOW);

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // We want to know the IP address so we can send commands from our computer to the device
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Greet human when it tries to access the root / endpoint.
  // This is a good place to send some documentation about other calls available if you wish.
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    sendResponse(request, "Welcome to the Pump Board. Use /on and /off to control pump.");
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    digitalWrite(motPin, HIGH);
    sendResponse(request, "Haz had ON");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    digitalWrite(motPin, LOW);
    sendResponse(request, "Haz meh OFF");
  });

  // If human tries endpoint no exist, exec this function
  server.onNotFound(notFound);

  Serial.print("Starting web server on port ");
  Serial.println(webServerPort);
  server.begin();
} 

void loop() {
  // Nothing needed here at the moment
}
