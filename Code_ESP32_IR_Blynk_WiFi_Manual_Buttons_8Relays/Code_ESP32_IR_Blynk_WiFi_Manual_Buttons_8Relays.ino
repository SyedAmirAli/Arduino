 /**********************************************************************************
 *  TITLE: Blynk + IR + Manual (Push-Button) control 8-Channel Relays using ESP32 with Realtime Feedback & No WiFi control
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/2HxWGHXyCt4
 *  Related Blog : https://iotcircuithub.com/esp32-projects/
 *  by Tech StudyCell
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board ESP32 : https://github.com/espressif/arduino-esp32
 *  
 *  Download the Libraries:
 *  Blynk Library: https://github.com/blynkkk/blynk-library/releases/download/v0.6.1/Blynk_Release_v0.6.1.zip
 *  IRremote Library: https://github.com/Arduino-IRremote/Arduino-IRremote
 **********************************************************************************/
#define BLYNK_TEMPLATE_ID "TMPLSgETUamP"
#define BLYNK_TEMPLATE_NAME "COLLAGE PROJECT"

#include <IRremote.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer1;

// define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19
#define RelayPin5 18  //D18
#define RelayPin6 5   //D5
#define RelayPin7 25  //D25
#define RelayPin8 26  //D26

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27
#define SwitchPin5 33  //D33
#define SwitchPin6 32  //D32
#define SwitchPin7 15  //D15
#define SwitchPin8 4   //D4

#define wifiLed     2   //D2
#define IR_RECV_PIN 35  //D35

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_5    V5 
#define VPIN_BUTTON_6    V6
#define VPIN_BUTTON_7    V7 
#define VPIN_BUTTON_8    V8
#define VPIN_BUTTON_9    V9

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 4
int toggleState_5 = 1; //Define integer to remember the toggle state for relay 5
int toggleState_6 = 1; //Define integer to remember the toggle state for relay 6
int toggleState_7 = 1; //Define integer to remember the toggle state for relay 7
int toggleState_8 = 1; //Define integer to remember the toggle state for relay 8

int wifiFlag = 0;

IRrecv irrecv(IR_RECV_PIN);
decode_results results;


#define AUTH "ddiE-cQ66l0XP2VAVwxpAY7R8G-GoDtG"                 // You should get Auth Token in the Blynk App.  
#define WIFI_SSID "SYED_AMIR_ALI"             //Enter Wifi Name
#define WIFI_PASS "syedamirali"         //Enter wifi Password

void relayOnOff(int relay){
  switch (relay) {
    case 1:
      if (toggleState_1 == 1) {
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 0;
        Serial.println("Device1 ON");
      } else {
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 1;
        Serial.println("Device1 OFF");
      }
      delay(100);
      break;
    case 2:
      if (toggleState_2 == 1) {
        digitalWrite(RelayPin2, LOW); // turn on relay 2
        toggleState_2 = 0;
        Serial.println("Device2 ON");
      } else {
        digitalWrite(RelayPin2, HIGH); // turn off relay 2
        toggleState_2 = 1;
        Serial.println("Device2 OFF");
      }
      delay(100);
      break;
    case 3:
      if (toggleState_3 == 1) {
        digitalWrite(RelayPin3, LOW); // turn on relay 3
        toggleState_3 = 0;
        Serial.println("Device3 ON");
      } else {
        digitalWrite(RelayPin3, HIGH); // turn off relay 3
        toggleState_3 = 1;
        Serial.println("Device3 OFF");
      }
      delay(100);
      break;
    case 4:
      if (toggleState_4 == 1) {
        digitalWrite(RelayPin4, LOW); // turn on relay 4
        toggleState_4 = 0;
        Serial.println("Device4 ON");
      } else {
        digitalWrite(RelayPin4, HIGH); // turn off relay 4
        toggleState_4 = 1;
        Serial.println("Device4 OFF");
      }
      delay(100);
      break;
    case 5:
      if (toggleState_5 == 1) {
        digitalWrite(RelayPin5, LOW); // turn on relay 5
        toggleState_5 = 0;
        Serial.println("Device5 ON");
      } else {
        digitalWrite(RelayPin5, HIGH); // turn off relay 5
        toggleState_5 = 1;
        Serial.println("Device5 OFF");
      }
      delay(100);
      break;
    case 6:
      if (toggleState_6 == 1) {
        digitalWrite(RelayPin6, LOW); // turn on relay 6
        toggleState_6 = 0;
        Serial.println("Device6 ON");
      } else {
        digitalWrite(RelayPin6, HIGH); // turn off relay 6
        toggleState_6 = 1;
        Serial.println("Device6 OFF");
      }
      delay(100);
      break;
    case 7:
      if (toggleState_7 == 1) {
        digitalWrite(RelayPin7, LOW); // turn on relay 7
        toggleState_7 = 0;
        Serial.println("Device7 ON");
      } else {
        digitalWrite(RelayPin7, HIGH); // turn off relay 7
        toggleState_7 = 1;
        Serial.println("Device7 OFF");
      }
      delay(100);
      break;
    case 8:
      if (toggleState_8 == 1) {
        digitalWrite(RelayPin8, LOW); // turn on relay 8
        toggleState_8 = 0;
        Serial.println("Device8 ON");
      } else {
        digitalWrite(RelayPin8, HIGH); // turn off relay 8
        toggleState_8 = 1;
        Serial.println("Device8 OFF");
      }
      delay(100);
      break;
    default:
      break;
  }
}

