#define BLYNK_TEMPLATE_ID "TMPL6P1qhAgrQ"
#define BLYNK_TEMPLATE_NAME "Esp32 Wroom Test"
#define BLYNK_AUTH_TOKEN "49PHHeuZpBD-LmDL5vLJ0flup7ein-Ko"

#include <BlynkSimpleESP32.h>
#include <WiFi.h>

#define V_PIN_1 V1
#define V_PIN_2 V2
#define V_PIN_3 V3
#define V_PIN_4 V4
#define V_PIN_5 V5 

const int switch_1 = 18, switch_2 = 19, switch_3 = 22, switch_4 = 23, switch_5 = 15, relay_1 = 17, relay_2 = 32, relay_3 = 33, relay_4 = 4, relay_5 = 5;
bool state_1 = LOW, state_2 = LOW, state_3 = LOW, state_4 = LOW, state_5 = LOW; 

void manageManualSwitch(int pin){
  switch(pin){
    case switch_1:
      if(digitalRead(switch_1) == LOW){
        state_1 = !state_1;
        digitalWrite(pin, state_1);
      }
      break;

    default:
      break;
  }
}