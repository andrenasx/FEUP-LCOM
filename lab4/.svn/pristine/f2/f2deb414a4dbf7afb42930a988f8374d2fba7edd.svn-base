// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "i8042.h"
#include "i8254.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


extern uint8_t code; // byte read
extern int mouse_id; //MOUSE_IRQ
extern unsigned int counter; //timer 0 counter
extern bool done; //if done drawing


int (mouse_test_packet)(uint32_t cnt) {

  uint32_t irq_set;
  int r, ipc_status;
  message msg;
  uint32_t print_counter = 0;
  struct packet packet;
  uint8_t byteCnt = 0;
  uint8_t byte[3];

  if(mouse_subscribe_int(&irq_set)!=0){
    return 1;
  }

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_EN)!=0){ //enable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);


  while(cnt>print_counter) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  mouse_ih();
                  build_packet(byte, &byteCnt);
                  if(byteCnt==3){
                    if(mouse_parse_packet(byte, &packet)==0){
                      mouse_print_packet(&packet);
                      print_counter++;
                      byteCnt=0;
                    }
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

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_DIS)!=0){  //disable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);

  if (mouse_unsubscribe_int()!=0){
      return 1;
  }

  return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {

  uint32_t print_counter = 0;
  struct packet packet;
  uint8_t byteCnt = 0;
  uint8_t byte[3];

  while(cnt>print_counter){

    if(write_mouse_command(MOUSE_READ_DATA)!=0){
      return 1;
    }

    while(byteCnt<3){
      mouse_ih();
      build_packet(byte, &byteCnt);
    }

    if(mouse_parse_packet(byte, &packet)==0){
      mouse_print_packet(&packet);
      print_counter++;
      byteCnt=0;
    }

    tickdelay(micros_to_ticks(period*1000));
  }

  if(write_mouse_command(MOUSE_STREAM_MODE)!=0){ //enable stream mode
    return 1;
  }
  if(write_mouse_command(MOUSE_DIS)!=0){ //disable data reporting
    return 1;
  }
  
  //reset Minix default state
  if(write_command(KBC_CMD_REG, KBC_WRITE_CMD)!=0){
    return 1;
  }
  if(write_command(IN_BUF, minix_get_dflt_kbc_cmd_byte()) != 0){
    return 1;
  }

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  uint32_t mouse_irq_set;
  uint8_t timer_irq_set;
  int r, ipc_status;
  message msg;
  struct packet packet;
  uint8_t byteCnt = 0;
  uint8_t byte[3];

  if(mouse_subscribe_int(&mouse_irq_set)!=0){
    return 1;
  }
  if(timer_subscribe_int(&timer_irq_set)!=0){
    return 1;
  }

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_EN)!=0){
    return 1;
  }
  sys_irqenable(&mouse_id);

  while((idle_time*sys_hz())>counter) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & mouse_irq_set) { /* subscribed interrupt */
                  counter=0;
                  mouse_ih();
                  build_packet(byte, &byteCnt);
                  if(byteCnt==3){
                    if(mouse_parse_packet(byte, &packet)==0){
                      mouse_print_packet(&packet);
                      byteCnt=0;
                    }
                  }
                }
                if (msg.m_notify.interrupts & timer_irq_set) {
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

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_DIS)!=0){
    return 1;
  }
  sys_irqenable(&mouse_id);

  if (mouse_unsubscribe_int()!=0){
    return 1;
  }
  if(timer_unsubscribe_int()!=0){
    return 1;
  }

  return 0;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {

  uint32_t irq_set;
  int r, ipc_status;
  message msg;
  struct packet packet;
  uint8_t byteCnt = 0;
  uint8_t byte[3];

  if(mouse_subscribe_int(&irq_set)!=0){
    return 1;
  }

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_EN)!=0){ //enable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);


  while(!done) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  mouse_ih();
                  build_packet(byte, &byteCnt);
                  if(byteCnt==3){
                    if(mouse_parse_packet(byte, &packet)==0){
                      statemachine(x_len, tolerance, &packet);
                      mouse_print_packet(&packet);
                      byteCnt=0;
                    }
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

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_DIS)!=0){  //disable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);

  if (mouse_unsubscribe_int()!=0){
      return 1;
  }

  return 0;
}
