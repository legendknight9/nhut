//======================================================================================================//
//======================================================================================================//
// PROJECT LED MATRIX                                                                                   //
// Author : Luu Thanh Nhut                                                                              //
// Date : August 2015                                                                                   //
// Copyright : I am the owner. This project is free to share, reuse, refer ... but at your own risks.   //
//======================================================================================================//
//======================================================================================================//
#include "led_matrix_ds18b20.h"

void sys_initialize() {
    TRISD = 0b00000011;
    PORTD = 0;   
    nLMRS = 0;
    SCCLK = 1;
    nSC_E = 1;
    __delay_ms(5);
    nLMRS = 1;    
    ds18b20_initialize();
    __delay_ms(5);   
}

void data_to_column(unsigned short long d_col) {
    char loop = 23;
    while(loop > 0) {            
        Data = ((d_col >> loop) & 1);
        _delay(5);
        SHCLK0 = 1;  
        __delay_us(10);
        SHCLK0 = 0;
        __delay_us(10);
        loop--;
    }
    Data = d_col & 1;
    _delay(5);
    SHCLK0 = 1;  
    __delay_us(10);
    SHCLK0 = 0;
    //__delay_us(10);  
    _delay(5);
    
    SHCLK = 1;  
    __delay_us(10);
    SHCLK = 0;
    //__delay_us(1);
}
unsigned char line1, line2, line3;
unsigned short long d_column;
void data_to_row(const unsigned char d_row[21]) {    
    nLMRS = 0;
    __delay_us(10);
    nLMRS = 1;
     
    /*
     d_row[n] : 7   6           5           4           3           2            1           0
    column 7  : 
     line3    : 0 d_row[20].7 d_row[19].7 d_row[18].7 d_row[17].7 d_row[16]].7 d_row[15].7 d_row[14].7
     line2    : 0 d_row[13].7 d_row[12].7 d_row[11].7 d_row[10].7 d_row[9]].7  d_row[8].7  d_row[7].7
     line1    : 0 d_row[6].7  d_row[5].7  d_row[4].7  d_row[3].7  d_row[2]].7  d_row[1].7  d_row[0].7
    column 6  : 
     line3    : 0 d_row[20].6 d_row[19].6 d_row[18].6 d_row[17].6 d_row[16]].6 d_row[15].6 d_row[14].6
     line2    : 0 d_row[13].6 d_row[12].6 d_row[11].6 d_row[10].6 d_row[9]].6  d_row[8].6  d_row[7].6
     line1    : 0 d_row[6].6  d_row[5].6  d_row[4].6  d_row[3].6  d_row[2]].6  d_row[1].6  d_row[0].6
    ...
    ...     
    column 0  : 
     line3    : 0 d_row[20].0 d_row[19].0 d_row[18].0 d_row[17].0 d_row[16]].0 d_row[15].0 d_row[14].0
     line2    : 0 d_row[13].0 d_row[12].0 d_row[11].0 d_row[10].0 d_row[9]].0  d_row[8].0  d_row[7].0
     line1    : 0 d_row[6].0  d_row[5].0  d_row[4].0  d_row[3].0  d_row[2]].0  d_row[1].0  d_row[0].0      
     */        
    unsigned char mask = 0x80;
    line3 = ((d_row[20] & mask) >> 1) + ((d_row[19] & mask) >> 2) + ((d_row[18] & mask) >> 3) + 
            ((d_row[17] & mask) >> 4) + ((d_row[16] & mask) >> 5) + ((d_row[15] & mask) >> 6) + ((d_row[14] & mask) >> 7);
    line2 = ((d_row[13] & mask) >> 1) + ((d_row[12] & mask) >> 2) + ((d_row[11] & mask) >> 3) + 
            ((d_row[10] & mask) >> 4) + ((d_row[9] & mask) >> 5) + ((d_row[8] & mask) >> 6) + ((d_row[7] & mask) >> 7);
    line1 = ((d_row[6] & mask) >> 1) + ((d_row[5] & mask) >> 2) + ((d_row[4] & mask) >> 3) + 
            ((d_row[3] & mask) >> 4) + ((d_row[2] & mask) >> 5) + ((d_row[1] & mask) >> 6) + ((d_row[0] & mask) >> 7);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);        

    mask = 0x40;
    line3 = (d_row[20] & mask) + ((d_row[19] & mask) >> 1) + ((d_row[18] & mask) >> 2) + 
            ((d_row[17] & mask) >> 3) + ((d_row[16] & mask) >> 4) + ((d_row[15] & mask) >> 5) + ((d_row[14] & mask) >> 6);
    line2 = (d_row[13] & mask) + ((d_row[12] & mask) >> 1) + ((d_row[11] & mask) >> 2) + 
            ((d_row[10] & mask) >> 3) + ((d_row[9] & mask) >> 4) + ((d_row[8] & mask) >> 5) + ((d_row[7] & mask) >> 6);
    line1 = (d_row[6] & mask) + ((d_row[5] & mask) >> 1) + ((d_row[4] & mask) >> 2) + 
            ((d_row[3] & mask) >> 3) + ((d_row[2] & mask) >> 4) + ((d_row[1] & mask) >> 5) + ((d_row[0] & mask) >> 6);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);     
    
    mask = 0x20;
    line3 = ((d_row[20] & mask) << 1) + (d_row[19] & mask) + ((d_row[18] & mask) >> 1) + 
            ((d_row[17] & mask) >> 2) + ((d_row[16] & mask) >> 3) + ((d_row[15] & mask) >> 4) + ((d_row[14] & mask) >> 5);
    line2 = ((d_row[13] & mask) << 1) + (d_row[12] & mask) + ((d_row[11] & mask) >> 1) + 
            ((d_row[10] & mask) >> 2) + ((d_row[9] & mask) >> 3) + ((d_row[8] & mask) >> 4) + ((d_row[7] & mask) >> 5);
    line1 = ((d_row[6] & mask) << 1) + (d_row[5] & mask) + ((d_row[4] & mask) >> 1) + 
            ((d_row[3] & mask) >> 2) + ((d_row[2] & mask) >> 3) + ((d_row[1] & mask) >> 4) + ((d_row[0] & mask) >> 5);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);
    
    mask = 0x10;
    line3 = ((d_row[20] & mask) << 2) + ((d_row[19] & mask) << 1) + (d_row[18] & mask) + 
            ((d_row[17] & mask) >> 1) + ((d_row[16] & mask) >> 2) + ((d_row[15] & mask) >> 3) + ((d_row[14] & mask) >> 4);
    line2 = ((d_row[13] & mask) << 2) + ((d_row[12] & mask) << 1) + (d_row[11] & mask) + 
            ((d_row[10] & mask) >> 1) + ((d_row[9] & mask) >> 2) + ((d_row[8] & mask) >> 3) + ((d_row[7] & mask) >> 4);
    line1 = ((d_row[6] & mask) << 2) + ((d_row[5] & mask) << 1) + (d_row[4] & mask) + 
            ((d_row[3] & mask) >> 1) + ((d_row[2] & mask) >> 2) + ((d_row[1] & mask) >> 3) + ((d_row[0] & mask) >> 4);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);

    mask = 0x08;
    line3 = ((d_row[20] & mask) << 3) + ((d_row[19] & mask) << 2) + ((d_row[18] & mask) << 1) + 
            (d_row[17] & mask) + ((d_row[16] & mask) >> 1) + ((d_row[15] & mask) >> 2) + ((d_row[14] & mask) >> 3);
    line2 = ((d_row[13] & mask) << 3) + ((d_row[12] & mask) << 2) + ((d_row[11] & mask) << 1) + 
            (d_row[10] & mask) + ((d_row[9] & mask) >> 1) + ((d_row[8] & mask) >> 2) + ((d_row[7] & mask) >> 3);
    line1 = ((d_row[6] & mask) << 3) + ((d_row[5] & mask) << 2) + ((d_row[4] & mask) << 1) + 
            (d_row[3] & mask) + ((d_row[2] & mask) >> 1) + ((d_row[1] & mask) >> 2) + ((d_row[0] & mask) >> 3);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);

    mask = 0x04;
    line3 = ((d_row[20] & mask) << 4) + ((d_row[19] & mask) << 3) + ((d_row[18] & mask) << 2) + 
            ((d_row[17] & mask) << 1) + (d_row[16] & mask) + ((d_row[15] & mask) >> 1) + ((d_row[14] & mask) >> 2);
    line2 = ((d_row[13] & mask) << 4) + ((d_row[12] & mask) << 3) + ((d_row[11] & mask) << 2) + 
            ((d_row[10] & mask) << 1) + (d_row[9] & mask) + ((d_row[8] & mask) >> 1) + ((d_row[7] & mask) >> 2);
    line1 = ((d_row[6] & mask) << 4) + ((d_row[5] & mask) << 3) + ((d_row[4] & mask) << 2) + 
            ((d_row[3] & mask) << 1) + (d_row[2] & mask) + ((d_row[1] & mask) >> 1) + ((d_row[0] & mask) >> 2);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);
    
    mask = 0x02;
    line3 = ((d_row[20] & mask) << 5) + ((d_row[19] & mask) << 4) + ((d_row[18] & mask) << 3) + 
            ((d_row[17] & mask) << 2) + ((d_row[16] & mask) << 1) + (d_row[15] & mask) + ((d_row[14] & mask) >> 1);
    line2 = ((d_row[13] & mask) << 5) + ((d_row[12] & mask) << 4) + ((d_row[11] & mask) << 3) + 
            ((d_row[10] & mask) << 2) + ((d_row[9] & mask) << 1) + (d_row[8] & mask) + ((d_row[7] & mask) >> 1);
    line1 = ((d_row[6] & mask) << 5) + ((d_row[5] & mask) << 4) + ((d_row[4] & mask) << 3) + 
            ((d_row[3] & mask) << 2) + ((d_row[2] & mask) << 1) + (d_row[1] & mask) + ((d_row[0] & mask) >> 1);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);

    mask = 0x01;
    line3 = ((d_row[20] & mask) << 6) + ((d_row[19] & mask) << 5) + ((d_row[18] & mask) << 4) + 
            ((d_row[17] & mask) << 3) + ((d_row[16] & mask) << 2) + ((d_row[15] & mask) << 1) + (d_row[14] & mask);
    line2 = ((d_row[13] & mask) << 6) + ((d_row[12] & mask) << 5) + ((d_row[11] & mask) << 4) + 
            ((d_row[10] & mask) << 3) + ((d_row[9] & mask) << 2) + ((d_row[8] & mask) << 1) + (d_row[7] & mask);
    line1 = ((d_row[6] & mask) << 6) + ((d_row[5] & mask) << 5) + ((d_row[4] & mask) << 4) + 
            ((d_row[3] & mask) << 3) + ((d_row[2] & mask) << 2) + ((d_row[1] & mask) << 1) + (d_row[0] & mask);
    d_column = line3;
    d_column = (d_column << 8) + line2;
    d_column = (d_column << 8) + line1;
    data_to_column(d_column);    
  
    nSC_E = 0;
}

