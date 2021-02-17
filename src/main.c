#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // make the LED pin an output for PORTA
    DDRA = 0xFF;                    // Set all portA pins as output
    PORTA = 0x00;                      //Turn all LEDS off

    // make the switch pin an input for PORTE
    DDRE = ~(_BV(PE6)|_BV(PE4));    //Set pin 4 and 6 as input
    PORTE = _BV(PE4)|_BV(PE6);      //Set pin 4 and 6 as pull up

    char state_w = 0;               //Initiate W button pressed as 0

    while (1)
    {
        _delay_ms(100);                 //Delay clock with 100ms
        if(~PINE & _BV(PE4)) {          // If west button is pressed
            if (!state_w) {             //Check if west button has already been pressed
                if (PORTA == 0xff) {
                    PORTA = 0;
                }
                PORTA = (PORTA << 1) + 1;      //Switch LED7
                state_w = 1;            //Set west button state to pressed
            }
        } else {
            state_w = 0;
        }

    }

    return 0;
}
