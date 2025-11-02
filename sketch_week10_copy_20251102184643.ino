// Pins
const int POTENTIOMETER_PIN = A0; // Analog input pin for potentiometer
const int BUTTON_PIN = 2; // Digital input pin for push button
const int RED = 5;  // Digital output pin for RGB LED (red)
const int GREEN = 6;  // Digital output pin for RGB LED (green)
const int YELLOW = 9; // Digital output pin for RGB LED (yellow)

// Variables
int potentiometerValue = 0; // Potentiometer value
bool buttonState = false; // Button state
int colorIndex = 0; // Index of current color

void setup() {
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

void loop() {
  potentiometerValue = analogRead(POTENTIOMETER_PIN);
  
  // Map potentiometer value to LED brightness
  int brightness = map(potentiometerValue, 0, 1023, 0, 255);
  
  // Set the LED color based on the current color index
  switch (colorIndex) {
    case 0:  // Red
      analogWrite(RED, brightness);
      analogWrite(GREEN, 0);
      analogWrite(YELLOW, 0);
      break;
    case 1:  // Green
      analogWrite(RED, 0);
      analogWrite(GREEN, brightness);
      analogWrite(YELLOW, 0);
      break;
    case 2:  // Yellow
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(YELLOW, brightness);
      break;
  }

  // Check button state
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!buttonState) {
      // Toggle color index
      colorIndex = (colorIndex + 1) % 3;
      buttonState = true;
      delay(200);
    }
  } else {
    buttonState = false;
  }
}