/*
 * line_number : 0 - 3
 */
void select_line(char line_number) {   
    char loop = line_number * 8;
    SCCLK = 1;
    SC_RS = 1;
    __delay_us(10);
    SC_RS = 0;
    __delay_us(10);
    while (loop-- > 0) {
        SCCLK = 0;
        __delay_us(1);
        SCCLK = 1;
        __delay_us(1);
    }
}

void next_row() {
    nSC_E = 1;
    SCCLK = 0;
    __delay_us(1);
    SCCLK = 1;
    __delay_us(1);        
}

/*
 * line_number : 0 - 3
 */
void write_atline(char line_number) {
    select_line(line_number);
    write_line();
}

void write_line() {
    data_to_row(d_row0); 
    next_row();
    data_to_row(d_row1); 
    next_row();
    data_to_row(d_row2); 
    next_row();
    data_to_row(d_row3); 
    next_row();
    data_to_row(d_row4); 
    next_row();
    data_to_row(d_row5); 
    next_row();
    data_to_row(d_row6); 
    next_row();
    data_to_row(d_row7); 
    next_row();
}

void main() {
    sys_initialize();    
    while (1) {
        write_line(0);
        write_line(1);
        write_line(2);
        write_line(3);
    }
    
//REMIND !!    
/* //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************************
*******************************************************************************************
**** NOTE : Make code generator program to prepare display data and improve scan rate. ****
*******************************************************************************************
*******************************************************************************************
*/ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
//    char time = 1;
//    while(1) {             
//        switch(current_row) {        
//            case 0 :    data_to_row(d_row0); // row 0 
//                        __delay_ms(period);
//                        break;
//            case 1 :    data_to_row(d_row1); // row 1       
//                        __delay_ms(period);
//                        break;
//            case 2 :    data_to_row(d_row2); // row 2       
//                        __delay_ms(period);
//                        break;
//            case 3 :    data_to_row(d_row3); // row 3       
//                        __delay_ms(period);            
//                        break;
//            case 4 :    data_to_row(d_row4); // row 4      
//                        __delay_ms(period);            
//                        break;
//            case 5 :    data_to_row(d_row5); // row 5       
//                        __delay_ms(period);            
//                        break;
//            case 6 :    data_to_row(d_row6); // row 6       
//                        __delay_ms(period);            
//                        break;                        
//            case 7 :    data_to_row(d_row7); // row 6       
//                        __delay_ms(period);            
//                        break;                        
//            default :   break;
//        }
//    }    
}

