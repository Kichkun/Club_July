#include <FS.h>
#include <WebSocketsServer.h>
#include "HelperFunctions.h"
#include <PJON.h>

PJON<SoftwareBitBang> bus(14);

void error_handler(uint8_t code, uint16_t data, void *custom_pointer) {
  if(code == PJON_CONNECTION_LOST) {
    Serial.print("Connection with device ID ");
    Serial.print(bus.packets[data].content[0], DEC);
    Serial.println(" is lost.");
  }
  if(code == PJON_PACKETS_BUFFER_FULL) {
    Serial.print("Packet buffer is full, has now a length of ");
    Serial.println(data, DEC);
    Serial.println("Possible wrong bus configuration!");
    Serial.println("higher PJON_MAX_PACKETS if necessary.");
  }
  if(code == PJON_CONTENT_TOO_LONG) {
    Serial.print("Content is too long, length: ");
    Serial.println(data);
  }
};

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  //TODO Create valid type conversion (single int -> uint8_t*)
  //webSocket.broadcastBIN({(int)payload[0]}, 1);
};

void setup() {
  Serial.begin(115200);
  delay(1000);

  bus.set_error(error_handler);
  bus.set_receiver(receiver_function);
  bus.strategy.set_pin(5);
  bus.begin();

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

unsigned int a = 0, n;
int i = 0;
void loop() {
    n = millis();
    if (n - a > 1){
      int len = 100;
      int now = i++;// - 128;//random(0, 255) - 128; //Диапазон отпрвки -128 - 127
      if (i == 127) i = 0;
      //lenght of %xx% must be %len%
      int xx[100] = {now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now, now};
      webSocket.broadcastBIN((uint8_t *)(xx), len);
      a = n;
    }

    server.handleClient();
    webSocket.loop();
    bus.receive(50000);
    bus.update();
}

