#include <Homie.h>
#include "Relay.h"

// Generic Configuration
#define FW_NAME "sonoff-dual-R2-homie"
#define FW_VERSION "1.0.0"
#define APP_BAUD_RATE 115200

// Pin Layout
#define RESET_BUTTON_PIN    10
#define LED_PIN             13
#define RELAY1_PIN          12
#define RELAY2_PIN          5
#define RELAY1_EXT_PIN      9
#define RELAY2_EXT_PIN      0

//Relay Configuration
#define RELAY1_ID "relay1"
#define RELAY2_ID "relay2"

Relay *relay1;
Relay *relay2;

void externalPinsLoop() {
    relay1->checkAndApplyExternalSwitch();
    relay2->checkAndApplyExternalSwitch();
};

void setup() {
    Serial.begin(APP_BAUD_RATE);
    Homie.getLogger() << endl << "Starting setup" << endl;
    relay1 = new Relay(RELAY1_ID, "switch", RELAY1_PIN, RELAY1_EXT_PIN);
    relay2 = new Relay(RELAY2_ID, "switch", RELAY2_PIN, RELAY2_EXT_PIN);
    Homie.getLogger() << endl << "Done pin setup" << endl;

    Homie_setFirmware(FW_NAME, FW_VERSION);
    Homie.setLedPin(LED_PIN, LOW)
            .setLoopFunction(externalPinsLoop)
            .setResetTrigger(RESET_BUTTON_PIN, LOW, 2000);

    Homie.setup();
}

void loop() {
    Homie.loop();
}
