// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  long data = analogRead(A0);   // turn the LED on (HIGH is the voltage level)
  Serial.println(data);
  delay(1000);                       // wait for a second
}
