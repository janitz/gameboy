void turnTetrimino(byte turn_direction)
{
  byte offs = 1;
  for(byte i = 0; i < 4; i++)
  {
    if(current_tetrimino[3][i] == 1)
    {
      offs = 0;
    }
    if(current_tetrimino[i][3] == 1)
    {
      offs = 0;
    }
  }
  if(current_tetrimino[0][0]+current_tetrimino[1][0]+current_tetrimino[0][1] == 0)
  {
    offs = 0;
  }

  byte help_array[4][4] = {
    {
      0,0,0,0    }
    ,{
      0,0,0,0    }
    ,{
      0,0,0,0    }
    ,{
      0,0,0,0    }
  };

  for(char y = 0; y < (4 - offs); y++)
  {
    for(char x = 0; x < (4 - offs); x++)
    {
      if(turn_direction == right)
      {
        help_array[x][(3 - offs) - y] = current_tetrimino[y][x];      
      }
      else if(turn_direction == left)
      {
        help_array[(3 - offs) - x][y] = current_tetrimino[y][x];   
      }
    }    
  }

  for(char y = 0; y < (4 - offs); y++)
  {
    for(char x = 0; x < (4 - offs); x++)
    {
      current_tetrimino[y][x] = help_array[y][x];
    }
  }


}

