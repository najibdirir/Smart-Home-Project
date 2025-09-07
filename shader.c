#include "One_for_all_header.h"


void light_2_servo(void) {
  if(light_flag_servo && servo_activator == 2){
      light_flag_servo =0;
      measure_light();// Update light sensor readings
   }  
    int light_difference = light_sensor_1 - light_sensor_2;

    // Determine the appropriate servo position based on light difference
    int servo_position = determineServoPosition(light_difference);

    // Move the servo to the calculated position
    move_servo(servo_position);
    //delay(1000); // Delay between measurements
}

int determineServoPosition(int light_difference) {
  // Define thresholds for movement
    const int THRESHOLD_SMALL = 50; // Small movement threshold
    const int THRESHOLD_MEDIUM = 150; // Medium movement threshold
    const int THRESHOLD_LARGE = 300; // Large movement threshold

    // Determine the servo position based on light difference
    if (light_difference >= THRESHOLD_LARGE) {
        return 160; // Maximum right turn
    } else if (light_difference >= THRESHOLD_MEDIUM) {
        return 130; // Medium right turn
    } else if (light_difference >= THRESHOLD_SMALL) {
        return 100; // Small right turn
    } else if (light_difference <= -THRESHOLD_LARGE) {
        return 0; // Maximum left turn
    } else if (light_difference <= -THRESHOLD_MEDIUM) {
        return 30; // Medium left turn
    } else if (light_difference <= -THRESHOLD_SMALL) {
        return 60; // Small left turn
    } else {
        return 90; // No turn or minimal adjustment
    }
}