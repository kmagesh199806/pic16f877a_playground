void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(5, OUTPUT); //set the pin 5 as output
  pinMode(6, OUTPUT); //set the pin 5 as output
  pinMode(7, OUTPUT); //set the pin 5 as output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH); //set the 5 pin as 1
  delay(1000); 
  digitalWrite(5, LOW); //set the 5 pin as 0
  delay(1000); 
  digitalWrite(6, HIGH); //set the 6 pin as 1
  delay(1000); 
  digitalWrite(6, LOW); //set the 5 pin as 0
  delay(1000); 
  digitalWrite(7, HIGH); //set the 7 pin as 1
  delay(1000); 
  digitalWrite(7, LOW); //set the 5 pin as 0
  delay(1000); 
}