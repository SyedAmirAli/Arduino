#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define WiFi_SSID "Syed Amir Ali"
#define WiFi_PASSWORD "syedamirali"

const char* INITIAL_API_URL = "https://esp32.syedamirali.com/";
String apiUrl;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(WiFi_SSID, WiFi_PASSWORD);

  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WIFI Connected on ");
  Serial.print(WiFi_SSID);
  sendGetRequest();
}

void loop() {
  if (apiUrl.isEmpty()) {
    Serial.println("INITIAL_API_REQUEST_SENDED!");
    sendGetRequest();
  } else {
    Serial.print("API_URL => ");
    Serial.println(apiUrl);
  }

  delay(1000);
}

void sendGetRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(INITIAL_API_URL);
    // Send GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Print response body
      String response = http.getString();

      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, response);

      if (error) {
        Serial.print("Parsing failed: ");
        Serial.println(error.c_str());
        return;
      }

      const char* apiUrlChar = doc["apiUrl"];
      if (apiUrlChar != nullptr) {
        apiUrl = String(apiUrlChar);
      }

      Serial.println("Response: " + response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  }
}
