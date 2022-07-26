#include <Arduino.h>
#include <CircuitOS.h>
#include <Nibble.h>

Display* display;
Sprite* sprite;

//Physics based variables
bool UpHeld;
bool RightHeld;
bool LeftHeld;

float F[2];
float force[2];
float juice;

int bh = 24;
int bw = 24;
int PHBX;
int PHBY;
int LVLx;
int LVLy;
int y = 64;
int x = 64;
int yDir = 0;
int xDir = 0;
int radius = 3;

bool Up;
bool Down;
bool Right;
bool Left;

//Other variables
int level = 0;
int lives = 2;
float timer;
bool speedRun;

bool J; //juice
bool L; //lives
bool T; //timer

bool menu;
bool button[3] = {false, true, false};
int ballColor[7] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_ORANGE, TFT_PURPLE, TFT_YELLOW, TFT_WHITE};
int ballColorIndex = 0;
int menuBallX = 64;
int moveBy = 1;
bool enter;

bool levelBtns[7] = {true, false, false, false, false, false, false};
float levelTimes[5];
bool startTime;
float startingTime;
float curentTime;
bool levelTimesMenu;

bool gameMenu;
bool BtnAny;
bool up;
bool left;
bool right;

void setup() {
  Nibble.begin();
  display = Nibble.getDisplay();
  sprite = display->getBaseSprite();
  Input::getInstance()->setBtnPressCallback(BTN_UP, BTN_UP_press);
  Input::getInstance()->setBtnReleaseCallback(BTN_UP, BTN_UP_release);
  Input::getInstance()->setButtonHeldCallback(BTN_UP, 300, BTN_UP_held_300ms);
  Input::getInstance()->setBtnPressCallback(BTN_RIGHT, BTN_RIGHT_press);
  Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, BTN_RIGHT_release);
  Input::getInstance()->setButtonHeldCallback(BTN_RIGHT, 300, BTN_RIGHT_held_300ms);
  Input::getInstance()->setBtnPressCallback(BTN_LEFT, BTN_LEFT_press);
  Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, BTN_LEFT_release);
  Input::getInstance()->setButtonHeldCallback(BTN_LEFT, 300, BTN_LEFT_held_300ms);
  Input::getInstance()->setBtnPressCallback(BTN_DOWN, BTN_DOWN_press);
  Input::getInstance()->setBtnPressCallback(BTN_A, BTN_A_press);
  Input::getInstance()->setBtnPressCallback(BTN_B, BTN_B_press);
  Input::getInstance()->setBtnPressCallback(BTN_C, BTN_C_press);
  Input::getInstance()->setBtnReleaseCallback(BTN_C, BTN_C_release);
  
  sprite->setTextSize(1);
  sprite->setTextFont(2);
  sprite->setTextColor(TFT_BLACK);
  sprite->clear(TFT_BLACK);

  PHBX = x-radius;
  PHBY = y-radius;

  Level();
}

void loop(){
  Input::getInstance()->loop(0);
  
  if (lives <= 0){
    Level();
    lives = 2;
    }

  if (menu){
    Menu();
    }else{
      RunLevel();
      }

  if (levelTimesMenu){
    LevelTimes();
    }

  if (gameMenu){
    GameMenu();
    }

  if (up || right || left){
    BtnAny = true;
    }else{
      BtnAny = false;
      }
  
  display->commit();
}

void RunLevel(){
  sprite->clear(TFT_LIGHTGREY);
    
  //rendering LEVEL
  _level();

  //physicEngine
  Physics(0.15);
  
  //drawing Player
  Player(force[0], force[1], radius);

  if (UpHeld && juice>0){
    F[1] = -2;
    juice -= 0.5;
    }
  if (RightHeld && juice>0){
    F[0] = 2;
    juice -= 0.5;
    }
  if (LeftHeld && juice>0){
    F[0] = -2;
    juice -= 0.5;
    }
  }

