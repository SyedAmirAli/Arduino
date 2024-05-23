#include <EEPROM.h>
#include "resources.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Create an instance of the web server on port 80
ESP8266WebServer server(80);

const char* default_ap_ssid = "ESP-01 WiFi"; // Default AP SSID
const char* default_ap_password = "12345678"; // Default AP Password

// Global variables to store WiFi credentials
char stored_ssid[33];
char stored_password[33];

// Button pin
const int buttonPin = 0; // GPIO 0

// Long press detection variables
unsigned long buttonPressTime = 0;
const unsigned long longPressDuration = 3000; // 3 seconds
int signalMode = 0; // if the signal mode is 0 then the wifi is running on client mode and the signal mode is 1 then the wifi mode is running on host mode!

// Function to handle root URL
void handleRoot() {
  server.send_P(200, "text/html", webpage);
}

// Function to handle WiFi credentials form submission
void handleWiFiResetForm() {
  if (server.method() == HTTP_POST) {
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    writeStringIntoEEPROM(1, ssid);
    // writeStringIntoEEPROM(100, password);

    Serial.print("NEW SSID: ");
    Serial.println(ssid);
    Serial.print("NEW Password: ");
    Serial.println(password);

    server.send(200, "text/html", "<h1>Credentials Saved. Please restart your ESP8266.</h1>");
  } else {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

// Function to setup Access Point mode
void setupAPMode() {
  WiFi.softAP(default_ap_ssid, default_ap_password);
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Define the handling function for the root URL
  server.on("/", handleRoot);
  server.on("/wifi-credentials", HTTP_POST, handleWiFiResetForm);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void setup() {
  // Start the Serial communication
  Serial.begin(115200);

  // Initialize button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // Start in Client mode by default
  setupAPMode();

  readInSL();
}

void loop() {
  // Handle client requests
  server.handleClient();

  readInSL();
}

void readInSL(){
  Serial.println("WiFi SSID => ");
  Serial.print(readStringFromEEPROM(1));
  // Serial.println("WiFi Password => ");
  // Serial.print(readStringFromEEPROM(100));

  delay(3000);
}


  // // Check if the button is pressed
  // if (digitalRead(buttonPin) == LOW) {
  //   // Button is pressed
  //   if (buttonPressTime == 0) {
  //     // Record the time when the button is first pressed
  //     buttonPressTime = millis();
  //   } else if (millis() - buttonPressTime > longPressDuration) {
  //     // If the button is held for more than the long press duration
  //     Serial.println("Long press detected, switching to Access Point mode...");

  //     // Debounce delay
  //     delay(500);

  //     // Switch to Access Point mode
  //     WiFi.disconnect();
  //     setupAPMode();

  //     // Reset button press time to avoid multiple triggers
  //     buttonPressTime = 0;
  //   }
  // } else {
  //   // Button is not pressed
  //   buttonPressTime = 0;
  // }
// Function to setup Client mode
// void setupClientMode() {
//   WiFi.begin(stored_ssid, stored_password);

//   Serial.print("Connecting to ");
//   Serial.println(stored_ssid);

//   // Wait for connection
//   unsigned long startAttemptTime = millis();
//   Serial.print("Connecting");
//   while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
//     delay(500);
//     Serial.print(".");
//   }

//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("\nWiFi connected!\t IP address: ");
//     Serial.println(WiFi.localIP());
//   } else {
//     Serial.println("Failed to connect, switching to Access Point mode");
//     // printWifiCredentials();
//     setupAPMode();
//   }
// }

    // Save credentials to EEPROM
    // EEPROM.begin(512);
    // for (int i = 0; i < 32; ++i) {
    //   EEPROM.write(i, i < ssid.length() ? ssid[i] : 0);
    // }
    // for (int i = 0; i < 32; ++i) {
    //   EEPROM.write(32 + i, i < password.length() ? password[i] : 0);
    // }
    // EEPROM.commit();
    // EEPROM.end();

    // Store credentials in global variables
    // ssid.toCharArray(stored_ssid, 33);
    // password.toCharArray(stored_password, 33);

    // Print credentials to serial monitor
// Function to read WiFi credentials from EEPROM
// void readWiFiCredentialsFromEEPROM() {
//   EEPROM.begin(512);
//   for (int i = 0; i < 32; ++i) {
//     stored_ssid[i] = EEPROM.read(i);
//     if (stored_ssid[i] == 0) break;
//   }
//   stored_ssid[32] = '\0'; // Ensure null-terminated string
//   for (int i = 0; i < 32; ++i) {
//     stored_password[i] = EEPROM.read(32 + i);
//     if (stored_password[i] == 0) break;
//   }
//   stored_password[32] = '\0'; // Ensure null-terminated string
//   EEPROM.end();
// }

  // Read WiFi credentials from EEPROM
  // readWiFiCredentialsFromEEPROM();
  // printWifiCredentials();

// void printWifiCredentials(){
//   // Print the credentials read from EEPROM
//   Serial.print("Stored SSID: ");
//   Serial.println(stored_ssid);
//   Serial.print("Stored Password: ");
//   Serial.println(stored_password);
// }