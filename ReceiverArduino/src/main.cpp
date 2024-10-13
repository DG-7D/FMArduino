#include <Arduino.h>
const int STEP = 100;
const int PRECISION = 112;
const int WIDTH = 10;
const int zeroLevel = 1024 / 2;

int count = 0;
unsigned long lastTime = 0;

int decodeData(int interval) {
    return round(interval / PRECISION / (double)WIDTH) * STEP;
}

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    while (analogRead(A0) > zeroLevel) {
    }
    while (analogRead(A0) < zeroLevel) {
    }
    unsigned long currentTime = micros();
    unsigned long interval = currentTime - lastTime;
    lastTime = currentTime;
    count++;
    if (count == 50) {
        Serial.println(decodeData(interval));
        count = 0;
    }
}