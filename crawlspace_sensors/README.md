# Crawlspace Sensors
## Introduction
These sensors are used to monitor the enviorment underneath a home without a foundation. Useful for monitoring the main water line to prevent it from freezing, and knowing if there are significant air leaks.

Sensors provided:

 - Main waterline temperature
 - TODO: Humidity and ambient air temperature

## Parts
 - ESP8266
 - DS18B20 in waterproof cable form, as long as needed to reach near middle of waterline
 - Electrical tape, pipe insulation to hold sensor in place on waterline & prevent false readings from air
 - 5V, 1A power supply
 - Box & hardware to protect from weather

## Wiring
TODO: Document what was done

## Config
See config.h and input WiFi information alongside MQTT broker and topic.

## Reliability
With a well sealed box, I've been running this feeding into homeassistant since late 2017 without a hiccup in Northern Alberta, Canada. It's allowed me to just glance to see if freezing would be an issue without having to crawl under the house and check. Which is very nice in the -30 to -40c weather.
