/*******************************************************
System clock initialization created by the
CodeWizardAVR V3.31 UL Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : CIV Router
*******************************************************/

// I/O Registers definitions
#include <io.h>

// Standard definitions
#include <stddef.h>

// System Clocks initialization
void system_clocks_init(void)
{
unsigned char n,s;

// Optimize for speed
#pragma optsize- 
// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// External 8000,000 kHz clock source on XTAL1 initialization
OSC.XOSCCTRL=OSC_XOSCSEL_EXTCLK_gc;
// Enable the external clock source
OSC.CTRL|=OSC_XOSCEN_bm;

// PLL initialization
// Ensure that the PLL is disabled before configuring it
OSC.CTRL&= ~OSC_PLLEN_bm;
// PLL clock source: External Osc. or Clock
// PLL multiplication factor: 4
// PLL frequency: 32,000000 MHz
// Set the PLL clock source and multiplication factor
n=OSC_PLLSRC_XOSC_gc | (4<<OSC_PLLFAC_gp);
// Enable the PLL
CCP=CCP_IOREG_gc;
OSC.PLLCTRL=n;
OSC.CTRL|=OSC_PLLEN_bm;

// Wait for the PLL to stabilize
while ((OSC.STATUS & OSC_PLLRDY_bm)==0);

// System Clock prescaler A division factor: 1
// System Clock prescalers B & C division factors: B:1, C:1
// ClkPer4: 32000,000 kHz
// ClkPer2: 32000,000 kHz
// ClkPer:  32000,000 kHz
// ClkCPU:  32000,000 kHz
n=(CLK.PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm | CLK_PSBCDIV0_bm))) |
	CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
CCP=CCP_IOREG_gc;
CLK.PSCTRL=n;

// Select the system clock source: Phase Locked Loop
n=(CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_PLL_gc;
CCP=CCP_IOREG_gc;
CLK.CTRL=n;

// Disable the unused oscillators: 32 kHz, 2 MHz, 32 MHz
OSC.CTRL&= ~(OSC_RC32KEN_bm | OSC_RC2MEN_bm | OSC_RC32MEN_bm);

// ClkPer output disabled
PORTCFG.CLKEVOUT&= ~PORTCFG_CLKOUT_gm;
// Restore interrupts enabled/disabled state
SREG=s;
// Restore optimization for size if needed
#pragma optsize_default
}

