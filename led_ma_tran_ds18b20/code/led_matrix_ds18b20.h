#include <16F887.h>
#include <myds18b20.h>
#include "my_sign.h"

#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=8MHz,restart_wdt)
#use FIXED_IO( D_outputs=PIN_D7,PIN_D6,PIN_D5,PIN_D4,PIN_D3,PIN_D2 )
#use FIXED_IO( E_outputs=PIN_E0 )
#define Pause        PIN_D0
#define Temp         PIN_D1
#define SCCLK        PIN_D2
#define SC_SIGNAL    PIN_D3
#define Data         PIN_D4
#define SHCLK0       PIN_D5
#define SHCLK        PIN_D6
#define LMRS         PIN_D7

int1 current_row[8] = {0, 0, 0, 0, 0, 0, 0, 0};


