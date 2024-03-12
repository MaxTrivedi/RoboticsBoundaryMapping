
#include <USBCore.h>
u8 USB_SendSpace(u8 ep);
#define SERIAL_ACTIVE (USB_SendSpace(CDC_TX) >= 50)

#include "motors.h"
#include "data.h"
#include "encoders.h"
#include "kinematics.h"

#define COLLECT_DATA 0
#define RETRIEVE_DATA   1

Motors_c motors;
Data data;
Kinematics_c kinematics;

int state = COLLECT_DATA;

void setup() {
    //setup components
    motors.init();
    setupEncoder0();
    setupEncoder1();

    //setup other
    pinMode(LED_BUILTIN, OUTPUT);
    
    // Configure the Serial port
    Serial.begin(9600);
}

void loop() {
    kinematics.update();
    if (state == COLLECT_DATA) {
        if(data.resultsFull()) {
          motors.setMotorPower( 0, 0);
          state = RETRIEVE_DATA;
        } else {
          motors.setMotorPower( 15, 15);
          float new_items[3] = {kinematics.Xt, kinematics.Yt, kinematics.Ot};
          data.updateResults(new_items);
          delay(10);
        }
    }
    else if (state == RETRIEVE_DATA) {
        data.reportResultsOverSerial();
        delay(3000);
    }
}
