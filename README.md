# FastPin

An Arduino library for safe and high-speed digital read/write operations.

## Usage
``` cpp
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
```

> ⚠️ FastPin only disables PWM timers in `begin()`. DO NOT use `analogWrite()` on the same pin.


## Contributions Welcome

We're open to contributions, especially for improvements in speed and efficiency. Feel free to open issues or pull requests with optimizations, feature requests, or bug reports to help make this project even better. Your input is valuable and appreciated!