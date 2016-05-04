// based on https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library
// MQ135 library from https://github.com/GeorgK/MQ135

#include <Homie.h>
#include <MQ135.h>

#define FW_NAME         "wemos-mq135"
#define FW_VERSION      "0.0.1"

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

#define SENSOR_PIN      A0
#define PUB_INTERVAL    5   // seconds

MQ135 gasSensor = MQ135(SENSOR_PIN);

HomieNode co2Node("co2", "sensor");

unsigned long lastPublish = 0;

void loopHandler() {
  if (millis() - lastPublish >= PUB_INTERVAL * 1000UL) {  
    float rzero = gasSensor.getRZero();
    float ppm = gasSensor.getPPM();

    // calibration only
    Homie.setNodeProperty(co2Node, "rzero", String(rzero), false);

    // ppm measurement
    if (Homie.setNodeProperty(co2Node, "ppm", String(ppm), false)) {
      lastPublish = millis();
    }
  }
}

void setup() {
  Homie.setFirmware(FW_NAME, FW_VERSION);

  Homie.registerNode(co2Node);
  
  Homie.setLoopFunction(loopHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
