#define BLYNK_TEMPLATE_ID "TMPLSgETUamP"
#define BLYNK_TEMPLATE_NAME "COLLAGE PROJECT"
#define BLYNK_AUTH_TOKEN "ddiE-cQ66l0XP2VAVwxpAY7R8G-GoDtG"
#define WIFI_SSID "SYED_AMIR_ALI"
#define WIFI_PASSWORD "syedamirali"

#include <WiFi.h>
#include <DHT11.h>
#include <IRremote.h>
#include <BlynkSimpleEsp32.h>

// define the GPIO connected with Relays and switches
#define RELAY_PIN_1 23  //D23
#define RELAY_PIN_2 22  //D22
#define RELAY_PIN_3 21  //D21
#define RELAY_PIN_4 19  //D19
#define MOTOR_RELAY_PIN 15 

// Define all Motor and sensor pins
#define SONAR_TRIG_PIN 4 // Ultrasonic sensor trigger pin  
#define SONAR_ECHO_PIN 5 // Ultrasonic sensor echo pin  
#define DHT_PIN 18 // DHT11 sensor pin  
#define CURRENT_SENSOR_PIN 33 // ACS-712 sensor pin  
#define VOLTAGE_SENSOR 32 // ZMPT101B sensor pin 
#define MOTOR_MANUAL_SWITCH_PIN 25 // Motor Relay pin  

#define wifiLed 2
int wifiFlag = 0;

#define SWITCH_PIN_1 13  //D13
#define SWITCH_PIN_2 12  //D12
#define SWITCH_PIN_3 14  //D14
#define SWITCH_PIN_4 27  //D27

#define VPIN_BUTTON_1            V1 
#define VPIN_BUTTON_2            V2
#define VPIN_BUTTON_3            V3 
#define VPIN_BUTTON_4            V4
#define WATER_LEVEL_VPIN         V5
#define CURRENT_RATE_VPIN        V6
#define VOLTAGE_RATE_VPIN        V7
#define TEMPERATURE_VPIN         V8
#define HUMIDITY_VPIN            V9
#define MOTOR_MANUAL_SWITCH_VPIN V0

//Define integer to remember the toggle state for relay
int toggleState_1 = 1;  
int toggleState_2 = 1;  
int toggleState_3 = 1; 
int toggleState_4 = 1; 


//Set Water Level Distance in CM
int 
emptyTankDistance = 70,  //Distance when tank is empty
fullTankDistance = 30,  //Distance when tank is full 
triggerPer = 10;  // alarm will start when water level drop below triggerPer

// initiate DHT11 sensor & blynk timer
DHT11 dht(DHT_PIN);
BlynkTimer timer;

float temperature = 0.00, humidity = 0.00, distance = 0.00, duration = 0.00, waterLevelPer = 0.00;

void setup(){
  Serial.begin(115200);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(SWITCH_PIN_4, INPUT_PULLUP);

  digitalWrite(RELAY_PIN_1, toggleState_1);
  digitalWrite(RELAY_PIN_2, toggleState_2);
  digitalWrite(RELAY_PIN_3, toggleState_3);
  digitalWrite(RELAY_PIN_4, toggleState_4);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
  Blynk.config(BLYNK_AUTH_TOKEN); // Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  delay(1000);

  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);

  pinMode(MOTOR_RELAY_PIN, OUTPUT);
  pinMode(MOTOR_MANUAL_SWITCH_PIN, INPUT_PULLUP);

  pinMode(SONAR_TRIG_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
}

void loop(){
  manualButton();
  activateDhtSensor();
  measureWaterLevel();

  if(WiFi.status() == WL_CONNECTED){
    Blynk.run();
  }

  timer.run();
  sp();
}

void relayOnOff(int relay){
  switch (relay) {
    case 1:
      if (toggleState_1 == 1) {
        digitalWrite(RELAY_PIN_1, LOW); // turn on relay 1
        toggleState_1 = 0;
        Serial.println("Device1 ON");
      } else {
        digitalWrite(RELAY_PIN_1, HIGH); // turn off relay 1
        toggleState_1 = 1;
        Serial.println("Device1 OFF");
      }
      delay(100);
      break;

    case 2:
      if (toggleState_2 == 1) {
        digitalWrite(RELAY_PIN_2, LOW); // turn on relay 2
        toggleState_2 = 0;
        Serial.println("Device2 ON");
      } else {
        digitalWrite(RELAY_PIN_2, HIGH); // turn off relay 2
        toggleState_2 = 1;
        Serial.println("Device2 OFF");
      }
      delay(100);
      break;

    case 3:
      if (toggleState_3 == 1) {
        digitalWrite(RELAY_PIN_3, LOW); // turn on relay 3
        toggleState_3 = 0;
        Serial.println("Device3 ON");
      } else {
        digitalWrite(RELAY_PIN_3, HIGH); // turn off relay 3
        toggleState_3 = 1;
        Serial.println("Device3 OFF");
      }
      delay(100);
      break;

    case 4:
      if (toggleState_4 == 1) {
        digitalWrite(RELAY_PIN_4, LOW); // turn on relay 4
        toggleState_4 = 0;
        Serial.println("Device4 ON");
      } else {
        digitalWrite(RELAY_PIN_4, HIGH); // turn off relay 4
        toggleState_4 = 1;
        Serial.println("Device4 OFF");
      }
      delay(100);
      break;
    default:
      break;
  }
}

