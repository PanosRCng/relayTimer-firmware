/*
 *    tiny85_button
 *
 *
 *
 *  - ATtiny85 Button library
 *
 *
 *
 *
 *    (*) developed (and tested) for a ATtiny85 running 
 *    at 8 MHz from its internal oscillator
 */


#ifndef TINY85_BUTTON_H_
#define TINY85_BUTTON_H_


#include <avr/io.h>
#include <avr/interrupt.h>


class TINY85_BUTTON
{

  public:

    TINY85_BUTTON();

    ~TINY85_BUTTON();

    void init(int *button_pins, int num_of_pins);

    bool pressed(int query_pin);


  private:

    int find_pin(int query_pin);

    bool state_changed(int pin_index);

    bool get_state(int pin);

    void initCCR1AInterrupt(void);

};


#endif
