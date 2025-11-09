 #include "pitches.h" 

int BUZZER = 6;
int BUTTON = 13;
int ECHO_PIN = 4;       
int TRIG_PIN = 5;

bool sensorActive = true;  // true = sensor working, false = paused
bool lastButtonState = HIGH;

void setup() {
  pinMode(ECHO_PIN, INPUT);    // echo pin measure the duration of pulses coming back from the distance sensor
  pinMode(TRIG_PIN, OUTPUT);   // trigger pin output pulses of electricity
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // button connects to GND when pressed
  Serial.begin(9600);
}

void loop() {

  bool buttonState = digitalRead(BUTTON);

  // When button is pressed (LOW) and was not pressed before → toggle
  if (buttonState == LOW && lastButtonState == HIGH) {
    sensorActive = !sensorActive;
    if (!sensorActive) {
      noTone(BUZZER);
      Serial.println("Sensor paused");
    } else {
      Serial.println("Sensor active");
    }
    delay(300); // simple cooldown to avoid double toggling
  }

  lastButtonState = buttonState;

  if (sensorActive) {
    int distance = getDistance();
    Serial.println(distance);
    if (1 < distance && distance < 5) {
      tone(BUZZER, NOTE_C4);
    } else if (5 < distance && distance < 10) {
      tone(BUZZER, NOTE_D4);
    } else if (10 < distance && distance < 15) {
      tone(BUZZER, NOTE_E4);
    } else if (15 < distance && distance < 20) {
      tone(BUZZER, NOTE_F4);
    } else if (20 < distance && distance < 25) {
      tone(BUZZER, NOTE_G4);
    } else if (25 < distance && distance < 30) {
      tone(BUZZER, NOTE_A4);
    } else if (30 < distance && distance < 35) {
      tone(BUZZER, NOTE_B4);
    } else {
      noTone(BUZZER);
    }
  }
}

float getDistance() {
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  echoTime = pulseIn(ECHO_PIN, HIGH);      //pulsein command to see how long it takes for pulse to bounce back to sensor
  calculatedDistance = echoTime / 55.2;    //calculate  distance of object that reflected the pulse in cm 
  return calculatedDistance;
}
