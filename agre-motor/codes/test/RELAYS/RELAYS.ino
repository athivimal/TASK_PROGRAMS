
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  digitalWrite(D1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(D2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(D3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D3, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(D4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D4, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(D5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D5, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}
