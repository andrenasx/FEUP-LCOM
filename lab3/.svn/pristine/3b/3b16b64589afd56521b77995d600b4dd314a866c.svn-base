#include <lcom/lcf.h>

#include <stdint.h>

#include "i8254.h"
#include "i8042.h"

int kbd_id = KBD_IRQ; //HOOK_ID=1
uint8_t code = 0x00;


int (kbd_subscribe_int)(uint8_t *bit_no) {
  *bit_no = BIT(kbd_id); //bits_no = 1

  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_id)==1){
    printf("Error in sys_irqsetpolicy\n");
    return 1;
  }

  return 0;
}

int (kbd_unsubscribe_int)() { 
  
  if(sys_irqrmpolicy(&kbd_id)==1){
    printf("Error in sys_irqrmpolicy\n");
    return 1;
  }

  return 0;
}

void (kbc_ih)(void) {
  uint8_t ctrl;
  code=0x00;

  if(util_sys_inb(STAT_REG, &ctrl) != 0){
    return;
  }

  if((ctrl & STAT_REG_OBF) != 0 || (ctrl & (STAT_REG_PARITY | STAT_REG_TIMEOUT)) != 0){ //Check if Output Buffer is full or if Parity of Timeout Error
    if(util_sys_inb(OUT_BUF, &code) != 0){ //Check if Error getting ScanCode from Output Buffer
      code = 0x00;
      return;
    }
  }
}


int (kbd_enable)() {
  uint8_t cmd;

  if (sys_outb(KBC_CMD_REG, KBC_READ_CMD) != 0){
    return 1;
  }

  if (util_sys_inb(OUT_BUF, &cmd) != 0){ //Check for Error getting command byte
    return 1;
  }

  cmd |= BIT(0);  //Enables Interrupt on OBF, from keyboard (sets bit to 1)

  if (sys_outb(KBC_CMD_REG, KBC_WRITE_CMD) != 0){
    return 1;
  }

  if (sys_outb(KBC_WRITE_CMD, cmd) != 0){ //Checks for Error writing command byte
    return 1;
  }

  return 0;
}
