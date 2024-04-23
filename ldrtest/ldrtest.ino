const int ldrPin = 34;
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  if(ldrValue == 0){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  delay(100); // Wait for 1 second before reading again
}
