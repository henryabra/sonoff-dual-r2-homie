//
// Created by Henry Abravanel on 11/04/2018.
//

#ifndef SONOFF_DUAL_HOMIE2_RELAYDATA_H
#define SONOFF_DUAL_HOMIE2_RELAYDATA_H

#include <Homie.h>

#define TRUE "true"
#define FALSE "false"

class Relay {
private:
    const uint8_t pin;
    const uint8_t externalPin;
    HomieNode node;
    int externalPinState;

public:
    Relay(const char *id, const char *type, uint8_t pin, uint8_t externalPin);

    bool isOn();

    void toggle();

    void checkAndApplyExternalSwitch();

private:
    bool handler(const HomieRange &range, const String &value);

    void setRelayState(bool state);
};


#endif //SONOFF_DUAL_HOMIE2_RELAYDATA_H
