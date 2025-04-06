/*******************************************************
This program was created by the CodeWizardAVR V3.31 UL 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : CIV Router
Version : 1
Date    : 13.09.2018
Author  : Kurt Moraw DJ0ABR
Company : Helitron
Comments: 


Chip type               : ATxmega128A3
Program type            : Application
AVR Core Clock frequency: 32,000000 MHz
Memory model            : Small
Data Stack size         : 2048
*******************************************************/

#include <civ.h>


void main(void)
{
unsigned char n;

    // Interrupt system initialization
    // Optimize for speed
    #pragma optsize- 
    // Make sure the interrupts are disabled
    #asm("cli")
    // Low level interrupt: On
    // Round-robin scheduling for low level interrupt: Off
    // Medium level interrupt: On
    // High level interrupt: Off
    // The interrupt vectors will be placed at the start of the Application FLASH section
    n=(PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) |
        PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm;
    CCP=CCP_IOREG_gc;
    PMIC.CTRL=n;
    // Set the default priority for round-robin scheduling
    PMIC.INTPRI=0x00;
    // Restore optimization for size if needed
    #pragma optsize_default

    system_clocks_init(); 
    init_tx();
    ports_init();
    vports_init();
    usartc0_init();
    usartc1_init();
    usartd0_init();
    usartd1_init();
    usarte0_init();
    usarte1_init();
    usartf0_init(); 
    tcc0_init();  

    // Globally enable interrupts
    #asm("sei")     
    
    PORTA.OUT = 0xff;   // LEDs off
    PORTB.OUT = 0xff;

    einschaltblinken();

    while (1)
    {        
        read_civ();
        send_fifo();  
        rs232_leds();            
    }
}
