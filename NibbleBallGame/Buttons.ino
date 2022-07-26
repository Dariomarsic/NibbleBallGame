void BTN_A_press(){
  Piezo.tone(220, 50);
  if ((level == 0 || gameMenu) && !button[0]){
    enter = true;
    }else{
      Level();
      }
  }

void BTN_B_press(){
  if (Piezo.isMuted()){
    Piezo.setMute(false);
    }else{
      Piezo.setMute(true);
      }
  }

void BTN_C_press(){
  if (level > 0){
    gameMenu = true;
    }
  }

void BTN_C_release(){
  gameMenu = false;
  }

void BTN_DOWN_press(){
  if (level == 0 && menu){
    if (button[0]){
      button[1] = true;
      button[0] = false;
      }else if (button[1]){
        button[2] = true;
        button[1] = false;
        }else if (button[2]){
          button[0] = true;
          button[2] = false;
          }
    }else if (level == 0 && levelTimesMenu){
      if (levelBtns[0]){
        levelBtns[1] = true;
        levelBtns[0] = false;
        }else if (levelBtns[1]){
          levelBtns[2] = true;
          levelBtns[1] = false;
          }else if (levelBtns[2]){
            levelBtns[3] = true;
            levelBtns[2] = false;
            }else if (levelBtns[3]){
              levelBtns[4] = true;
              levelBtns[3] = false;
              }else if (levelBtns[4]){
                levelBtns[5] = true;
                levelBtns[4] = false;
                }else if (levelBtns[5]){
                  levelBtns[6] = true;
                  levelBtns[5] = false;
                  }else if (levelBtns[6]){
                    levelBtns[0] = true;
                    levelBtns[6] = false;
                    }
      }
  }

void BTN_UP_press(){
  up = true;
  if (juice > 0 && level > 0){
    F[1] = -4;
    juice -= 6;
    }else if (level == 0 && menu){
      if (button[0]){
        button[2] = true;
        button[0] = false;
          }else if (button[2]){
            button[1] = true;
            button[2] = false;
              }else if (button[1]){
                button[0] = true;
                button[1] = false;
                }
      }else if (level == 0 && levelTimesMenu){
        if (levelBtns[0]){
          levelBtns[6] = true;
          levelBtns[0] = false;
          }else if (levelBtns[1]){
            levelBtns[0] = true;
            levelBtns[1] = false;
            }else if (levelBtns[2]){
              levelBtns[1] = true;
              levelBtns[2] = false;
              }else if (levelBtns[3]){
                levelBtns[2] = true;
                levelBtns[3] = false;
                }else if (levelBtns[4]){
                  levelBtns[3] = true;
                  levelBtns[4] = false;
                    }else if (levelBtns[5]){
                      levelBtns[4] = true;
                      levelBtns[5] = false;
                      }else if (levelBtns[6]){
                        levelBtns[5] = true;
                        levelBtns[6] = false;
                        }
      }
  }

void BTN_UP_release(){
  up = false;
  UpHeld = false;
  }

void BTN_UP_held_300ms(){
  up = true;
  UpHeld = true;
  }

void BTN_RIGHT_press(){
  right = true;
  if (juice > 0 && level > 0){
    F[0] = 4;
    juice -= 6;
    }else if (level == 0 && button[0]){
      if (ballColorIndex == 6){
        ballColorIndex = 0;
        }else{
          ballColorIndex++;
          }
      }
  }

void BTN_RIGHT_release(){
  right = false;
  RightHeld = false;
  }

void BTN_RIGHT_held_300ms(){
  right = true;
  RightHeld = true;
  }

void BTN_LEFT_press(){
  left = true;
  if (juice > 0 && level > 0){
    F[0] = -4;
    juice -= 6;
    }else if (level == 0 && button[0]){
      if (ballColorIndex == 0){
        ballColorIndex = 6;
        }else{
          ballColorIndex--;
          }
      }
  }

void BTN_LEFT_release(){
  left = false;
  LeftHeld = false;
  }

void BTN_LEFT_held_300ms(){
  left = true;
  LeftHeld = true;
  }
