#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // make the LED pin an output for PORTA
    DDRA = 0xFF;                    // Set all portA pins as output
    PORTA = 0x00;                   //Turn all LEDS off

    // make the switch pin an input for PORTE
    DDRE &= ~_BV(PE5);    //Set pin 4 and 6 as input
    PORTE |= _BV(PE5);      //Set pin 4 and 6 as pull up

    char state_w = 0;               //Initiate W button pressed as 0
    char paused = 0;
    unsigned char counter = 0x00;   // Initiate counter at 0

    char active_count_state = 0;    //Initialize active count state as 0 = add

    while (1)
    {
        _delay_ms(70);                          //Delay clock with 70ms

        if(~PINE & _BV(PE5)) {                  //If west button is pressed
            if (!state_w) {                     //Check if west button has already been pressed
                paused ^= 1;                    //Toggle Paused
                state_w = 1;                    //Set west button state to pressed
            }
        } else {
            state_w = 0;    //Set west button state to unpressed
        }

        if (!paused) {
            if(active_count_state == 0 && counter == 8) {
                active_count_state = 1;     //Set count state to substract when counter reaches 15 and state is add
            } else if (active_count_state == 1 && counter == 0) {
                active_count_state = 0;     //Set count state to add when counter reaches 0 and state is substract
            }

            if (!active_count_state) {      //Check for count state (substract = 1 | add = 0)
                counter +=1;
            } else {
                counter -= 1;               
            }
        }


        PORTA = _BV(counter);       //Set led on position offset by counter to on
    }

    return 0;
}