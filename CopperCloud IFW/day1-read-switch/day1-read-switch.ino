/* Sketch to read state of a PIN */

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600); // serail communication to monitor - baud rate
  pinMode(04, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  // digitalWrite(13, LOW);    // this is how we write to a PIN
  int pinValue = digitalRead(04);             // this is how we read a PIN
  Serial.print("Pin:");
  Serial.println(pinValue);
  delay(100);
}
