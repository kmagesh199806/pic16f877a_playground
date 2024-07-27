#include <LiquidCrystal.h> // Include the LiquidCrystal library
// Initialize the LiquidCrystal display with the specified pin numbers
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}
void loop() {
  char pr[15]={"RX DATA:"}; // Define a character array for the label "RX DATA:"
  char prt[15]={"TX DATA:"}; // Define a character array for the label "TX DATA:" 
  lcd.setCursor(0,0); // Set the cursor position to the beginning of the first row
  for(int i=0;i<8;i++) // Loop to write the characters of the "RX DATA:" label
    lcd.write(pr[i]); // Write each character to the LCD
  lcd.setCursor(0,1); // Set the cursor position to the beginning of the second row
  for(int i=0;i<8;i++) // Loop to write the characters of the "TX DATA:" label
    lcd.write(prt[i]); // Write each character to the LCD 
  // Check if there is serial data available
  while (Serial.available() >= 0) {
    char receivedData = Serial.read(); // Read the incoming serial data
    // Check the received data and update the LCD and send back modified data via serial
    if (receivedData == 'A') {
      lcd.setCursor(8, 0); // Set the cursor position for displaying received data
      lcd.write(receivedData); // Write the received data to the LCD
      receivedData = 'a'; // Modify the received data
      Serial.write(receivedData); // Send back modified data via serial
      lcd.setCursor(8, 1); // Set the cursor position for displaying modified data
      lcd.write('a'); // Write the modified data to the LCD
    } else if (receivedData == 'B') {
      // Repeat the above steps for other received characters ('B', 'C', 'D')
    } else if (receivedData == 'C') {
      // Repeat the above steps for other received characters ('B', 'C', 'D')
    } else if (receivedData == 'D') {
      // Repeat the above steps for other received characters ('B', 'C', 'D')
    }
  }
}
