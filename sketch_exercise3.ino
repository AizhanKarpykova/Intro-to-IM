const int LED = 9;
const int POT = A0;


void setup() {
Serial.begin(9600);
pinMode(LED, OUTPUT);


// Test the LED
digitalWrite(LED, HIGH);
delay(500);
digitalWrite(LED, LOW);
}


void loop() {
int p_value = analogRead(POT); // read from the potentiometer
int move = map(p_value, 0, 1023, -1, 2); // map the value to -1, 0, and 1
Serial.println(move);


if (Serial.available() > 0) {
// read from p5.js
int touch = Serial.parseInt();
// set the LED command
if (touch == 1) {
digitalWrite(LED, HIGH);
} else {
digitalWrite(LED, LOW);
}
}
}
