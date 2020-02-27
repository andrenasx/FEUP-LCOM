#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_


#define DELAY_US 20000
#define KBD_IRQ 1

//Status Register
#define STAT_REG_OBF  BIT(0)  // Output Buffer Full - data available for reading
#define STAT_REG_IBF  BIT(1)  // Input Buffer Full - don't write commands or aguments
#define STAT_REG_SYS BIT(2)  //System Flag - 0 after a power on reset.
#define STAT_REG_A2  BIT(3)  // Writting input buffer to 0x64 sets this to 1 (Command port);
                            // Writting to 0x60 sets this to 0 (Data port);
#define STAT_REG_INH  BIT(4)  //Inhibit flag: 0 if keyboard is inhibited
#define STAT_REG_AUX BIT(5)  //Mouse data
#define STAT_REG_TIMEOUT  BIT(6)  //Timeout error - invalid data
#define STAT_REG_PARITY BIT(7)  //Parity Error - invalid data

//KBC Commands
#define KBC_READ_CMD  0X20  //Read Command Byte
#define KBC_WRITE_CMD 0X60  //Write Command Byte 
#define KBC_CHECK_KBC 0XAA  //Check KBC - returns 0x55 if OK; returns 0xFC if Error
#define KBC_CHECK_KBD 0XAB  //Check Keyboard Interface - returns 0 if OK
#define KBC_DIS_KBD 0XAD  //Disable Keyboard Interface
#define KBC_EN_KBD  0XAE  //Enbale Keyboard Interface

#define STAT_REG  0X64
#define OUT_BUF 0X60
#define IN_BUF  0X60
#define KBC_CMD_REG 0x64  //Commands to the KBC
#define KBC_CMD_ARG  0x60 //Arguments of KBC Commands
#define ESC_BREAKCODE 0x81
#define TWO_BYTE_SCANCODE 0xE0


#endif /* _LCOM_I8042_H */
