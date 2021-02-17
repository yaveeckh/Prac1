#include <avr/io.h>
#include <util/delay.h>

//Binary to gray code
char binary_gc(unsigned char binary) {
    return binary ^ (binary >> 1);
}

int main(void)
{
    // make the LED pin an output for PORTA
    DDRA = 0xFF;                    // Set all portA pins as output
    PORTA = 0x00;                      //Turn all LEDS off

    // make the switch pin an input for PORTE
    DDRE = ~(_BV(PE6)|_BV(PE4));    //Set pin 4 and 6 as input
    PORTE = _BV(PE4)|_BV(PE6);      //Set pin 4 and 6 as pull up

    char state_w = 0;               //Initiate W button pressed as 0
    unsigned char counter = 0x00; // Initiate counter at 0
    while (1)
    {
        _delay_ms(100);                 //Delay clock with 100ms
        if(~PINE & _BV(PE4)) {          //If west button is pressed
            if (!state_w) {             //Check if west button has already been pressed
                counter += 1;        //Add 1 to counter when button is pressed
                if (counter == 16) {    //Check if counter is equal to 16 => reset
                    PORTA = 0;
                    counter = 0;
                }

                PORTA = counter;        //Count with leds
                state_w = 1;            //Set west button state to pressed
            }
        } else {
            state_w = 0;                //Set west button state to unpressed
        }

    }

    return 0;
}
