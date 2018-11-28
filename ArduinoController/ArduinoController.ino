int xPin = A1;
int yPin = A0;

String message = "";
int xVal = 0;
int yVal = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);  
}

void loop() {
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

    Serial.println(message);  
    delay(50);
  }
}
