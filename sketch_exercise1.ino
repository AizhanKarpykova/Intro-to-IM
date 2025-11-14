int LED = A0;

void setup() {
Serial.begin(9600);
pinMode(LED, INPUT);
}

void loop() {
int sensorValue = analogRead(A0);
Serial.println(sensorValue);
delay(5);
}
