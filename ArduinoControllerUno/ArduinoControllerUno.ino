#include <SoftwareSerial.h>

// Bluetooth Pins
const int rxPin = 2;
const int txPin = 3;
const int statePin = 4;
SoftwareSerial BTSerial(rxPin, txPin);

// Button Pins
const int topButtonPin = A0;
const int leftButtonPin = A1;
const int bottomButtonPin = A2;
const int rightButtonPin = A3;

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

void setup() {
  // Initialize Serial Communication At 9600 Baud Rate
  BTSerial.begin(9600);

  pinMode (topButtonPin, INPUT);
  pinMode (leftButtonPin, INPUT);
  pinMode (bottomButtonPin, INPUT);
  pinMode (rightButtonPin, INPUT);

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

  // Buttons
  if (digitalRead(topButtonPin) == HIGH){
    delay(100);
    
    BTSerial.println("0x50"); // "P"
  } else if (digitalRead(leftButtonPin) == HIGH){
    delay(100);
    
    BTSerial.println("0x50"); // "P"
  } else if (digitalRead(bottomButtonPin) == HIGH){
    delay(100);
    
    BTSerial.println("0x50"); // "P"
  } else if (digitalRead(rightButtonPin) == HIGH){
    delay(100);
    
    BTSerial.println("0x50"); // "P"
  }
  
  // Joystick
  xVal = map(analogRead(xPin), 0, 1023, -100, 100);
  yVal = map(analogRead(yPin), 0, 1023, -100, 100);
  // WASD
  if (!(xVal < 25 && xVal > -25 && yVal < 25 && yVal > -25)){
    if (abs(xVal) > abs(yVal)){
      if (xVal > 0){
        if (!rotated){
          BTSerial.println("0x44"); // "D"
        } else {
          BTSerial.println("0x44"); // "D"
        }
      } else {
        if (!rotated){
          BTSerial.println("0x41"); // "A"
        } else {
          BTSerial.println("0x41"); // "A"
        }
      }
    } else {
      if (yVal > 0){
        if (!rotated){
          BTSerial.println("0x57"); // "W"
        } else {
          BTSerial.println("0x53"); // "S"
        }
      } else {
        if (!rotated){
          BTSerial.println("0x53"); // "S"
        } else {
          BTSerial.println("0x57"); // "W"
        }
      }
    }
  }

  // Delay
  delay(50);
}
