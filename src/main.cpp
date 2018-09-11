#include <Arduino.h>
#include <Keypad.h>
#include <Secrets.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

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
    if (key && key == PASS_CODE[index]) {
        Serial.print("match! key=");
        Serial.print(key);
        Serial.print(", index = ");
        Serial.println(index);
        index++;
        if (index == 4) {
          triggerGarageDoor();
          index = 0;
        }
    } else {
        Serial.print("NO match! key=");
        Serial.print(key);
        Serial.print(", index = ");
        Serial.print(index);
        index = 0;
    }
}
