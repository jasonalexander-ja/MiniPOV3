#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>


// This function basically wastes time
void delay_ms( uint16_t milliseconds)
{
   for( ; milliseconds > 0; milliseconds--)
   {
      _delay_ms( 1);
   }
} 

int main(void) {

  DDRB = 0xFF;        // set port B to output only

  PORTB = 0; // turn off all LEDs
  while (1) {
    PORTB = 0x1;      // turn on only LED #1
    delay_ms(200);
    PORTB = 0x2;      // turn on only LED #2
    delay_ms(200);
    PORTB = 0x4;      // etc..
    delay_ms(200);
    PORTB = 0x8;
    delay_ms(200);
    PORTB = 0x10; 
    delay_ms(200);
    PORTB = 0x20; 
    delay_ms(200);
    PORTB = 0x40; 
    delay_ms(200);
    PORTB = 0x80;    // turn on LED #8
    delay_ms(200);
  }
}
