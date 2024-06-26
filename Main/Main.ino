#include <USBCore.h>
u8 USB_SendSpace(u8 ep);
#define SERIAL_ACTIVE (USB_SendSpace(CDC_TX) >= 50)

#include "motors.h"
#include "frontsensor.h"
#include "data.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define LED_PIN 13  // Pin to activate the orange LED
#define BUZZER_PIN A7
#define NOTE_A4  440
#define COLLECT_DATA 0
#define RETRIEVE_DATA   1

boolean led_state;  // Variable to "remember" the state of the LED, and toggle it.
// Global definition of the time interval
# define KINEMATIC_SENSOR_UPDATE  25

// Timestamps for different contexts.
unsigned long motor_ts;
unsigned long front_sensor_ts;
unsigned long kinematics_ts;
unsigned long last_sensor_reading_ts;
unsigned long turnStartTime;
float targetAngle;

Motors_c motors;
Kinematics_c kinematics;
Data_c data;
FrontSensor_c frontsensor;
int state = COLLECT_DATA;

// SETUP ---------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("***RESET***");

  motors.initialise();
  frontsensor.initialise();

  setupEncoder0();
  setupEncoder1();

  // Set initial timestamp values
  motor_ts       = millis();
  front_sensor_ts = millis();
  last_sensor_reading_ts = millis();

  // Set LED pin as an output
  pinMode( LED_PIN, OUTPUT );
  // Set initial state of the LED
  led_state = false;

  pinMode(BUZZER_PIN, OUTPUT);
  tone(BUZZER_PIN, NOTE_A4, 100);
  delay(3000);

}

// MAIN ----------------------------------------------------------------------------
void loop() {
  unsigned long current_ts = millis();

  if (current_ts - kinematics_ts > KINEMATIC_SENSOR_UPDATE) {
    kinematics.update();
    kinematics_ts = millis();
    float x_position = kinematics.getX_position();
    float y_position = kinematics.getY_position();
    float theta = kinematics.getThetaDeg();
    frontsensor.initialise();

    if (state == COLLECT_DATA) {
      if (data.resultsFull()) {
        motors.setMotorPower(0, 0);
        state = RETRIEVE_DATA;
      } else {
        motors.setMotorPower(15, -15);
        if (millis() - last_sensor_reading_ts > 200) {
          last_sensor_reading_ts = millis();
          unsigned long leftSensorReading = frontsensor.readLeftSensor();
          unsigned long rightSensorReading = frontsensor.readRightSensor();
          float new_items[6] = {leftSensorReading, rightSensorReading, (float)(millis()-last_sensor_reading_ts), x_position, y_position, theta};
          data.updateResults(new_items);
        }
      }
    }
    else if (state == RETRIEVE_DATA) {
      data.reportResultsOverSerial();
      motors.setMotorPower(0, 0);
      delay(3000);

    }
  }
}
