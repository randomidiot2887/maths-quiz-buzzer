#include <Arduino.h>

/*
Made for four houses
each house gets one led and one button
the buttons are retarded
*/

// Array containing buttons so i can easily talk with the buttons
const int BUTTONS[4] = {4, 5, 6, 7};
// Array containing leds so i can easily talk with the leds
const int LED[4] = {8, 9, 10, 11};
// pin id of master button
const int MASTER_BUTTON(3);
// Serial baud
const int SERIAL_BAUD(9600);

int state = 0;
// VOID SETUP, SO THE BOOTLOADER OF TGHE ARDUINO WILL BE FUCKING HAPPY
void setup() {
  // Initialising Serial
  Serial.begin(SERIAL_BAUD);
  Serial.print(SERIAL_BAUD); Serial.println(" baud is the frequency at which the Arduino has been made to output serial at");

  // Setting pinMode
  for (int i=0; i<4; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
    pinMode(LED[i], OUTPUT);
  }
  Serial.println("Initialised I/O");
}

// Allows program to determine what mode it is in
void State(int state = 0) {
  // In state 0, the program will check if any of the buttons are pressed
  // In state 1, the program will wait until the fucking master button is pressed
  if (state == 0) {
    state++;
    }
  else if (state == 1) {
    state = 0;
    }
}


// TO SHUT UP COMPILER
void loop() {
  // Waiting until any team presses their button, so the state can be changed and the program can start waiting for the master button to be pressed
  if (state == 0) {
    for (int i=0; i<4; i++) {
      if (digitalRead(BUTTONS[i]) == LOW) {
        Serial.print("Button "); Serial.print(i); Serial.println(" is pressed");
        digitalWrite(LED[i], HIGH);
        State(state);
      }
    }
  }
  // Waiting for the master button to be pressed, so the state can be reset and the program can start over
  else if (state == 1) {
    if (digitalRead(MASTER_BUTTON) == LOW) {
      Serial.println("Master button is pressed, resetting state");
      for (int i=0; i<4; i++) {
        digitalWrite(LED[i], LOW);
      }
      State(state);
    }
  }
}
