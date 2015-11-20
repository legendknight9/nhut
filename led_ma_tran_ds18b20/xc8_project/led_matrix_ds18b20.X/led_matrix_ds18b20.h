//======================================================================================================//
//======================================================================================================//
// PROJECT LED MATRIX                                                                                   //
// Author : Luu Thanh Nhut                                                                              //
// Date : August 2015                                                                                   //
// Copyright : I am the owner. This project is free to share, reuse, refer ... but at your own risks.   //
// History/project plan :                                                                               //
// + Hardware : build circuit                                                   finalizing...           //
// + Firmware : Code this project                                               on-going...             //
//   ++ Write to led matrix lines                                               done                    //
//   ++ Make DS18B20 library                                                    about to do             //
//      +++ Make interfacing library                                                                    //
//      +++ Make temperature display-data library                                                       //
//   ++ Display temperature to led matrix line                                  waiting                 //
//   ++ Make DS12887 libray                                                     waiting                 //
//      +++ Make interfacing library                                                                    //
//      +++ Make temperature display-data library                                                       //
//   ++ Display something to led matrix line                                    waiting                 //
//      +++ Some message                                                                                //
//      +++ Temperature                                                                                 //
//      +++ Date time                                                                                   //
// + Software : Make Code-generator program for fixed display data              pending...              //
//======================================================================================================//
//======================================================================================================//

#define _XTAL_FREQ 8000000
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include "myds18b20.h"
#include "my_sign.h"

#define Pause        RD0
#define Temp         RD1
#define SCCLK        RD2
#define nSC_E        RD3
#define Data         RD4
#define SHCLK0       RD5
#define SHCLK        RD6
#define nLMRS        RD7
#define SC_RS        RE2




