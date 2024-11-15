#include <FastPin.h>

FastWritePin ledPin(LED_BUILTIN);

void setup() { ledPin.begin(); }

void loop() {
    ledPin.write(HIGH);
    delay(1000);
    ledPin.write(LOW);
    delay(1000);
}
