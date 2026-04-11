#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int symbolButtonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int backButtonPin = 10;

char symbols[] = {'h', 'e', 'l', 'o', ' ', 'w', 'r', 'd'};

String currentText = "";

void setup() {
  lcd.init();
  lcd.backlight();

  for(int i = 0; i < 8; i++) {
    pinMode(symbolButtonPins[i], INPUT_PULLUP);
  }
  pinMode(backButtonPin, INPUT_PULLUP);
  
  lcd.setCursor(0, 0);
  lcd.print("Ready to type:");
}

void loop() {
  for(int i = 0; i < 8; i++) {
    if (digitalRead(symbolButtonPins[i]) == LOW) {
      currentText += symbols[i];
      updateDisplay();
      delay(200);
    }
  }

  if (digitalRead(backButtonPin) == LOW) {
    if (currentText.length() > 0) {
      currentText.remove(currentText.length() - 1);
      updateDisplay();
    }
    delay(200);
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Text:");
  lcd.setCursor(0, 1);
  lcd.print(currentText);
}