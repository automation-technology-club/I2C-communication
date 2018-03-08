/* LeRoy Miller (C) 2018, see license.h for license information */

/*
 * http://crouton.mybluemix.net/crouton/dashboard
 */
 
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h> //https://github.com/knolleary/pubsubclient
/* Change MQTT_MAX_PACKET_SIZE in PubSubClient.h to 512 */
#include <Wire.h>

#define  RELAYPIN D1
#define BUTTON D3

WiFiClient  espClient;
PubSubClient client(espClient);

//const char* deviceInfo = "{\"deviceInfo\":{\"name\":\"Relay Toggle\",\"endPoints\":{\"relay\":{\"title\":\"Relay\",\"card-type\":\"crouton-simple-toggle\",\"values\":{\"value\":\"false\"},\"labels\":{\"true\":\"on\",\"false\":\"off\"}}},\"description\":\"Simple Relay ON OFF\",\"status\":\"ok\"}}";
//const char* deviceInfo = "{\"deviceInfo\":{\"name\":\"Relay Toggle\",\"endPoints\":{\"relay\":{\"title\":\"Relay\",\"card-type\":\"crouton-simple-button\",\"values\":{\"value\":\"false\"},\"icons\":{\"icon\":\"power-off\"}}},\"description\":\"Simple Relay ON OFF\",\"status\":\"ok\"}}";

const char* deviceInfo = "{\"deviceInfo\":{\"name\":\"Relay Toggle\",\"endPoints\":{\"relay\":{\"title\":\"Relay\",\"card-type\":\"crouton-simple-button\",\"values\":{\"value\":\"false\"},\"icons\":{\"icon\":\"power-off\"}},\"status\":{\"title\":\"Relay Status\",\"card-type\":\"crouton-simple-text\",\"units\":\"\",\"values\":{\"value\":\"OFF\"}}},\"description\":\"Simple Relay ON OFF\",\"status\":\"ok\"}}";

const char* mqtt_server = "broker.hivemq.com";
const char* deviceOutbox = "/outbox/RELAY1LFM1/deviceInfo";
const char* relayOutbox = "/outbox/RELAY1LFM1/status";
const char* relayInbox = "/inbox/RELAY1LFM1/relay";

bool relayState = 0;
int counter = 0;

void setup() {
  Wire.begin();
 Serial.begin(9600);
  WiFiManager wifiManager;
wifiManager.autoConnect("AutoConnectAP");
  pinMode(RELAYPIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), toggleRelay, HIGH);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
reconnect();
delay(1000);
//updateDeviceInfo();
}

void loop() {
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
  yield();
  counter ++;
  if (counter > 5000) {
    updateDeviceInfo();
    counter = 0;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  toggleRelay();
}

void toggleRelay() {
  relayState=!relayState;
  digitalWrite(RELAYPIN, relayState);
  //char buff;
  //sprintf(buff, "{\"value\":\"%d\"}", relayState);
  if (relayState == 0) { client.publish(relayOutbox, "{\"value\":\"OFF\"}"); }
  if (relayState == 1) { client.publish(relayOutbox, "{\"value\":\"ON\"}");  }   
  //client.publish(relayOutbox, buff);
  Wire.beginTransmission(8); //transmit to device #8
  Wire.write("S");
  Wire.endTransmission();
}

void updateDeviceInfo() {
  client.publish(deviceOutbox, deviceInfo);
  Serial.println(deviceInfo);
  }

  void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client165546648844654","/outbox/RELAY1LFM1/lwt",0,0,"offline")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      
      updateDeviceInfo();
      client.subscribe(relayInbox);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
