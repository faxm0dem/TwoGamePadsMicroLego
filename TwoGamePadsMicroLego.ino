// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
// 2018-03-01 modification by Fabien Wernli to use two gamepads and support 2 buttons
//--------------------------------------------------------------------

#include <Joystick.h>
#define JOY_COUNT 2

Joystick_ Joystick[JOY_COUNT] = {
  Joystick_(0x03, JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false),
  Joystick_(0x44, JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false),
};

void setup() {
  // Initialize Button Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  // Initialize Joystick Library
  for (int index = 0; index < JOY_COUNT; index++) {
    Joystick[index].begin();
    Joystick[index].setXAxisRange(-1, 1);
    Joystick[index].setYAxisRange(-1, 1);
  }
}

// Last state of the buttons
int lastButtonState[2][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0}};
int buttonPinMap[2][6] = {{2,5,3,4,1,0},{10,6,16,8,9,7}};

void loop() {
// loop through controllers
for (int joy = 0; joy < JOY_COUNT; joy++) {
  // Read pin values
  for (int index = 0; index < 6; index++)
  {
    int currentButtonState = !digitalRead(buttonPinMap[joy][index]);
    if (currentButtonState != lastButtonState[joy][index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick[joy].setYAxis(-1);
          } else {
            Joystick[joy].setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick[joy].setXAxis(1);
          } else {
            Joystick[joy].setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick[joy].setYAxis(1);
          } else {
            Joystick[joy].setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick[joy].setXAxis(-1);
          } else {
            Joystick[joy].setXAxis(0);
          }
          break;
        case 4: // FIRE
          Joystick[joy].setButton(0, currentButtonState);
          break;
        case 5: // FIRE2
          Joystick[joy].setButton(1, currentButtonState);
          break;
      }
      lastButtonState[joy][index] = currentButtonState;
    }
  }
}
  delay(10);
}

