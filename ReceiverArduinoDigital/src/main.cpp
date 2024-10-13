#include <Arduino.h>
const int STEP = 100;
const int PRECISION = 4;
const int WIDTH = 300;

volatile unsigned long lastTime = 0;
volatile unsigned long highDuration = 0;
volatile unsigned long lowDuration = 0;
volatile unsigned long interval = 0;

int lastData = 0;
int lastValidData = 0;

int decodeData(int interval) {
    return round(interval / PRECISION / (double)WIDTH) * STEP;
}

void onChange() {
    unsigned long currentTime = micros();
    if (digitalRead(2)) {
        lowDuration = currentTime - lastTime;
    } else {
        highDuration = currentTime - lastTime;
    }
    if (abs(highDuration - lowDuration) < PRECISION * WIDTH) {
        interval = highDuration + lowDuration;
        return;
    }
    lastTime = currentTime;
}

void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), onChange, CHANGE);
}

void loop() {
    const int data = decodeData(interval);
    if (data == lastData) {
        if (data != lastValidData) {
            Serial.println(data);
        }
        lastValidData = data;
    }
    lastData = data;
}