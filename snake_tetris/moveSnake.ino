void moveSnake(byte game)
{
  for(byte y = 0; y < (game == menu ? 7 : 16); y++)     // foreach col of playground
  {       
    for(byte x = 0; x < 8; x++)    // foreach row of playground
    {
      if(playground[y][x] > 0)     // if playground is greater than zero
      {
        playground[y][x]--;        // decrement playground
      }
    } 
  }

  switch(dir)                      // switch current move direction
  {
    case up:                       
      head_y--;                    // decrement head y_pos
      if(head_y < 0)               // if head y_pos is smaler than zero
      {
        head_y = 15;               // set head y_pos to 15
      }
      break;
    
    case right:                   
      head_x++;                    // increment head x_pos
      if(head_x > 7)               // if head x_pos is greater than 7
      {
        head_x = 0;                // set head x_pos to zero
      }
      break;
      
    case down:                    
      head_y++;                    // increase head y_pos
      if(head_y > 15)              // if head y_pos is greater than 15
      {
        head_y = 0;                // set head y_pos to zero
      }
      break;
      
    case left:
      head_x--;                    // decrease head x_pos
      if(head_x < 0)               // if head x_pos is smaler than zero
      {
        head_x = 7;                // set head x_pos to 7
      }
      break;
  } 
  
  if(playground[head_y][head_x] > 0) //if crash
  {
    lost = true; 
    return;
  }
  
  playground[head_y][head_x] = snake_length / 2; // place the new head
  
  if((head_x == food_x) && (head_y == food_y) && (game != menu))   //if eaten
  {
    snake_length++;                              //increment the length of the snake
    yourscore++;
    delaytime *= (39.0 / 40);
    if((snake_length % 2) == 0)                  // ervery second time
    {
      for(byte y = 0; y < 16; y++)               // foreach col of playground
      {       
        for(byte x = 0; x < 8; x++)              // foreach row of playground
        {
          if(playground[y][x] > 0)               // if playground is greater than zero
          {
            playground[y][x]++;                  // increment playground
          }  
        }    
      }
    }
    placeFood();                               //place new food
  }
  
  return;
}

void placeFood()
{
  food_x += (random() % 8);      // increase x_pos of food randomly
  food_y += (random() % 16);     // increase y_pos of food randomly
  
  for(byte y = 0; y < 16; y++)   // increment y_pos of food up to 16 times
  {
    food_y++;
    while(food_y >= 16)          // while y_pos of food is out of playground 
    {
      food_y -= 16;              // subtract 16
    }
    for(byte x = 0; x < 8; x++)  //increment x_pos of food up to 8 times
    {
      food_x++;
      while(food_x >= 8)         // while x_pos of food is out of playground
      {
        food_x -= 8;             // subtract 8
      }
      if(playground[food_y][food_x] == 0)
      {
        return;                  // return if the food has a vacant position
      }
    }
  }      
}
