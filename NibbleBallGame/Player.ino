void Player(int X, int Y, int Radius){
  sprite->fillCircle(x, y, Radius, ballColor[ballColorIndex]);
  sprite->drawCircle(x, y, Radius, TFT_BLACK);

  LVLx += X;
  LVLy += Y;
}
