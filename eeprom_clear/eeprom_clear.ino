#include <EEPROM.h>

void setup(){
 EEPROM.write(0,0); //snake msB
 EEPROM.write(1,0); //snake lsB
 EEPROM.write(2,0); //tetris msB
 EEPROM.write(3,0); //tetris lsB
 
}
void loop(){}
