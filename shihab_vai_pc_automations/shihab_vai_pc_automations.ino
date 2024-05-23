#define BLYNK_TEMPLATE_ID "TMPL6CUrXEC0d"
#define BLYNK_TEMPLATE_NAME "PC Automations"
#define BLYNK_AUTH_TOKEN "_jk0pGwkoSyFwMRHoYrUOC5x_RFks8tY"

//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define PC_VPIN V0
#define FAN_VPIN V1
#define LED_VPIN V2

char ssid[] = "SHIHAB";
char password[] = "Nointernet";  
const char auth[] = "_jk0pGwkoSyFwMRHoYrUOC5x_RFks8tY";
const int PC_PIN = 0, FAN_PIN = 1, LED_PIN = 2; // use the 0, 1 & 2 gpio pins!
 
Servo srv;

void setup() {
  Serial.begin(115200); 
  Serial.print("Connecting");

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  Blynk.begin(auth, ssid, password);

  // pin defines
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
 
  srv.attach(PC_PIN);
  srv.write(0); 
}

void servoController(){
  srv.write(20);
  delay(1000);
  srv.write(-20);
} 

// When App button is pushed - switch the state
BLYNK_WRITE(LED_VPIN) {
  digitalWrite(LED_PIN, param.asInt());
}

BLYNK_WRITE(FAN_VPIN) {
  digitalWrite(FAN_PIN, param.asInt());
}

BLYNK_WRITE(PC_VPIN) {
  int state = param.asInt();
  if(state) servoController();

  Serial.println("PC Switch Triggering!");
} 

void loop() {
  Blynk.run(); 
}