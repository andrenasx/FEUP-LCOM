#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "keyboard.h"
#include "i8042.h"
#include "utils.h"
#include "timer.h"

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


extern int cnt;
extern uint8_t code;
extern unsigned int counter;


int(kbd_test_scan)() {

  uint8_t irq_set;
  int r, ipc_status;
  message msg;
  uint8_t scan_code[2];
  bool two_byte = false;
  bool make;


  if(kbd_subscribe_int(&irq_set) == 1){
    return 1;
  }
 
  while(code != ESC_BREAKCODE) {
      /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  kbc_ih();
                  if(!two_byte){
                    scan_code[0]=code;
                    if(code == TWO_BYTE_SCANCODE){
                      two_byte = true;
                    }
                    else{
                      make = (code & 0x80) == 0;
                      kbd_print_scancode(make, 1, scan_code);
                    }
                  }
                  else{
                    two_byte = false;
                    scan_code[1]=code;
                    make = (code & 0x80) == 0;
                    kbd_print_scancode(make, 2, scan_code);
                  }
                } 
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }


  if(kbd_print_no_sysinb(cnt) != 0){
    return 1;
  }
  cnt=0;

  if(kbd_unsubscribe_int() != 0){
   return 1;
  }

  return 0;
}

int(kbd_test_poll)() {
  
  uint8_t scan_code[2];
  bool two_byte = false;
  bool make;

  while (code != ESC_BREAKCODE)
  {
    kbc_ih();

    if(code==0x00){
      tickdelay(micros_to_ticks(DELAY_US));
      continue;
    }

    if(!two_byte){
      scan_code[0]=code;
      if(code == TWO_BYTE_SCANCODE){
        two_byte = true;
      }
      else{
      make = (code & 0x80) == 0;
      kbd_print_scancode(make, 1, scan_code);
      }
    }
    else{
      two_byte = false;
      scan_code[1]=code;
      make = (code & 0x80) == 0;
      kbd_print_scancode(make, 2, scan_code);
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if(kbd_print_no_sysinb(cnt) != 0){
    return 1;
  }
  cnt=0;

  kbd_enable();

  return 0;
}

int(kbd_test_timed_scan)(uint8_t idle){                //the difference is that this function uses timer 0, so it needs to subscribe timer 0 to check if it has be more then x time
  uint8_t kbd_irq_set;
  int r, ipc_status;
  message msg;
  uint8_t scan_code[2];
  bool two_byte = false;
  bool make;
  uint8_t timer_irq_set;

  if(timer_subscribe_int(&timer_irq_set) == 1){
      return 1;
  }

  if(kbd_subscribe_int(&kbd_irq_set) == 1){
      return 1;
  }

  while(code != ESC_BREAKCODE && (counter / 60.0) < idle) {
      /* Get a request message. */
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
      }
      if (is_ipc_notify(ipc_status)) { /* received notification */
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                  if (msg.m_notify.interrupts & kbd_irq_set) { /* subscribed interrupt */
                    kbc_ih();
                    counter = 0;  //counter needs to be reseted
                    if(!two_byte){
                      scan_code[0]=code;
                      if(code == TWO_BYTE_SCANCODE){
                        two_byte = true;
                      }
                      else{
                        make = (code & 0x80) == 0;
                        kbd_print_scancode(make, 1, scan_code);
                      }
                    }
                    else{
                      two_byte = false;
                      scan_code[1]=code;
                      make = (code & 0x80) == 0;
                      kbd_print_scancode(make, 2, scan_code);
                    }
                  }
                  else if(msg.m_notify.interrupts & timer_irq_set) {
                      timer_int_handler();
                  }
                  break;
              default:
                  break; /* no other notifications expected: do nothing */
          }
      } else { /* received a standard message, not a notification */
          /* no standard messages expected: do nothing */
      }
  }


  if(kbd_print_no_sysinb(cnt) != 0){
      return 1;
  }
  cnt=0;

  if(timer_unsubscribe_int() == 1){       //unsubscribe timer and check if it worked
      return 1;
  }

  if(kbd_unsubscribe_int() != 0){
      return 1;
  }

  return 0;
}
