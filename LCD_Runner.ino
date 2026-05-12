#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 7;

int playerRow = 1;
int obstaclePos = 15;
int score = 0;

bool gameOver = false;
bool gameStarted = false;

// Player Character
byte player[8] = {
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

void setup() {

  lcd.init();
  lcd.backlight();

  pinMode(buttonPin, INPUT_PULLUP);

  lcd.createChar(0, player);

  lcd.clear();

  // Start Screen
  lcd.setCursor(2, 0);
  lcd.print("LCD RUNNER");

  lcd.setCursor(1, 1);
  lcd.print("Press Button");
}

void resetGame() {

  obstaclePos = 15;
  score = 0;
  gameOver = false;

  lcd.clear();
}

void loop() {

  // Start Game
  if (!gameStarted) {

    if (digitalRead(buttonPin) == LOW) {

      delay(200);
      gameStarted = true;
      lcd.clear();
    }

    return;
  }

  // Restart Game
  if (gameOver) {

    if (digitalRead(buttonPin) == LOW) {

      delay(200);

      resetGame();
    }

    return;
  }

  // Jump
  if (digitalRead(buttonPin) == LOW) {
    playerRow = 0;
  } else {
    playerRow = 1;
  }

  lcd.clear();

  // Score on Right Side
  lcd.setCursor(6, 0);
  lcd.print("Score:");
  lcd.print(score);

  // Player
  lcd.setCursor(1, playerRow);
  lcd.write(byte(0));

  // Obstacle
  lcd.setCursor(obstaclePos, 1);
  lcd.print("|");

  // Collision
  if (obstaclePos == 1 && playerRow == 1) {

    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("GAME OVER");

    lcd.setCursor(2, 1);
    lcd.print("Score:");
    lcd.print(score);

    gameOver = true;

    return;
  }

  // Move Obstacle
  obstaclePos--;

  // Increase Score
  if (obstaclePos < 0) {

    obstaclePos = 15;
    score++;
  }

  delay(150);
}