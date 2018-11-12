/*
 *    tiny85_alarm
 *
 *
 *
 *	- ATtiny85 ADC library
 *
 *
 *
 *
 *  	(*) developed (and tested) for a ATtiny85 running 
 *	  at 8 MHz from its internal oscillator
 */


#ifndef TINY85_ADC_H_
#define TINY85_ADC_H_


#include <avr/io.h>


class TINY85_ADC
{

  public:

    TINY85_ADC();

    ~TINY85_ADC();

    void init(void);

    unsigned char measure(void);
  
};



#endif
