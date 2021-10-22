const int buttonPin0 = 2;
const int buttonPin1 = 4;
int buttonState0 = 0;
int buttonState1 = 0;
byte inByte = 0;
int bandera0 = 0;
int bandera1 = 0;

#include "pitches.h"
const int buttonPin = 2;    // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
const int buttonPin2 = 3;    // the number of the pushbutton pin
int buttonState2;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
const int buttonPin3 = 4;    // the number of the pushbutton pin
int buttonState3;             // the current reading from the input pin
int lastButtonState3 = LOW;   // the previous reading from the input pin
const int buttonPin4 = 7;    // the number of the pushbutton pin
int buttonState4;             // the current reading from the input pin
int lastButtonState4 = LOW;   // the previous reading from the input pin

const int tiva = 6;
int tstate = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime4 = 0;  // the last time the output pin was toggled

unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// notes in the melody:
int melody[] = {
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, 
NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,  
NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 
NOTE_F5, NOTE_G5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_D5,
0, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_D5, NOTE_B4, NOTE_E5, NOTE_F5,
NOTE_F5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
NOTE_D5, 0, 0, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_F5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5,
NOTE_A5, NOTE_D5, 0, NOTE_D5, NOTE_E4, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, 
NOTE_D5, 0, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_D5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4,8,4,8,4,8,8,8,8,4,8,4,8,4,8,8,8,8,4,8,4,8,
4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
8,4,8,8,8,4,4,8,8,4,4,8,8,4,4,8,4,
4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
8,4,8,8,8,4,4,4,8,4,8,8,8,4,4,8,8
};

int noteDurationsp[] = {
  60, 40
};
int melodyp[] = {
  NOTE_C6, NOTE_D6
};

void setup(){
 Serial.begin(9600);
 pinMode(buttonPin0, INPUT_PULLUP);
 pinMode(buttonPin1, INPUT_PULLUP);
 
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(tiva, INPUT);
}

void loop(){
  inByte = 0;
  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState0 == HIGH) {
    bandera0 = 1;   
  }else{
   if(bandera0 == 1){
      inByte = 1;
      bandera0 = 0;
      }
    }
   
  if (buttonState1 == HIGH) {
    bandera1 = 1;   
  }else{
   if(bandera1 == 1){
      inByte = 2;
      bandera1 = 0;
      }
    }
    Serial.write(inByte);
    Serial.println(inByte);
    delay(75);
    
  tstate = digitalRead(tiva);
  if (tstate == LOW){
     // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(melody)/sizeof(int)); thisNote++) {
    tstate = digitalRead(tiva);
    if (tstate == HIGH){
      break;
    }
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  }


  if (tstate == HIGH){
int reading = !digitalRead(buttonPin);


  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
            for (int thisNote = 0; thisNote < 2; thisNote++) {
              int noteDuration = 1000 / noteDurationsp[thisNote];
              tone(8, melodyp[thisNote], noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
      }
    }
  }

  
  int reading2 = !digitalRead(buttonPin2);

    if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }


    if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
            for (int thisNote = 0; thisNote < 2; thisNote++) {
              int noteDuration = 1000 / noteDurationsp[thisNote];
              tone(8, melodyp[thisNote], noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
      }
    }
  }


     int reading3 = !digitalRead(buttonPin3);

    if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime3 = millis();
  }



    if ((millis() - lastDebounceTime3) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      // only toggle the LED if the new button state is HIGH
      if (buttonState3 == HIGH) {
            for (int thisNote = 0; thisNote < 2; thisNote++) {
              int noteDuration = 1000 / noteDurationsp[thisNote];
              tone(8, melodyp[thisNote], noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
      }
    }
  }


   
   int reading4 = !digitalRead(buttonPin4);
      if (reading4 != lastButtonState4) {
      // reset the debouncing timer
      lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

      // only toggle the LED if the new button state is HIGH
      if (buttonState4 == HIGH) {
            for (int thisNote = 0; thisNote < 2; thisNote++) {
              int noteDuration = 1000 / noteDurationsp[thisNote];
              tone(8, melodyp[thisNote], noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
      }
    }
  }



  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
  lastButtonState4 = reading4;  
  }
}
