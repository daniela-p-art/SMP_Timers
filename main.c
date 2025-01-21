#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop the watchdog timer to prevent unwanted resets
    PM5CTL0 &= ~LOCKLPM5;       // Disable GPIO high-impedance mode to activate I/O configuration

    P4OUT = 0x00;               // Initialize all P4 output pins to LOW
    P4DIR |= BIT6;              // Set P4.6 (Green LED) as output
    P4DIR |= BIT7;              // Set P4.7 (Red LED) as output
    P4DIR |= BIT4;              // Set P4.4 (Yellow LED) as output

    // Timer B0 configuration for Green LED blinking
    TB0CCR0 = 8195;             // Set Timer B0 period for a 1-second interval (32kHz ACLK)
    TB0CCR2 = TB0CCR0 / 2;      // Set duty cycle to 50%
    TB0CCTL2 |= OUTMOD_3 | CCIE;// Set output mode to Set/Reset and enable interrupt

    // Timer B1 configuration for Yellow LED blinking
    TB1CCR0 = 8195;             // Set Timer B1 period for a 1-second interval (32kHz ACLK)
    TB1CCR2 = 4800;             // Set duty cycle for approximately 0.5-second ON time
    TB1CCTL0 |= OUTMOD_3 | CCIE;// Enable interrupt for Timer B1 CCR0

    // Timer B2 configuration for Red LED blinking
    TB2CCR0 = 8195;             // Set Timer B2 period for a 1-second interval (32kHz ACLK)
    TB2CCR2 = 8000;             // Set duty cycle for approximately 0.9-second ON time
    TB2CCTL0 |= OUTMOD_3 | CCIE;// Enable interrupt for Timer B2 CCR0

    // Start timers in "Up mode" using ACLK and clear previous settings
    TB0CTL |= MC__UP | TBSSEL__ACLK | TBCLR;
    TB1CTL |= MC__UP | TBSSEL__ACLK | TBCLR;
    TB2CTL |= MC__UP | TBSSEL__ACLK | TBCLR;

    __bis_SR_register(GIE);     // Enable global interrupts
}

// Interrupt Service Routine for Timer B0 (Green LED)
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void) {
    P4OUT ^= BIT6;              // Toggle P4.6 (Green LED)
    TB0CCTL2 &= ~CCIFG;         // Clear interrupt flag for Timer B0 CCR2
}

// Interrupt Service Routine for Timer B1 (Yellow LED)
#pragma vector = TIMER1_B0_VECTOR
__interrupt void TIMER1_B0_ISR(void) {
    P4OUT ^= BIT4;              // Toggle P4.4 (Yellow LED)
    TB1CCTL2 &= ~CCIFG;         // Clear interrupt flag for Timer B1 CCR2
}

// Interrupt Service Routine for Timer B2 (Red LED)
#pragma vector = TIMER2_B0_VECTOR
__interrupt void TIMER2_B0_ISR(void) {
    P4OUT ^= BIT7;              // Toggle P4.7 (Red LED)
    TB2CCTL2 &= ~CCIFG;         // Clear interrupt flag for Timer B2 CCR2
}
