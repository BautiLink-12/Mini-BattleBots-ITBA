#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPin = A12;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car"); 
  pinMode(ledPin, OUTPUT);
  Serial.println("Bluetooth Started. Ready to pair!");
}

void loop() {
  
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    
  
    Serial.write(incomingChar);

   
    if (incomingChar == 'b') {
      digitalWrite(ledPin, HIGH); // Turn LED ON
    } 
    else if (incomingChar == 'f') {
      digitalWrite(ledPin, LOW);  // Turn LED OFF
    }
  }

  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
}