/*
 *    tiny85_alarm
 *
 *
 *
 *	- ATtiny85 Alarm library
 *
 *
 *	- 
 *
 *
 *
 *  	(*) developed (and tested) for a ATtiny85 running 
 *	  at 8 MHz from its internal oscillator
 */


#ifndef TINY85_ALARM_H_
#define TINY85_ALARM_H_


#include <avr/io.h>
#include <avr/interrupt.h>



class TINY85_ALARM
{

  public:

    TINY85_ALARM();

    ~TINY85_ALARM();

    void init(void);

    void start(unsigned char);

    void stop(void);

    bool check(void);


  private:

    unsigned char minutes_to_count;
    unsigned char seconds;
    unsigned char minutes;

    void tick(void);

    // init a Timer/Counter0 Compare Match Interrupt on OCR0A
    void initCCR0AInterrupt(void);  

};


#endif
