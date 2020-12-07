#include "configuration.h"

void rootPage() {
  char content[] = "BLE Presence v1.0";
  Server.send(200, "text/plain", content);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    client.connect(ID_MQTT, BROKER_USER, BROKER_PASSWORD);
    if (client.connect("esp-room")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
