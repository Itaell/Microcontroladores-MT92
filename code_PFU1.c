/*
 * File:   code_PFU1.c
 * Author: marfi
 *
 * Created on 30 de junio de 2021, 10:20 PM
 */

#include <xc.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC = INTIO7
unsigned char uni = 0;
unsigned char dec = 0;
unsigned char cen = 0;
unsigned char con = 0;
const char num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

void __interrupt() pulsos(void){
    
    if (INT0IF == 1){ // Clear
        con ++;
        INT0IF = 0; 
    }
    
    if (INT1IF == 1){ // Conteo
        con = 0;
        INT1IF = 0;
    }
}

void desnum(int con){

    uni = con%10;
    dec = con/10;
    cen = con/100;

}

void multip(unsigned char cen, unsigned char dec, unsigned char uni){

    LATAbits.LA1 = 1;
    LATD = cen;
    __delay_ms(20);
    LATAbits.LA1 = 0;
    
    LATAbits.LA2 = 1;
    LATD = dec;
    __delay_ms(20);
    LATAbits.LA2 = 0;
        
    LATAbits.LA3 = 1;
    LATD = uni;
    __delay_ms(20);
    LATAbits.LA3 = 0;
}

void main(void) {
    
    OSCCONbits.SCS = 0x3;
    OSCCONbits.IRCF = 0x5;
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISA = 0x00;
    ANSELA = 0x00;
    ANSELB = 0x00;
    INT0IE = 1; //RB0
    INT1IE = 1; //RB1
    GIE = 1;
    PEIE = 1;
    
    while(1){
        
        LATAbits.LA0 = 0;
        multip(cen, dec, uni);
        desnum(con);
        cen = (num[cen]);
        dec = (num[dec]);
        uni = (num[uni]);
    }
    return;
}