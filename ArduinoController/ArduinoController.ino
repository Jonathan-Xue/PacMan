#include <SoftwareSerial.h>

// Debug
bool debugMode = false;

// Bluetooth Pins
const int txPin = 2;
const int rxPin = 3;
const int statePin = 4;
SoftwareSerial BTSerial(rxPin, txPin);

// Joystick Pins
const int xPin = A1;
const int yPin = A0;

// Output Pins
const int rLEDPin = 9;
const int gLEDPin = 10;
const int bLEDPin = 11;

// Bluetooth Vars
bool bluetoothConnected;

// Joystick Vars
int xVal = 0;
int yVal = 0;

// Output Vars
String message = "";

void setup() {
  // initialize serial communications at 9600 bps:
  if (debugMode){
    Serial.begin(9600);
  } else {
    BTSerial.begin(9600); 
  }

  pinMode (statePin, INPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);  
}

void loop() {
  // Bluetooth
  if (digitalRead(statePin) == HIGH){
    bluetoothConnected = true;
  } else {
    bluetoothConnected = false;
  }
  
  if (bluetoothConnected){
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 0);
  } else {
    analogWrite(rLEDPin, 255);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 0);
  }

  
  // Joystick
  xVal = map(analogRead(xPin), 0, 1023, -100, 100);
  yVal = map(analogRead(yPin), 0, 1023, -100, 100);

  // WASD
  if (!(xVal < 25 && xVal > -25 && yVal < 25 && yVal > -25)){
    if (abs(xVal) > abs(yVal)){
      if (xVal > 0){
        message = "0x44"; //"D";
      } else {
        message = "0x41"; //"A";
      }
    } else {
      if (yVal > 0){
        message = "0x57"; //"W";
      } else {
        message = "0x53"; //"S";
      }
    }
  }

  // Transmit Message
  if (message != ""){
    if (debugMode){
      Serial.println(message);
    }
    else {
      BTSerial.println(message);
    }

    message = "";
  }

  // Delay
  delay(50);
}
