#include "DHT.h"
#include "PubSubClient.h"
#include "ESP8266WiFi.h"

#include "config.h"

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);

  dht.begin();

  setup_wifi(); // Start up Wi-Fi
  client.setServer(mqtt_server, 1883); // Set up MQTT connection
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client_growtent")) {
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
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) { // Retry connection to MQTT server until it is connected
    reconnect();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    delay(2000);
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.println(humidity);
  client.publish(topic_h, String(humidity).c_str(), true);
  Serial.print("Temperature: ");
  Serial.println(temp);
  client.publish(topic_t, String(temp).c_str(), true);

  float moisture_percentage;
  float raw_moisture;

  raw_moisture = analogRead(SSPIN);
  moisture_percentage = constrain(map(raw_moisture, 860, 380, 0, 100), 0, 100);

  Serial.print("Soil Moisture = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  client.publish(topic_m, String(moisture_percentage).c_str(), true);

  delay(300000);
}
