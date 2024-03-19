#ifndef _FRONTSENSOR_H
#define _FRONTSENSOR_H
#define EMIT_PIN    11    // Infra-red LEDs pin
#define LEFT_BUMP_PIN   5    // Analog pin for left bumper sensor
#define RIGHT_BUMP_PIN  4    // Analog pin for right bumper sensor

class FrontSensor_c {
public:
    FrontSensor_c() {
    }

    void initialise() {
        pinMode(EMIT_PIN, OUTPUT);
        digitalWrite(EMIT_PIN, LOW);
        Serial.begin(9600);
        Serial.println("***RESET***LINESENSOR");
    }

    unsigned long readLeftSensor() {
        pinMode(EMIT_PIN, OUTPUT);
        digitalWrite(EMIT_PIN, LOW);
        pinMode(LEFT_BUMP_PIN, OUTPUT);
        digitalWrite(LEFT_BUMP_PIN, HIGH);
        delayMicroseconds(10);
        pinMode(LEFT_BUMP_PIN, INPUT);

        unsigned long start_time = micros();
        while (digitalRead(LEFT_BUMP_PIN) == HIGH) {}
        unsigned long end_time = micros();

        digitalWrite(EMIT_PIN, HIGH);
        return end_time - start_time;
    }

    unsigned long readRightSensor() {
        pinMode(EMIT_PIN, OUTPUT);
        digitalWrite(EMIT_PIN, LOW);
        pinMode(RIGHT_BUMP_PIN, OUTPUT);
        digitalWrite(RIGHT_BUMP_PIN, HIGH);
        delayMicroseconds(10);
        pinMode(RIGHT_BUMP_PIN, INPUT);

        unsigned long start_time = micros();
        while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {}
        unsigned long end_time = micros();

        digitalWrite(EMIT_PIN, HIGH);
        return end_time - start_time;
    }
};

#endif
