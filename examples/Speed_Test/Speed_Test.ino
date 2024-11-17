#include <Arduino.h>

#include "FastPin.h"

#define WRITE_PIN 2
#define READ_PIN 3
#define EXECUTIONS_PER_AVERAGE 1000
#define AVERAGES_PER_TEST 1000

FastWritePin writePin(WRITE_PIN);
FastReadPin readPin(READ_PIN);

float avarageDuration(void (*func)()) {
    long startTime, endTime;
    float totalAvg = 0;

    for (int i = 0; i < AVERAGES_PER_TEST; i++) {
        startTime = micros();
        for (int j = 0; j < EXECUTIONS_PER_AVERAGE; j++) {
            func();
        }
        endTime = micros();
        totalAvg += static_cast<float>(endTime - startTime) / static_cast<float>(EXECUTIONS_PER_AVERAGE);
    }

    return totalAvg / static_cast<float>(AVERAGES_PER_TEST);
}

void setup() {
    Serial.begin(115200);

    // digitalWrite
    pinMode(WRITE_PIN, OUTPUT);

    float avarage = avarageDuration([]() { digitalWrite(WRITE_PIN, LOW); });
    Serial.print(F("AVG micros / digitalWrite: "));
    Serial.println(avarage);

    // FastWritePin
    writePin.begin();

    float fastAvarage = avarageDuration([]() { writePin.write(LOW); });
    Serial.print(F("AVG micros / FastWritePin: "));
    Serial.println(fastAvarage);

    // Write results
    Serial.print(F("FastWritePin is "));
    Serial.print(avarage / fastAvarage);
    Serial.println(F(" times faster than digitalWrite.\n"));

    // digitalRead
    pinMode(READ_PIN, INPUT);

    avarage = avarageDuration([]() { digitalRead(READ_PIN); });
    Serial.print(F("AVG micros / digitalRead: "));
    Serial.println(avarage);

    // FastReadPin
    readPin.begin();

    fastAvarage = avarageDuration([]() { readPin.read(); });
    Serial.print(F("AVG micros / FastReadPin: "));
    Serial.println(fastAvarage);

    // Read results
    Serial.print(F("FastReadPin is "));
    Serial.print(avarage / fastAvarage);
    Serial.println(F(" times faster than digitalRead."));
}

void loop() {}
