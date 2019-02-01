# Growtent Germination Sensors
![Picture of sensors in HA](picture.png?raw=true)
## Introduction
The sensors here are used to monitor the enviorment in a growtent compartment used for germinating seedlings.

Sensors provided:

 - Soil moisture
 - Ambient humidity and air temperature

## Parts
 - ESP8266 (NodeMCU type)
 - DHT11 temperature and humidity sensor
 - Resistive moisture probe. like 50c USD on eBay. Search "Soil moisture sensor esp8266"
 - 5V, 1A DC power supply
 - Breadboard and wires (or you can solder directly, if you want)

## Wiring
![Wiring on breadboard (not a sketch)](wiring_actual.jpg?raw=true)
Below is the written version
 - NodeMCU A0 to resistive sensor data pin
 - NodeMCU D2 to DHT11 data pin
 - NodeMCU 3V3 to + bus
 - NodeMCU GND to - bus
 - Resistive sensor VIN to + bus
 - Resistive sensor GND to - bus
 - DHT11 VIN to + bus
 - DHT11 GND to - bus
 - 5V power supply to NodeMCU VIN
 - 5V power supply ground to - bus
 
TODO: Sketch of wiring

## Config
See config.h and input WiFi information alongside MQTT broker and topics.
