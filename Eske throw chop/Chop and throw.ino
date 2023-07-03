#include <Keyboard.h>

void yeet(){
  if(digitalRead(9)== HIGH){
    Keyboard.press(KEY_LEFT_CTRL);
    delay(50);
    Keyboard.press('W');
    delay(50);
    Keyboard.release(KEY_LEFT_CTRL);
    delay(50);
    Keyboard.release('w');
  }
}

void pickupndrop(){
  if(digitalRead(9)== HIGH){
    Keyboard.press(' ');
    Keyboard.release(' ');
  }
}

void cancelchop(bool &chop){
  Keyboard.press('s');
    delay(200);
    Keyboard.release('s');

    Keyboard.press('a');
    delay(200);
    Keyboard.release('a');

    Keyboard.press('w');
    delay(200);
    Keyboard.release('w');

    Keyboard.press('d');
    delay(200);
    Keyboard.release('d');
     chop = true;
}

void chop(bool &chop){
  Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.release(KEY_LEFT_CTRL);
    chop = false;
}

void setup() {
  pinMode(13, INPUT);
  pinMode(9, INPUT);
  
  
}
bool stopchop = true;
bool tootilted = true;

void loop() {
  if(digitalRead(13)== HIGH){
    chop(stopchop);
  } else if (!stopchop && !(digitalRead(9)== HIGH)) {
    cancelchop(stopchop);
  }
 
  if(digitalRead(9)== HIGH){
    pickupndrop();
  }
}