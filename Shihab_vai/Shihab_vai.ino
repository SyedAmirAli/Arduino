#define BLYNK_TEMPLATE_ID "TMPL6eRguGIj_"
#define BLYNK_TEMPLATE_NAME "SHIHAB AUTOMATION"
#define BLYNK_AUTH_TOKEN "5LvsZf6g6xaLgcRzmF6NKW1JVnB_Nuzv"

//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <AceButton.h>
#include <Servo.h>

char ssid[] = "SHIHAB";
char pass[] = "Nointernet";

bool fetch_blynk_state = true;  // true or false

using namespace ace_button;

// define the GPIO connected with Relays and switches
#define RelayPin1 5  // D1
#define RelayPin2 4  // D2

#define SwitchPin1 13  // D7
#define SwitchPin2 2   // D4 + WIFI LED 

#define wifiLed   16   // D0

#define servoPin 12 // D6
#define servoSwitchPin 15 // D8

// Change the virtual pins according to the rooms
#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3

// Relay State
bool toggleState_1 = LOW; // Define integer to remember the toggle state for relay 1
bool toggleState_2 = LOW; // Define integer to remember the toggle state for relay 2

int wifiFlag = 0;
char auth[] = BLYNK_AUTH_TOKEN;

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2); 

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);

BlynkTimer timer;
Servo srv;

void setup() {
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(wifiLed, OUTPUT);

  srv.attach(servoPin);
  srv.write(0);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(servoSwitchPin, INPUT_PULLUP);

  // During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);

  digitalWrite(wifiLed, HIGH);

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);

  button1.init(SwitchPin1);
  button2.init(SwitchPin2);

  // Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  Blynk.config(auth);
  delay(1000);

  if (!fetch_blynk_state) {
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
}

void servoController(){
  srv.write(20);
  delay(1000);
  srv.write(-20);
}

void servoSwitchController() {
  int state = digitalRead(servoSwitchPin);

  if (state == LOW) {
    servoController();
    while (digitalRead(servoSwitchPin) == LOW) {
      delay(10); // Wait until the switch is released before proceeding
    }
  } else {
    srv.write(0);
  }
}


// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  int state = param.asInt();
  
  if(state){
    servoController();
  }
}

BLYNK_WRITE(VPIN_BUTTON_C) {
  all_SwitchOff();
}

void all_SwitchOff() {
  toggleState_1 = 0;
  digitalWrite(RelayPin1, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  delay(100);
  toggleState_2 = 0;
  digitalWrite(RelayPin2, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  delay(100);
}

void checkBlynkStatus() {
  // called every 3 seconds by SimpleTimer
  bool isconnected = Blynk.connected();
  if (!isconnected) {
    wifiFlag = 1;
    Serial.println("Blynk Not Connected");
    digitalWrite(wifiLed, HIGH);
  } else {
    wifiFlag = 0;
    if (!fetch_blynk_state) {
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    }
    digitalWrite(wifiLed, LOW);
    // Serial.println("Blynk Connected");
  }
}

BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state) {
    Blynk.syncVirtual(VPIN_BUTTON_1);
    Blynk.syncVirtual(VPIN_BUTTON_2);
  }
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates SimpleTimer

  button1.check();
  button2.check();
  // servoSwitchController();
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT_1 FIRED");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RelayPin1, toggleState_1);
      toggleState_1 = !toggleState_1;
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT_2 FIRED");
  switch (eventType) {
    case AceButton::kEventReleased:
      digitalWrite(RelayPin2, toggleState_2);
      toggleState_2 = !toggleState_2;
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      break;
  }
}