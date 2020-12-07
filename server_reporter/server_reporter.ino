#include "configuration.h"

HardwareSerial Receiver(2);

#define Receiver_Txd_pin 17
#define Receiver_Rxd_pin 16

char mac_address[18];

void update_data() {
  root["mac"] = mac_address;
}

void sendDataMQTT() {
  serializeJson(root, body);
  body.toCharArray(msg, 150);
  body = "";

  if (client.publish(PUB_TOPIC, msg) == true) {
    Serial.print("Published data: ");
    Serial.println(msg);
  }
}

void setup() {
  //Serial.begin(Baud Rate, Data Protocol, Txd pin, Rxd pin);
  Serial.begin(115200);                                                   
  Receiver.begin(115200, SERIAL_8N1, Receiver_Txd_pin, Receiver_Rxd_pin); 

  Server.on("/", rootPage);
  Portal.begin();
  Serial.println("Web server started:" + espClient.localIP().toString());

  client.setServer(mqtt_server, 1883);
}

void loop() {
  Portal.handleClient();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Receiver.available()) {
    String received_mac = Receiver.readString();
    if (received_mac) {
      received_mac.toCharArray(mac_address, 18);
      Serial.println(mac_address);
      update_data();
      sendDataMQTT();
    }
  };
}
