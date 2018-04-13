#include "Relay.h"

Relay::Relay(const char *id, const char *type, const uint8_t pin, const uint8_t externalPin) : pin(pin),
                                                                                               externalPin(externalPin),
                                                                                               node(id, type) {
    pinMode(pin, OUTPUT);
    pinMode(externalPin, INPUT_PULLUP);
    digitalWrite(pin, LOW);
    externalPinState = digitalRead(externalPin);
    node.advertise("on").settable([&](const HomieRange &range, const String &value) -> bool {
        return handler(range, value);
    });
    Homie.getLogger() << "Created Relay [" << id << "] pin [" << pin << "] external pin [" << externalPin
                      << "] external pin state [" << externalPinState << "]" << endl;
}

bool Relay::isOn() {
    return digitalRead(pin) == HIGH;
}

void Relay::toggle() {
    setRelayState(!isOn());
}

void Relay::setRelayState(bool state) {
    digitalWrite(pin, static_cast<uint8_t>(state ? HIGH : LOW));
    bool on = isOn();
    node.setProperty("on").send(on ? TRUE : FALSE);
}

void Relay::checkAndApplyExternalSwitch() {
    int currentExternalPinState = digitalRead(externalPin);
    bool differs = currentExternalPinState != externalPinState;
    if (differs) {
        externalPinState = currentExternalPinState;
        toggle();
    }
}

bool Relay::handler(const HomieRange &range, const String &value) {
    if (value != TRUE && value != FALSE) {
        return false;
    }
    setRelayState(value == TRUE);
    return true;
}
