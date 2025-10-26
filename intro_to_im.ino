int ledBlue = 8;      // Blue LED pin
int ledYellow = 4;    // Yellow LED pin
int foilSwitch = 2;   // Foil switch pin

void setup() {
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  digitalWrite(foilSwitch, HIGH);
  // pinMode(foilSwitch, INPUT); // use external pull-down resistor
}

void loop() {
  int switchState = digitalRead(foilSwitch); // read foil switch

  if (switchState == LOW) {  // foils touching
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledYellow, HIGH);
    delay(500);                    // on for 500ms
    digitalWrite(ledYellow, LOW);
    delay(500);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledYellow, LOW);
  }
}






