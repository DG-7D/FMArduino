#include <Arduino.h>
const int STEP = 100;
const int PRECISION = 112;
const int WIDTH = 10;
const int zeroLevel = 1024 / 2;

unsigned long lastTime = 0;

int lastValue = 0;
int lastValidValue = 0;

int decodeData(int interval) {
    return round(interval / PRECISION / (double)WIDTH) * STEP;
}

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    while (analogRead(A0) > zeroLevel * 1.1) {
    }
    while (analogRead(A0) < zeroLevel * 0.9) {
    }
    unsigned long currentTime = micros();
    unsigned long interval = currentTime - lastTime;
    lastTime = currentTime;

    const int value = decodeData(interval);
    if (value == lastValue) {
        if (value != lastValidValue) {
            Serial.println(value);
        }
        lastValidValue = value;
    }
    lastValue = value;
}