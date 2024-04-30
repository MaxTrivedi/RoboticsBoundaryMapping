#include <USBCore.h>
u8 USB_SendSpace(u8 ep);
#define SERIAL_ACTIVE (USB_SendSpace(CDC_TX) >= 50)

#define COLLECT_DATA 0
#define RETRIEVE_DATA   1

#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
#include "frontsensor.h"
#include "data.h"

Motors_c motors;
Kinematics_c kinematics;
Data_c data;
FrontSensor_c frontsensor;
int state = COLLECT_DATA;

unsigned long last_sensor_reading_ts;

void setup() {
    //setup components
    motors.init();
    frontsensor.initialise();
    setupEncoder0();
    setupEncoder1();

    //setup other
    pinMode(LED_BUILTIN, OUTPUT);
    last_sensor_reading_ts = millis();
    
    // Configure the Serial port
    Serial.begin(9600);
    delay(3000);
}

void loop() {
    if (state == COLLECT_DATA) {
      // kinematics.Ot < -3.1415926535897932384626433832795/3 for angle experiment
      if (kinematics.Xt < -5 || data.resultsFull()) {
        motors.setMotorPower(0, 0);
        state = RETRIEVE_DATA;
        int new_items[6] = {0, 0, (float)(millis()-last_sensor_reading_ts), kinematics.Xt, kinematics.Yt, kinematics.Ot*180/3.1415926535897932384626433832795};
      }
      else{
        //motors.setMotorPower(15, -13); for angle experiment
        motors.setMotorPower(-14, -13);
        if (millis() - last_sensor_reading_ts > 20) {
            last_sensor_reading_ts = millis();
            unsigned long leftSensorReading = frontsensor.readLeftSensor();
            unsigned long rightSensorReading = frontsensor.readRightSensor();
            kinematics.update();
            float new_items[6] = {leftSensorReading, rightSensorReading, (float)(millis()-last_sensor_reading_ts), (float) kinematics.Xt, (float) kinematics.Yt, (float) kinematics.Ot};
            data.updateResults(new_items);
            Serial.print(kinematics.Xt);
            Serial.print(", ");
            Serial.print(kinematics.Yt);
            Serial.print(", ");
            Serial.print(kinematics.Ot);
            Serial.print("\n");
          }
      }
    } if (state == RETRIEVE_DATA) {
      Serial.print(kinematics.Xt);
      Serial.print(", ");
      Serial.print(kinematics.Yt);
      Serial.print(", ");
      Serial.print(kinematics.Ot);
      Serial.print("\n");
      data.reportResultsOverSerial();
      motors.setMotorPower(0, 0);
      delay(3000);
    }
}
