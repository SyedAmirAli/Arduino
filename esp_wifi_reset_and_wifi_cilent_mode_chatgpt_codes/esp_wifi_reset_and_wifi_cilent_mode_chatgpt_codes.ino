const char webpage[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang='en'>
    <head>
      <meta charset='UTF-8' />
      <meta name='viewport' content='width=device-width, initial-scale=1.0' />
      <title>Password Reset Form</title> 
      <style>
        * {
          margin: 0;
          padding: 0;
          box-sizing: border-box;
          font-family: 'Poppins', sans-serif;
        }

        body {
          font-size: 16px;
          font-weight: 400;
          width: 100%;
          height: 100vh;
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;

          background-color: #ffffff;
          background: linear-gradient(
            to top right,
            rgba(6, 182, 212, 0.1),
            rgba(236, 72, 153, 0.1),
            rgba(168, 85, 247, 0.1)
          );
        }

        .card {
          padding: 20px;
          border-radius: 12px;
          border: 1px solid #eee;
          background-color: #ffffff50;
          box-shadow: 0px 2px 4px 0px rgba(0, 0, 0, 0.12);
          max-width: 420px;
          width: 100%;
        }

        .card-body {
          width: 100%;
          margin-top: 12px;
        }

        .card-body .input-group {
          display: flex;
          flex-direction: column;
          margin-top: 12px;
          width: 100%;
          position: relative;
        }

        .card-body .input-group input {
          font-weight: 500;
          padding: 8px 12px;
          margin-top: 4px;
          font-size: 17px;
          width: 100%;
          font-style: 'Romoto Mono', sans-serif;
          border: 1px dashed #bbb;
          background-color: #ffffff;
          outline: none;
          color: #7a7a7a;
          letter-spacing: 0.0125rem;
        }

        .card-header {
          width: 100%;
          display: flex;
          align-items: center;
          justify-content: center;
          border-bottom: 1px dashed #1fbeae;
          padding-bottom: 10px;
          margin-bottom: 20px;
        }

        .card-header h1 {
          color: #1fbeae;
        }

        .card-body .input-group label {
          font-size: 14px;
          font-weight: 700;
          color: #7a7a7a;
        }

        .card-body .input-group input:focus {
          border-color: #1fbeae;
          color: #1fbeae;
          font-weight: 600;
        }

        .card-body .input-group input::placeholder {
          font-weight: 500;
        }

        .submit-btn {
          width: 100%;
          padding-top: 20px;
        }

        .submit-btn button {
          width: 100%;
          padding: 8px 12px;
          font-size: 17px;
          text-transform: uppercase;
          font-weight: 700;
          background-color: #000;
          color: #ffffff;
          border: 1px dashed #bababa;
          border-radius: 4px;
          transition: 500ms;
          letter-spacing: 0.0125rem;
        }

        .submit-btn button:hover {
          background-color: #1fbeae;
          letter-spacing: 0.025rem;
        }

        .card-body .input-group i {
          position: absolute;
          font-size: 20px;
          z-index: 10;
          right: 10px;
          top: 28px;
          cursor: pointer;
        }

        .card-body .input-group i.eye {
          color: #ce150f;
          fill: #ce150f;
          display: none;
        }

        .card-body .input-group i.eye-slash {
          color: #1fbeae;
          fill: #1fbeae;
          display: block;
        }

        .card-body .input-group.active i.eye {
          display: block;
        }

        .card-body .input-group.active i.eye-slash {
          display: none;
        }
      </style>
    </head>
    <body>
      <form
        class='card'
        method='post'
        enctype='multipart/form-data'
        action='/wifi-credentials'
      >
        <div class='card-header'>
          <h1>WiFi Reset Form</h1>
        </div>
        <div class='card-body'>
          <div class='input-group'>
            <label for='ssid'>WiFi SSID</label
            ><input
              type='text'
              name='ssid'
              id='ssid'
              class='ssid'
              placeholder='Input Here Your WiFi SSID'
            />
          </div>
          <div class='input-group' id='password-group'>
            <label for='password'>WiFi Password</label
            ><input
              type='password'
              name='password'
              id='password'
              class='password'
              placeholder='Input Here Your WiFi Password'
            />
            <i class='eye-slash'
              ><svg
                width='20'
                height='20'
                xmlns='http://www.w3.org/2000/svg'
                viewBox='0 0 640 512'
              >
                <path
                  d='M38.8 5.1C28.4-3.1 13.3-1.2 5.1 9.2S-1.2 34.7 9.2 42.9l592 464c10.4 8.2 25.5 6.3 33.7-4.1s6.3-25.5-4.1-33.7L525.6 386.7c39.6-40.6 66.4-86.1 79.9-118.4c3.3-7.9 3.3-16.7 0-24.6c-14.9-35.7-46.2-87.7-93-131.1C465.5
                   68.8 400.8 32 320 32c-68.2 0-125 26.3-169.3 60.8L38.8 5.1zm151 118.3C226 97.7 269.5 80 320 80c65.2 0 118.8 29.6 159.9 67.7C518.4 183.5 545 226 558.6 256c-12.6 28-36.6 66.8-70.9 100.9l-53.8-42.2c9.1-17.6 14.2-37.5
                   14.2-58.7c0-70.7-57.3-128-128-128c-32.2 0-61.7 11.9-84.2 31.5l-46.1-36.1zM394.9 284.2l-81.5-63.9c4.2-8.5 6.6-18.2 6.6-28.3c0-5.5-.7-10.9-2-16c.7 0 1.3 0 2 0c44.2 0 80 35.8 80 80c0 9.9-1.8 19.4-5.1 28.2zm51.3
                   163.3l-41.9-33C378.8 425.4 350.7 432 320 432c-65.2 0-118.8-29.6-159.9-67.7C121.6 328.5 95 286 81.4 256c8.3-18.4 21.5-41.5 39.4-64.8L83.1 161.5C60.3 191.2 44 220.8 34.5 243.7c-3.3 7.9-3.3 16.7 0 24.6c14.9 35.7 
                   46.2 87.7 93 131.1C174.5 443.2 239.2 480 320 480c47.8 0 89.9-12.9 126.2-32.5zm-88-69.3L302 334c-23.5-5.4-43.1-21.2-53.7-42.3l-56.1-44.2c-.2 2.8-.3 5.6-.3 8.5c0 70.7 57.3 128 128 128c13.3 0 26.1-2 38.2-5.8z'
                /></svg
            ></i>

            <i class='eye'>
              <svg
                xmlns='http://www.w3.org/2000/svg'
                viewBox='0 0 576 512'
                width='20'
                height='20'
              >
                <path
                  d='M288 80c-65.2 0-118.8 29.6-159.9 67.7C89.6 183.5 63 226 49.4 256c13.6 30 40.2 72.5 78.6 108.3C169.2 402.4 222.8 432 288 432s118.8-29.6 159.9-67.7C486.4 328.5 513 286 526.6
                   256c-13.6-30-40.2-72.5-78.6-108.3C406.8 109.6 353.2 80 288 80zM95.4 112.6C142.5 68.8 207.2 32 288 32s145.5 36.8 192.6 80.6c46.8 43.5 78.1 95.4 93 131.1c3.3 7.9 3.3 16.7 0 24.6c-14.9 35.7-46.2 87.7-93 
                   131.1C433.5 443.2 368.8 480 288 480s-145.5-36.8-192.6-80.6C48.6 356 17.3 304 2.5 268.3c-3.3-7.9-3.3-16.7 0-24.6C17.3 208 48.6 156 95.4 112.6zM288 336c44.2 0 80-35.8 80-80s-35.8-80-80-80c-.7 0-1.3 0-2 
                   0c1.3 5.1 2 10.5 2 16c0 35.3-28.7 64-64 64c-5.5 0-10.9-.7-16-2c0 .7 0 1.3 0 2c0 44.2 35.8 80 80 80zm0-208a128 128 0 1 1 0 256 128 128 0 1 1 0-256z'
                />
              </svg>
            </i>
          </div>

          <div class='submit-btn'>
            <button>save wifi credentials</button>
          </div>
        </div>
      </form>

      <script>
        const dom = (id) => document.querySelector(id);

        dom('i.eye').onclick = function (e) {
          dom('#password').type = 'password';
          dom('#password-group').classList.remove('active');
        };

        dom('i.eye-slash').onclick = function (e) {
          dom('#password').type = 'text';
          dom('#password-group').classList.add('active');
        };
      </script>
    </body>
  </html>
)rawliteral";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// Create an instance of the web server on port 80
ESP8266WebServer server(80);