void manualButton(){
  //Manual Switch Control
  if (digitalRead(SWITCH_PIN_1) == LOW){
    delay(200);
    relayOnOff(1);      
  }
  else if (digitalRead(SWITCH_PIN_2) == LOW){
    delay(200);
    relayOnOff(2);
  }
  else if (digitalRead(SWITCH_PIN_3) == LOW){
    delay(200);
    relayOnOff(3);
  }
  else if (digitalRead(SWITCH_PIN_4) == LOW){
    delay(200);
    relayOnOff(4);
  }
}

void allSwitchOff(){
  toggleState_1 = 1; digitalWrite(RELAY_PIN_1, toggleState_1);  delay(100);
  toggleState_2 = 1; digitalWrite(RELAY_PIN_2, toggleState_2);  delay(100);
  toggleState_3 = 1; digitalWrite(RELAY_PIN_3, toggleState_3);  delay(100);
  toggleState_4 = 1; digitalWrite(RELAY_PIN_4, toggleState_4);  delay(100);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RELAY_PIN_1, toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RELAY_PIN_2, toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RELAY_PIN_3, toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RELAY_PIN_4, toggleState_4);
}

BLYNK_WRITE(MOTOR_MANUAL_SWITCH_VPIN){
  int state = param.asInt();

  if(state == 1){
    if(waterLevelPer < 99){
      Serial.println("Blynk Motor Start...");
      digitalWrite(MOTOR_RELAY_PIN, HIGH);
    }

    if(waterLevelPer > 99) {
      Serial.println("Blynk Motor Stop by Tank Full...");
      digitalWrite(MOTOR_RELAY_PIN, LOW);
    }
  } else {
    Serial.println("Blynk Motor Stop...");
    digitalWrite(MOTOR_RELAY_PIN, LOW);
  }
}

void checkBlynkStatus() { 
  bool isconnected = Blynk.connected();

  if (isconnected == false) {
    wifiFlag = 1;
    digitalWrite(wifiLed, LOW); //Turn off WiFi LED
  }
  if (isconnected == true) {
    wifiFlag = 0;
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); 
    
    digitalWrite(wifiLed, HIGH); //Turn on WiFi LED
  }
}

void activateDhtSensor(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (humidity == DHT11::ERROR_CHECKSUM && humidity == DHT11::ERROR_TIMEOUT) { 
    Serial.println(DHT11::getErrorString(humidity)); 
  }

  if (temperature == DHT11::ERROR_CHECKSUM && temperature == DHT11::ERROR_TIMEOUT) { 
    Serial.println(DHT11::getErrorString(temperature)); 
  }

  Blynk.virtualWrite(HUMIDITY_VPIN, humidity);
  Blynk.virtualWrite(TEMPERATURE_VPIN, temperature);
}

void measureWaterLevel(){
  // Set the trigger pin LOW for 2uS
  digitalWrite(SONAR_TRIG_PIN, LOW);
  delayMicroseconds(2);
 
  // Set the trigger pin HIGH for 20us to send pulse
  digitalWrite(SONAR_TRIG_PIN, HIGH);
  delayMicroseconds(20);
 
  // Return the trigger pin to LOW
  digitalWrite(SONAR_TRIG_PIN, LOW);
 
  // Measure the width of the incoming pulse
  duration = pulseIn(SONAR_ECHO_PIN, HIGH);
  distance = ((duration / 2) * 0.343) / 10;

  if(distance <= fullTankDistance){
    waterLevelPer = 100.00;
  }

  if (distance > (fullTankDistance - 10)  && distance < emptyTankDistance ){
    waterLevelPer = map((int)distance ,emptyTankDistance, fullTankDistance, 0, 100);
  }

  if(distance >= emptyTankDistance){
    waterLevelPer = 0.00;
  }

  if(waterLevelPer < 10){
    Serial.println("Manual Water Pump is ON");

    digitalWrite(MOTOR_RELAY_PIN, HIGH);
    Blynk.virtualWrite(MOTOR_MANUAL_SWITCH_VPIN, 1);
  }

  if(waterLevelPer > 99){
    Serial.println("Auto Water Pump is OFF");

    digitalWrite(MOTOR_RELAY_PIN, LOW);
    Blynk.virtualWrite(MOTOR_MANUAL_SWITCH_VPIN, 0);
  }

  if(digitalRead(MOTOR_MANUAL_SWITCH_PIN) == LOW && waterLevelPer < 90){
    Serial.println("Manual Water Pump is ON");
    
    digitalWrite(MOTOR_RELAY_PIN, HIGH);
    Blynk.virtualWrite(MOTOR_MANUAL_SWITCH_VPIN, 1);
  } 
  
  if(digitalRead(MOTOR_MANUAL_SWITCH_PIN) == LOW && waterLevelPer > 99) {
    Serial.println("Tank Already Full.");
    
    digitalWrite(MOTOR_RELAY_PIN, LOW);
    Blynk.virtualWrite(MOTOR_MANUAL_SWITCH_VPIN, 0);
  }

  // Delay & actions before repeating measurement
  Blynk.virtualWrite(WATER_LEVEL_VPIN, waterLevelPer);
  delay(100);
}

void sp(){
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" %");

  Serial.print("\tDistance => ");
  Serial.print(distance);
  Serial.print(" cm");

  Serial.print("\tWater Level => ");
  Serial.print(waterLevelPer);
  Serial.println(" %");
  
  delay(1000);
}















































