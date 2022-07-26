int CB;

void _level(){
  
  //i = counter, e = xPosition, q = yPosition

  for (int i = 0, e = 0, q = 0; i < 640; i++){
    CB = LEVEL[i];

    if (CB == 8){
      e = -1;
      q++;
      }
    
    if (CB == 1){
      block(bw*e, bh*q, bw, bh);
      }else if (CB > 20 && CB < 30){
        spike(bw*e, bh*q, bw, bh, CB-20);
        }else if (CB > 30){
          lava(bw*e, bh*q, bw, bh, CB-30);
          }else if (CB == 4){
            finish(bw*e, bh*q, bw, bh);
            }
    e++;
    }
}