const char* default_ap_ssid = "ESP8266_AP"; // Default AP SSID
const char* default_ap_password = "12345678"; // Default AP Password

// Global variables to store WiFi credentials
char stored_ssid[33];
char stored_password[33];

// Button pin
const int buttonPin = 0; // GPIO 0

// Long press detection variables
unsigned long buttonPressTime = 0;
const unsigned long longPressDuration = 3000; // 3 seconds

// Function to handle root URL
void handleRoot() {
  server.send_P(200, "text/html", webpage);
}

// Function to handle WiFi credentials form submission
void handleWiFiResetForm() {
  if (server.method() == HTTP_POST) {
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    // Save credentials to EEPROM
    EEPROM.begin(512);
    for (int i = 0; i < 32; ++i) {
      EEPROM.write(i, i < ssid.length() ? ssid[i] : 0);
    }
    for (int i = 0; i < 32; ++i) {
      EEPROM.write(32 + i, i < password.length() ? password[i] : 0);
    }
    EEPROM.commit();
    EEPROM.end();

    // Store credentials in global variables
    ssid.toCharArray(stored_ssid, 33);
    password.toCharArray(stored_password, 33);

    // Print credentials to serial monitor
    Serial.print("SSID: ");
    Serial.println(stored_ssid);
    Serial.print("Password: ");
    Serial.println(stored_password);

    server.send(200, "text/html", "<h1>Credentials Saved. Please restart your ESP8266.</h1>");
  } else {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

// Function to read WiFi credentials from EEPROM
void readWiFiCredentialsFromEEPROM() {
  EEPROM.begin(512);
  for (int i = 0; i < 32; ++i) {
    stored_ssid[i] = EEPROM.read(i);
    if (stored_ssid[i] == 0) break;
  }
  stored_ssid[32] = '\0'; // Ensure null-terminated string
  for (int i = 0; i < 32; ++i) {
    stored_password[i] = EEPROM.read(32 + i);
    if (stored_password[i] == 0) break;
  }
  stored_password[32] = '\0'; // Ensure null-terminated string
  EEPROM.end();
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

// Function to setup Client mode
void setupClientMode() {
  WiFi.begin(stored_ssid, stored_password);
  Serial.print("Connecting to ");
  Serial.println(stored_ssid);

  // Wait for connection
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect, switching to Access Point mode");
    setupAPMode();
  }
}

void setup() {
  // Start the Serial communication
  Serial.begin(115200);
  Serial.println();

  // Initialize button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // Read WiFi credentials from EEPROM
  readWiFiCredentialsFromEEPROM();

  // Print the credentials read from EEPROM
  Serial.print("Stored SSID: ");
  Serial.println(stored_ssid);
  Serial.print("Stored Password: ");
  Serial.println(stored_password);

  // Start in Client mode by default
  setupClientMode();
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // Button is pressed
    if (buttonPressTime == 0) {
      // Record the time when the button is first pressed
      buttonPressTime = millis();
    } else if (millis() - buttonPressTime > longPressDuration) {
      // If the button is held for more than the long press duration
      Serial.println("Long press detected, switching to Access Point mode...");

      // Debounce delay
      delay(500);

      // Switch to Access Point mode
      WiFi.disconnect();
      setupAPMode();

      // Reset button press time to avoid multiple triggers
      buttonPressTime = 0;
    }
  } else {
    // Button is not pressed
    buttonPressTime = 0;
  }
}
