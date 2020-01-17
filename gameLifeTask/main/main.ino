#include "LedControl.h"
#include "game.h"

//#include <TFT.h> 
//#include <SPI.h>
//
//#define cs 10
//#define dc 9
//#define rst 8

//TFT TFTscreen = TFT(cs, dc, rst);

int displayCount = 1;
LedControl display = LedControl(26,22,24,displayCount);
Game game = Game(8);

const uint64_t gameUpdateDelayMs = 500;
const uint64_t displayUpdateDelayMs = 100;
uint64_t lastGameUpdate;
uint64_t lastDisplayUpdate;

void setup ()
{
//  TFTscreen.begin();
//  TFTscreen.background(100, 0, 0);
//  TFTscreen.setTextSize(2);
//  
  for (int i =0;i < displayCount; i++)
  {
    display.shutdown(i, false);
    display.setIntensity(i, 4);
    display.clearDisplay(i);
  }
}

void loop()
{
//  int redRandom = random(0, 255);
//  int greenRandom = random (0, 255);
//  int blueRandom = random (0, 255);
//
//  TFTscreen.stroke(redRandom, greenRandom, blueRandom);
//
//  TFTscreen.text("Hello, World!", 6, 57);
//
//  delay(200);
//  
  writeBoard();
  updateGame();
}

void writeBoard()
{
   if (millis() - lastDisplayUpdate > displayUpdateDelayMs) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      int displayNum = (i / 8) + (j / 8);
      display.setLed(displayNum,i%8,j%8,game.board[i][j]);
    }
    lastDisplayUpdate = millis();    
   }
}

void updateGame()
{
   if (millis() - lastGameUpdate > gameUpdateDelayMs){
    game.updateBoard();
    lastGameUpdate = millis();
   }
}
