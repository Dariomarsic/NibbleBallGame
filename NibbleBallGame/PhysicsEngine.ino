float drag = 0.2;
float G = 0.2;

void Physics(float g){
  Collision();
  
  ColReaction();
  
  force[0] = F[0];
  force[1] = F[1];

  if (!Down && F[1] >= 0){
    force[1] += G;
    if (G < 3){
      G += g;
      }
    }else{
      G = 0.2;
      }
  
  Drag();

  if (L){
    Lives();
    }

  if (J){
    Juice();
    }

  if (T){
    Timer();
    }
}

void Collision(){
  int BLOx;
  int BLOy;
  int xof;
  int yof;
  
  int UPy;
  int DOWNy;
  int RIGHTx;
  int LEFTx;

  if (force[0] > 0){
    xof = -radius;
    }else if (force[0] < 0){
      xof = radius;
      }else{
        xof = 0;
        }

  if (force[1] > 0){
    yof = -radius;
    }else if (force[1] < 0){
      yof = radius;
      }else{
        yof = 0;
        }
  
  BLOx = (x+LVLx+xof)/bw;
  BLOy = (y+LVLy+yof)/bh;

  UPy = -LVLy+(BLOy*bh)-1;
  DOWNy = -LVLy+(BLOy*bh)+bh;
  RIGHTx = -LVLx+(BLOx*bw)+bw;
  LEFTx = -LVLx+(BLOx*bw)-1;

  int CurrentBlock;

  CurrentBlock = BLOx+(BLOy*20);

  if (LEVEL[-20+CurrentBlock] > 0 && UPy >= PHBY){
    if (LEVEL[-20+CurrentBlock] == 4){
      Piezo.tone(800, 50);
      if (speedRun){
        StopTimer();
        level = 0;
        Level();
        menu = false;
        levelTimesMenu = true;
        }else if (level == 5){
          StopTimer();
          level = 0;
          Level();
          }else{
            StopTimer();
            level += 1;
            Level();
            }
      }else if (LEVEL[-20+CurrentBlock] == 23){
        lives -= 1;
        Piezo.tone(500, 50);
        }else if (LEVEL[-20+CurrentBlock] == 33){
          lives -= 2;
          Piezo.tone(100, 50);
          }
    Up = true;
    moveByPixels(0, 1);
    }else{
      Up = false;
      }
  if (LEVEL[20+CurrentBlock] > 0 && DOWNy <= PHBY+(2*radius)){
    if (LEVEL[20+CurrentBlock] == 4){
      Piezo.tone(800, 50);
      if (speedRun){
        StopTimer();
        level = 0;
        Level();
        menu = false;
        levelTimesMenu = true;
        }else if (level == 5){
          StopTimer();
          level = 0;
          Level();
          }else{
            StopTimer();
            level += 1;
            Level();
            }
      }else if (LEVEL[20+CurrentBlock] == 21){
        lives -= 1;
        Piezo.tone(500, 50);
        }else if (LEVEL[20+CurrentBlock] == 31){
          lives -= 2;
          Piezo.tone(100, 50);
          }
    Down = true;
    }else{
      Down = false;
      }
  if (LEVEL[1+CurrentBlock] > 0 && RIGHTx <= PHBX+(2*radius)){
    if (LEVEL[1+CurrentBlock] == 4){
      Piezo.tone(800, 50);
      if (speedRun){
        StopTimer();
        level = 0;
        Level();
        menu = false;
        levelTimesMenu = true;
        }else if (level == 5){
          StopTimer();
          level = 0;
          Level();
          }else{
            StopTimer();
            level += 1;
            Level();
            }
      }else if (LEVEL[1+CurrentBlock] == 24){
        lives -= 1;
        Piezo.tone(500, 50);
        }else if (LEVEL[1+CurrentBlock] == 34){
          lives -= 2;
          Piezo.tone(100, 50);
          }
    Right = true;
    moveByPixels(-1, 0);
    }else{
      Right = false;
      }
  if (LEVEL[-1+CurrentBlock] > 0 && LEFTx >= PHBX){
    if (LEVEL[-1+CurrentBlock] == 4){
      Piezo.tone(800, 50);
      if (speedRun){
        StopTimer();
        level = 0;
        Level();
        menu = false;
        levelTimesMenu = true;
        }else if (level == 5){
          StopTimer();
          level = 0;
          Level();
          }else{
            StopTimer();
            level += 1;
            Level();
            }
      }else if (LEVEL[-1+CurrentBlock] == 22){
        lives -= 1;
        Piezo.tone(500, 50);
        }else if (LEVEL[-1+CurrentBlock] == 32){
          lives -= 2;
          Piezo.tone(100, 50);
          }
    Left = true;
    moveByPixels(1, 0);
    }else{
      Left = false;
      }
}

void ColReaction(){
  if (Up){
    F[1] = -(F[1]/2);
    }

  if (Right){
    F[0] = -F[0];
    }else if (Left){
      F[0] = -F[0];
      }
}

void Lives(){
  sprite->drawCircle(14, 109, 4, TFT_BLACK);
  sprite->drawCircle(22, 109, 4, TFT_BLACK);
  sprite->drawTriangle(10, 111, 26, 111, 18, 119, TFT_BLACK);

  if (lives == 1){
    sprite->fillCircle(14, 109, 3, TFT_RED);
    sprite->fillTriangle(11, 111, 18, 111, 18, 118, TFT_RED);
    sprite->fillCircle(22, 109, 3, TFT_LIGHTGREY);
    sprite->fillTriangle(18, 111, 25, 111, 18, 118, TFT_LIGHTGREY);
    }else if (lives > 1){
      sprite->fillCircle(14, 109, 3, TFT_RED);
      sprite->fillCircle(22, 109, 3, TFT_RED);
      sprite->fillTriangle(11, 111, 25, 111, 18, 118, TFT_RED);
      }
  }

void Juice(){
  if (juice < 126 && !BtnAny){
    juice += 0.3;
    }else if (juice <= 0 && BtnAny){
      Piezo.tone(60, 10);
      }

  sprite->fillCircle(110, 111, juice/18, TFT_BLUE);
  sprite->drawCircle(110, 111, 8, TFT_BLACK);
  }

void Timer(){
  if (startTime){
    startingTime = millis();
    startTime = false;
    }
  curentTime = 0.001*(millis()-startingTime);

  sprite->setCursor(45, 104);
  sprite->print(curentTime);

  if (speedRun){
    if (levelTimes[-1+level] == 0){
      sprite->setCursor(45, 2);
      sprite->print("-.--");
      }else{
        sprite->setCursor(45, 2);
        sprite->print(levelTimes[-1+level]);
        }
    }
  }

void StopTimer(){
  if ((level > 3 || speedRun) && (curentTime < levelTimes[-1+level] || levelTimes[-1+level] == 0)){
    levelTimes[-1+level] = curentTime;
    }
  }

void Drag(){
  if (F[0] > 0){
    F[0] -= drag;
    }
  if (F[0] < 0){
    F[0] += drag;
    }
  if (F[1] > 0){
    F[1] -= drag;
    }
  if (F[1] < 0){
    F[1] += drag;
    }
}

void moveByPixels(int Xpix, int Ypix){
  LVLx += Xpix;
  LVLy += Ypix;
}
