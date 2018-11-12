#include "TINY85_BUTTON.h"


#define HIGH true
#define LOW false

int *tiny85_button_pins;
int tiny85_button_n_pins;
volatile unsigned char tiny85_button_ticks[6];
volatile bool tiny85_button_enabled[6];
bool tiny85_button_state[6];


// interrupt service routine (ISR) for Timer/Counter1 Compare Match A
ISR(TIMER1_COMPA_vect)
{
  int i;

  for(i=0; i<tiny85_button_n_pins; i++)
  {
    tiny85_button_ticks[i]++;

    if(tiny85_button_ticks[i] >= 30)
    {
      tiny85_button_ticks[i] = 0;
      tiny85_button_enabled[i] = true;
    }
  }
}


TINY85_BUTTON::TINY85_BUTTON()
{
  //
}


TINY85_BUTTON::~TINY85_BUTTON()
{
  //
}


void TINY85_BUTTON::init(int *button_pins, int num_of_pins)
{
  tiny85_button_pins = button_pins;
  tiny85_button_n_pins = num_of_pins;

  int i;
  for(i=0; i<tiny85_button_n_pins; i++)
  {
    DDRB |= (0 << tiny85_button_pins[i]);  // set as input
    //PORTB |= (1 << tiny85_button_pins[i]); // pullup resistor to input pin

    tiny85_button_state[i] = HIGH;
    tiny85_button_ticks[i] = 0;
    tiny85_button_enabled[i] = true;
  }

  initCCR1AInterrupt();
}


bool TINY85_BUTTON::pressed(int query_pin)
{
  int i = find_pin(query_pin);

  if(i == -1)
  {
    return false;
  }

  if(tiny85_button_enabled[i])
  {
    if( state_changed(i) && (tiny85_button_state[i] == LOW) )
    {
      tiny85_button_ticks[i] = 0;
      tiny85_button_enabled[i] = false;

      return true;
    }
  }

  return false;
}


bool TINY85_BUTTON::state_changed(int pin_index)
{
  bool new_state = get_state(tiny85_button_pins[pin_index]);

  if( new_state != tiny85_button_state[pin_index] )
  {
    tiny85_button_state[pin_index] = new_state;
    return true;
  }

  return false;
}


bool TINY85_BUTTON::get_state(int pin)
{
  if( !(PINB & (1 << pin)) )
  {
    return LOW;
  }

  return HIGH;
}


int TINY85_BUTTON::find_pin(int query_pin)
{
  int i;
 
  for(i=0; i<tiny85_button_n_pins; i++)
  {
    if( query_pin == tiny85_button_pins[i] )
    {
      return i;
    }
  }

  return -1;
}

void TINY85_BUTTON::initCCR1AInterrupt()
{
  TCNT1 = 0x00;

  OCR1C = 0xFF;    // number to count up to (0xFF = 255)
  OCR1A = 0XFF;    // number to count up to (0xFF = 255)
    
  TCCR1 = 0x8B;    // Clear Timer/Counter on Compare Match, CTC mode -- clock source CLK/1024

  TIMSK |= (1 << OCIE1A);   // Timer/Counter1 Output Compare Interrupt Enable
}

