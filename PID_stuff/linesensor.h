// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

# define EMIT_PIN    11       // Documentation says 11.
# define LS_LEFT_PIN A11     // Complete for DN1 pin
# define LS_MIDLEFT_PIN A0  // Complete for DN2 pin
# define LS_MIDDLE_PIN A2   // Complete for DN3 pin
# define LS_MIDRIGHT_PIN A3 // Complete for DN4 pin
# define LS_RIGHT_PIN A4    // Complete for DN5 pin
// The pin used to activate the IR LEDs
# define EMIT_PIN 11

# define left_thres 810
# define mid_thres 800
# define right_thres 790

float LR_sum = 0.0;
float W = 0.0;

// Class to operate the linesensor(s).
class LineSensor_c {
  public:

    // Store our pin numbers into an array.  We can then
    // use this as a "find and replace" for the pin number
    // using just an index of the array from 0 to 4 (1-5)
    int ls_pins[5] = {LS_LEFT_PIN,
                      LS_MIDLEFT_PIN,
                      LS_MIDDLE_PIN,
                      LS_MIDRIGHT_PIN,
                      LS_RIGHT_PIN
                     };

    // Global "permanent" store of line sensor values
    int ls_value[5] = {500,
                       500,
                       500,
                       500,
                       500
                      };

    // Constructor, must exist.
    LineSensor_c() {

    }

    void readLineSensor( int which_sensor ) {
      if ( which_sensor >= 0 && which_sensor <= 4) {
        ls_value[ which_sensor ] = analogRead( ls_pins[ which_sensor ] );
      }

    }

    void updateSensors( ) {

      // Loop across all sensors.
      for ( int i = 0; i < 5; i++ ) {
        readLineSensor( i );
      }
    }

    void initialise() {

      // Loop across each pin, setting pinMode().
      for ( int i = 0; i < 5; i++ ) {
        pinMode(ls_pins[ i ], INPUT_PULLUP);

        // Configure the EMIT pin as output and
        // high.  This will active some infra-red
        // (IR) LEDs for our sensors to read.
        pinMode( EMIT_PIN, OUTPUT );
        digitalWrite( EMIT_PIN, HIGH );
      }
    }
    bool onLine() {
      // returns true if any sensors are over threshold
      if (ls_value[1] > left_thres || ls_value[2] > mid_thres || ls_value[3] > right_thres) {
        return true;
      } else {
        return false;
      }
    }
    float weightedMeasurement() {
      // Ex3
      LR_sum = ls_value[1] + ls_value[3];
      W = 2 * (ls_value[1] - ls_value[3]) / LR_sum;
      return W;
    }


};



#endif
