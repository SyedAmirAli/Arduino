// #include <ArduinoBLE.h>

// void setup() {
//   Serial.begin(115200);

//   // Initialize BLE
//   if (!BLE.begin()) {
//     Serial.println("Failed to initialize BLE");
//     while (1);
//   }

//   // Start scanning for Bluetooth devices
//   BLE.scan();
//   Serial.print("Connecting");
// }

// void loop() {
//   Serial.print(".");
//   delay(1000);
//   // Check for BLE devices
//   BLEDevice peripheral = BLE.available();
//   if (peripheral) {
//     Serial.print("\nFound device: ");
//     Serial.println(peripheral.address());

//     // Save the MAC address of the found device
//     String receiverMAC = peripheral.address();
//     Serial.print("\nReceiver MAC: ");
//     Serial.println(receiverMAC);

//     // Check if the found device is your Bluetooth amplifier receiver
//     // Replace the following line with your own logic to match the receiver MAC
//     if (receiverMAC == "4b:fb:c8:4a:fc:4f") { // Replace with your receiver's MAC address
//       // Initiate pairing
//       if (peripheral.connect()) {
//         Serial.println("Pairing initiated with Bluetooth amplifier receiver");
//         delay(5000); // Wait for the pairing process to complete (adjust as needed)
//         peripheral.disconnect();
//         Serial.println("Pairing completed");
//         while (1); // End the sketch after pairing
//       } else {
//         Serial.println("Failed to initiate pairing");
//       }
//     }
//   }
// }


// #include <ArduinoBLE.h>

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);

//   // Initialize BLE
//   if (!BLE.begin()) {
//     Serial.println("Failed to initialize BLE");
//     while (1);
//   }

//   Serial.print("Connecting");

//   // Start scanning for Bluetooth devices
//   BLE.scan();
// }

// void loop() {
//   Serial.print(".");
//   delay(1000);
//   // Check for BLE devices
//   BLEDevice peripheral = BLE.available();
//   if (peripheral) {
//     Serial.print("Found device: ");
//     Serial.println(peripheral.address());

//     // Save the MAC address of the found device
//     String receiverMAC = peripheral.address();
//     Serial.print("Receiver MAC: ");
//     Serial.println(receiverMAC);

//     // Check if the found device is your Bluetooth amplifier receiver
//     // Replace the following line with your own logic to match the receiver MAC
//     if (receiverMAC == "B5:5B:A3:53:7B:C6") { // Replace with your receiver's MAC address
//       // Initiate pairing
//       if (peripheral.connect()) {
//         Serial.println("Pairing initiated with Bluetooth amplifier receiver");
//         delay(5000); // Wait for the pairing process to complete (adjust as needed)
//         peripheral.disconnect();
//         Serial.println("Pairing completed");
//         while (1); // End the sketch after pairing
//       } else {
//         Serial.println("Failed to initiate pairing");
//       }
//     }
//   }
// }

#include <ArduinoBLE.h>

// Bluetooth amplifier receiver MAC address
char receiverMAC[] = "B5:5B:A3:53:7B:C6";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE");
    while (1);
  }

  // Attempt to connect to the Bluetooth amplifier receiver
  Serial.print("Connecting to receiver: ");
  Serial.println(receiverMAC);
  connectToReceiver();
}

void loop() {
  // Your code for communication with the Bluetooth amplifier receiver goes here
}

void connectToReceiver() {
  // Scan for BLE peripherals
  BLEDevice peripheral;
  while (!peripheral) {
    peripheral = BLE.available();
  }

  // Check if the found peripheral is the Bluetooth amplifier receiver
  if (peripheral.address() == receiverMAC) {
    Serial.println("Found receiver, attempting to connect...");
    if (peripheral.connect()) {
      Serial.println("Connected to receiver");
    } else {
      Serial.println("Failed to connect to receiver");
    }
  }
}

