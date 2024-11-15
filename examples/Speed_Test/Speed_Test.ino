#include <Arduino.h>

#include "FastPin.h"

#define WRITE_PIN 2
#define READ_PIN 3

FastWritePin writePin(WRITE_PIN);
FastReadPin readPin(READ_PIN);

float avarageDuration(byte times, void (*func)()) {
    long startTime = micros();
    for (byte i = 0; i < times; i++) {
        func();
    }
    long endTime = micros();
    return static_cast<float>(endTime - startTime) / static_cast<float>(times) * 2.0;
}

void setup() {
    Serial.begin(115200);

    // digitalWrite
    pinMode(WRITE_PIN, OUTPUT);

    float avarage = avarageDuration(50, []() {
        digitalWrite(WRITE_PIN, HIGH);
        digitalWrite(WRITE_PIN, LOW);
    });
    Serial.print(F("AVG micros / digitalWrite: "));
    Serial.println(avarage);

    // FastWritePin
    writePin.begin();

    avarage = avarageDuration(50, []() {
        writePin.write(HIGH);
        writePin.write(LOW);
    });
    Serial.print(F("AVG micros / FAST dig. write: "));
    Serial.println(avarage);

    // digitalRead
    pinMode(READ_PIN, INPUT);

    float avarage = avarageDuration(50, []() {
        digitalRead(READ_PIN);
        digitalRead(READ_PIN);
    });
    Serial.print(F("AVG micros / digitalRead "));
    Serial.println(avarage);

    // FastReadPin
    readPin.begin();

    avarage = avarageDuration(50, []() {
        readPin.read();
        readPin.read();
    });
    Serial.print(F("AVG micros / FAST dig. read: "));
    Serial.println(avarage);
}

void loop() {}
