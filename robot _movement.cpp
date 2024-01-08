#include <AccelStepper.h>
#include <NewPing.h>

// Define HC-SR04 ultrasonic sensor pins
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).

// Create NewPing instance for HC-SR04
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

// Define stepper motor pins
#define STEPPER_PIN1 2
#define STEPPER_PIN2 3
#define STEPPER_PIN3 4
#define STEPPER_PIN4 5

// Create AccelStepper instance for stepper motor
AccelStepper stepper(AccelStepper::FULL4WIRE, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

void setup() {
  Serial.begin(9600); // Initialize serial communication

  stepper.setMaxSpeed(2000); // Set maximum speed of the stepper motor
  stepper.setAcceleration(1000); // Set acceleration of the stepper motor
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read serial input

    // Perform actions based on received commands
    if (command == 'F') {
      stepper.setSpeed(100); // Set forward speed
      stepper.runSpeed();    // Move the stepper motor forward
    } else if (command == 'B') {
      stepper.setSpeed(-100); // Set backward speed
      stepper.runSpeed();     // Move the stepper motor backward
    } else if (command == 'S') {
      stepper.setSpeed(0); // Stop the stepper motor
      stepper.runSpeed();  // Stop the motor
    }
  }

  // Read distance from HC-SR04 sensor
  unsigned int distance = sonar.ping_cm();

  // Send distance data via serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100); // Small delay
}
