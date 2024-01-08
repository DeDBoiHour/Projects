#include <AccelStepper.h>
#include <NewPing.h>

// HC-SR04
#define TRIGGER_PIN  12  //trigger pin
#define ECHO_PIN     11  // echo pin 
#define MAX_DISTANCE 200 // Maximum distance (in cm).

// NewPing instance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

// Define stepper motor pins
#define STEPPER_PIN1 2
#define STEPPER_PIN2 3
#define STEPPER_PIN3 4
#define STEPPER_PIN4 5

// AccelStepper instance for motor
AccelStepper stepper(AccelStepper::FULL4WIRE, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

void setup() {
  Serial.begin(9600); // Initialize serial communication

  stepper.setMaxSpeed(2000); // maximum speed of motor
  stepper.setAcceleration(1000); // acceleration of motor
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read(); // serial input

    if (command == 'F') {
      stepper.setSpeed(100); // forward speed
      stepper.runSpeed();    // Motor moves forward
    } else if (command == 'B') {
      stepper.setSpeed(-100); // backward speed
      stepper.runSpeed();     // Motor moves backward
    } else if (command == 'S') {
      stepper.setSpeed(0); // Stop
      stepper.runSpeed();  // Stop the motor
    }
  }

  // Distance from HC-SR04 sensor
  unsigned int distance = sonar.ping_cm();

  // Send distance data via serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100); // Small delay so that it doesnt fry your CPU :D 
}
