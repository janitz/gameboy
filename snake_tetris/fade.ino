void fade(byte dir_1, byte dir_2)        // this function turns all leds on(from bottom to top), and then all leds off(from top to bottom)
{                                        // used as a kind of clear screen
  if(dir_1 == up)
  {
    for(char y = 15; y >= 0 ; y--)       // all rows from bottom to top  // need a char because its signed
    {      
      switchRow(y, true);
    }
  }
  else if(dir_1 = down)
  {
    for(byte y = 0; y < 16; y++)         // all rows from top to bottom
    {
      switchRow(y, true);
    }
  }
  
  delay(100);                            // wait 0,1 sec
  
  if(dir_2 == up)
  {
    for(char y = 15; y >= 0 ; y--)       // all rows from bottom to top  // need a char because its signed
    {
      switchRow(y, false);
    }
  }
  else if(dir_2 = down)
  {
    for(byte y = 0; y < 16; y++)         // all rows from top to bottom
    {
      switchRow(y, false);
    }
  }  
  return;
}

void switchRow(byte number, boolean on)
{
  delay(30);                               // wait 0,03 sec
  for(byte x = 0; x < 8; x++)              // all columns
  {
    playground[number][x] = (on ? 1 : 0);  // set led
  }
  playgroundToMatrix(false, false);        // convert playground to output format without the food
  sendMatrix();                            // send the output array to the ledMatrix     
}
