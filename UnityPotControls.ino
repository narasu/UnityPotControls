#include <SerialCommand.h>

SerialCommand sCmd;

const int b1Pin = 4;
const int l1Pin = 10;
const int l2Pin = 11;

const int readTimeout = 24;

// Variables will change:
int b1State = 0;         // current state of the button
int b1LastState = 0;     // previous state of the button

int pressed = 0;

byte up = 0;
byte down = 0;
byte left = 0;
byte right = 0;

byte bytesReceived[6];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at b bits per second:
  Serial.begin(9600);
  while (!Serial);

  //sCmd.addCommand("PING", pingHandler);
  // initialize the button pin as a input:
  pinMode(b1Pin, INPUT);

  pinMode(l1Pin, OUTPUT);
  pinMode(l2Pin, OUTPUT);
  
}

void loop() {
  
  // x and y input
  int xVal = analogRead(A0);
  int yVal = analogRead(A1);

  b1LastState = DetectButtonPress(b1Pin, b1State, b1LastState);

  // print out the value you read:
  Serial.print(xVal);Serial.print(";");
  Serial.print(yVal);Serial.print(";");
  Serial.print(b1LastState); 
  Serial.println();
  Serial.flush();

  bytesReceived[5]=0;
  if (Serial.available()>5) {
    int i=0;
    while (Serial.available()>0) {
      if (i<6) {
        bytesReceived[i] = Serial.read();
      }
      else {
        Serial.read();
      }
      i++;
    }
  }
  
  up = bytesReceived[0];
  down = bytesReceived[1];
  left = bytesReceived[2];
  right = bytesReceived[3];


  if (bytesReceived[4] == 0 && bytesReceived[5] == 255){
    analogWrite(l1Pin, up);
    analogWrite(l2Pin, down);
  }

  //analogWrite(l1Pin, 120);
  delay(readTimeout);
}

int DetectButtonPress(int pin, int buttonState, int lastButtonState) {
  // read the pushbutton input pin:
  buttonState = digitalRead(pin);
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  return lastButtonState;
}
