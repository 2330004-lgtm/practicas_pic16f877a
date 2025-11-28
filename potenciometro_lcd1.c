/*
 * File:   potenciometro_lcd1.c
 * Author: Ximena Muñiz
 *
 * Created on 24 de noviembre de 2025, 07:15 PM
 */
#include <xc.h>
#include <stdio.h>


#define _XTAL_FREQ 20000000UL   // 20 MHz

// RS = RB6, EN = RB7 para PIC16F877A
#define LCD_RS      PORTBbits.RB6
#define LCD_EN      PORTBbits.RB7

#define LCD_RS_TRIS TRISBbits.TRISB6
#define LCD_EN_TRIS TRISBbits.TRISB7



void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_puts(const char *s);
void lcd_goto(unsigned char row, unsigned char col);

void adc_init(void);
unsigned int adc_read_an0(void);



void main(void) {

    //CONFIG PUERTOS 

    // PORTD como salida 
    TRISD = 0x00;
    PORTD = 0x00;

    // RS y EN en B6 y B7
    LCD_RS_TRIS = 0;   // RB6 salida (RS)
    LCD_EN_TRIS = 0;   // RB7 salida (EN)
    LCD_RS = 0;
    LCD_EN = 0;

    // RA0 como entrada analógica (AN0)
    // RA1 RA5 como salidas 
    TRISA = 0b00000001;   

    PORTA = 0b00111111;   

    
   
    TRISE = 0b00000000;    
    PORTE = 0b00000111;  

    // INICIALIZAR MÓDULOS 

    adc_init();
    lcd_init();

    // Buffers para texto
    char line1[17];
    char line2[17];

 
    while (1) {

        //  Leer ADC en AN0 
        unsigned int raw = adc_read_an0();

        //  Convertir a mV (con Vref = 5000 mV)
       
        unsigned long temp = raw;
        temp = temp * 5000UL;
        unsigned int mv = (unsigned int)(temp / 1023UL);

      
        sprintf(line1, "RAW: %4u", raw);
        sprintf(line2, "mV:  %4u", mv);

       
        lcd_goto(1, 1);
        lcd_puts("                "); 
        lcd_goto(1, 1);
        lcd_puts(line1);

        lcd_goto(2, 1);
        lcd_puts("                ");  
        lcd_goto(2, 1);
        lcd_puts(line2);

        __delay_ms(100);    
    }
}



void adc_init(void) {
   
    
    ADCON1 = 0x87;

    ADCON0 = 0x81;

    __delay_ms(10);        
}

unsigned int adc_read_an0(void) {

    

    __delay_ms(2);         // tiempo de adquisición (Tacq)

    GO_nDONE = 1;          
    while (GO_nDONE);      // esperar a que termine

    
    return ((unsigned int)ADRESH << 8) | ADRESL;
}



static void lcd_pulse_enable(void) {
    LCD_EN = 1;
    __delay_us(2);
    LCD_EN = 0;
    __delay_us(50);
}

void lcd_cmd(unsigned char cmd) {
    LCD_RS = 0;       
    PORTD = cmd;       
    lcd_pulse_enable();
    if (cmd == 0x01 || cmd == 0x02) {
        __delay_ms(2); 
    }
}

void lcd_data(unsigned char data) {
    LCD_RS = 1;        
    PORTD = data;
    lcd_pulse_enable();
}

void lcd_puts(const char *s) {
    while (*s) {
        lcd_data(*s++);
    }
}

void lcd_init(void) {
    __delay_ms(20);     

    lcd_cmd(0x38);       
    lcd_cmd(0x0C);       
    lcd_cmd(0x06);       
    lcd_cmd(0x01);       
    __delay_ms(2);
}

void lcd_goto(unsigned char row, unsigned char col) {
    unsigned char addr;

    if (row == 1)
        addr = 0x00 + (col - 1);  // fila 1
    else
        addr = 0x40 + (col - 1);  // fila 2

    lcd_cmd(0x80 | addr);
}