byte validMove()
{
  byte crash = none;
  for(char count_y = 0; count_y < 4; count_y++)
  {
    for(char count_x = 0; count_x < 4; count_x++)
    {
      if(((count_x + tetr_x) >= 0) && ((count_x + tetr_x) < 8) && ((count_y + tetr_y) >= 0) && ((count_y + tetr_y) < 16))
      {
        if((playground[count_y + tetr_y][count_x + tetr_x] > 0) && (current_tetrimino[count_y][count_x] > 0))
        {
          if(count_y < 2)
          {
            crash |= up;
          } 
          else
          {
            crash |= down;
          }
          if(count_x < 2)
          {
            crash |= left;
          }
          else
          {
            crash |= right;
          }

        }
      }
      else if (current_tetrimino[count_y][count_x] > 0)
      {
        if(count_y < 2)
        {
          crash |= down;
        } 
        else
        {
          crash |= up;
        }
        if(count_x < 2)
        {
          crash |= left;
        }
        else
        {
          crash |= right;
        }
      }
    }
  }
  return crash;
}







