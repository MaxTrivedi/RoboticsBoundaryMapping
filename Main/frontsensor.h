// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _FRONTSENSOR_H
#define _FRONTSENSOR_H
#define EMIT_PIN    11    // Infra-red LEDs pin
#define LEFT_BUMP_PIN   5    // Analog pin for left bumper sensor
#define RIGHT_BUMP_PIN  4    // Analog pin for right bumper sensor

// Class to operate the linesensor(s).
class FrontSensor_c {
  public:
    // Constructor, must exist.
    FrontSensor_c() {
    }
    // initialise pins and motor states.
    void initialise() {
      // Set initial pin modes and states
      pinMode(EMIT_PIN, OUTPUT); // Set EMIT as an output
      digitalWrite(EMIT_PIN, LOW); // Turn off IR LEDs initially

      // Start Serial, wait to connect, print a debug message.
      Serial.begin(9600);
      Serial.println("***RESET***LINESENSOR");
    }

    float readFrontSensors() {
      // Enable IR LEDs
      pinMode(EMIT_PIN, OUTPUT);
      digitalWrite(EMIT_PIN, LOW);

      // Prepare sensor reading for left bumper
      pinMode(LEFT_BUMP_PIN, OUTPUT);
      digitalWrite(LEFT_BUMP_PIN, HIGH);
      delayMicroseconds(10);
      pinMode(LEFT_BUMP_PIN, INPUT);
      unsigned long start_time_left = micros();
      while (digitalRead(LEFT_BUMP_PIN) == HIGH) {
        // Waiting for left bumper sensor
      }
      unsigned long end_time_left = micros();

      // Prepare sensor reading for right bumper
      pinMode(RIGHT_BUMP_PIN, OUTPUT);
      digitalWrite(RIGHT_BUMP_PIN, HIGH);
      delayMicroseconds(10);
      pinMode(RIGHT_BUMP_PIN, INPUT);
      unsigned long start_time_right = micros();
      while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {
        // Waiting for right bumper sensor
      }
      unsigned long end_time_right = micros();

      // Turn off IR LEDs
      pinMode(EMIT_PIN, INPUT);

      unsigned long elapsed_time_left = end_time_left - start_time_left;
      unsigned long elapsed_time_right = end_time_right - start_time_right;


      // Print the sensor values to the Serial monitor
      //Serial.print("Left Bumper Sensor Value: ");
      Serial.print(elapsed_time_left);
      Serial.print(',');
      //Serial.print(", Right Bumper Sensor Value: ");
      Serial.print(elapsed_time_right);
      Serial.print(',');
    }
};



#endif
