byte selectGame() // returns the game to play
{
  initializeGame(menu);
  int count_snake = 0;
  int count_tetris = 0;
  byte stay = none;
  while((stay != up) && (stay != down))
  { 
    delay(1);
    if((stay == right) && (dir_last != right))
    {
      brightnes++;
      if(brightnes > 15)
      {
        brightnes = 15;
      } 
    }
    if((stay == left) && (dir_last != left))
    {
      brightnes--;
      if(brightnes < 1)
      {
        brightnes = 1;
      } 
    }
    sendSettings(0x0A, brightnes);
    dir_last = stay;            
    count_snake++;
    count_tetris++;
    if((count_snake % 100) == 0)
    {
     
      moveSnake(menu);
      if(count_snake == 400)
      {
        dir = down;
      }
      else if(count_snake == 600)
      {
        food_x = 1;
        food_y = 2;
      }
      else if(count_snake == 800)
      {
        dir = right;
      }      
      else if(count_snake == 1200)
      {
        dir = up;        
      }
      else if(count_snake == 1400)
      {
        food_x = 5;
        food_y = 4;
      }
      else if(count_snake == 1600)
      {
        dir = right;        
        count_snake = 0;
      }
    } 
   if((count_tetris % 100) == 0)
   {
     if((count_tetris % 200) == 0)
     {
       tetr_y++;
       if (tetr_y > 15)
       {
         newTetrimino();
         tetr_x = 2;
         tetr_y = 7;         
         count_tetris = 0;
       }
     }
     if(count_tetris == 700)
     {
       tetr_x++;
     }
     else if(count_tetris == 900)
     {
       turnTetrimino(left);
     }
     else if(count_tetris == 1100)
     {
       turnTetrimino(left);
     }
     else if(count_tetris == 1300)
     {
       tetr_x--;
     }
     else if(count_tetris == 1400)
     {
       tetr_x--;
     }     
   }
   playgroundToMatrix(true, true);
   sendMatrix();
   stay = buttonCheck() ;   
  }
  
  return (stay == down) ? tetris : snake ;  
}
