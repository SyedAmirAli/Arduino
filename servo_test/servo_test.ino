#define BLYNK_TEMPLATE_ID "TMPLSgETUamP"
#define BLYNK_TEMPLATE_NAME "COLLAGE PROJECT"
#define BLYNK_AUTH_TOKEN "ddiE-cQ66l0XP2VAVwxpAY7R8G-GoDtG"

#include <DHT11.h>
#include <WiFi.h>
#include <AceButton.h>
#include <BlynkSimpleEsp32.h>
using namespace ace_button;

// Define all Motor and sensor pins
#define SONAR_TRIG_PIN 12 // Ultrasonic sensor trigger pin  
#define SONAR_ECHO_PIN 13 // Ultrasonic sensor echo pin  
#define DHT_PIN 14 // DHT11 sensor pin  
#define CURRENT_SENSOR_PIN 27 // ACS-712 sensor pin  
#define VOLTAGE_SENSOR 26 // ZMPT101B sensor pin 

// Define all the switch pins
#define SWITCH_1 4  
#define SWITCH_2 23  
#define SWITCH_3 22  
#define SWITCH_4 19  
#define MOTOR_MANUAL_SWITCH_PIN 25 // Motor Relay pin  

// AceButton button1(SWITCH_1);
// AceButton button2(SWITCH_2);
// AceButton button3(SWITCH_3);
// AceButton button4(SWITCH_4);

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);

// Define all the relay pins
const int RELAY_1 = 33; 
const int RELAY_2 = 32; 
const int RELAY_3 = 18; 
const int RELAY_4 = 21; 
const int MOTOR_RELAY_PIN = 15; 

bool STATE_1 = LOW;
bool STATE_2 = LOW;
bool STATE_3 = LOW;
bool STATE_4 = LOW;


// Define all the blynk virtual pin'v variables
#define WATER_LEVEL_VPIN V5
#define CURRENT_RATE_VPIN V6
#define VOLTAGE_RATE_VPIN V7
#define TEMPERATURE_VPIN V8
#define HUMIDITY_VPIN V9

#define SWITCH_1_VPIN V1
#define SWITCH_2_VPIN V2
#define SWITCH_3_VPIN V3
#define SWITCH_4_VPIN V4
#define MOTOR_MANUAL_SWITCH_VPIN V0

// wifi and password
const char* ssid = "SYED_AMIR_ALI";
const char* password = "syedamirali";

// initiate DHT11 sensor
DHT11 dht(DHT_PIN);
int temperature = 0.00, humidity = 0.00, distance = 0.00;

void setup(){
  Serial.begin(115200);
  connectToWiFi();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  pinMode(MOTOR_RELAY_PIN, OUTPUT);
  pinMode(MOTOR_MANUAL_SWITCH_VPIN, INPUT_PULLUP);

  pinMode(SONAR_TRIG_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);

  button1.init(SWITCH_1);
  button2.init(SWITCH_2);
  button3.init(SWITCH_3);
  button4.init(SWITCH_4);
}

void loop(){
  Blynk.run();

  // run all the utility functions
  activateDhtSensor();
  measureWaterLevel();

  button1.check();
  button2.check();
  button3.check();
  button4.check();

  delay(100); // Execution after every seconds
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RELAY_1, STATE_1);
      STATE_1 = !STATE_1;
      Blynk.virtualWrite(SWITCH_1_VPIN, STATE_1);
      // my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_1);
      break;
  }
}
void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RELAY_2, STATE_2);
      STATE_2 = !STATE_2;
      Blynk.virtualWrite(SWITCH_2_VPIN, STATE_2);
      // my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_2);
      break;
  }
}
void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RELAY_3, STATE_3);
      STATE_3 = !STATE_3;
      Blynk.virtualWrite(SWITCH_3_VPIN, STATE_3);
      // my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_3);
      break;
  }
}
void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RELAY_4, STATE_4);
      STATE_4 = !STATE_4;
      Blynk.virtualWrite(SWITCH_4_VPIN, STATE_4);
      // my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_4);
      break;
  }
}


void activateDhtSensor(){
  int result = dht.readTemperatureHumidity(temperature, humidity);

  if(result == 0){
    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.print(" °C\tHumidity: ");
    // Serial.print(humidity);
    // Serial.println(" %");
  } else {
    Serial.println(DHT11::getErrorString(result));
  }

  Blynk.virtualWrite(HUMIDITY_VPIN, humidity);
  Blynk.virtualWrite(TEMPERATURE_VPIN, temperature);
}


void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
  }
}

BLYNK_WRITE(SWITCH_1_VPIN){
  STATE_1 = param.asInt(); 
  digitalWrite(RELAY_1, STATE_1);
}

BLYNK_WRITE(SWITCH_2_VPIN){
  STATE_2 = param.asInt(); 
  digitalWrite(RELAY_2, STATE_2);
}

BLYNK_WRITE(SWITCH_3_VPIN){
  STATE_3 = param.asInt(); 
  digitalWrite(RELAY_3, STATE_3);
}

BLYNK_WRITE(SWITCH_4_VPIN){
  STATE_4 = param.asInt(); 
  digitalWrite(RELAY_4, STATE_4);

}


void measureWaterLevel(){
  long duration;

  digitalWrite(SONAR_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIG_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(SONAR_TRIG_PIN, LOW);

  duration = pulseIn(SONAR_ECHO_PIN, HIGH);
  distance = (duration * 0.343) / 2;

  // Serial.print("Distance => ");
  // Serial.print(distance);
  // Serial.println(" cm");

  Blynk.virtualWrite(WATER_LEVEL_VPIN, distance);
}


























