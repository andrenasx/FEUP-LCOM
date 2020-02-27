#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define DELAY_US 20000
#define KBD_IRQ 1
#define MOUSE_IRQ 12 

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

//PS/2 MOUSE
#define LB                      BIT(0)
#define RB                      BIT(1)
#define MB                      BIT(2)
#define X_SIGN                  BIT(4)
#define Y_SIGN                  BIT(5)
#define X_OV                    BIT(6)
#define Y_OV                    BIT(7)

//Mouse-related KBC Commands
#define KBC_READ_CMD  0X20  //Read Command Byte
#define KBC_WRITE_CMD 0X60  //Write Command Byte
#define KBC_CHECK_KBC 0XAA  //Check KBC - returns 0x55 if OK; returns 0xFC if Error
#define KBC_CHECK_KBD 0XAB  //Check Keyboard Interface - returns 0 if OK
#define KBC_DIS_KBD 0XAD  //Disable Keyboard Interface
#define KBC_EN_KBD  0XAE  //Enbale Keyboard Interface
#define KBC_DIS_MOUSE 0XA7	//Disable Mouse
#define KBC_EN_MOUSE 0XA8	//Enable Mouse
#define KBC_CHECK_MOUSE 0XA9
#define KBC_WRITE_BYTE_MOUSE  0XD4

//Mouse Commands
#define MOUSE_RESET         0xFF    // Mouse Reset
#define MOUSE_RESEND        0xFE    // For serial communication errors
#define MOUSE_DEFAULTS      0xF6    // Set default values
#define MOUSE_DIS           0xF5    // Disable Data Reporting - In stream mode, should be sent before any other command
#define MOUSE_EN            0xF4    // Enable Data Reporting - In stream mode only
#define MOUSE_SAMPLE_RATE   0xF3    // Sets state sampling rate
#define MOUSE_REMOTE_MODE   0xF0    // Set Remote Mode - Send data on request only
#define MOUSE_READ_DATA     0xEB    // Send data packet request
#define MOUSE_STREAM_MODE   0xEA    // Set Stream Mode - Send data on events
#define MOUSE_STATUS_REQ    0xE9    // Get mouse configuration (3 bytes)
#define MOUSE_RESOLUTION    0xE8    // Sets Resolution
#define MOUSE_SCAL2_1       0xE7    // Accelaration Mode
#define MOUSE_SCAL1_1       0Xe6    // Linear mode


#define ESC_BREAKCODE	0x81
#define TWO_BYTE_SCANCODE	0xE0
#define ACK     0xFA
#define NACK    0xFE
#define ERROR   0xFC

//KBC Command Byte
#define DIS2  BIT(5)
#define DIS BIT(4)
#define INT2  BIT(1)
#define INT BIT(0)


//KBC Ports
#define STAT_REG  0X64
#define OUT_BUF 0X60
#define IN_BUF  0X60
#define KBC_CMD_REG 0x64  //Commands to the KBC
#define KBC_CMD_ARG  0x60 //Arguments of KBC Commands


#endif /* _LCOM_I8042_H */
