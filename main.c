/*
 * SmartFan.c
 *
 * Created: 30/08/2017 5:32:48 p.m.
 * Author : rwin746
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "Prototype.h"

#define F_OSC 8000000 // System oscillator clock frequency
#define BAUD 9600 // Baud rate
#define MYUBRR F_CPU/(16*BAUD) - 1 // UBRR

//interrupt service routine
ISR(PCINT0_vect) {
	//write code to do something when PA1 toggles

}

int main(void)
{
/*
    DDRA &= ~(1 << PA1); // presumably we are attempting to detect a change in input
	cli(); //disable interrupt when setting interrupts
	PCMSK0 |= (1 << PCINT1); //enable pin change interrupt on PA1
	GIMSK |= (1 <<PCIE0); //enable pin change interrupt 0 (PCINT1 is with PCI0)
	sei(); //enable global interrupt
*/	
	
	// uart_init(MYUBRR);

    while (1) 
    {
		//set input/output pins
		//set PA1 and PA2 as output (to drive the switches)
		DDRA |= (1<<DDA1)|(1<<DDA2);
		//set PA3 as input (for hall-effect sensor)
		DDRA &= ~(1<<DDA3);

		while(1){
			if ( PINA |= (1<<PINA3) ) { //read hall sensor signal, if high
				PORTA |= (1<<PORTA1); //turn on one of the switch
				PORTA &= ~(1<<PORTA2); //turn off the other switch
			}
			else { 	//if hall sensor signal is low
				PORTA &= ~(1<<PORTA1); //turn off one of the switch
				PORTA |= (1<<PORTA2); //turn on the other
				}
			} // How to turn fan off?
		}
	]
	
/*
void uart_init(unsigned int MYUBRR) {

	// Set baud rate
	UBRR0H = (unsigned char)(MYUBRR>>8);
	UBRR0L = (unsigned char)MYUBRR;
	
	// Enable transmitter
	UCSR0B = (1<<TXEN0);
	
	// set frame format: 8data, single stop bit, no parity
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

// Configure for Fast PWM Mode
TCCR0A |= (1<<WGM00) | (1<<WMG01);
TCCR0B &= ~(1<<WGM02);

TCCR0B |= (1<< CS00);


// Set Values for Duty Cycle and Frequency
uint8_t TOP = 250;
uint8_t dutySet = 125;
	
OCR0A = TOP;
OCR0B = dutySet;

	TOCPMSA0 &= ~((1<< TOCC0S0) | (1<< TOCC0S1));

	// Clear OC0B when Compare Match
	TCCR0A |= (1<< COM0B1);
	TOCPMCOE |= (1<< TOCC0OE);

}
*/
