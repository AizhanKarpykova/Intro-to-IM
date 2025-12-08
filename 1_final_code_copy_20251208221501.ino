  /*
    Capacitive Sensor Sketch 
    Paul Badger 2008
  */

  #include <CapacitiveSensor.h>

  // Serial
  const long BAUD_RATE = 9600;

  // Sensor Pins 
  const int rightSendPin = 4;
  const int rightReceivePin = 2;

  const int leftSendPin = 7;
  const int leftReceivePin = 8;

  // LED Pins 
  const int led1 = 12;
  const int led2 = 13;

  // Sensor Settings 
  // Higher values improve stability but reduce speed
  const int sensorSamples = 30;

  // Baseline Settings 
  // Number of readings taken to establish baseline
  const int baselineReadings = 20;
  // Delay between baseline samples (ms)
  const int baselineDelay = 5;

  // Touch Sensitivity 
  // Threshold above baseline that indicates a touch
  const int touchOffset = 300;

  // Loop Delay 
  // Small delay to stabilize loop execution
  const int loopDelay = 10;

// Create capacitive sensor objects
  CapacitiveSensor rightSensor(rightSendPin, rightReceivePin);
  CapacitiveSensor leftSensor(leftSendPin, leftReceivePin);

 // Stores baseline capacitance values for each sensor
  long rightBase = 0;
  long leftBase = 0;

 // Tracks whether a sensor was previously touched
  bool rightTouched = false;
  bool leftTouched = false;

  void setup() {
    Serial.begin(BAUD_RATE);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

  // Calculate baseline readings for both sensors
    long rightSum = 0;
    long leftSum = 0;
// Measure baseline capacitance for each sensor
    for (int i = 0; i < baselineReadings; i++) {
      rightSum += rightSensor.capacitiveSensor(sensorSamples);
      leftSum  += leftSensor.capacitiveSensor(sensorSamples);
      delay(baselineDelay);
    }
 // Compute average baseline value
    rightBase = rightSum / baselineReadings;
    leftBase  = leftSum / baselineReadings;
  // Notify p5.js that Arduino is ready
    Serial.println("Arduino Ready with auto-baseline");
  }

  void loop() {
     // Read sensor values
    long rightValue = rightSensor.capacitiveSensor(sensorSamples);
    long leftValue  = leftSensor.capacitiveSensor(sensorSamples);

  // Determine if sensors are being touched
    bool rightActive = rightValue > (rightBase + touchOffset);
    bool leftActive  = leftValue  > (leftBase  + touchOffset);


 // Send RIGHT command only when the right sensor is newly touched
    if (rightActive && !rightTouched) {
      Serial.println("RIGHT");
    }
 // Send LEFT command only when the left sensor is newly touched
    if (leftActive && !leftTouched) {
      Serial.println("LEFT");
    }
  // Detect release: touch was active before but now inactive
    bool rightReleased = rightTouched && !rightActive;
    bool leftReleased  = leftTouched  && !leftActive;
// Send STOP only when both sensors are released
    if ((rightReleased || leftReleased) && !(rightActive || leftActive)) {
      Serial.println("STOP");
    }
  // Update current touch state
    rightTouched = rightActive;
    leftTouched  = leftActive;

   // Check for incoming commands from p5.js
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();

      if (command == "GAMEOVER_ON") {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
      }
  
      if (command == "GAMEOVER_OFF") {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
      }
    }

    delay(loopDelay);
  }
