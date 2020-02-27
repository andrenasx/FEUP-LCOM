#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

unsigned int counter = 0; //Initialize the counter
int hook_id = TIMER0_IRQ;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  uint8_t rb;

  if(timer_get_conf(timer, &rb)){  //get current timer conf
    return 1;
  }

  if(timer<0||timer>2){ // Check for invalid timer 
    return 1;
  }

  if(freq<19 || freq > TIMER_FREQ){ //Check given frequency for invalid values
    printf("Error invalid frequency value");
    return 1;
  }

  uint8_t LSB;
  uint8_t MSB;
  uint16_t initfreq = (uint16_t) (TIMER_FREQ / freq); // initial value frequency is equal to the clock frequency divided by the timer operating frequency

  util_get_LSB(initfreq, &LSB);   //new LSB
  util_get_MSB(initfreq, &MSB);   //new MSB


//creating control word, 4LSB maintained and selected counter

  switch (timer)
  {
  case 0:
    rb = ((rb & 0x0F) | TIMER_SEL0 | TIMER_LSB_MSB);  // we use the 0x0F mask to make sure the 4 least significant bits aren't changed ; creates control word

    sys_outb(TIMER_CTRL, rb);
    sys_outb(TIMER_0,LSB);
    sys_outb(TIMER_0,MSB);
    break;

  case 1:
    rb = ((rb & 0x0F) | TIMER_SEL1 | TIMER_LSB_MSB);
    sys_outb(TIMER_CTRL, rb);
    sys_outb(TIMER_1,LSB);
    sys_outb(TIMER_1,MSB);
    break;

  case 2:
    rb = ((rb & 0x0F) | TIMER_SEL2 | TIMER_LSB_MSB);
    sys_outb(TIMER_CTRL, rb);
    sys_outb(TIMER_2,LSB);
    sys_outb(TIMER_2,MSB);
    break;

  default:
    return 1;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = BIT(hook_id); //bits_no = 0

  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)==1){
    printf("Error in sys_irqsetpolicy\n");
    return 1;
  }

  return 0;
}

int (timer_unsubscribe_int)() { 
  
  if(sys_irqrmpolicy(&hook_id)==1){
    printf("Error in sys_irqrmpolicy\n");
    return 1;
  }

  return 0;
}

void (timer_int_handler)() {
  counter++; //increment counter
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if(timer<0||timer>2){ //check for invalid timer
    return 1;
  }

  uint8_t rdbcommand = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));

  if(sys_outb(TIMER_CTRL, rdbcommand)){
    return 1;
  }

  util_sys_inb(TIMER_0 + timer, st);

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  if(timer<0||timer>2){ //check for invalid timer
    return 1;
  }

  union timer_status_field_val conf;

  if (field == tsf_all){
    conf.byte = st;
  }

  else if (field == tsf_initial){
    st &= 0x30; // get bit 5 and 4
    st>>=4; // move bit 5 and 4 to final bits
    conf.in_mode = st;
  }

  else if(field == tsf_mode){
    st &= 0x0E; //get bit 3, 2 and 1
    st>>=1; // move to final bits

    //6 and 7 are treated diferently because of future compability
    if(st==6){
      conf.count_mode=2;
    }
    else if(st==7){
      conf.count_mode=3;
    }
    else{
      conf.count_mode=st;
    }
  }

  else if(field== tsf_base){
    if(st & TIMER_BCD){
      conf.bcd=true; // if last bit is 1 count in BCD 
    }
    else
    {
      conf.bcd=false; //if last bit is 0 count in binary
    }
  }

  else{
    return 1;
  }

  if(timer_print_config(timer, field, conf)==1){
    return 1;
  }

  return 0;
}
