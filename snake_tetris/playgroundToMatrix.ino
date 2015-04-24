void playgroundToMatrix(boolean with_food, boolean with_tetr)
{
  for(byte x = 0; x < 8; x++)                                             // foreach col
  {
    led_matrix[x] = 0;                                                    // initialize row with zero
    led_matrix[x + 8] = 0;                                                // initialize row+8 with zero
    for(byte y = 0; y < 8; y++)                                           // for 0 to col/2
    {
      led_matrix[x] |= (((playground[y][x] > 0) ? 128 : 0) >> y);         // if number on playground is greater than zero, set the matching bit high 
      led_matrix[x + 8] |= (((playground[y + 8][x] > 0) ? 128 : 0) >> y); // if number on playground is greater than zero, set the matching bit high   
    }
  }
  if(with_food)
  {
    if(food_y < 8)                                                          
    {
      led_matrix[food_x] |= (128 >> food_y);                               // set the bit on the pos of the food high
    }
    else
    {
      led_matrix[food_x + 8] |= (128 >> (food_y - 8));                     // set the bit on the pos of the food high
    }
  }
  
  if(with_tetr)
  {
    for(byte y = 0; y < 4; y++)
    {       
      for(byte x = 0; x < 4; x++)
      {
        if(((y + tetr_y) >= 0) && ((x + tetr_x) >= 0) && ((x + tetr_x) < 16) && ((y + tetr_y) < 16))
        {
          if(((x + tetr_x) < 8) && ((y + tetr_y) < 8))
          {
            led_matrix[x + tetr_x] |= ((current_tetrimino[y][x] == 0) ? 0 : (128 >> (y + tetr_y)));               // set the bit on the pos of the food high
          }
          else
          {    
            led_matrix[x + tetr_x + 8] |= ((current_tetrimino[y][x] == 0) ? 0 : (128 >> (y + tetr_y - 8)));       // set the bit on the pos of the food high
          }
        }
      }
    }
  }
  return;
}


/*
       x -->
          0    1    2    3    4    5    6    7
 Y      _________________________________________
       |  __   __   __   __   __   __   __   __  |
 |  0  | | 7| |  | |  | |  | |  | |  | |  | |  | |
 |  1  | |06| |1 | |2 | |3 | |4 | |5 | |6 | |7 | |
 V  2  | | 5| |  | |  | |  | |  | |  | |  | |  | |
    3  | | 4| |  | |  | |  | |  | |  | |  | |  | |
    4  | | 3| |  | |  | |  | |  | |  | |  | |  | |
    5  | | 2| |  | |  | |  | |  | |  | |  | |  | |
    6  | | 1| |  | |  | |  | |  | |  | |  | |  | |
    7  | |_0| |__| |__| |__| |__| |__| |__| |__| |
       |  __   __   __   __   __   __   __   __  |
    8  | |  | |  | |  | |  | |  | |  | |  | |  | |
    9  | |8 | |9 | |10| |11| |12| |13| |14| |15| |
   10  | |  | |  | |  | |  | |  | |  | |  | |  | |
   11  | |  | |  | |  | |  | |  | |  | |  | |  | |
   12  | |  | |  | |  | |  | |  | |  | |  | |  | |
   13  | |  | |  | |  | |  | |  | |  | |  | |  | |
   14  | |  | |  | |  | |  | |  | |  | |  | |  | |
   15  | |__| |__| |__| |__| |__| |__| |__| |__| |
       |_________________________________________|

playground[y][x]

the rectangles in playground[][] show how to store data in matrix for correct output saved in led_matrix[]

*/