void Menu(){
  sprite->clear(TFT_DARKGREY);
  
  if (button[0]){
    sprite->fillCircle(menuBallX, 30, 13, ballColor[ballColorIndex]);
    sprite->drawCircle(menuBallX, 30, 13, TFT_BLACK);
    sprite->fillTriangle(menuBallX-32, 30, menuBallX-20, 18, menuBallX-20, 42, TFT_LIGHTGREY);
    sprite->setCursor(menuBallX-26, 22);
    sprite->print("L");
    sprite->fillTriangle(menuBallX+32, 30, menuBallX+20, 18, menuBallX+20, 42, TFT_LIGHTGREY);
    sprite->setCursor(menuBallX+21, 22);
    sprite->print("R");
    }else if (!button[0]){
      if (menuBallX == 90){
        moveBy = -1;
        }else if (menuBallX == 38){
          moveBy = 1;
          }
      menuBallX += moveBy;
      sprite->fillCircle(menuBallX, 30, 10, ballColor[ballColorIndex]);
      sprite->drawCircle(menuBallX, 30, 10, TFT_BLACK);
      
      }if (button[1]){
        sprite->fillRect(28, 60, 72, 20, TFT_LIGHTGREY);
        sprite->drawRect(28, 60, 72, 20, TFT_BLACK);
        sprite->setCursor(44, 62);
        sprite->print("TIMES");
        if (enter){
          menu = false;
          speedRun = true;
          levelTimesMenu = true;
          enter = false;
          }
        sprite->setCursor(1, 114);
        sprite->print("A to enter");
        }else if (!button[1]){
          sprite->fillRect(28, 60, 72, 20, TFT_LIGHTGREY);
          sprite->setCursor(50, 62);
          sprite->print("times");
          
          }if (button[2]){
            sprite->fillRect(28, 90, 72, 20, TFT_LIGHTGREY);
            sprite->drawRect(28, 90, 72, 20, TFT_BLACK);
            sprite->setCursor(44, 92);
            sprite->print("START");
            if (enter){
              level = 1;
              Level();
              enter = false;
              }
            sprite->setCursor(1, 114);
            sprite->print("A to enter");
            }else if (!button[2]){
              sprite->fillRect(28, 90, 72, 20, TFT_LIGHTGREY);
              sprite->setCursor(50, 92);
              sprite->print("start");
              }
  }

