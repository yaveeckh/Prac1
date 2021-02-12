
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // make the LED pin an output for PORTA
    DDRA = 0xFF;                    // Set all portA pins as output
    PORTA = 0;                      //Turn all LEDS off

    // make the switch pin an input for PORTE
    DDRE = ~(_BV(PE6)|_BV(PE4));    //Set pin 4 and 6 as input
    PORTE = _BV(PE4)|_BV(PE6);      //Set pin 4 and 6 as pull up

    char state_w = 0;               //Initiate W button pressed as 0
    char state_e = 0;               //Initiate E button pressed as 1
    
    while (1)
    {
        _delay_ms(100);                 //Delay clock with 100ms
        
        if(~PINE & _BV(PE4)) {          // If west button is pressed
            if (!state_w) {             //Check if west button has already been pressed
                PORTA ^= _BV(PA7);      //Switch LED7
                state_w = 1;            //Set west button state to pressed
            }
        } else if (~PINE & _BV(PE6)) {  //If east button is pressed
            if (!state_e) {             //Check if east button has already been pressed
                PORTA ^= _BV(PA1);      //Switch LED1
                state_e = 1;            //Set east button state to pressed
            }
        } else {
            state_w = 0;                //Set west button state to unpressed
            state_e = 0;                //Set east button state to unpressed
        }
    }

    return 0;
}