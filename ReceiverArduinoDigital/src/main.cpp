#include <Arduino.h>
const int LAMBDA_MIN = 500;
const int LAMBDA_MAX = 20000;
const int STEP = 30;

volatile unsigned long lastTime = 0;
volatile unsigned long highDuration = 0;
volatile unsigned long lowDuration = 0;
volatile unsigned long lambda = 0;

int lastData = 0;

int decodeData(int lambda) {
    return floor((double)(lambda - LAMBDA_MIN) / (LAMBDA_MAX - LAMBDA_MIN) * STEP);
}

void onChange() {
    unsigned long currentTime = micros();
    if (digitalRead(2)) {
        lowDuration = currentTime - lastTime;
    } else {
        highDuration = currentTime - lastTime;
    }
    lastTime = currentTime;

    if (highDuration < LAMBDA_MIN / 2 || LAMBDA_MAX / 2 < highDuration ||
        lowDuration < LAMBDA_MIN / 2 || LAMBDA_MAX / 2 < lowDuration) {
        return;
    }

    lambda = highDuration + lowDuration;
}

void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), onChange, CHANGE);
}

void loop() {
    const int data = decodeData(lambda);
    if (data != lastData) {
        Serial.println(data);
        lastData = data;
    }
}