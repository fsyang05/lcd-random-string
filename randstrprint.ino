#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// function declarations not necessary. habit
void strprinter(char (*ptr)[20], int size, int* print);
int isPressed(int READ_PIN);

/*
  Declaring LCD object. lcd(I2C_address, rows, cols)
    - 0x27 is standard I2C address for most LCD displays.
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

// reading button input
const int SW_PIN = 22;

/* 
  Initializing array A -> n x 32 two-dimensional array. Spaces used to reach 32 chars after text to prevent referencing uninitialized memory.
  Note that random works better with larger n.
  Aptr used to reference A, enables call by reference later.
*/
char const A[][32] = {
                "Hello World                     ",
                "Message 1                       ",
                "Carpe diem                      ",
                // Include strings here.
              };
char (*Aptr)[32] = A;

/*
  Number of strings contained in A.
*/
int size = sizeof(A) / sizeof(A[0]);

/*
  Tracks whether string has been printed. 1 = printed, 0 = unprinted
  printptr enables call by reference later.
*/
int print = 0;
int* printptr = &print;

/*
  Keynotes:
    - Calls srand, allowing for time-based random number generation
    - Reads input from binary input system using digital pin. SW_PIN indicates wiring location of the joystick switch
    - Writes HIGH to location; whenever input pin reads LOW (switch is pressed), new message is generated

    - Initializes LCD display/backlighting, clears junk that might be displayed on startup
    - Optional introduction message.
*/
void setup() 
{
  srand(time(NULL));

  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  /* OPTIONAL INTRO MESSAGE PRIOR TO LOOP

  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Press the button...");

  delay(4000);

  lcd.clear();

  */
}

/*
  Checks for button press and if message is currently displayed. If no message displayed and button pressed, randomly generates a new message
*/
void loop() 
{

  if (isPressed(SW_PIN) == 1) {
    print = 0;
    lcd.clear();
  }

  if (print == 0) {
    strprinter(Aptr, size, printptr);
  }

}

/*
  Selects random string from A using pointer dereferencing and arithmetic. 
*/
void strprinter(char (*ptr)[32], int size, int* print)
{
  char (*pcopy)[32] = ptr; // so ptr is unchanged
  int randint = rand() % size;
  int strsize;

  // line wrapping support

  lcd.setCursor(0, 0);

  for (int i = 0; i <= 15; ++i) {
    lcd.print((*(pcopy + randint))[i]); // need this to access JUST the ith index of *(pcopy + randint)
  }
    
  lcd.setCursor(0, 1);

  for (int j = 16; j < sizeof(*(pcopy + randint)); ++j) {
    lcd.print((*(pcopy + randint))[j]);
  }

  // message is printed.
  
  *print = 1;
}

/*
  Returns 1 if button pressed (read is 0) and returns 0 otherwise
*/
int isPressed(int READPIN)
{
  if (digitalRead(READPIN) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}
