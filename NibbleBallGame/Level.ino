void Level(){
  if (level == 0){
    menu = true;
    
    }else if (level == 1){
      menu = false;
      if (speedRun){
        juice = 126;
        L = true;
        J = true;
        T = true;
        startTime = true;
        }else{
          juice = 9999;
          L = false;
          J = false;
          T = false;
          }
      moveByPixels(-LVLx-64, -LVLy-64);
      moveByPixels(108, 60);
      
      }else if (level == 2){
        menu = false;
        if (speedRun){
          juice = 126;
          L = true;
          J = true;
          T = true;
          startTime = true;
          }else{
            juice = 9999;
            L = true;
            J = false;
            T = false;
            }
        moveByPixels(-LVLx-64, -LVLy-64);
        moveByPixels(132, 300);
        
        }else if (level == 3){
          menu = false;
          if (speedRun){
            juice = 126;
            L = true;
            J = true;
            T = true;
            startTime = true;
            }else{
              juice = 126;
              L = true;
              J = true;
              T = false;
              }
          moveByPixels(-LVLx-64, -LVLy-64);
          moveByPixels(180, 108);
          
          }else if (level == 4){
            menu = false;
            juice = 126;
            L = true;
            J = true;
            T = true;
            startTime = true;
            moveByPixels(-LVLx-64, -LVLy-64);
            moveByPixels(324, 348);
            
            }else if (level == 5){
              menu = false;
              juice = 126;
              L = true;
              J = true;
              T = true;
              startTime = true;
              moveByPixels(-LVLx-64, -LVLy-64);
              moveByPixels(36, 492);
              }
  }
