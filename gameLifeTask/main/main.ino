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

int displayCount = 1;
LedControl display = LedControl(26,22,24,displayCount);
Game game = Game(8);

const uint64_t gameUpdateDelayMs = 500;
const uint64_t displayUpdateDelayMs = 100;
uint64_t lastGameUpdate;
uint64_t lastDisplayUpdate;

void setup ()
{
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  
  for (int i =0;i < displayCount; i++)
  {
    display.shutdown(i, false);
    display.setIntensity(i, 4);
    display.clearDisplay(i);
  }
}

void loop()
{
  
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRect(0, 0, 8, 8,ST77XX_GREEN);
//  writeBoard();
//  updateGame();
}
//
//void writeBoard()
//{
//   if (millis() - lastDisplayUpdate > displayUpdateDelayMs) {
//  for (int i = 0; i < 8; i++)
//    for (int j = 0; j < 8; j++)
//    {
//      int displayNum = (i / 8) + (j / 8);
//      display.setLed(displayNum,i%8,j%8,game.board[i][j]);
//    }
//    lastDisplayUpdate = millis();    
//   }
//}

void updateGame()
{
   if (millis() - lastGameUpdate > gameUpdateDelayMs){
    game.updateBoard();
    lastGameUpdate = millis();
   }
}
