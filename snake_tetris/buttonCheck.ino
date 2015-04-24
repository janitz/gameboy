byte buttonCheck() 
{
  return (PIND / 4) % 16;  // return port d from pin 2 to pin 5
}



void buttonSnake() 
{
  switch((PIND / 4) % 16)    // read port d and mask pin2 to pin 5
  {
    case up:                 // button up is pressed
      if(dir != down)        // can't do a 180° turn
      {
        dir_new = up;        // new direction is up
        return;
      }
      break;
    case right:              // button right is pressed
      if(dir != left)        // can't do a 180° turn
      {
        dir_new = right;     // new direction is right
        return;
      }
      break;
    case down:               // button down is pressed
      if(dir != up)          // can't do a 180° turn
      {
        dir_new = down;      // new direction is down
        return;
      }
      break;
    case left:               // button left is pressed
      if(dir != right)       // can't do a 180° turn
      {
        dir_new = left;      // new direction is left
        return;
      }
      break;
    default:
      return;
      break;
  }
}


void buttonTetris()
{
  switch((PIND / 4) % 16)    // read port d and mask pin2 to pin 5
  {
    case up:                 // button up is pressed
      if(dir_last != up)
      {
        turnTetrimino(right);
        boolean solved = (validMove() == none);
        
        if(!solved && ((validMove() & down) != none))
        {
          tetr_y--;          
          if(validMove() != none)
          {
            tetr_y++;
          }
          else
          {
            solved = true;
          }
        }  
        if(!solved && ((validMove() & down) != none))
        {
          tetr_y -= 2;
          if(validMove() != none)
          {
            tetr_y += 2;
          }
          else
          {
            solved = true;
          }
        }
        if(!solved && ((validMove() & left) != none))
        {
          tetr_x++;
          if(validMove() != none)
          {
            tetr_x--;
          }   
          else
          {
            solved = true;
          }          
        }
        if(!solved && ((validMove() & right) != none))
        {
          tetr_x--;
          if(validMove() != none)
          {
            tetr_x++;            
          }
          else
          {
            solved = true;
          }          
        }         
        if(!solved && ((validMove() & left) != none))
        {
          tetr_x += 2;          
          if(validMove() != none)
          {
            tetr_x -= 2;           
          }             
          else
          {
            solved = true;
          }        
        }
        if(!solved && ((validMove() & right) != none))
        {
          tetr_x -= 2;          
          if(validMove() != none)
          {
            tetr_x += 2;
          }
          else
          {
            solved = true;
          }          
        }
        
        if(!solved)
        {
          turnTetrimino(left);
        }
      }      
      dir_last = up;
      return;
      break;
    case right:              // button right is pressed
      if(dir_last == right)
      {
        button_hold++;
        if(button_hold > 150)
        {
          tetr_x++;
          if(validMove() != none)
          {
            tetr_x--;
          }
          button_hold = 0;
        }
      }
      else
      {
        button_hold = 0;
      }
      dir_last = right;
      return;
      break;
    case down:               // button down is pressed      
      dir_last = down;
      return;
      break;
    case left:               // button left is pressed
      if(dir_last == left)
      {
        button_hold++;
        if(button_hold > 150)
        {
          tetr_x--;
          if(validMove() != none)
          {
            tetr_x++;
          }
          button_hold = 0;
        }
      }
       else
      {
        button_hold = 0;
      }
      dir_last = left;
      return;
      break;
    default:
      dir_last = none;
      return;
      break;
  }
   
}