/*
    while (1) {
        data_to_row(d_row0);
        nSC_E = 0;
        int address = 0;
        while (address++ < 32) {
            SCCLK = 0;
            __delay_ms(100);
            SCCLK = 1;
            __delay_ms(100);
        }
        nLMRS = 0;
        __delay_ms(10);
        nLMRS = 1;
        __delay_ms(10);
    }
*/

   /*
   22 21 20 19 18 17 16
   14 13 12 11 10 9  8
   6  5  4  2  2  1  0
   
   167 159 151 143 135 127 119
   111 103 95  87  79  71  63
   55  47  39  31  23  15  7  
   */   
//!void data_to_row(bit d_row[168]) {
//!   char column, line, index, indexDI, number_of_led_matrix_per_line;
//!
//!   column = 8;
//!   while(column-- > 0)
//!   {
//!      line = 3;
//!      while (line-- > 0) {                        
//!         //indexDI = 7 * line + line - 2;
//!         indexDI = 22;
//!         number_of_led_matrix_per_line = 7;
//!         while (number_of_led_matrix_per_line-- > 0) {
//!            index = (line * 56) - 1 - ((7 - number_of_led_matrix_per_line) * 8) - (8 - column);
//!            d_column[indexDI--] = d_row[index];
//!            if ((indexDI == 15) || (indexDI == 7)) {
//!               indexDI--;
//!            }
//!         }
//!      }
//!      d_column[23] = 0;
//!      data_to_column(d_column);
//!   }
//!   scan_row();
//!}

