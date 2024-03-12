#include "motors.h"
#include "frontsensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define LED_PIN 13  // Pin to activate the orange LED
#define BUZZER_PIN A7
#define NOTE_A4  440

boolean led_state;  // Variable to "remember" the state of the LED, and toggle it.
// Global definition of the time interval
# define FRONT_SENSOR_UPDATE 500
# define KINEMATICS_UPDATE  500

// Timestamps for different contexts.
unsigned long motor_ts;
unsigned long front_sensor_ts;
unsigned long kinematics_ts;
unsigned long turnStartTime;
float targetAngle;

Motors_c motors;
Kinematics_c kinematics;
FrontSensor_c frontsensor;

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

  // Set LED pin as an output
  pinMode( LED_PIN, OUTPUT );
  // Set initial state of the LED
  led_state = false;

  pinMode(BUZZER_PIN, OUTPUT);
  tone(BUZZER_PIN, NOTE_A4, 100);

}

// MAIN ----------------------------------------------------------------------------
int maxTurnPWM = 20;
int biasPWM = 30;

void loop() {
  unsigned long current_ts = millis();

  // Line Sensor Update
  if (current_ts - front_sensor_ts > FRONT_SENSOR_UPDATE) {
    frontsensor.readFrontSensors();
    front_sensor_ts = millis();
  }


  if (current_ts - kinematics_ts > KINEMATICS_UPDATE) {
    kinematics.update();
    kinematics_ts = millis();
    float x_position = kinematics.getX_position();
    float y_position = kinematics.getY_position();
    float theta = kinematics.getThetaDeg();
    Serial.print(x_position);
    Serial.print(",");
    Serial.print(y_position);
    Serial.print(",");
    Serial.println(theta);
  }


}
