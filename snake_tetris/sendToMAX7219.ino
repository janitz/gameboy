void sendMatrix()
{
  for(byte y = 0; y < 8; y++)
  {
    PORTB &= B11111011;                // CS low (pin 10)
    SPI.transfer(y + 1);               // send address matrix bottom
    SPI.transfer(led_matrix[y + 8]);   // send data matrix bottom
    SPI.transfer(y + 1);               // send address matrix top
    SPI.transfer(led_matrix[y]);       // send data matrix top
    PORTB |= B00000100;                //CS high (pin 10)
  }
  return;
}

void sendSettings(byte addr, byte data)
{
  PORTB &= B11111011;   // CS low (pin 10)
  SPI.transfer(addr);   // send address matrix bottom
  SPI.transfer(data);   // send data matrix bottom
  SPI.transfer(addr);   // send address matrix top
  SPI.transfer(data);   // send data matrix top
  PORTB |= B00000100;   //CS high (pin 10)
}
