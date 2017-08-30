/*
 * SmartFan.c
 *
 * Created: 30/08/2017 5:32:48 p.m.
 * Author : rwin746
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
// #include "prototype header file.h"

#define F_CPU 16000000 // System clock?
#define BAUD 9600 // baud rate
#define MYUBRR F_CPU/16/BAUD-1 // UBRR

//interrupt service routine
ISR(PCINT0_vect) {
	//write code to do something when PA1 toggles

}

int main(void)
{
    DDRA &= ~(1 << PA1); // presumably we are attempting to detect a change in input
	cli(); //disable interrupt when setting interrupts
	PCMSK0 |= (1 << PCINT1); //enable pin change interrupt on PA1
	GIMSK |= (1 <<PCIE0); //enable pin change interrupt 0 (PCINT1 is with PCI0)
	sei(); //enable global interrupt
	
	/*
	uart_init(MYUBRR);
	adc_init();
	timer0_init();
	timer1_init();
    stdout = &mystdout; //for printf	
*/
    while (1) 
    {
    }
}

//set input/output pins
void set_io() {
	//set PA1 and PA2 as output (to drive the switches)
	DDRA |= (1<<DDA1)|(1<<DDA2);
	//set PA3 as input (for hall-effect sensor)
	DDRA &= ~(1<<DDA3);

	while(1){
		if (PINA3) { //read hall sensor signal, if high
			PORTA |= (1<<PORTA1); //turn on one of the switch
			PORTA &= ~(1<<PORTA2); //turn off the other switch
		}
		else { 	//if hall sensor signal is low
			PORTA &= ~(1<<PORTA1); //turn off one of the switch
			PORTA |= (1<<PORTA2); //turn on the other
		}
	} // How to turn fan off?
}

