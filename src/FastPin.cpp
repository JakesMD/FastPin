#include "FastPin.h"

FastWritePin::FastWritePin(byte pin) { _pin = pin; }

void FastWritePin::begin(bool initialVal) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, initialVal);  // Turns off PWM timers.

    byte port = digitalPinToPort(_pin);
    _bitMask = digitalPinToBitMask(_pin);
    _outputRegister = port != NOT_A_PIN ? portOutputRegister(port) : NULL;
}

void FastWritePin::write(bool val) {
    if (_outputRegister == NULL) return;

    byte oldSREG = SREG;
    cli();

    if (val == LOW) {
        *_outputRegister &= ~_bitMask;
    } else {
        *_outputRegister |= _bitMask;
    }

    SREG = oldSREG;
}

FastReadPin::FastReadPin(byte pin) { _pin = pin; }

void FastReadPin::begin(bool pullup) {
    if (pullup) {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
    digitalRead(_pin);  // Turns off PWM timers.

    byte port = digitalPinToPort(_pin);
    _bitMask = digitalPinToBitMask(_pin);
    _inputRegister = port != NOT_A_PIN ? portInputRegister(port) : NULL;
}

bool FastReadPin::read() { return (_inputRegister != NULL && *_inputRegister & _bitMask) ? HIGH : LOW; }