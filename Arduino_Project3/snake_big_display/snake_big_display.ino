#include <U8glib.h>

U8GLIB_ST7920_128X64_4X u8g(10, 11, 12);

const int joyX = A2;
const int joyY = A3;
const int btnPin = 3; 

const int maxLength = 48;
int snakex[maxLength];
int snakey[maxLength];
int appleX, appleY;
int height = 4;
int length = 1;
int dirx = 2;
int diry = 0;
int dela = 110;
const int deadZone = 200;

bool appleEaten = true;
bool gamePaused = false;
bool isGameOver = false;
int score = 0;

void resetGame() {
  length = 1;
  score = 0;
  snakex[0] = 64;
  snakey[0] = 32;
  dirx = 2;
  diry = 0;
  isGameOver = false;
  gamePaused = false;
  appleEaten = true;
}

void setup() {
  pinMode(btnPin, INPUT_PULLUP);
  randomSeed(analogRead(0));
  resetGame();
}

void updateLogic() {
  if (digitalRead(btnPin) == LOW) {
    delay(200); 
    if (isGameOver) resetGame();
    else gamePaused = !gamePaused;
    return;
  }

  if (gamePaused || isGameOver) return;

  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);

  if (xVal < 512 - deadZone && dirx == 0) { dirx = -2; diry = 0; }
  else if (xVal > 512 + deadZone && dirx == 0) { dirx = 2; diry = 0; }
  else if (yVal < 512 - deadZone && diry == 0) { dirx = 0; diry = -2; }
  else if (yVal > 512 + deadZone && diry == 0) { dirx = 0; diry = 2; }

  for (int i = length - 1; i > 0; i--) {
    snakex[i] = snakex[i - 1];
    snakey[i] = snakey[i - 1];
  }

  snakex[0] += dirx;
  snakey[0] += diry;

  if (snakex[0] < 0 || snakex[0] >= 128 || snakey[0] < 0 || snakey[0] >= 64) {
    isGameOver = true;
    return;
  }

  if (abs(snakex[0] - appleX) < 4 && abs(snakey[0] - appleY) < 4) {
    if (length < maxLength) length++;
    score += 10;
    appleEaten = true;
  }

  if (appleEaten) {
    appleX = random(4, 120);
    appleY = random(4, 58);
    appleEaten = false;
  }

  for (int i = 1; i < length; i++) {
    if (snakex[0] == snakex[i] && snakey[0] == snakey[i]) isGameOver = true;
  }
}

void draw() {
  u8g.drawCircle(appleX, appleY, 2);
  for (int i = 0; i < length; i++) {
    u8g.drawBox(snakex[i], snakey[i], height, height);
  }

  u8g.setFont(u8g_font_4x6);
  u8g.setPrintPos(100, 6);
  u8g.print("SC:");
  u8g.print(score);

  if (gamePaused && !isGameOver) {
    u8g.setColorIndex(0);
    u8g.drawBox(30, 22, 68, 18);
    u8g.setColorIndex(1);
    u8g.drawFrame(30, 22, 68, 18);
    u8g.setFont(u8g_font_5x7);
    u8g.drawStr(44, 34, "PAUSED");
  }

  if (isGameOver) {
    u8g.setColorIndex(0);
    u8g.drawBox(2, 15, 124, 34);
    u8g.setColorIndex(1);
    u8g.drawFrame(2, 15, 124, 34);
    u8g.setFont(u8g_font_6x10);
    u8g.drawStr(34, 28, "GAME OVER!");
    u8g.setFont(u8g_font_4x6);
    u8g.drawStr(10, 42, "PRESS BUTTON TO RESTART");
  }
}

void loop() {
  updateLogic();
  u8g.firstPage(); 
  do {
    draw();
  } while (u8g.nextPage());
  delay(dela);
}