void block (int bx, int by, int bw, int bh){
  sprite->fillRect(bx-LVLx, by-LVLy, bw, bh, TFT_DARKGREY);
}

void lava (int bx, int by, int bw, int bh, int ori){
  if (ori == 1){
    sprite->fillRect(bx-LVLx, by-LVLy, bw, bh/2, TFT_RED);
    sprite->fillRect(bx-LVLx, by-LVLy+(bh/2), bw, bh/2, TFT_DARKGREY);
    }else if (ori == 2){
      sprite->fillRect(bx-LVLx, by-LVLy, bw/2, bh, TFT_DARKGREY);
      sprite->fillRect(bx-LVLx+(bh/2), by-LVLy, bw/2, bh, TFT_RED);
      }else if (ori == 3){
        sprite->fillRect(bx-LVLx, by-LVLy, bw, bh/2, TFT_DARKGREY);
        sprite->fillRect(bx-LVLx, by-LVLy+(bh/2), bw, bh/2, TFT_RED);
        }else if (ori == 4){
          sprite->fillRect(bx-LVLx, by-LVLy, bw/2, bh, TFT_RED);
          sprite->fillRect(bx-LVLx+(bh/2), by-LVLy, bw/2, bh, TFT_DARKGREY);
          }
}

void spike (int bx, int by, int bw, int bh, int ori){
  if (ori == 1){
    sprite->fillTriangle(bx-LVLx, by-LVLy+(bh/2), bx-LVLx+(bw/4), by-LVLy, bx-LVLx+(bw/2), by-LVLy+(bh/2), TFT_DARKCYAN);
    sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy+(bh/2), bx-LVLx+bw-(bw/4), by-LVLy, bx-LVLx+bw, by-LVLy+(bh/2), TFT_DARKCYAN);
    sprite->fillRect(bx-LVLx, by-LVLy+(bh/2), bw, bh/2, TFT_DARKGREY);
    }else if (ori == 2){
      sprite->fillRect(bx-LVLx, by-LVLy, bw/2, bh, TFT_DARKGREY);
      sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy, bx-LVLx+bw, by-LVLy+(bh/4), bx-LVLx+(bw/2), by-LVLy+(bh/2), TFT_DARKCYAN);
      sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy+(bh/2), bx-LVLx+bw, by-LVLy+bh-(bh/4), bx-LVLx+(bw/2), by-LVLy+bh, TFT_DARKCYAN);
      }else if (ori == 3){
        sprite->fillRect(bx-LVLx, by-LVLy, bw, bh/2, TFT_DARKGREY);
        sprite->fillTriangle(bx-LVLx, by-LVLy+(bh/2), bx-LVLx+(bw/4), by-LVLy+bh, bx-LVLx+(bw/2), by-LVLy+(bh/2), TFT_DARKCYAN);
        sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy+(bh/2), bx-LVLx+bw-(bw/4), by-LVLy+bh, bx-LVLx+bw, by-LVLy+(bh/2), TFT_DARKCYAN);
        }else if (ori == 4){
          sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy, bx-LVLx, by-LVLy+(bh/4), bx-LVLx+(bw/2), by-LVLy+(bh/2), TFT_DARKCYAN);
          sprite->fillTriangle(bx-LVLx+(bw/2), by-LVLy+(bh/2), bx-LVLx, by-LVLy+bh-(bh/4), bx-LVLx+(bw/2), by-LVLy+bh, TFT_DARKCYAN);
          sprite->fillRect(bx-LVLx+(bh/2), by-LVLy, bw/2, bh, TFT_DARKGREY);
          }
}

void finish (int bx, int by, int bw, int bh){
  sprite->fillRect(bx-LVLx, by-LVLy, bw, bh, TFT_YELLOW);
  sprite->drawRect(bx-LVLx, by-LVLy, bw, bh, TFT_GREENYELLOW);
}