void LevelTimes(){
  level = 0;
  sprite->clear(TFT_LIGHTGREY);
  
  if (levelBtns[0]){
    if (enter){
      enter = false;
      levelTimesMenu = false;
      level = 1;
      Level();
      }
    sprite->fillRect(28, 5, 95, 20, TFT_DARKGREY);
    sprite->drawRect(28, 5, 95, 20, TFT_RED);
    sprite->setCursor(32, 7);
    sprite->print("1. |");
    sprite->setCursor(65, 7);
    if (levelTimes[0] == 0){
      sprite->print("-.--");
      }else{
        sprite->print(levelTimes[0]);
        }
    }else if (!levelBtns[0]){
      sprite->fillRect(28, 5, 95, 20, TFT_DARKGREY);
      sprite->setCursor(32, 7);
      sprite->print("1. |");
      sprite->setCursor(65, 7);
      if (levelTimes[0] == 0){
        sprite->print("-.--");
        }else{
          sprite->print(levelTimes[0]);
          }
      
      }if (levelBtns[1]){
        if (enter){
          enter = false;
          levelTimesMenu = false;
          level = 2;
          Level();
          }
        sprite->fillRect(28, 30, 95, 20, TFT_DARKGREY);
        sprite->drawRect(28, 30, 95, 20, TFT_RED);
        sprite->setCursor(32, 32);
        sprite->print("2. |");
        sprite->setCursor(65, 32);
        if (levelTimes[1] == 0){
          sprite->print("-.--");
          }else{
            sprite->print(levelTimes[1]);
            }
        }else if (!levelBtns[1]){
          sprite->fillRect(28, 30, 95, 20, TFT_DARKGREY);
          sprite->setCursor(32, 32);
          sprite->print("2. |");
          sprite->setCursor(65, 32);
          if (levelTimes[1] == 0){
            sprite->print("-.--");
            }else{
              sprite->print(levelTimes[1]);
              }
          
          }if (levelBtns[2]){
            if (enter){
              enter = false;
              levelTimesMenu = false;
              level = 3;
              Level();
              }
            sprite->fillRect(28, 55, 95, 20, TFT_DARKGREY);
            sprite->drawRect(28, 55, 95, 20, TFT_RED);
            sprite->setCursor(32, 57);
            sprite->print("3. |");
            sprite->setCursor(65, 57);
            if (levelTimes[2] == 0){
              sprite->print("-.--");
              }else{
                sprite->print(levelTimes[2]);
                }
            }else if (!levelBtns[2]){
              sprite->fillRect(28, 55, 95, 20, TFT_DARKGREY);
              sprite->setCursor(32, 57);
              sprite->print("3. |");
              sprite->setCursor(65, 57);
              if (levelTimes[2] == 0){
                sprite->print("-.--");
                }else{
                  sprite->print(levelTimes[2]);
                  }
          
              }if (levelBtns[3]){
                if (enter){
                  enter = false;
                  levelTimesMenu = false;
                  level = 4;
                  Level();
                  }
                sprite->fillRect(28, 80, 95, 20, TFT_DARKGREY);
                sprite->drawRect(28, 80, 95, 20, TFT_RED);
                sprite->setCursor(32, 82);
                sprite->print("4. |");
                sprite->setCursor(65, 82);
                if (levelTimes[3] == 0){
                  sprite->print("-.--");
                  }else{
                    sprite->print(levelTimes[3]);
                    }
                }else if (!levelBtns[3]){
                  sprite->fillRect(28, 80, 95, 20, TFT_DARKGREY);
                  sprite->setCursor(32, 82);
                  sprite->print("4. |");
                  sprite->setCursor(65, 82);
                  if (levelTimes[3] == 0){
                      sprite->print("-.--");
                      }else{
                        sprite->print(levelTimes[3]);
                        }
          
                  }if (levelBtns[4]){
                    if (enter){
                      enter = false;
                      levelTimesMenu = false;
                      level = 5;
                      Level();
                      }
                    sprite->fillRect(28, 105, 95, 20, TFT_DARKGREY);
                    sprite->drawRect(28, 105, 95, 20, TFT_RED);
                    sprite->setCursor(32, 107);
                    sprite->print("5. |");
                    sprite->setCursor(65, 107);
                    if (levelTimes[4] == 0){
                      sprite->print("-.--");
                      }else{
                        sprite->print(levelTimes[4]);
                        }
                    }else if (!levelBtns[4]){
                      sprite->fillRect(28, 105, 95, 20, TFT_DARKGREY);
                      sprite->setCursor(32, 107);
                      sprite->print("5. |");
                      sprite->setCursor(65, 107);
                      if (levelTimes[4] == 0){
                        sprite->print("-.--");
                        }else{
                          sprite->print(levelTimes[4]);
                          }
                      
                      }if (levelBtns[5]){
                        if (enter){
                          enter = false;
                          for (int i = 0; i < 7; i++){
                            levelTimes[i] = 0;
                            }
                          }
                        sprite->drawRect(5, 5, 20, 95, TFT_RED);
                        sprite->drawLine(24, 5, 5, 99, TFT_RED);
                        sprite->setCursor(12, 6);
                        sprite->print("C");
                        sprite->setCursor(12, 25);
                        sprite->print("L");
                        sprite->setCursor(12, 44);
                        sprite->print("E");
                        sprite->setCursor(12, 63);
                        sprite->print("A");
                        sprite->setCursor(12, 82);
                        sprite->print("R");
                        }else if (!levelBtns[5]){
                          sprite->setCursor(12, 6);
                          sprite->print("C");
                          sprite->setCursor(12, 25);
                          sprite->print("L");
                          sprite->setCursor(12, 44);
                          sprite->print("E");
                          sprite->setCursor(12, 63);
                          sprite->print("A");
                          sprite->setCursor(12, 82);
                          sprite->print("R");
                          
                          }if (levelBtns[6]){
                            if (enter){
                              levelTimesMenu = false;
                              speedRun = false;
                              enter = false;
                              level = 0;
                              Level();
                              }
                            sprite->fillRect(5, 105, 20, 20, TFT_RED);
                            sprite->drawRect(5, 105, 20, 20, TFT_BLACK);
                            sprite->fillTriangle(10, 115, 20, 110, 20, 119, TFT_LIGHTGREY);
                            sprite->drawTriangle(10, 115, 20, 110, 20, 119, TFT_BLACK);
                            }else if (!levelBtns[6]){
                              sprite->fillRect(5, 105, 20, 20, TFT_RED);
                              sprite->fillTriangle(10, 115, 20, 110, 20, 119, TFT_LIGHTGREY);
                              menu = false;
                              }
  }

