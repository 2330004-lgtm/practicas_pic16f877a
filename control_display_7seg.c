/*
 * File:   control_display_7seg.c
 * Author: Ximena Muñiz
 *
 * Created on 21 de noviembre de 2025, 08:20 PM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) {
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISEbits.TRISE2 = 0;
    TRISAbits.TRISA5 = 0;
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    
    TRISCbits.TRISC0 = 1;
    
    const unsigned char nums[10] = {
        0b1111110,
        0b0110000,
        0b1101101,
        0b1111001,
        0b0110011,
        0b1011011,
        0b1011111,
        0b1110000,
        0b1111111,
        0b1111011
        
    };
    
    unsigned char digit = 0;
    
    while(1){
        
        unsigned char n = nums[digit];
        
        PORTAbits.RA1 = (n >> 6) & 1;
        PORTAbits.RA2 = (n >> 5) & 1;
        PORTAbits.RA3 = (n >> 4) & 1;
        PORTEbits.RE2 = (n >> 3) & 1;
        PORTAbits.RA5 = (n >> 2) & 1;
        PORTEbits.RE0 = (n >> 1) & 1;
        PORTEbits.RE1 = (n >> 0) & 1;
        
        if(PORTCbits.RC0 == 1){
            __delay_ms(30);
            if(PORTCbits.RC0 == 1){
                digit++;
                if(digit >= 10) digit = 0;
                while(PORTCbits.RC0 == 1);
                __delay_ms(30);
            }
        }
    }
   
}
