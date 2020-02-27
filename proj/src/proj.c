// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you

#include "i8042.h"
#include "i8254.h"
#include "game.h"

extern uint8_t kbd_code;
extern unsigned int timer_counter;
extern int mouse_id;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
} 


int(proj_main_loop)(int argc, char *argv[]) {
  uint8_t kbd_irq_set=KBD_IRQ;
  uint8_t timer_irq_set=TIMER0_IRQ;
  uint32_t mouse_irq_set=MOUSE_IRQ;
  int r, ipc_status;
  message msg;
  uint8_t byteCnt = 0;
  struct packet pp;
  uint8_t byte[3];

  //1152x864
  if(vg_init(0x14C) == NULL){
    return 1;
  }

  if(mouse_subscribe_int(&mouse_irq_set)!=0){
    return 1;
  }

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_EN)!=0){ //enable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_STREAM_MODE)!=0){ //enable stream mode
    return 1;
  }
  sys_irqenable(&mouse_id);

  if(kbd_subscribe_int(&kbd_irq_set)!=0){
      return 1;
  }

  if (timer_subscribe_int(&timer_irq_set)!=0){
    return 1;
  }

  loadGameXPMs();
  startGame();
  Game* game = getGame();

  while(game->state!=END){
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
                  switch(game->state){
                    case GAME:
                      updateUFO();
                      break;
                    case MENU:
                      if(kbd_code==ESC_BREAKCODE)
                        game->state=END;
                      break;
                    default:
                      break;
                  }
                }
                if (msg.m_notify.interrupts & mouse_irq_set) {
                  mouse_ih();
                  build_packet(byte, &byteCnt);
                  if(byteCnt==3){
                    if(mouse_parse_packet(byte, &pp)==0){
                      byteCnt=0;
                      updateMouse(pp, game);
                    }
                  }
                }
                if (msg.m_notify.interrupts & timer_irq_set) { /* subscribed interrupt */
                  switch(game->state){
                    case MENU:
                      drawMainMenu();
                      moveMouse(game);
                      mouseMainMenuChange(game);
                      swapBuffer();
                      break;
                    case HELP:
                      drawHelp();
                      moveMouse(game);;
                      mouseMenuChange(game);
                      swapBuffer();
                      break;
                    case GAME:
                      timer_int_handler();
                      shoot_time_handler(game);
                      drawBackground();
                      if(game->score<700){
                        if(timer_counter % 100 == 0){
                          createRandomAsteroid();
                          game->score+=10;
                        }
                      }
                      else if(game->score<1800){
                        if(timer_counter % 80 == 0){
                          createRandomAsteroid();
                          game->score+=10;
                        }
                      }
                      else{
                        if(timer_counter % 60 == 0){
                          createRandomAsteroid();
                          game->score+=10;
                        }
                      }
                      moveAsteroid(game);
                      moveUFO(game);
                      moveMouse(game);
                      drawScore();
                      checkBulletAsteroidColision(game);
                      resetShot(game);
                      swapBuffer();
                      checkAsteroidUFOColision(game);
                      break;
                    case GAMEOVER:
                      drawGameOver();
                      drawGameOverScore();
                      moveMouse(game);
                      mouseMenuChange(game);
                      swapBuffer();
                      break;
                    case END:
                      destroyGame();
                      break;
                    default:
                      break;
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
  
  if(vg_exit() !=0){
    return 1;
  }

  sys_irqdisable(&mouse_id);
  if(write_mouse_command(MOUSE_DIS)!=0){  //disable data reporting
    return 1;
  }
  sys_irqenable(&mouse_id);

  if(mouse_unsubscribe_int() != 0){
    return 1;
  }
  
  if(kbd_unsubscribe_int() != 0){
    return 1;
  }

  if(timer_unsubscribe_int()!=0){
    return 1;
  }


  return 0;
}
