#include "DallasTemperature.h"
#include "OneWire.h"
#include "PubSubClient.h"
#include "ESP8266WiFi.h"

#include "config.h"

OneWire wMainWire(WMAIN_PIN);
DallasTemperature wMainTemp(&wMainWire);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial) { }
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client_crawlspace")) {
    // if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
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

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(MQTT_SERVER, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  float temp;
  
  do {
    wMainTemp.requestTemperatures(); 
    temp = wMainTemp.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.println(temp);
  } while (temp == 85.0 || temp == (-127.0));

  client.publish(WMAIN_TOPIC, String(temp).c_str(), true);
  delay(1000);
  
  client.disconnect();

  Serial.println("Published!");
  delay(300000);
}
