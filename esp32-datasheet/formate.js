switch (relay) {
    case 1:
        if (toggleState_1 == 1) {
            digitalWrite(RelayPin1, LOW); // turn on relay 1
            toggleState_1 = 0;
            Serial.println("Device1 ON");
        } else {
            digitalWrite(RelayPin1, HIGH); // turn off relay 1
            toggleState_1 = 1;
            Serial.println("Device1 OFF");
        }
        delay(100);
        break;
    case 2:
        if (toggleState_2 == 1) {
            digitalWrite(RelayPin2, LOW); // turn on relay 2
            toggleState_2 = 0;
            Serial.println("Device2 ON");
        } else {
            digitalWrite(RelayPin2, HIGH); // turn off relay 2
            toggleState_2 = 1;
            Serial.println("Device2 OFF");
        }
        delay(100);
        break;
    case 3:
        if (toggleState_3 == 1) {
            digitalWrite(RelayPin3, LOW); // turn on relay 3
            toggleState_3 = 0;
            Serial.println("Device3 ON");
        } else {
            digitalWrite(RelayPin3, HIGH); // turn off relay 3
            toggleState_3 = 1;
            Serial.println("Device3 OFF");
        }
        delay(100);
        break;
    case 4:
        if (toggleState_4 == 1) {
            digitalWrite(RelayPin4, LOW); // turn on relay 4
            toggleState_4 = 0;
            Serial.println("Device4 ON");
        } else {
            digitalWrite(RelayPin4, HIGH); // turn off relay 4
            toggleState_4 = 1;
            Serial.println("Device4 OFF");
        }
        delay(100);
        break;
    case 5:
        if (toggleState_5 == 1) {
            digitalWrite(RelayPin5, LOW); // turn on relay 5
            toggleState_5 = 0;
            Serial.println("Device5 ON");
        } else {
            digitalWrite(RelayPin5, HIGH); // turn off relay 5
            toggleState_5 = 1;
            Serial.println("Device5 OFF");
        }
        delay(100);
        break;
    case 6:
        if (toggleState_6 == 1) {
            digitalWrite(RelayPin6, LOW); // turn on relay 6
            toggleState_6 = 0;
            Serial.println("Device6 ON");
        } else {
            digitalWrite(RelayPin6, HIGH); // turn off relay 6
            toggleState_6 = 1;
            Serial.println("Device6 OFF");
        }
        delay(100);
        break;
    case 7:
        if (toggleState_7 == 1) {
            digitalWrite(RelayPin7, LOW); // turn on relay 7
            toggleState_7 = 0;
            Serial.println("Device7 ON");
        } else {
            digitalWrite(RelayPin7, HIGH); // turn off relay 7
            toggleState_7 = 1;
            Serial.println("Device7 OFF");
        }
        delay(100);
        break;
    case 8:
        if (toggleState_8 == 1) {
            digitalWrite(RelayPin8, LOW); // turn on relay 8
            toggleState_8 = 0;
            Serial.println("Device8 ON");
        } else {
            digitalWrite(RelayPin8, HIGH); // turn off relay 8
            toggleState_8 = 1;
            Serial.println("Device8 OFF");
        }
        delay(100);
        break;
    default:
        break;
}
