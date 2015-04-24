
      ///////////////////////////////////////////////////////
     //                                           ___     //
    // O             snake by janis              / o \   //
   //  |\   ______   ______   ______   ______   /  __/  //
  //   \ \_/  __  \_/  __  \_/  __  \_/  __  \_/  /    //
 //     \____/  \_____/  \_____/  \_____/  \_____/    //
///////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////
     // _                                                 //
    // |_|   _     tetris by janis    _    _      _      //
   //  |_|  |_|     _ _    _ _       |_|  |_|_   |_|_   //
  //   |_|  |_|_   |_|_|  |_|_|_    _|_|  |_|_|  |_|_| //
 //    |_|  |_|_|  |_|_|    |_|_|  |_|_|    |_|  |_|  //
///////////////////////////////////////////////////////

// hardware: look at the bottom of this document

#include <SPI.h>
#include <EEPROM.h>


//games
#define menu 0
#define snake 1
#define tetris 2

//directions
#define none 0
#define up 1
#define right 2
#define down 4
#define left 8

// global variables
byte digit_small[10][4] = {
  {0 , 62, 34, 62}, //0
  {0 , 18, 62,  2}, //1
  {0 , 18, 38, 26}, //2
  {0 , 42, 42, 62}, //3
  {0 , 56, 14,  8}, //4
  {0 , 58, 42, 36}, //5
  {0 , 62, 42, 46}, //6
  {0 , 32, 38, 56}, //7
  {0 , 62, 42, 62}, //8
  {0 , 58, 42, 62}};//9

const byte lscore = 44;     
byte score[lscore] = {
  0,  0,  0,  0, 
  0,  0,  0,  0,    
  0,  0,  0,  0, 
  0,  0,  0,  0,    
  0,  0,  0,  0,
  0,  8,  8,  8, //-
  0, 58, 42, 46, //S
  0, 28, 34, 34, //C
  0, 62, 34, 62, //O
  0, 62, 44, 58, //R
  0, 62, 42, 34};//E
  
const byte lbest = 40;
byte best[lbest] = {
  0,  0,  0,  0, 
  0,  0,  0,  0,    
  0,  0,  0,  0, 
  0,  0,  0,  0,    
  0,  0,  0,  0,
  0,  8,  8,  8, //-
  0, 62, 42, 20, //B
  0, 62, 42, 34, //E
  0, 58, 42, 46, //S
  0, 32, 62, 32};//T

byte tetrimino[7][4][4] = {
 {{0, 0, 0, 0},       //O
  {0, 1, 1, 0},
  {0, 1, 1, 0},
  {0, 0, 0, 0}},
  
 {{0, 0, 0, 0},       //I
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {0, 0, 0, 0}},
  
 {{0, 1, 0, 0},       //L
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 0, 0}},
  
 {{0, 1, 0, 0},       //J
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 0, 0}},
  
 {{0, 1, 1, 0},       //S
  {1, 1, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}},
  
 {{1, 1, 0, 0},       //Z
  {0, 1, 1, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}},
  
 {{0, 1, 0, 0},       //T
  {1, 1, 1, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}}};

byte current_tetrimino[4][4] = {
  {0, 0, 0, 0}, 
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}};
  
  
  
