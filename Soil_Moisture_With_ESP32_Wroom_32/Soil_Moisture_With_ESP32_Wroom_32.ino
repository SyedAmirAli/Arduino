#define BLYNK_TEMPLATE_ID "TMPL6P1qhAgrQ"
#define BLYNK_TEMPLATE_NAME "Esp32 Wroom Test"
#define BLYNK_AUTH_TOKEN "49PHHeuZpBD-LmDL5vLJ0flup7ein-Ko"

#define SENSOR_PIN 35
#define WIFI_LED 2
#define MOTOR_RELAY 25

const char* WIFI_SSID = "Girls Project";
const char* WIFI_PASSWORD = "12345678";

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

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
}

void loop() {
  Blynk.run();
  readSoilMoisture();
  updateStatus();
  delay(1000);
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









// #define BLYNK_TEMPLATE_ID "TMPL6P1qhAgrQ"
// #define BLYNK_TEMPLATE_NAME "Esp32 Wroom Test"
// #define BLYNK_AUTH_TOKEN "49PHHeuZpBD-LmDL5vLJ0flup7ein-Ko"
// #define WIFI_SSID "SYED_AMIR_ALI"
// #define WIFI_PASSWORD "syedamirali"

// #include <WiFi.h>
// #include <BlynkSimpleEsp32.h>

// #define SENSOR_PIN 35
// #define WIFI_LED 2
// #define MOTOR_RELAY 34

// String msg = "Motor Stoped. Water Level is Normal!";
// float moisture = 0.00;
// int switch_state = 0; 

// void setup() {
//   // Debug console
//   Serial.begin(705200);
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//   pinMode(MOTOR_RELAY, OUTPUT);
//   pinMode(WIFI_LED, OUTPUT);

//   Serial.print("Connecting");
//   while (WiFi.status() != WL_CONNECTED){
//     Serial.print(".");

//     digitalWrite(WIFI_LED, LOW);
//     delay(500);
//     digitalWrite(WIFI_LED, HIGH);
//     delay(500); 
//   }

//   digitalWrite(WIFI_LED, HIGH);
//   digitalWrite(MOTOR_RELAY, LOW); 

//   Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD); 
// }

// void loop() {
//   soilMoisture();
//   Blynk.run();//Run the Blynk library
//   wifiLedOn();
  
//   delay(200);
// }

// void wifiLedOn(){
//   if(WiFi.status() == WL_CONNECTED){
//     digitalWrite(WIFI_LED, HIGH);
//   }
// }

// //Get the ultrasonic SENSOR_PIN values
// void soilMoisture() {
//   int value = analogRead(SENSOR_PIN);

//   Serial.print("Analog 'SENSOR' Value: ");
//   Serial.print(value);

//   value = map(value, 0, 4095, 0, 100);
//   moisture = (value - 100) * -1;

//   Blynk.virtualWrite(V0, moisture);
//   // Blynk.virtualWrite(V2, msg);

//   Serial.print("\t  Maping => ");
//   Serial.print(moisture); 
//   Serial.println("%"); 

//   if(moisture > 70){
//     msg = "Automatically Water Pump Stopped!";
        
//     Blynk.virtualWrite(V2, msg);
//     digitalWrite(MOTOR_RELAY, LOW); 
//   } else if(moisture < 30){
//     msg = "Automatically Water Pump Stared!";
        
//     Blynk.virtualWrite(V2, msg);
//     digitalWrite(MOTOR_RELAY, HIGH); 
//   } 
// }

// //Get the button value
// BLYNK_WRITE(V1) {
//   switch_state = param.asInt();

//   if(switch_state == 1){
//     if(moisture > 70 && digitalRead(MOTOR_RELAY) == HIGH){
//       msg = "Water Lavel Is Already Full. Motor Cann't Sart!";
        
//       Blynk.virtualWrite(V2, msg);
//       digitalWrite(MOTOR_RELAY, LOW); 
//     }

//     if(moisture < 100 && digitalRead(MOTOR_RELAY) == LOW){
//       msg = "Manually Motor were Started!";
          
//       Blynk.virtualWrite(V2, msg);
//       digitalWrite(MOTOR_RELAY, HIGH); 
//     }
//   } else {
//     if(moisture < 30 && digitalRead(MOTOR_RELAY) == HIGH){
//       msg = "Motor Cann't Stopping. Water Level is Very Low!";
        
//       Blynk.virtualWrite(V2, msg);
//       digitalWrite(MOTOR_RELAY, HIGH); 
//     } else {
//       msg = "Manually Motor were Stopped!";
          
//       Blynk.virtualWrite(V2, msg);
//       digitalWrite(MOTOR_RELAY, LOW); 
//     } 
//   }
// }


    // if (val == 1) {
    //   if(moisture > 70){
    //     msg = "Water Lavel Is Already Full.";
        
    //     Blynk.virtualWrite(V2, msg);
    //     digitalWrite(MOTOR_RELAY, LOW); 
    //   } else {
    //     digitalWrite(MOTOR_RELAY, LOW);  
    //   }
    // } else {
    //   if(moisture < 30){
    //     msg = "Motor cann't OFF. Water Level is very LOW.";
        
    //     Blynk.virtualWrite(V2, msg);
    //     digitalWrite(MOTOR_RELAY, HIGH); 
    //   } else {
    //     digitalWrite(MOTOR_RELAY, HIGH);  
    //   }
    // }