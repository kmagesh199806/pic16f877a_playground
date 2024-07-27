#include <LiquidCrystal.h> // Include the LiquidCrystal library

LiquidCrystal lcd(13, 12, 7, 6, 5, 4, 3, 2, 1, 0); // Create an instance of the LiquidCrystal class

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  const char* array = "ORIG VAL:"; // Define a character array for the label "ORIG VAL:"
  const char* array1 = "CALIB VAL:"; // Define a character array for the label "CALIB VAL:"
  lcd.setCursor(0, 0); // Set the cursor position to the beginning of the first row
  for (int x = 0; x < 9; x++) {
    lcd.write(array[x]); // Write each character of "ORIG VAL:" to the LCD with a delay
    delay(50);
  }
  lcd.setCursor(0, 1); // Set the cursor position to the beginning of the second row
  for (int x = 0; x < 10; x++) {
    lcd.write(array1[x]); // Write each character of "CALIB VAL:" to the LCD with a delay
    delay(100);
  }
}

void loop() {
  int adc = analogRead(A0); // Read the analog input from pin A0
  lcd.setCursor(9, 0); // Set the cursor position for displaying the ADC value
  if (adc < 1000) 
    lcd.write(' '); // Add space for formatting if ADC value is less than 1000
  if (adc < 100) 
    lcd.write(' '); // Add space for formatting if ADC value is less than 100
  if (adc < 10) 
    lcd.write(' '); // Add space for formatting if ADC value is less than 10
  lcd.print(adc); // Display the ADC value on the LCD

  lcd.setCursor(10, 1); // Set the cursor position for displaying the voltage value
  int voltage = map(adc, 0, 1023, 0, 100); // Map the ADC value to a percentage
  if (voltage < 10) 
    lcd.write(' '); // Add space for formatting if voltage is less than 10
  if (voltage < 100)
    lcd.write(' '); // Add space for formatting if voltage is less than 100
  lcd.print(voltage); // Display the voltage percentage on the LCD

  delay(500); // Delay before reading the analog input again
}
