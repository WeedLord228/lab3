#include "LedControl.h"
#include "game.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


GameState gs = Preparing;
int displayCount = 1;
LedControl display = LedControl(26,22,24,displayCount);
Game game = Game(16);

const uint64_t gameUpdateDelayMs = 200;
const uint64_t displayUpdateDelayMs = 100;
uint64_t lastGameUpdate;
uint64_t lastDisplayUpdate;

void setup ()
{
  Serial.begin(115200);
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);
}

void loop()
{
  char command = Serial.read();
  if(tolower(command) == 's')
  {
    gs = Playing;
  }
  if(tolower(command) == 'p')
  if (gs == Preparing){
  changeBoard(Serial.parseInt(),Serial.parseInt());
  }
  
  drawBoard();
  if (gs == Playing){
    updateGame();
  }
}

void drawBoard()
{
   if (millis() - lastDisplayUpdate > displayUpdateDelayMs) {
  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++)
    {
      if (game.board[i][j]){
        tft.fillRect(i*8, j*8, 8, 8,ST77XX_GREEN);
      }
      else
      {
        tft.fillRect(i*8, j*8, 8, 8,ST77XX_BLACK);
      }
    }
    lastDisplayUpdate = millis();    
   }
}

void changeBoard (int i, int j)
{
  bool c = game.board[i][j];
  game.board[i][j] = !c;
}

void updateGame()
{
   if (millis() - lastGameUpdate > gameUpdateDelayMs){
    game.updateBoard();
    lastGameUpdate = millis();
   }
}
