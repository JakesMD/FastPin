#include <FastPin.h>

FastWritePin ledPin(LED_BUILTIN);
FastReadPin buttonPin(2);

void setup() {
    ledPin.begin();
    buttonPin.begin(true);
}

void loop() {
    ledPin.write(buttonPin.read());
    delay(50);
}
