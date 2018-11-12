#include "TINY85_ALARM.h"


volatile unsigned char tiny85_alarm_ticks;

// interrupt service routine (ISR) for Timer/Counter0 Compare Match A
ISR(TIMER0_COMPA_vect)
{
  tiny85_alarm_ticks++;
}


TINY85_ALARM::TINY85_ALARM()
{
  //
}


TINY85_ALARM::~TINY85_ALARM()
{
  //
}


void TINY85_ALARM::init(void)
{
  initCCR0AInterrupt();
}


void TINY85_ALARM::start(unsigned char minutes_set)
{
  minutes_to_count = minutes_set;

  tiny85_alarm_ticks = 0;
  seconds = 0;
  minutes = 0;

  TIFR |= (1 << OCF0A); // clear Output Compare Flag A
  TIMSK |= (1 << OCIE0A); // TC0 compare match A interrupt enable
}


void TINY85_ALARM::stop(void)
{
  TIMSK &= ~(1 << OCIE0A);; 
}


bool TINY85_ALARM::check(void)
{
  tick();

  if(minutes >= minutes_to_count)
  {
     return true;
  }

  return false;
}


void TINY85_ALARM::tick(void)
{
  if(tiny85_alarm_ticks >= 30)
  {
    tiny85_alarm_ticks = 0;
    seconds++;  
  }

  if(seconds >= 60)
  {
    seconds = 0;
    minutes++;
  }

}


void TINY85_ALARM::initCCR0AInterrupt()
{
  OCR0A  = 0xFF;    // number to count up to (0xFF = 255)
  TCCR0A = 0x02;    // clear Timer on Compare Match (CTC) mode
  TCCR0B = 0x05;    // clock source CLK/1024
}

