#include "TINY85_ADC.h"


TINY85_ADC::TINY85_ADC()
{
  //
}


TINY85_ADC::~TINY85_ADC()
{
  //
}


void TINY85_ADC::init(void)
{
  ADMUX =
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
            (0 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
            (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
            (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 64, bit 2 
            (1 << ADPS1) |     // set prescaler to 64, bit 1 
            (0 << ADPS0);      // set prescaler to 64, bit 0  
}


unsigned char TINY85_ADC::measure(void)
{
    ADCSRA |= (1 << ADSC);         // start ADC measurement
    while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

    unsigned char measure = ADCH;

    return measure;
}
