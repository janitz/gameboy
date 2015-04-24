void initializeGame(byte game)
{ 
  for(byte y = 0; y < 16; y++)         // foreach col of playground
  {       
    for(byte x = 0; x < 8; x++)        // foreach row of playground
    {
      playground[y][x] = 0;            // set to zero
    }    
  }
  lost = false;                    // at the beginning you havn't already lost 
  yourscore = 0;                   // start with score 0
  switch(game)
  {
    case menu:
    {                  
      head_x = 1;                      // start x_pos
      head_y = 1;                      // start x_pos
      food_x = 5;                      // food x_pos
      food_y = 4;                      // food y_pos
      playground[1][1] = 4;            // place start-snake on playground
      playground[2][1] = 3;            // place start-snake on playground
      playground[3][1] = 2;            // place start-snake on playground
      playground[4][1] = 1;            // place start-snake on playground
      snake_length = 8;                // start length of the snake
      dir = right;                     // move to the right
      for(byte x = 0; x < 8; x++)  
      {
        playground[7][x] = 1;          // the seperation line between snake and twtris
        playground[8][x] = 1;          // the seperation line between snake and tetris
      }
      newTetrimino();
      tetr_x = 2;
      tetr_y = 7;
    }
    break;
    case snake:
    {                  
      delaytime = 20000;                 // starting with this delay between each move of the snake
      head_x = 4;                      // start x_pos
      head_y = 10;                     // start x_pos
      playground[10][4] = 3;           // place start-snake on playground
      playground[11][4] = 2;           // place start-snake on playground
      playground[12][4] = 1;           // place start-snake on playground
      snake_length = 6;                // start length of the snake
      placeFood();                     // place the first food 
      placeFood();                     // place the food again
      playgroundToMatrix(true, false); // convert playground to output format
      sendMatrix();                    // send the output array to the ledMatrix
      while(buttonCheck() == none)     // wait until a button is pressed
      {
        delayMicroseconds(10);         
      }
      dir = up;                         // move to top
      dir_new = up;            
    }
    break;
    case tetris:
    {
      delaytime = 800;                 // starting with this delay between each move of the snake
      dir_last = none;
      newTetrimino();
      tetr_y = 0;
      playgroundToMatrix(false, true); // convert playground to output format
      sendMatrix();                    // send the output array to the ledMatrix
      while(buttonCheck() == none)     // wait until a button is pressed
      {
        delayMicroseconds(10);         
      }
    }
    break;
  }
  return;
}
