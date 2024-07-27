#include <LiquidCrystal.h> // Include the LiquidCrystal library

LiquidCrystal lcd(13,12,7,6,5,4,3,2,1,0); // Create an instance of the LiquidCrystal class

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
}

void loop() {
  char array = "MAGESH"; // Define a character array with the name "array"
  unsigned char cmd1[6] = {0, 1, 2, 3, 4, 5}; // Define an array of unsigned characters for the first row commands
  unsigned char cmd2[6] = {15, 14, 13, 12, 11, 10}; // Define an array of unsigned characters for the second row commands

  for (int x = 0; x < 6; x++) {
    lcd.setCursor(cmd1[x], 0); // Set the cursor position for the first row
    lcd.write(array[x]); // Write the character from the array to the LCD
    delay(100); // Pause for 100 milliseconds
  }

  for (int j = 0; j < 6; j++) {
    lcd.setCursor(cmd2[j], 1); // Set the cursor position for the second row
    lcd.write(array[j]); // Write the character from the array to the LCD
    delay(100); // Pause for 100 milliseconds
  }
}
