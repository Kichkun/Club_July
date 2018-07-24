#include <FS.h>
#include <WebSocketsServer.h>
#include "HelperFunctions.h"


void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  Serial.println(); Serial.print("Configuring access point...");
  setupWiFi();
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(myIP);

  server.on("/", HTTP_GET, []() {
    handleFileRead("/");
  });

  server.onNotFound([]() {                
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  webSocket.begin();                              
  webSocket.onEvent(webSocketEvent);            

  server.begin();
  Serial.println("HTTP server started");
  yield();
}

void loop() {
    if(Serial.available() > 0){
        webSocket.broadcastBIN({(int)Serial.read()}, 1);
    }
    server.handleClient();
    webSocket.loop();
}

