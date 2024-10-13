#include <Arduino.h>
const int LAMBDA_MIN = 500;
const int LAMBDA_MAX = 20000;
const int STEP = 30;
const int zeroLevel = 1024 / 2;

unsigned long lastTime = 0;

int lastData = 0;

int decodeData(int lambda) {
    return floor((double)(lambda - LAMBDA_MIN) / (LAMBDA_MAX - LAMBDA_MIN) * STEP);
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
    unsigned long lambda = currentTime - lastTime;
    lastTime = currentTime;

    if (lambda < LAMBDA_MIN || LAMBDA_MAX < lambda) {
        return;
    }

    const int data = decodeData(lambda);
    if (data != lastData) {
        Serial.println(data);
        lastData = data;
    }
}