void manual_button(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      relayOnOff(1);      
    }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      relayOnOff(2);
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      relayOnOff(3);
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      relayOnOff(4);
    }
    else if (digitalRead(SwitchPin5) == LOW){
      delay(200);
      relayOnOff(5);      
    }
    else if (digitalRead(SwitchPin6) == LOW){
      delay(200);
      relayOnOff(6);
    }
    else if (digitalRead(SwitchPin7) == LOW){
      delay(200);
      relayOnOff(7);
    }
    else if (digitalRead(SwitchPin8) == LOW){
      delay(200);
      relayOnOff(8);
    }
}

void ir_remote(){
  if (irrecv.decode(&results)) {
      switch(results.value){
          case 0x80BF49B6:  relayOnOff(1);  break;
          case 0x80BFC936:  relayOnOff(2);  break;
          case 0x80BF33CC:  relayOnOff(3);  break;
          case 0x80BF718E:  relayOnOff(4);  break;
          case 0x80BFF10E:  relayOnOff(5);  break;
          case 0x80BF13EC:  relayOnOff(6);  break;
          case 0x80BF51AE:  relayOnOff(7);  break;
          case 0x80BFD12E:  relayOnOff(8);  break;
          case 0x80BF3BC4:  all_SwitchOff(); break;
          default : break;         
        }   
        //Serial.println(results.value, HEX);    
        irrecv.resume();   
  } 
}

void all_SwitchOff(){
  toggleState_1 = 1; digitalWrite(RelayPin1, toggleState_1);  delay(100);
  toggleState_2 = 1; digitalWrite(RelayPin2, toggleState_2);  delay(100);
  toggleState_3 = 1; digitalWrite(RelayPin3, toggleState_3);  delay(100);
  toggleState_4 = 1; digitalWrite(RelayPin4, toggleState_4);  delay(100);
  toggleState_5 = 1; digitalWrite(RelayPin5, toggleState_5);  delay(100);
  toggleState_6 = 1; digitalWrite(RelayPin6, toggleState_6);  delay(100);
  toggleState_7 = 1; digitalWrite(RelayPin7, toggleState_7);  delay(100);
  toggleState_8 = 1; digitalWrite(RelayPin8, toggleState_8);  delay(100);
}

// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, toggleState_4);
}

BLYNK_WRITE(VPIN_BUTTON_5) {
  toggleState_5 = param.asInt();
  digitalWrite(RelayPin5, toggleState_5);
}

BLYNK_WRITE(VPIN_BUTTON_6) {
  toggleState_6 = param.asInt();
  digitalWrite(RelayPin6, toggleState_6);
}

BLYNK_WRITE(VPIN_BUTTON_7) {
  toggleState_7 = param.asInt();
  digitalWrite(RelayPin7, toggleState_7);
}

BLYNK_WRITE(VPIN_BUTTON_8) {
  toggleState_8 = param.asInt();
  digitalWrite(RelayPin8, toggleState_8);
}

BLYNK_WRITE(VPIN_BUTTON_9) {
  all_SwitchOff();
}

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

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
    Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
    Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
    Blynk.virtualWrite(VPIN_BUTTON_7, toggleState_7);
    Blynk.virtualWrite(VPIN_BUTTON_8, toggleState_8);
    
    digitalWrite(wifiLed, HIGH); //Turn on WiFi LED
  }
}
void setup()
{
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);
  pinMode(RelayPin7, OUTPUT);
  pinMode(RelayPin8, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SwitchPin5, INPUT_PULLUP);
  pinMode(SwitchPin6, INPUT_PULLUP);
  pinMode(SwitchPin7, INPUT_PULLUP);
  pinMode(SwitchPin8, INPUT_PULLUP);
  
  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);
  digitalWrite(RelayPin5, toggleState_5);
  digitalWrite(RelayPin6, toggleState_6);
  digitalWrite(RelayPin7, toggleState_7);
  digitalWrite(RelayPin8, toggleState_8);


  WiFi.begin(WIFI_SSID, WIFI_PASS);
  timer1.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
  Blynk.config(AUTH);
  delay(1000);

  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
  Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
  Blynk.virtualWrite(VPIN_BUTTON_7, toggleState_7);
  Blynk.virtualWrite(VPIN_BUTTON_8, toggleState_8);
}

void loop()
{      
  ir_remote();
  manual_button();
  
  if (WiFi.status() == WL_CONNECTED)
  {
    Blynk.run();
  }
  
  timer1.run(); // Initiates SimpleTimer
}
