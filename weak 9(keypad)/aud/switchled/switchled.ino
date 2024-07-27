const int led1Pin = 3; // Pin for the first LED
const int led2Pin = 4; // Pin for the second LED
const int led3Pin = 5; // Pin for the third LED
const int led4Pin = 6; // Pin for the fourth LED

void setup() {
  pinMode(1, INPUT_PULLUP); // Set pin 1 as input with internal pull-up resistor
  pinMode(2, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
  pinMode(led1Pin, OUTPUT); // Set led1Pin as output
  pinMode(led2Pin, OUTPUT); // Set led2Pin as output
  pinMode(led3Pin, OUTPUT); // Set led3Pin as output
  pinMode(led4Pin, OUTPUT); // Set led4Pin as output
}

void loop() {
  int inp1 = digitalRead(1); // Read state of pin 1
  int inp2 = digitalRead(2); // Read state of pin 2
  
  if (inp1 == HIGH & inp2==HIGH) // Check if both pins are HIGH
  {
    digitalWrite(led1Pin, HIGH); // Turn on all LEDs
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, HIGH);
    delay(100); // Pause
    digitalWrite(led1Pin, LOW); // Turn off all LEDs
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
    delay(100); // Pause
  }
  else if(inp1 == LOW & inp2==HIGH) // Check if pin 1 is LOW and pin 2 is HIGH
  {
    digitalWrite(led1Pin, HIGH); // Turn on first LED
    delay(100); // Pause
    digitalWrite(led1Pin, LOW); // Turn off first LED
    digitalWrite(led2Pin, HIGH); // Turn on second LED
    delay(100); // Pause
    digitalWrite(led2Pin, LOW); // Turn off second LED
    digitalWrite(led3Pin, HIGH); // Turn on third LED
    delay(100); // Pause
    digitalWrite(led3Pin, LOW); // Turn off third LED
    digitalWrite(led4Pin, HIGH); // Turn on fourth LED
    delay(100); // Pause
    digitalWrite(led4Pin, LOW); // Turn off fourth LED
  }
  else if(inp1 == HIGH & inp2==LOW) // Check if pin 1 is HIGH and pin 2 is LOW
  {
    digitalWrite(led4Pin, HIGH); // Turn on fourth LED
    delay(100); // Pause
    digitalWrite(led4Pin, LOW); // Turn off fourth LED
    digitalWrite(led3Pin, HIGH); // Turn on third LED
    delay(100); // Pause
    digitalWrite(led3Pin, LOW); // Turn off third LED
    digitalWrite(led2Pin, HIGH); // Turn on second LED
    delay(100); // Pause
    digitalWrite(led2Pin, LOW); // Turn off second LED
    digitalWrite(led1Pin, HIGH); // Turn on first LED
    delay(100); // Pause
    digitalWrite(led1Pin, LOW); // Turn off first LED
  }
  else if(inp1 == LOW & inp2==LOW) // Check if both pins are LOW
  {
    digitalWrite(led1Pin, HIGH); // Turn on first LED
    digitalWrite(led2Pin, HIGH); // Turn on second LED
    digitalWrite(led3Pin, HIGH); // Turn on third LED
    digitalWrite(led4Pin, HIGH); // Turn on fourth LED
    digitalWrite(led1Pin, LOW); // Turn off first LED
    delay(100); // Pause
    digitalWrite(led1Pin, HIGH); // Turn on first LED
    digitalWrite(led2Pin, LOW); // Turn off second LED
    delay(100); // Pause
    digitalWrite(led2Pin, HIGH); // Turn on second LED
    digitalWrite(led3Pin, LOW); // Turn off third LED
    delay(100); // Pause
    digitalWrite(led3Pin, HIGH); // Turn on third LED
    digitalWrite(led4Pin, LOW); // Turn off fourth LED
    delay(100); // Pause
    digitalWrite(led4Pin, HIGH); // Turn on fourth LED
  }
}
