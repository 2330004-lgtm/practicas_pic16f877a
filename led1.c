/*
 * File:   led1.c
 * Author: Ximena Muñiz
 *
 * Created on 20 de noviembre de 2025, 09:54 PM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000


void main(void) {
    TRISCbits.TRISC7 = 0;
    TRISBbits.TRISB1 = 1;
    
    PORTCbits.RC7 = 0;
    
    while(1){
        if(PORTBbits.RB1 == 1){
            PORTCbits.RC7 = 1;
        }
        
        if(PORTBbits.RB1 == 0){
            PORTCbits.RC7 = 0;
        }
        
    }
}