void GameMenu(){
  sprite->fillRect(20, 20, 88, 88, TFT_LIGHTGREY);
  sprite->drawRect(20, 20, 88, 88, TFT_BLACK);
  sprite->setCursor(26, 34);
  sprite->print("Wanna quit?");
  sprite->fillRect(38, 72, 52, 20, TFT_DARKGREY);
  sprite->drawRect(38, 72, 52, 20, TFT_BLACK);
  sprite->setCursor(48, 72);
  sprite->print("YES");
  
  if (enter){
    if (speedRun){
      level = 0;
      Level();
      menu = false;
      enter = false;
      gameMenu = false;
      levelTimesMenu = true;
      }else{
        level = 0;
        enter = false;
        gameMenu = false;
        Level();
        }
    }
  }

//----------Level-Data----------

int LEVEL[640] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8,
  1, 4, 0, 34, 0, 0, 0, 1, 0, 0, 0, 1, 4, 32, 0, 0, 0, 4, 1, 8,
  1, 1, 0, 34, 0, 1, 0, 0, 0, 1, 0, 0, 0, 32, 0, 21, 21, 1, 1, 8,
  1, 0, 0, 34, 1, 1, 1, 1, 1, 1, 1, 1, 1, 32, 0, 34, 1, 23, 1, 8,
  1, 0, 0, 1, 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 34, 0, 1, 8,
  1, 0, 0, 1, 23, 0, 1, 1, 31, 1, 0, 31, 0, 1, 32, 0, 34, 0, 1, 8,
  32, 0, 0, 34, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 32, 0, 34, 0, 1, 8,
  32, 0, 0, 1, 0, 23, 1, 31, 31, 1, 1, 1, 1, 0, 32, 0, 34, 0, 1, 8,
  32, 0, 23, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 32, 0, 34, 0, 1, 8,
  32, 0, 0, 1, 23, 0, 1, 0, 1, 31, 31, 31, 31, 1, 32, 0, 34, 0, 1, 8,
  32, 0, 0, 1, 0, 0, 1, 0, 1, 4, 0, 0, 0, 0, 32, 0, 34, 0, 1, 8,
  1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 31, 31, 1, 0, 32, 0, 34, 0, 1, 8,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 32, 0, 34, 0, 1, 8,
  1, 0, 0, 1, 21, 1, 33, 1, 31, 1, 31, 1, 31, 1, 32, 0, 34, 0, 1, 8,
  1, 0, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 8,
  1, 31, 1, 1, 1, 1, 0, 22, 0, 1, 31, 1, 1, 0, 1, 0, 23, 0, 1, 8,
  1, 0, 0, 0, 0, 1, 0, 22, 0, 0, 0, 0, 1, 0, 22, 0, 0, 0, 1, 8,
  1, 0, 1, 31, 31, 1, 0, 1, 1, 1, 1, 0, 22, 0, 1, 33, 32, 0, 1, 8,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 8,
  1, 21, 1, 1, 1, 1, 21, 23, 1, 1, 1, 21, 21, 1, 1, 0, 1, 0, 1, 8,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 1, 8,
  1, 33, 31, 31, 31, 31, 1, 0, 1, 31, 31, 1, 31, 31, 1, 0, 1, 0, 1, 8,
  1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 24, 0, 1, 8,
  1, 0, 24, 0, 31, 1, 0, 1, 1, 0, 1, 0, 24, 1, 1, 0, 1, 0, 1, 8,
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 32, 0, 24, 0, 1, 0, 1, 8,
  1, 31, 31, 31, 31, 0, 1, 0, 1, 0, 0, 0, 32, 0, 0, 0, 1, 0, 1, 8,
  1, 4, 0, 0, 1, 0, 1, 31, 1, 0, 21, 1, 1, 1, 1, 21, 1, 0, 1, 8,
  1, 23, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 24, 0, 1, 8,
  1, 0, 0, 23, 23, 0, 21, 21, 21, 0, 1, 0, 0, 0, 24, 0, 1, 0, 1, 8,
  1, 1, 0, 0, 0, 0, 23, 0, 24, 0, 1, 1, 23, 1, 1, 0, 23, 0, 1, 8,
  22, 0, 0, 31, 31, 0, 0, 0, 34, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 8,
  1, 21, 21, 1, 1, 1, 1, 31, 1, 21, 1, 31, 31, 31, 1, 1, 1, 31, 1, 8
};
