// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

const float wheel_diameter = 31;  // wheel diameter in mm
const float wheel_circumference = PI * wheel_diameter;
const int countsPerRevolution = 90;
const float wheel_base = 81; // distance between wheels in mm
float theta_deg;

float calculateDistance(int counter) {
    float revolutions = (float)counter / (float)countsPerRevolution;
    float distance = revolutions * wheel_circumference;
    return distance; // distance in mm
}

// Class to track robot position.
class Kinematics_c {
  private:
    float theta = 0.0; // total rotation in radians
    float theta_deg = 0;
    float x_position = 0.0; // x position in mm
    float y_position = 0.0; // y position in mm
    int last_count_e_left = 0; // previous left encoder count
    int last_count_e_right = 0; // previous right encoder count
    float distanceMovedLeftPrev = 0.0; // previous left wheel distance
    float distanceMovedRightPrev = 0.0; // previous right wheel distance

  public:
    Kinematics_c() {
    }
      void update() {
      int delta_count_left = count_e_left - last_count_e_left;
      int delta_count_right = count_e_right - last_count_e_right;

      float distanceMovedLeft = calculateDistance(count_e_left);
      float distanceMovedRight = calculateDistance(count_e_right);

      float deltaDistanceLeft = distanceMovedLeft - distanceMovedLeftPrev;
      float deltaDistanceRight = distanceMovedRight - distanceMovedRightPrev;
/*
      Serial.print("Left wheel distance Moved: ");
      Serial.print(deltaDistanceLeft);
      Serial.println(" mm");

      Serial.print("Right wheel distance Moved: ");
      Serial.print(deltaDistanceRight);
      Serial.println(" mm");
*/
      float delta_d = deltaDistanceLeft - deltaDistanceRight;
      theta = theta + delta_d / wheel_base; // Theta will be in radians

      float averageDistance = (deltaDistanceLeft + deltaDistanceRight) / 2.0;
      x_position = x_position + averageDistance * cos(theta);
      y_position = y_position + averageDistance * sin(theta);

      // Update previous values
      last_count_e_left = count_e_left;
      last_count_e_right = count_e_right;
      distanceMovedLeftPrev = distanceMovedLeft;
      distanceMovedRightPrev = distanceMovedRight;

      theta_deg = theta * 180.0 / PI;
      
    }
    float getThetaDeg() const {
        return theta_deg;
    }

    float getX_position() const {
        return x_position;
    }
    float getY_position() const {
        return y_position;
    }

    float returnHome_distance() const {
        return sqrt(x_position * x_position + y_position * y_position);
    }

    float returnHome_angle() const {
        // Calculate the angle to turn to face the origin
        float angle_to_origin = atan2(-y_position, -x_position); // Angle in radians

        // Convert current bearing to radians
        float theta_rad = theta_deg * M_PI / 180.0;

        // Calculate the relative angle to turn, convert it back to degrees
        float turn_angle = (angle_to_origin - theta_rad) * 180.0 / M_PI;

        // Normalize the angle to the range [-180, 180] degrees
        while (turn_angle > 180) turn_angle -= 360;
        while (turn_angle < -180) turn_angle += 360;

        return turn_angle;
    }
};



#endif
