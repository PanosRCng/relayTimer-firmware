/*
 *    RelayTimer
 *
 *
 *	- Firmware for the AT85RT2L1B1P system
 *
 *

 *
 *  	(*) developed (and tested) for ATtiny85 microprocessor running 
 *	  at 8 MHz from its internal oscillator
 */



#include <avr/io.h>
#include "TINY85_ALARM.h"
#include "TINY85_ADC.h"
#include "TINY85_BUTTON.h"


#define LED_PIN_GREEN PB2
#define LED_PIN_RED PB1
#define BUTTON_PIN PB0
#define RELAY_CONTROL_PIN PB3
#define TICKING 1
#define SETUP 2



int main(void)
{
  DDRB |= (1 << LED_PIN_GREEN);  // set as output
  DDRB |= (1 << LED_PIN_RED);  // set as output
  DDRB |= (1 << RELAY_CONTROL_PIN);  // set as output

  int button_pins[] = {BUTTON_PIN}; 

  TINY85_ALARM alarm;
  TINY85_ADC adc;
  TINY85_BUTTON button;

  alarm.init();
  adc.init();
  button.init(button_pins, 1);

  sei();

  int state = SETUP;
  unsigned char minutes = 0;

  while(1) 
  {    
    
    if(state == TICKING)
    {
      PORTB |= (1 << RELAY_CONTROL_PIN); 
      PORTB |= (1 << LED_PIN_GREEN); 
      PORTB &= ~(1 << LED_PIN_RED);

      if( button.pressed(BUTTON_PIN) )
      {
        alarm.stop();
        state = SETUP;

        continue;
      }
      
      if(alarm.check())
      {        
        alarm.stop();
        state = SETUP;
        continue;
      }
    }

    if(state == SETUP)
    { 
      PORTB &= ~(1 << RELAY_CONTROL_PIN);
      PORTB |= (1 << LED_PIN_RED); 
      PORTB &= ~(1 << LED_PIN_GREEN); 

      if( button.pressed(BUTTON_PIN) )
      {
	minutes = adc.measure();

        alarm.start(minutes);
        state = TICKING;

	continue;
      }
    }
    
  }

  return 0;
}


