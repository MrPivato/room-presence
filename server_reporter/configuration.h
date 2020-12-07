#pragma once

/* WiFi *****************************************************/
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

WebServer Server;
AutoConnect Portal(Server);

WiFiClient espClient;
/************************************************************/
/* MQTT *****************************************************/
#include <PubSubClient.h>
const char* mqtt_server = "xxxxxxx";
const char* BROKER_USER = "xxxxxx";
const char* BROKER_PASSWORD = "xxxxxx";

#define ID_MQTT  "esp-room"
#define PUB_TOPIC   "/ble-presence/room"
#define SENSOR_MODEL "ESP32"

PubSubClient client(espClient);
/************************************************************/
/* Sensors **************************************************/
#define ARDUINOJSON_USE_DOUBLE 0

#include <ArduinoJson.h>

char msg[150];
DynamicJsonDocument root(1024);
String body;
/************************************************************/
