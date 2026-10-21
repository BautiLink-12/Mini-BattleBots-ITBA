#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int C1 = 18;
int A1 = 19;       //Wheels 
int C2 = 21;
int A2 = 22;

int M1 = 12;
int M2 = 13;     //Chainsaw 

int timesPressed = 0; //track the times the the attack button is pressed so it turns on or off the chainsaw, even -> off, odd -> on

char currentDriveState = 's'; // Store drive command ('f', 'b', 'l', 'r', 's')

void setup() {
   
 Serial.begin(115200);
 SerialBT.begin("ESP32_Car"); //change to Robots name on the controller 
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(18, OUTPUT);
 pinMode(19, OUTPUT);
 pinMode(21, OUTPUT);
 pinMode(22, OUTPUT);
}

void loop() {
 

 if (SerialBT.available()) {
   char cmd = SerialBT.read();
   Serial.write(cmd);

   //Chainsaaw ON and OFF 
   if (cmd == 'a') {
     timesPressed++; 
     if (timesPressed % 2 == 0) {
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);      
     } else {
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
     }
   } else if (cmd == 'f' || cmd == 'b' || cmd == 'l' || cmd == 'r' || cmd == 's') {
     currentDriveState = cmd;  //it tracks if its moving forward, back, left or right,
   }
 }

 //ROTATE WHEELs
 if (currentDriveState == 'f') {
    digitalWrite(C1, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(C2, HIGH);                    //forward
    digitalWrite(A2, LOW);
 }
 else if (currentDriveState == 'b') {
    digitalWrite(C1, LOW);
    digitalWrite(A1, HIGH);                     // backwards
    digitalWrite(C2, LOW);
    digitalWrite(A2, HIGH);
 }
 else if (currentDriveState == 'l') {
    digitalWrite(C1, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(C2, HIGH);
    digitalWrite(A2, LOW);                         //left
    delay(200);
    digitalWrite(C1, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(C2, LOW);
    digitalWrite(A2, LOW); 
    currentDriveState = 's';
 }
 else if (currentDriveState == 'r') {
    digitalWrite(C1, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(C2, LOW);
    digitalWrite(A2, HIGH);
    delay(200);                                        //right
    digitalWrite(C1, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(C2, LOW);
    digitalWrite(A2, LOW); 
    currentDriveState = 's';
 }
 else {
    digitalWrite(C1, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(C2, LOW);
    digitalWrite(A2, LOW); 
 }
}
