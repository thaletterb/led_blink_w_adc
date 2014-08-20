/****************************************************************************
Title:    Enable ADC
Author:   
File:     
Software: AVR-GCC
Hardware: Atmega328P  

Description:
    This example shows how to use the built in ADC functionality of the AVR
    and do something useful with it (lighting an LED)
    Based on tutorial found here:
    http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=56429


*****************************************************************************/
#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
    unsigned char ret;

    DDRB  = 0xff;                              // use all pins on port B for output 
    PORTB = 0x00;                              // (LED's low & off)

    setup_adc();
    for(;;){
        ADCSRA |= (1 << ADSC); // Start a new conversion, 
        if(ADCH < 128){
            PORTB=0x00;
        }
        else{
            PORTB=0xFF;
        }
    }
}

void setup_adc(){
    ADCSRA |= ((1<<ADPS1)|(1<<ADPS0));   // setups up ADC clock prescalar to 8 
    //ADCSRA |= (1<<ADPS2);   // setups up ADC clock prescalar to 16
    ADMUX |= (1<<REFS0);                            // set ref voltage to AVCC
    ADMUX |= (1<<MUX1);                             // setup ADC Channel 2
    ADMUX |= (1<<ADLAR);                            // left align results in ADC registers (10 bits across 2 regs)

    ADCSRB &= ~(1<<ADTS2);  // These three cleared should enable free-running mode
    ADCSRB &= ~(1<<ADTS1);
    ADCSRB &= ~(1<<ADTS0); 

    ADCSRA |= (1<<ADATE);                           // ??
    ADCSRA |= (1<<ADEN);                            // enable

    ADCSRA |= (1<<ADSC);                            // start sampling

}

