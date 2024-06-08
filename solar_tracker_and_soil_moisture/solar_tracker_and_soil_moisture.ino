 
#define BLYNK_TEMPLATE_ID "TMPL6P1qhAgrQ"
#define BLYNK_TEMPLATE_NAME "Esp32 Wroom Test"
#define BLYNK_AUTH_TOKEN "49PHHeuZpBD-LmDL5vLJ0flup7ein-Ko"

#define SENSOR_PIN 35
#define WIFI_LED 2
#define MOTOR_RELAY 25

const char* WIFI_SSID = "SYED_AMIR_ALI";
const char* WIFI_PASSWORD = "syedamirali";

#include <WiFi.h>
#include <ESP32Servo.h>
#include <BlynkSimpleEsp32.h>

Servo myservo;
static const int servoPin = 4;

#define LDR_2 12 // ADC 15
#define LDR_1 14 // ADC 16 

int pos = 90; 
int Resistance = 20;  

String msg = "Motor Stopped. Water Level is Normal!";
float moisture = 0.00;
int switch_state = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(MOTOR_RELAY, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);
  connectToWiFi();
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

  // solar tracker
  myservo.attach(servoPin); 
  pinMode(LDR_1, INPUT); 
  pinMode(LDR_2, INPUT); 

  myservo.write(pos); 
  delay(1000); 
}

void loop() {
  Blynk.run();
  readSoilMoisture();
  updateStatus();
  delay(1000);

  // solar tracker
  solarTracker();
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
    delay(500);
  }
  Serial.println("\nConnected to WiFi");
  digitalWrite(WIFI_LED, HIGH);
}

void readSoilMoisture() {
  int value = analogRead(SENSOR_PIN);
  Serial.println(value);
  moisture = map(value, 0, 4095, 0, 100);
  moisture = (moisture - 100) * -1;

  if (moisture > 70) {
    stopMotor("Automatically Water Pump Stopped!");
  } else if (moisture < 30) {
    startMotor("Automatically Water Pump Started!");
  }

  Serial.print(msg);
  Serial.print("\tMoisture Lave => ");
  Serial.print(moisture); 
  Serial.println("%"); 
}

void updateStatus() {
  Blynk.virtualWrite(V0, moisture);
  Blynk.virtualWrite(V2, msg);
}

void startMotor(String message) {
  msg = message;
  digitalWrite(MOTOR_RELAY, HIGH);
}

void stopMotor(String message) {
  msg = message;
  digitalWrite(MOTOR_RELAY, LOW);
}

BLYNK_WRITE(V1) {
  switch_state = param.asInt();

  if (switch_state == 1) {
    if (moisture > 70 && digitalRead(MOTOR_RELAY) == HIGH) {
      stopMotor("Water Level Is Already Full. Motor Can't Start!");
    } else if (moisture < 100 && digitalRead(MOTOR_RELAY) == LOW) {
      startMotor("Manually Motor Started! Water Level is Rising.");
    }
  } else {
    if (moisture < 30 && digitalRead(MOTOR_RELAY) == HIGH) {
      stopMotor("Motor Can't Stop. Water Level is Very Low!");
    } else {
      stopMotor("Manually Motor Stopped! Water Level Is OK.");
    }
  }
}
 
void solarTracker(){      
  int value_1 = analogRead(LDR_1); 
  int value_2 = analogRead(LDR_2); 
        
  if((abs(value_1 - value_2) <= Resistance) || (abs(value_2 - value_1) <= Resistance)) {} else {
    if(value_1 > value_2) {
      pos = pos+1; 
    }
    if(value_1 < value_2) {
      pos = pos-1; 
    }
  }
      
  if(pos > 180) {pos = 180;} 
  if(pos < 0) {pos = 0;} 
  myservo.write(pos); 
  delay(50);
}