//    while(column-- > 0)
//    {           
//        //unsigned char line1, line2, line3;
//        //line3 = 0; // bit 23 = 0 and clear line3
//        line3  = (d_row[20] & mask); // bit 22
//        line3 += (d_row[19] & mask) >> 2); // bit 21
//        line3 += ((d_row[18] & mask) >> 3); // bit 20
//        line3 += ((d_row[17] & mask) >> 4); // bit 19
//        line3 += ((d_row[16] & mask) >> 5); // bit 18
//        line3 += ((d_row[15] & mask) >> 6); // bit 17
//        line3 += ((d_row[14] & mask) >> 7); // bit 16
//        
//        //line2 = 0; // bit 15 = 0 & clear line2
//        line2  = ((d_row[13] & mask) >> 1); // bit 14
//        line2 += ((d_row[12] & mask) >> 2); // bit 13
//        line2 += ((d_row[11] & mask) >> 3); // bit 12
//        line2 += ((d_row[10] & mask) >> 4); // bit 11
//        line2 += ((d_row[9] & mask) >> 5); // bit 10
//        line2 += ((d_row[8] & mask) >> 6); // bit 9
//        line2 += ((d_row[7] & mask) >> 7); // bit 8
//        
//        //line1 = 0; // bit 7 = 0 & clear line1
//        line1  = ((d_row[6] & mask) >> 1); // bit 6
//        line1 += ((d_row[5] & mask) >> 2); // bit 5
//        line1 += ((d_row[4] & mask) >> 3); // bit 4
//        line1 += ((d_row[3] & mask) >> 4); // bit 3
//        line1 += ((d_row[2] & mask) >> 5); // bit 2
//        line1 += ((d_row[1] & mask) >> 6); // bit 1
//        line1 += ((d_row[0] & mask) >> 7); // bit 0        
//        //unsigned short long d_column = line3;
//        d_column = line3;
//        d_column = (d_column << 8) + line2;
//        d_column = (d_column << 8) + line1;
//        data_to_column(d_column);
//    }