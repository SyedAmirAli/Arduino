#include "ACS712.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Define ACS712 parameters based on datasheet
#define ACS_PIN A0 
#define SUPPLY_VOLTAGE 5.0 // VCC = 5V
#define MAX_ADC_VALUE 1023
#define SENSITIVITY_MV_PER_A 66 // Sensitivity: 66 mV/A for ACS712 30A module

ACS712 ACS(ACS_PIN, SUPPLY_VOLTAGE, MAX_ADC_VALUE, SENSITIVITY_MV_PER_A);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and dimensions (16 columns, 2 rows)

int humidity = 0;
float temperature, distance = 0.00, duration = 0.00, waterLevelPer = 0.00, voltage = 0.00, current = 0.00, power = 0.00;

unsigned long previousMillis = 0;  // Variable to store the previous millis value
int counter = 0;  // Initialize counter

void setup() {
  Serial.begin(115200);
  ACS.autoMidPoint();

  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
}

void loop() {
  loaderCounter();

  measureCurrent();
  readDataFromESP32();
  counterChanger();
  
  runDisplay();
  // delay(100);
}

void measureCurrent(){
  float average = 0, voltage = 208.00;

  uint32_t start = millis();
  for (int i = 0; i < 100; i++) {
    average += ACS.mA_AC();
  }
  uint32_t duration = millis() - start;
  
  float mA = average / 100.0;
  current = mA / 1000;

  Serial.print("CURRENT_MA:");
  Serial.println(mA);
}

void counterChanger() {
  unsigned long currentMillis = millis();  // Get the current time
  
  // Check if 10 seconds have elapsed
  if (currentMillis - previousMillis >= 16000) {
    // Increment the counter
    counter++;

    if (counter > 5) {
      counter = floor(counter % 5);
    } 
    
    previousMillis = currentMillis;
  }
  
  Serial.print("Counter: ");
  Serial.println(counter);
}

void readDataFromESP32() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    
    // Find the index of the delimiters
    int temperatureIndex = data.indexOf(',');
    int humidityIndex = data.indexOf(',', temperatureIndex + 1);
    int distanceIndex = data.indexOf(',', humidityIndex + 1);
    int waterLevelIndex = data.indexOf(',', distanceIndex + 1);
    int voltageIndex = data.indexOf(',', waterLevelIndex + 1);
    int currentMilliIndex = data.indexOf(',', voltageIndex + 1);
    int currentAmpereIndex = data.indexOf(',', currentMilliIndex + 1);
    
    // Extract each substring containing the value
    String temperatureStr = data.substring(0, temperatureIndex);
    String humidityStr = data.substring(temperatureIndex + 1, humidityIndex);
    String distanceStr = data.substring(humidityIndex + 1, distanceIndex);
    String waterLevelStr = data.substring(distanceIndex + 1, waterLevelIndex);
    String voltageStr = data.substring(waterLevelIndex + 1, voltageIndex);
    String currentMilliStr = data.substring(voltageIndex + 1, currentMilliIndex);
    String currentAmpereStr = data.substring(currentMilliIndex + 1, currentAmpereIndex);

    // Convert each substring to float
    temperature = temperatureStr.toFloat();
    humidity = humidityStr.toFloat();
    distance = distanceStr.toFloat();
    waterLevelPer = waterLevelStr.toFloat();
    voltage = voltageStr.toFloat();
    float currentMilli = currentMilliStr.toFloat();
    float currentAmpere = currentAmpereStr.toFloat();

    delay(100);  // Delay to display each value for 2 seconds
  }
}

int loader = 1;

void runDisplay(){
  lcd.clear();

  switch (counter) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Tempare: ");
      lcd.print(temperature);
      lcd.print("'C");
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.print(humidity);
      lcd.print("%");
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Voltage: ");
      lcd.print(voltage);
      lcd.print("V");
      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Current: ");
      lcd.print(current);
      lcd.print("A");
      break;
      
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("Water:  ");
      lcd.print(waterLevelPer);
      lcd.print("%");
      break;

    default:
      break;
  }
  
  // lcd.setCursor(0, 1);
  // lcd.print("     ______     ");
}

void loaderCounter() {
  loader++;
  if (loader > 16) {
    loader = 1;
  }

  lcd.setCursor(0, 1);
  for (int i = 0; i <= 16; i++) { // Changed condition from i >= 16 to i < 16
    if (i < loader) {
      lcd.print("_");
    } else {
      lcd.print(" "); // Print a space if the position is beyond the loader value
    }
  }
  // loader++;
  // delay(300);
}

