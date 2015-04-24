boolean tetriminoToPlayground()
{
  boolean success = true;
  for(byte y = 0; y < 4; y++)
  {
    for(byte x = 0; x < 4; x++)
    {
      if(current_tetrimino[y][x] > 0)
      {
        if((y + tetr_y >= 0) && (y + tetr_y < 16) &&
          (x + tetr_x >= 0) && (x + tetr_x < 8))
        { 
          playground[y + tetr_y][x + tetr_x] = 1;
        }
        else
        {
          success = false;
        }
      }
    }
  }
  if(success)
  {
    yourscore++;
    byte row_count = 0;
    for(byte count_y = 0; count_y < 16; count_y++)
    {
      byte pixel_count = 0;
      for(byte count_x = 0; count_x < 8; count_x++)
      {
        if(playground[count_y][count_x] > 0)
        {
          pixel_count++;
        }        
      }
      if(pixel_count >= 8)
      {
        row_count++;
        for(byte x = 0; x < 8; x++)
        {
          playground[count_y][x] = 0;
          delay(50);
          playgroundToMatrix(false, false);
          sendMatrix();
        }
        for(char y = count_y; y > 0; y--)
        {
          for(byte x = 0; x < 8; x++)
          {
            playground[y][x] = playground[y - 1][x];
          }
        }
        for(byte x = 0; x < 8; x++)
        {
          playground[0][x] = 0;
        }
      }
    }
    if(row_count == 1)
    {
      yourscore += 5;
    }
    else if(row_count == 2)
    {
      yourscore += 15;
    }
    else if(row_count == 3)
    {
      yourscore += 30;
    }
    else if(row_count == 4)
    {
      yourscore += 50;
    }
    delaytime *= (99.0 / 100);
    newTetrimino();
  }
  return success;
}

