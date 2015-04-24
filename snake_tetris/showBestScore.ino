void showBestScore(byte game)
{ 
  switch(game)                                                             // different scores for different games
  {
  case snake:
    {
      highscore = (EEPROM.read(0) << 8) + EEPROM.read(1);                  // load highscore from EEPROM
      if(yourscore > highscore)                                            // if your current score is bigger than the old highscore
      {
        highscore = yourscore;                                             // update highscore
        EEPROM.write(0 , yourscore >> 8);                                  // write high byte of the new highscore to EEPROM
        EEPROM.write(1 , yourscore);                                       // write low byte of the new highscore to EEPROM
      }
    }
    break;
  case tetris:
    {
      highscore = (EEPROM.read(2) << 8) + EEPROM.read(3);                  // load highscore from EEPROM
      if(yourscore > highscore)                                            // if your current score is bigger than the old highscore
      {
        highscore = yourscore;                                             // update highscore
        EEPROM.write(2 , yourscore >> 8);                                  // write high byte of the new highscore to EEPROM
        EEPROM.write(3 , yourscore);                                       // write low byte of the new highscore to EEPROM
      }
    }
    break;
  }
  // same show



  for(byte count = 0; count < 20; count++)                                 // reset the score and the best array
  {
    score[count] = 0;
    best[count] = 0;
  }

  char dig[5] = {0,0,0,0,0};                                               // array to save the digits of the score
  char digits_score = howMuchDigits(yourscore);                            // digits of the number 
  char digits_best = howMuchDigits(highscore);                             // digits of the number 

  for(byte length = 0; length < digits_score; length++)                     // for (number of digits)times 
  {
    dig[length] = (yourscore / expo(digits_score - (length + 1))) % 10;      // calculate the value of each digit
  }
  for(char x = 19; x >= (20 - (digits_score * 4)); x--)                     // write the value to the score matrix
  {
    score[x] = digit_small[dig[((x / 4) + digits_score) - 5]][x -((x / 4) * 4)]; // the digitwidth is 4 columns  
  }

  for(byte length = 0; length < digits_best; length++)                      // for (number of digits)times 
  {
    dig[length] = (highscore / expo(digits_best - (length + 1))) % 10;       // calculate the value of each digit
  }
  for(char x = 19; x >= (20 - (digits_best * 4)); x--)                      // write the value to the score matrix
  {
    best[x] = digit_small[dig[((x / 4) + digits_best) - 5]][x -((x / 4) * 4)]; // the digitwidth is 4 columns  
  }


  char offset_score = 13 - (digits_score * 4);                             // initial offset
  char offset_best = 13 - (digits_best * 4);                               // initial offset
  char leave = none;                                                       // variable for leaving the while loop
  while(leave == none)                                                    
  {
    offset_score ++;                                                       // move the text
    offset_best ++;                                                        // move the text
    if(offset_score > lscore)                                     // if the text is out of the screen
    {
      offset_score = 13 - (digits_score * 4);                                                   // reset the offset
    }
    if(offset_best > lbest)                                       // if the text is out of the screen
    {
      offset_best = 13 - (digits_best * 4);                                                    // reset the offset
    }

    for(char x = 0; x < 8; x++)                                            // foreach column of screen
    {
      if((x + offset_score >= 0) && (x + offset_score < lscore))      // if index is valid
      {
        led_matrix[x] = score[x + offset_score];                           // write to outputmatrix
      }
      else
      {
        led_matrix[x] = 0;                                                 // if index is invalid, write zero
      }

      if((x + offset_best >= 0) && (x + offset_best < lbest))         // if index is valid
      {
        led_matrix[x + 8] = best[x + offset_best];                         // write to outputmatrix
      }
      else
      {
        led_matrix[x + 8] = 0;                                             // if index is invalid, write zero
      }      
    }
    sendMatrix();                                                          // write to screen

    byte count = 0;                                                        // delay count
    while((count < 150) && (leave == none))                                // like a for loop with a break when a button is pressed                               
    {
      delay(1);
      count ++;
      leave = buttonCheck();
    }
  }
}

byte howMuchDigits(int number) // returns the number of digits of the variable (without the minus sign in case there is one)
{
  byte digits = 0;             // initialize with zero digits 
  if(number < 0)               // in case number is negative
  {
    number = -number;          // convert to positiv 
  }  
  do 
  {
    digits++;                  // increment num of digit
    number /= 10;              // divide by 10
  }
  while(number > 0);          // as long as number is positiv  
  return digits;               // return how many digits the 
}

int expo(byte exponent)               // returns (10 ^ exponent) no negative exponent accepted
{
  int val = 1;                        // initialise the value to return
  for(byte c = 0; c < exponent; c++)  // as long as c is smalet than the exponent
  {
    val *= 10;                        // miltiplie val with 10
  }
  return val;                         // return the value
}

