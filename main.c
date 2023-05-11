/*
 * Lab3.c
 *
 * Created: 5/30/2022 8:26:23 PM
 * Author : Abdalla 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "avr/iom328pb.h"

#define BAUD_RATE 9600
#define ubrr  F_CPU/16/BAUD_RATE-1

int const Keys [4][4] =
{
	{'1','2','3','A'}, 
	{'4', '5', '6', 'B'}, 
	{'7', '8', '9', 'C'}, 
	{'*', '0', '#', 'D'}
};


void USART_Init(int br)
{
	// Set the Baud rate to 9600
	UBRR0H = (br>>8);
	UBRR0L = br;

	// set the data bits to 8-bit
	UCSR0C |= ((1<<UCSZ00) | (1<<UCSZ01));
	UCSR0B &= ~(1<<UCSZ02);

	// set the stop bit to 1
	UCSR0C &= ~(1<<USBS0);
}

void USART_Transmit(char key)
{
	// enable the transmitter
	UCSR0B |= (1<<TXEN0);
	

	while (!(UCSR0A & (1<<UDRE0)));  // wait until the transmit register is cleared
		
	UDR0 = key;
}

void scan()
{
	while(1)
	{
		for (int i=0; i<4; i++)
		{
			PORTD &= ~(1<<(PORTD4+i));	//drive low on row i
			
			for (int j = 0; j<4; j++)
			{
				if ( !(PINB & (1<<(PORTB0+j))))
				{
					USART_Transmit(Keys[i][j]);
					while ( !(PINB & (1<<(PORTB0+j)))); // wait until the key is released
				}
			}
			PORTD |= (1<<PORTC4+i); // drive pin high again
		}
	}
	
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		
		DDRD |= 0xF0;	// rows are output and columns are inputs
		DDRB &= 0xF0;
		
		PORTD |= 0xF0;	// enable pull up resistors for the input pins and drive high for output pins
		PORTB |= 0x0F;
		
		USART_Init(ubrr);
		scan();
				 
    }
}