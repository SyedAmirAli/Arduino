/*Solar tracking system
   https://srituhobby.com
*/

//Include the servo motor library
#include <ESP32Servo.h>
//Define the LDR sensor pins
#define LDR1 12
#define LDR2 14
//Define the error value. You can change it as you like
#define error 10
//Starting point of the servo motor
int Spoint =  90;
//Create an object for the servo motor
Servo servo;

void setup() {
  Serial.begin(115200);
//Include servo motor PWM pin
  servo.attach(11);
//Set the starting point of the servo
  servo.write(Spoint);
  delay(1000);
}

void loop() {
//Get the LDR sensor value
  int ldr1 = analogRead(LDR1);
  Serial.print("LDR 1 => ");
  Serial.println(ldr1);
//Get the LDR sensor value
  int ldr2 = analogRead(LDR2);
  Serial.print("LDR 1 => ");
  Serial.println(ldr2);

//Get the difference of these values
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

//Check these values using a IF condition
  if ((value1 <= error) || (value2 <= error)) {

  } else {
    if (ldr1 > ldr2) {
      Spoint = --Spoint;
    }
    if (ldr1 < ldr2) {
      Spoint = ++Spoint;
    }
  }
//Write values on the servo motor
  servo.write(Spoint);
  delay(80);
}