#include <SoftwareSerial.h>

// Debug
bool debugMode = false;

// Bluetooth Pins
const int rxPin = 2;
const int txPin = 3;
const int statePin = 4;
//SoftwareSerial BTSerial(rxPin, txPin);

// Joystick Pins
const int xPin = A1; // Rotated 90 Degrees CCW
const int yPin = A0; // Rotated 90 Degrees CCW

// Output Pins
const int rLEDPin = 9;
const int gLEDPin = 10;
const int bLEDPin = 11;

// Bluetooth Vars
bool bluetoothConnected;

// Joystick Vars
bool rotated = true; // Standard VS 90 Degrees CW
int xVal = 0;
int yVal = 0;

// Output Vars
String message = "";

void setup() {
  // initialize serial communications at 9600 bps:
  if (debugMode){
    Serial.begin(9600);
  } else {
    //BTSerial.begin(9600); 
    Serial1.begin(9600);
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
        if (!rotated){
          message = "0x44"; //"D"
        } else {
          message = "0x44"; //"D"
        }
      } else {
        if (!rotated){
          message = "0x41"; //"A"
        } else {
          message = "0x41"; //"A"
        }
      }
    } else {
      if (yVal > 0){
        if (!rotated){
          message = "0x57"; //"W"
        } else {
          message = "0x53"; //"S"
        }
      } else {
        if (!rotated){
          message = "0x53"; //"S";
        } else {
          message = "0x57"; //"W"
        }
      }
    }
  }

  // Transmit Message
  if (message != ""){
    if (debugMode){
      Serial.println(message);
    }
    else {
      //BTSerial.println(message);
      Serial1.println(message);
    }

    message = "";
  }

  // Delay
  delay(50);
}
