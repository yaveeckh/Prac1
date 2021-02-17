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
    PORTA = 0x00;                   //Turn all LEDS off

    // make the switch pin an input for PORTE
    DDRE &= ~(_BV(PE6)|_BV(PE4));    //Set pin 4 and 6 as input
    PORTE |= _BV(PE4)|_BV(PE6);      //Set pin 4 and 6 as pull up

    char state_w = 0;               //Initiate W button pressed as 0
    unsigned char counter = 0x00;   // Initiate counter at 0

    char active_count_state = 0;

    while (1)
    {
        if(active_count_state == 0 && counter == 15) {
            active_count_state = 1;     //Set count state to substract when counter reaches 15 and state is add
        } else if (active_count_state == 1 && counter == 0) {
            active_count_state = 0;     //Set count state to add when counter reaches 0 and state is substract
        }

        _delay_ms(100);                         //Delay clock with 100ms
        if(~PINE & _BV(PE4)) {                  //If west button is pressed
            if (!state_w) {                     //Check if west button has already been pressed
                if (!active_count_state) {      //Check for count state (substract = 1 | add = 0)
                    counter +=1;
                } else {
                    counter -= 1;
                }

                PORTA = binary_gc(counter);        //Count with leds
                state_w = 1;                       //Set west button state to pressed
            }
        } else {
            state_w = 0;    //Set west button state to unpressed
        }
    }

    return 0;
}