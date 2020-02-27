#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"
#include "mouse.h"

int mouse_id=MOUSE_IRQ;
uint8_t mouse_code = 0x00;

int (mouse_subscribe_int)(uint32_t *bit_no){
  *bit_no = BIT(mouse_id);

    if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_id)==1){
      printf("Error in sys_irqsetpolicy\n");
      return 1;
    }

  return 0;
}

int (mouse_unsubscribe_int)() { 
  
  if(sys_irqrmpolicy(&mouse_id)==1){
    printf("Error in sys_irqrmpolicy\n");
    return 1;
  }

  return 0;
}

void (mouse_ih)(void) {
  uint8_t ctrl;
  mouse_code=0x00;

  if(util_sys_inb(STAT_REG, &ctrl) != 0){
    return;
  }
  
  if((ctrl & STAT_REG_OBF) != 0 || (ctrl & (STAT_REG_PARITY | STAT_REG_TIMEOUT)) != 0){ //Check if Output Buffer is full or if Parity of Timeout Error
    if(util_sys_inb(OUT_BUF, &mouse_code) != 0){ //Check if Error getting ScanCode from Output Buffer
      mouse_code = 0x00;
      return;
    }
  }
}

void build_packet(uint8_t *byte, uint8_t *pos){
  byte[*pos]=mouse_code;
  (*pos)++;
}

int (mouse_parse_packet)(uint8_t *byte, struct packet *packet){
  packet->bytes[0]=byte[0];
  packet->bytes[1]=byte[1];
  packet->bytes[2]=byte[2];

  packet->lb=(byte[0] & LB);  //1 if left button was pressed
  packet->rb=(byte[0] & RB);  //1 if right button was pressed
  packet->mb=(byte[0] & MB);  //1 if middle button was pressed
  packet->x_ov=(byte[0] & X_OV);  //1 if mouse x-displacement overflow
  packet->y_ov=(byte[0] & Y_OV);  //1 if mouse y-displacement overflow

  packet->delta_x = (int16_t) byte[1]; //mouse x-displacement: rightwards is positive
  packet->delta_y = (int16_t) byte[2]; //mouse y-displacement: upwards is positive

  //adds 1 to the left of the number (if it's negative) to complete the 16 bits
  if(byte[0] & X_SIGN) packet->delta_x |= (0xFF00);
  if(byte[0] & Y_SIGN) packet->delta_y |= (0xFF00);

  return 0;
}

int (write_command)(uint8_t port, uint8_t cmd){
  uint8_t stat, clear;
  
  while(true){
    if(util_sys_inb(STAT_REG, &stat)!=0){
      return 1;
    }
    if(stat & STAT_REG_OBF){
      util_sys_inb(OUT_BUF, &clear);
    }
    if((stat & STAT_REG_IBF) == 0){
      if(sys_outb(port, cmd)!=0){
        return 1;
      }
      //printf("6");
      return 0;
    }
    tickdelay(DELAY_US);
  }

  return 1;
}

int (write_mouse_command)(uint8_t cmd){
  uint8_t response;

  do{
    if(write_command(KBC_CMD_REG, KBC_WRITE_BYTE_MOUSE)!=0){
    return 1;
    }
    if(write_command(IN_BUF, cmd)!=0){
      return 1;
    }
    if(util_sys_inb(OUT_BUF, &response)!=0){
      return 1;
    }
  }while(response!=ACK);

  return 0;
}

bool done=false; //if done drawing

void statemachine(uint8_t x_len, uint8_t tolerance, struct packet *packet){
  struct mouse_ev *evt = mouse_detect_event(packet); //Build event
  static int state = 0; //Current state
  static int16_t x,y; //Movement

  switch(state){
    //Initial state
    case 0:
      x=0;
      y=0;
      if(evt->type==LB_PRESSED){
        state=1; //begin drawing up
      }
    break;

    //Draw Up
    case 1:
      if(evt->type==LB_RELEASED){
        if(x<x_len){ //if lb released and not minimum x lenght go back to initial state
          state=0;
        }
        if(abs(y/x)<1){
          state=0; //if lb released and slope<1 go back to inital state
        }

        state=2; //else everything OK go to vertex
      }
      else if(evt->type==MOUSE_MOV){
        //if movement in the wrong direction greater than torelance
        if(evt->delta_x<0 && abs(evt->delta_x)>tolerance){
          state=0; //back to initial state if torelance exceeded
        }
        else if(evt->delta_y<0 && abs(evt->delta_y)>tolerance){
          state=0; //back to initial state if torelance exceeded
        }

        //increment movement
        x+=evt->delta_x;
        y+=evt->delta_y;
      }
      break;
    
    //Vertex
    case 2:
      if(evt->type==RB_PRESSED){
        x=0; //reset movement 
        y=0;
        state=3; //begin drawing down
      }
      else if(evt->type==MOUSE_MOV){
        if((abs(evt->delta_x)>tolerance) || (abs(evt->delta_y)>tolerance)){
          state=0; //back to initial state if movement and torelance exceeded
        }
      }
      break;

    //Draw Down
    case 3:
      if(evt->type==RB_RELEASED){
        if(x<x_len){ //if lb released and not minimum x lenght go back to initial state
          state=0;
        }
        if(abs(y/x)<1){
          state=0; //if lb released and slope<1 go back to inital state
        }

        done=true; //else everything OK drawing is done
        break;
      }
      else if(evt->type==MOUSE_MOV){
        //if movement in the wrong direction greater than torelance
        if(evt->delta_x<0 && abs(evt->delta_x)>tolerance){
          state=0; //back to initial state if torelance exceeded
        }
        else if(evt->delta_y>0 && abs(evt->delta_y)>tolerance){
          state=0; //back to initial state if torelance exceeded
        }

        //increment movement
        x+=evt->delta_x;
        y+=evt->delta_y;
      }
      break;
    default:
      break;
  }
}
