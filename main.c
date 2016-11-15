#include <xc.h>
#include <htc.h>
#define _XTAL_FREQ 8000000
#pragma config FOSC     = INTOSC
#pragma config WDTE     = OFF
#pragma config PWRTE    = OFF
#pragma config MCLRE    = ON
#pragma config CP       = OFF
#pragma config BOREN    = ON
#pragma config CLKOUTEN = OFF
#pragma config IESO     = OFF
#pragma config FCMEN    = OFF
#pragma config WRT      = OFF
#pragma config PLLEN    = OFF
#pragma config STVREN   = ON
#pragma config BORV     = HI
#pragma config LVP      = OFF

void delay() {
	__delay_us(2500);
}

void reset() {
	LATA2 = LATC0 = LATC1 = LATC2 = 0;
}

void forward() {
	LATA2 = 1; LATC0 = 1; LATC1 = 0; LATC2 = 0; delay();
	LATA2 = 0; LATC0 = 1; LATC1 = 1; LATC2 = 0; delay();
	LATA2 = 0; LATC0 = 0; LATC1 = 1; LATC2 = 1; delay();
	LATA2 = 1; LATC0 = 0; LATC1 = 0; LATC2 = 1; delay();
}

void back() {
	LATA2 = 1; LATC0 = 0; LATC1 = 0; LATC2 = 1; delay();
	LATA2 = 0; LATC0 = 0; LATC1 = 1; LATC2 = 1; delay();
	LATA2 = 0; LATC0 = 1; LATC1 = 1; LATC2 = 0; delay();
	LATA2 = 1; LATC0 = 1; LATC1 = 0; LATC2 = 0; delay();
}

void forward_with_delay_ms(int delay) {
	LATA2 = 1; LATC0 = 1; LATC1 = 0; LATC2 = 0; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 0; LATC0 = 1; LATC1 = 1; LATC2 = 0; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 0; LATC0 = 0; LATC1 = 1; LATC2 = 1; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 1; LATC0 = 0; LATC1 = 0; LATC2 = 1; for (int i = 0; i < delay; i++) __delay_ms(1);
}

void back_with_delay_ms(int delay) {
	LATA2 = 1; LATC0 = 0; LATC1 = 0; LATC2 = 1; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 0; LATC0 = 0; LATC1 = 1; LATC2 = 1; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 0; LATC0 = 1; LATC1 = 1; LATC2 = 0; for (int i = 0; i < delay; i++) __delay_ms(1);
	LATA2 = 1; LATC0 = 1; LATC1 = 0; LATC2 = 0; for (int i = 0; i < delay; i++) __delay_ms(1);
}

void main() {
	OSCCON     = 0b01110010;
	ANSELA     = 0b00000000;
	ANSELC     = 0b00000000; 
	TRISA      = 0b00000000;
	WPUA       = 0b00000000;
	TRISC      = 0b00111000;
	WPUC       = 0b00000000;
	OPTION_REG = 0b00000000;
	PORTA      = 0;
	PORTC      = 0;
	
	int distance = 125;
	int toggle = 0;
	while (1) {
		if (RC5) {
			__delay_ms(300);
			if (RC5) {
				__delay_ms(5000);
				continue;
			}
			if (toggle % 2 == 1) {
				toggle++;
			} else {
				for (int i = 0; i < distance; i++) forward();
				__delay_ms(50);
			}
			for (int i = 0; i < distance - 5; i++) back();
			for (int i = 0, j = 3; i < 5; i++) {
				LATA2 = 1; LATC0 = 0; LATC1 = 0; LATC2 = 1; for (int i = 0; i < j; i++) __delay_ms(1); j += 2;
				LATA2 = 0; LATC0 = 0; LATC1 = 1; LATC2 = 1; for (int i = 0; i < j; i++) __delay_ms(1); j += 2;
				LATA2 = 0; LATC0 = 1; LATC1 = 1; LATC2 = 0; for (int i = 0; i < j; i++) __delay_ms(1); j += 2;
				LATA2 = 1; LATC0 = 1; LATC1 = 0; LATC2 = 0; for (int i = 0; i < j; i++) __delay_ms(1); j += 2;
			}
			reset();
		} else if (RC4) {
			__delay_ms(300);
			if (RC4) {
				__delay_ms(5000);
				continue;
			}
			if (toggle % 2 == 0) {
				for (int i = 0; i < distance; i++) forward_with_delay_ms(10);
			} else {
				for (int i = 0; i < distance; i++) back_with_delay_ms(10);
			}
			toggle++;
			reset();
		}
	}
}
