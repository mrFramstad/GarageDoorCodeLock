#include <Arduino.h>
#include <Keypad.h>
#include <Secrets.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int releePin = 12;
int index = 0;

void setup() {
    Serial.begin(115200);
    pinMode(releePin, OUTPUT);
}

void triggerGarageDoor () {
    digitalWrite(releePin, HIGH);
    delay(250);
    digitalWrite(releePin, LOW);
}

void loop() {
    char key = keypad.getKey();
    if (key) {
      if (key && key == PASS_CODE[index]) {
          Serial.print("match! key=");
          Serial.print(key);
          Serial.print(", index = ");
          Serial.println(index);
          index++;
          if (index == PASS_CODE_LENGTH) {
            triggerGarageDoor();
            index = 0;
          }
      } else {
          Serial.print("NO match! key=");
          Serial.print(key);
          Serial.print(", index = ");
          Serial.println(index);
          index = 0;
      }
  }
}
