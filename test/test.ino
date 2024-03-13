// #include <ArduinoBLE.h>

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);

//   // Initialize BLE
//   if (!BLE.begin()) {
//     Serial.println("Failed to initialize BLE");
//     while (1);
//   }

//   // Scan for Bluetooth devices
//   BLEDevice peripheral = BLE.available();
//   while (!peripheral) {
//     peripheral = BLE.available();
//   }

//   // Connect to the Bluetooth amplifier receiver module
//   if (peripheral.connect()) {
//     Serial.println("Connected to Bluetooth amplifier receiver");
//     // Send audio data to the module
//     // Implement audio streaming logic here
//   } else {
//     Serial.println("Failed to connect to Bluetooth amplifier receiver");
//   }
// }

// void loop() {
//   // Your code here
// }


#include <Bluetooth.h>
 
 // Replace "YOUR_ESP32_NAME" with your desired ESP32 name for discoverability
const char* deviceName = "YOUR_ESP32_NAME"; 

// Replace "XFW-BT" with the actual SERVICE_UUID of your XY-WRBT module if different
BluetoothServer server = BluetoothServer("XFW-BT"); 

void setup() {
  Serial.begin(115200);
  server.begin();
  Serial.println("Bluetooth device name set to: " + String(deviceName));
  Serial.println("Scanning for XY-WRBT Bluetooth module...");
}

void loop() {
  BluetoothClient client = server.available();
  if (client) {
    Serial.println("XY-WRBT module connected!");
    // Add your code to interact with the connected device for audio (refer to XY-WRBT documentation)
    client.stop();
  }

  delay(1000);
}