byte playground[16][8] = { // virtual board to play on
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
byte led_matrix[16] = { // this bytearray will be written directly to the max7219 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
 
// variables for all games
int delaytime = 0;          // time between moves //no unit because its for a cycles count in different cyles with different runtime
boolean lost = 0;           // is the game lost?
unsigned int yourscore = 0; // current score
unsigned int highscore = 0; // best score
byte input_store = 0;       // for flank-detection
int input_count = 0;        // how long is the input the same?
byte brightnes = 5;       // brightness of the max7219

// variables for snake
byte food_x = 0;        // 0=left  7=right
byte food_y = 0;        // 0=top  15=bottom
char head_x = 0;        // 0=left  7=right
char head_y = 0;        // 0=top  15=bottom
byte dir = up;          // direction
byte dir_new = none;    // direction memory       
byte snake_length = 0;  // length of the snake (real length is half of this)

//variables for tetris
char tetr_x = 0;        //
char tetr_y = 0;        //
byte curr_tetr = 0;      //
byte dir_last = none;   // 
int button_hold = 0;    //

void setup() 
{ 
  DDRB |= B00101100;         // Pin 10, 11, 13 OUTPUT 
  DDRD &= B11000000;         // Pin 2-7 INPUT
  randomSeed(A0);            // initialize random
  SPI.begin();               // initialize SPI
  // send a few settings to the ledmatrix driver max 7219
  sendSettings(0x0C, 0x00);  // shutdownmode on
  sendSettings(0x09, 0x00);  // no decode
  sendSettings(0x0A, 0x05);  // intensity
  sendSettings(0x0B, 0x07);  // 8 columns to scan
  sendSettings(0x0C, 0x01);  // shutdownmode off
  sendSettings(0x0F, 0x00);  // displaytest off 
}



void loop() 
{
  fade(up, down);                                         // like clear screen
  switch(selectGame())                                   // select the game to play
  {
    case snake:  
    {
      fade(up, up);
      initializeGame(snake);    
      while(!lost)                                       // as long as you haven't lost
      {
        for(int count = 0; count < delaytime; count ++)  // wait delaytime cycles
        {
          buttonSnake();                                 // check the buttons
          delayMicroseconds(10);
        } 
        dir =  dir_new;        
        moveSnake(snake);                                // move the snake and check for crash or eat
        playgroundToMatrix(true, false);                 // convert playground to output format with shiwing the food
        sendMatrix();                                    // send the output array to the max7219                
      }     
      
      delay(750);                                       // if lost wait a 3/4 second
      
      int count = 0;                                     // variable for blink at the crashpoint
      byte snake_part = 0;                               // variable for choose the led to blink
      while(count > -1)                                  // wait until a button is pressed and blink head
      {
        delay(2);                                        // wait 0,002 sec
        count ++;                                        // increment count
              
        if (count == 1)                                
        {           
          if(snake_part == (snake_length / 2) - 1)
          {
            snake_part = 0;
          } 
          snake_part++;                                    // increment the snake_part
          for(byte y = 0; y < 16; y++)
          {
            for(byte x = 0; x < 8; x++)
            {
              if(playground[y][x] == snake_part)
              {
                head_y = y;
                head_x = x;
              }
            }
          }                    
          playground[head_y][head_x] = 0;                // switch led at pos of head off
          playgroundToMatrix(true, false);               // convert playground to output format with showing the food
          sendMatrix();                                  // send the output array to the max7219    
        }
        if(count == 30)
        {
          playground[head_y][head_x] = snake_part;       // switch led at pos of head an
          count = 0;                                     // reset the count
        }
        if(buttonCheck() != none)                        // wait until a button is pressed
        {
          fade(up, down);                                        // clearscreen
          showBestScore(snake);                          // show yourscore and highscore in small digits
          count = -1;                                    // leave the "you have lost"- whileloop
        }        
      }
    }
    break;
      
    case tetris:
    {
      fade(down, down);
      initializeGame(tetris);    
      while(!lost)                                       // as long as you haven't lost
      {
        int count = 0;
        while( count < ((dir_last == down) ? delaytime / 10: delaytime))  // wait delaytime cycles
        {
          buttonTetris();                                 // check the buttons
          playgroundToMatrix(false, true); // convert playground to output format
          sendMatrix();                    // send the output array to the ledMatrix   
          count++;   
        } 
        tetr_y++;
        if(validMove() != none)
        {
          tetr_y--;
          lost = !tetriminoToPlayground();
        }
      }
      
      
      int count = 0;
      while(count > -1)                                  // wait until a button is pressed and blink head
      {
        delay(2);                                        // wait 0,002 sec
        count ++;  
        
        if(count == 30)
        {
          count = 0;
        }
        
        
        
        if(buttonCheck() != none)                        // wait until a button is pressed
        {
          fade(up, down);                                        // clearscreen
          showBestScore(tetris);                          // show yourscore and highscore in small digits
          count = -1;                                    // leave the "you have lost"- whileloop
        }        
      } 
    }
    break;
  }
}


/*

      this view is like you look on the parts while soldering (from underneath)



CPM12088BR 8x8 32mmx32mm Dot Matrix 3mm Common Anode Red


             ROW  ------------------------
DIG0 - ROW0   7  | 0. 0  0  0  0  0  0 .0 |l    COL3 - SEGC
DIG1 - ROW1   6  | 0. 0  0  0  0  0  0 .0 |a    COL1 - SEGA                              view
SEGF - COL6   5  | 0. 0  0  0  0  0  0 .0 |b    ROW6 - DIG6                               |
DIG7 - ROW7   4  | 0. 0  0  0  0  0  0 .0 |e    ROW5 - DIG5                               V
SEGD - COL4   3  | 0. 0  0  0  0  0  0 .0 |l    COL0 - SEGDP                    |  |  |  |  |  |  |  |  
DIG2 - ROW2   2  | 0. 0  0  0  0  0  0 .0 |i    ROW3 - DIG3                |\___|__|__|__|__|__|__|__|___/|
DIG4 - ROW4   1  | 0. 0  0  0  0  0  0 .0 |n    COL2 - SEGB                |           labeling           |
SEGG - COL7   0  | 0. 0  0  0  0  0  0 .0 |g    COL5 - SEGE                |______________________________|
                  ------------------------
              COL  7  6  5  4  3  2  1  0      




MAX7219CNG Serially Interfaced, 8-Digit LED Display Driver
           _____
DOUT  24 -|  U  |- 1  DIN                                              view
SEGD  23 -|     |- 2  DIG0                                              |
SEGDP 22 -|     |- 3  DIG4                                              V
SEGE  21 -|     |- 4  GND
SEGC  20 -|  M  |- 5  DIG6                                   _|_|_|_|_|_|_|_|_|_|_|_|_|_|_
V+    19 -|  A  |- 6  DIG2                                  |                             |
ISET  18 -|  X  |- 7  DIG3                                  |_____________________________|
SEGG  17 -|  7  |- 8  DIG7
SEGB  16 -|  2  |- 9  GND
SEGF  15 -|  1  |- 10 DIG5
SEGA  14 -|  9  |- 11 DIG1
CLK   13 -|_____|- 12 !CS/LOAD

 on each driver:
   ISET   -----(27kOhm)----- V+                                                   
   V+     ---(100µF elko)--- GND


 general conections:
   DOUT1  ------------------ DIN2     (1 = matrixdriver 1)
   !CS1   ------------------ !CS2     (2 = matrixdriver 2)
   CLK1   ------------------ CLK2

   !CS  ------- pin10 (SS pin)
   DIN1 ------- pin11 (MOSI pin)
   CLK  ------- pin13 (SCK pin)
     
            button   arduinoUNO   pulldown                     
    V+ ----- up ------- pin2 -----(10kOhm)----GND 
    V+ ----- right ---- pin3 -----(10kOhm)----GND 
    V+ ----- down ----- pin4 -----(10kOhm)----GND 
    V+ ----- left ----- pin5 -----(10kOhm)----GND 



   view from top of the mounted device

          --------------------------------------------------------
        /                                                          \
        |                                 ____________ labeling    |
        |                                V                         |
        |                     -----------------                    |
        |                    | o o o o o o o o |                   |
        |      matrix 1      | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   | 
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |         
        |                     -----------------                    |
        |                                 ____________ labeling    |
        |                                V                         |
        |                     -----------------                    |
        |                    | o o o o o o o o |                   |
        |      matrix 2      | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |
        |                    | o o o o o o o o |                   |         
        |                     -----------------                    |
        |                                                          |
        |                            ---                           |
        |                           | O | pin2                     |
        |                            ---                           |
        |                     ---           ---                    |
        |                    | O | pin5    | O | pin3              |
        |                     ---           ---                    |
        |                            ---                           |
        |                           | O | pin4                     |
        |                            ---                           |
        |                                                          |
         \                                                        /
           ------------------------------------------------------                           
 
                              

*/

