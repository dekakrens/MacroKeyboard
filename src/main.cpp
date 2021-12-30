#include "Keyboard.h"
#include "Keypad.h"
#include "Encoder.h"

const byte ROWS = 3;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'},
    {'9', '0', 'A', 'B'},
};

Encoder RotaryEncoder(4, 5);

// Variables that will change:
int modePushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

long encoderPos = -999;

const int modeButton = 9;       // Define pin for mode button

byte rowPins[ROWS] = {10, 16, A3};
byte colPins[COLS] = {A1, A0, 15, 14};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Sub Routine Section
void checkModeButton() {
    buttonState = digitalRead(modeButton);
    if(buttonState != lastButtonState) {
        if(buttonState == LOW) {
            modePushCounter++;
            Serial.print("Current Mode: ");
            Serial.print(modePushCounter);
            delay(50);
        }
        lastButtonState = buttonState;
        if(modePushCounter > 1) {       //I only set two mode
            modePushCounter = 0;
        }
    }
}

void horizontalEncoder() {
    long newPos = RotaryEncoder.read()/4;

    if(newPos != encoderPos && newPos > encoderPos) {
        encoderPos = newPos;
        Keyboard.press(KEY_LEFT_ARROW);
        Keyboard.release(KEY_LEFT_ARROW);
    }

    if(newPos != encoderPos && newPos < encoderPos) {
        encoderPos = newPos;
        Keyboard.press(KEY_RIGHT_ARROW);
        Keyboard.release(KEY_RIGHT_ARROW);
    }
}

void verticalEncoder() {
    long newPos = RotaryEncoder.read()/4;

    if(newPos != encoderPos && newPos > encoderPos) {
        encoderPos = newPos;
        Keyboard.press(KEY_UP_ARROW);
        Keyboard.release(KEY_UP_ARROW);
    }

    if(newPos != encoderPos && newPos < encoderPos) {
        encoderPos = newPos;
        Keyboard.press(KEY_DOWN_ARROW);
        Keyboard.release(KEY_DOWN_ARROW);
    }
}

void endZoomCall() {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.print('q');
    delay(350);
    Keyboard.release(KEY_LEFT_ALT);
    delay(50);
    Keyboard.write(9);
    delay(350);
    Keyboard.press(KEY_RETURN);
}

void programmingMode() {
    char key = keypad.getKey();
    if(key) {
        switch (key)
        {
        case '1':
            /* code */
            Keyboard.print(key);
            break;
        case '2':
            /* code */
            Keyboard.print(key);
            break;
        case '3':
            /* code */
            Keyboard.print(key);
            break;
        case '4':
            /* code */
            Keyboard.print(key);
            break;
        case '5':
            /* code */
            Keyboard.print(key);
            break;
        case '6':
            /* code */
            Keyboard.print(key);
            break;
        case '7':
            /* code */
            Keyboard.print(key);
            break;
        case '8':
            /* code */
            Keyboard.print(key);
            break;
        case '9':
            /* code */
            Keyboard.print(key);
            break;
        case '0':
            /* code */
            Keyboard.print(key);
            break;
        case 'A':
            /* code */
            Keyboard.print(key);
            break;
        case 'B':
            /* code */
            Keyboard.print(key);
            break;
        
        default:
            break;
        }
    }
}

void keywordingMode() {
    char key = keypad.getKey();
    if(key) {
        switch (key)
        {
        case '1':
            /* code */
            break;
        
        default:
            break;
        }
    }
}

void setup() {
    pinMode(modeButton, INPUT_PULLUP);
    Serial.begin(9600);
    Keyboard.begin();
}

void loop() {
    checkModeButton();

    switch (modePushCounter) {
        case 0:
            horizontalEncoder();
            programmingMode();
            break;

        case 1:
            verticalEncoder();
            programmingMode();
            break;
    }
}
