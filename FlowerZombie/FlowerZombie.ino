#include "constants.h"
#include "variables.h"

void setup() {
  Serial.begin(9600); // For debugging purposes
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT);
}

void loop() {
  
  read_count_button();
  read_reset_button();
  
}

// https://www.arduino.cc/en/Tutorial/StateChangeDetection
// Read's the number of times the input button has been pressed
// and then adds to a count if the button has been pressed and moves the rack incrementally
void read_count_button(){
  countButtonState = digitalRead(COUNT_BUTTON_PIN);

  if (countButtonState != countLastButtonState) {
    if (countButtonState == HIGH) {
      cupCount++;
        while(count <= FULL_ROTATION && count <= (64*cupCount) && !resetState){
          move_up();
          count++;
        }
    }
    delay(50);
  }
  countLastButtonState = countButtonState;
}

// Read's if the reset button has been reset
// and then calls the reset_rack() method to return the rack to it's starting position
void read_reset_button(){
  resetButtonState = digitalRead(RESET_BUTTON_PIN);

  if (resetButtonState != resetLastButtonState) {
    if (resetButtonState == HIGH) {
      reset_rack();
    }
    delay(50);
  }
  resetLastButtonState = resetButtonState;
}

// Method to reset the rack position to the starting position based on how the current count amoun
void reset_rack(){
    while(count >= 0){
      resetState = true;
      Serial.println(count);
      move_down();
      count--;
    }
    cupCount = 0;
    resetState = false;
}

// Adapted from nikodembartnik.pl by Nikodem Bartnik
// Method to move the rack up
void move_down(){
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);
  
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);
  
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);
  
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  delay(2);
}

// Adapted from nikodembartnik.pl by Nikodem Bartnik
// Method to move the rack down
void move_up(){
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  delay(2); 

  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);

  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);

  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  delay(2);
}
