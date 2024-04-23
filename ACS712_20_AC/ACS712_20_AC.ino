//
//    FILE: ACS712_20_AC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AC measurement with point to point
//     URL: https://github.com/RobTillaart/ACS712

#define BLYNK_TEMPLATE_ID "TMPL6yhBF0Vzh"
#define BLYNK_TEMPLATE_NAME "Wroom"
#define BLYNK_AUTH_TOKEN "1rH76Qt_da9IigwYvTv-ZcYhJRtC6rIr"
#define WIFI_SSID "SYED_AMIR_ALI"
#define WIFI_PASSWORD "syedamirali"

#include <ACS712.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A5, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD); // Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  delay(1000);


  //  use simulation
  ACS.setADC(signal, 5, 1024);

  ACS.autoMidPoint();
  Serial.print("MidPoint: ");
  Serial.print(ACS.getMidPoint());
  Serial.print(". Noise mV: ");
  Serial.println(ACS.getNoisemV());
}


void loop()
{
  delay(100);
  start = micros();
  //  int mA = ACS.mA_AC();
  int mA = ACS.mA_AC_sampling();
  Blynk.virtualWrite(V0, mA);
  stop = micros();
  Serial.print("mA: ");
  Serial.print(mA);
  Serial.print(". Form factor: ");
  Serial.print(ACS.getFormFactor());
  Serial.print("  time: ");
  Serial.println(stop - start);
  delay(5000);
}


//  simulated 50 Hz signal
uint16_t signal(uint8_t p)
{
  return 512 + 400 * sin((micros() % 1000000) * (TWO_PI * 50 / 1e6));
}


//  -- END OF FILE --

