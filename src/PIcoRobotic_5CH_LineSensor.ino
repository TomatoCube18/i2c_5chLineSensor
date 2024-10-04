/********************************Copyright Statement**************************************
**
** TomatoCube & Minoyo
**
**----------------------------------File Information--------------------------------------
** File Name: PicoRobotics_5CH_LineSensor.ino
** Creation Date: 2nd June 2023
** Function Description: PicoRobotic - i2C 5-Ch Line Sensor via the ATtiny1614 @ 8Mhz
** Operation Process:
** Hardware Platform: TomatoCube PicoRobotic MainBoard or any i2C capable devices 5/3.3V
** Copyright Statement: This code is an IP of TomatoCube and can only for non-profit or
**                      educational exchange.
**---------------------------Related Information of Modified Files------------------------
** Modifier: Percy Chen
** Modification Date: 4th October 2024       
** Modification Content:
**
** Extra Note:
**
**    Sensors 
**    --  PA1 (8)(ATTINY1614) 
**    --  PA2 (9)(ATTINY1614) 
**    --  PA3 (10)(ATTINY1614) 
**    --  PA4 (0)(ATTINY1614) 
**    --  PA5 (1)(ATTINY1614) 
**    
**    Pot
**    --  PA6 (2)(ATTINY1614)
**    
**    LED ShiftRegister 74595
**    --  PA7 (3)(ATTINY1614) - SER_DataIn(14)
**    --  PB2 (5)(ATTINY1614) - SCK_CLK(11)
**    --  PB3 (4)(ATTINY1614) - RCK_Latch(12)  
**    
**    I2C 
**    --  IO18 (SCL) <-> PB0 (ATTINY1614  
**    --  IO19 (SDA) <-> PB1 (ATTINY1614)
**    
**    
**     I2C commands table 
**     --  All i2c write commands have 2 bytes parameter (little endian)   
**     Write:
**     |   commands         | param1   | param2   |  description                          |  
**     |--------------------|----------|----------|---------------------------------------|  
**     | 0x02 | Enable      | 0/1      | dummy    | PA7 (3) LED. Disabled by Default      |
**     
**
******************************************************************************************/


#include <Wire.h>

// I2C address
#define I2CADDR 0x17

#define IN_A    8
#define IN_B    9
#define IN_C    10
#define IN_D    0
#define IN_E    1

#define IN_POT  2

#define SR_DAT  3
#define SR_CLK  5
#define SR_LATCH  4


volatile uint8_t rcv_buf[256];
volatile int rcv_len = 0;
uint8_t ir_state_temp = 0;
uint8_t ir_state = 0;

unsigned int potValue = 0;

void setup() {
    pinMode(IN_A, INPUT);
    pinMode(IN_B, INPUT);
    pinMode(IN_C, INPUT);
    pinMode(IN_D, INPUT);
    pinMode(IN_E, INPUT);

    pinMode(IN_POT, INPUT);
    
    pinMode(SR_LATCH, OUTPUT);
    pinMode(SR_CLK, OUTPUT);
    pinMode(SR_DAT, OUTPUT);
    
    Wire.begin(I2CADDR);            // join i2c bus
    Wire.onReceive(receiveEvent);   // I2C write
    Wire.onRequest(requestEvent);   // I2C read
}

void requestEvent() { // I2C read
    Wire.write(ir_state);
}

void receiveEvent(int howMany) {
    int i = 0;
    int p;
    int busy = rcv_len;
    
    while (0 < Wire.available()) { // loop through all but the last
    if (busy == 0) {
            rcv_buf[i++] = Wire.read(); // receive byte as a character
        } else {
            int a = Wire.read(); // dummy read
        }
    }
    if (i == 3) {
        rcv_len = i;
    }
}


void loop() {
    if( rcv_len > 0 ) {
    unsigned int param = ((rcv_buf[2]&0xff)<<8)+(rcv_buf[1]&0xff);  
    // little endian 2bytes param
    
    switch(rcv_buf[0]) {
        case 2: // enable
            if(param & 0x1) {
//                digitalWrite(LED, HIGH);
//                led_state = HIGH;
            }
            else {
//                digitalWrite(LED, LOW);
//                led_state = LOW;
            }
            break;
        }
        rcv_len = 0;
    }

    potValue = analogRead(IN_POT);
    ir_state_temp = 0;
    bitWrite(ir_state_temp, 0, potValue < analogRead(IN_A));
    bitWrite(ir_state_temp, 1, potValue < analogRead(IN_B));
    bitWrite(ir_state_temp, 2, potValue < analogRead(IN_C));
    bitWrite(ir_state_temp, 3, potValue < analogRead(IN_D));
    bitWrite(ir_state_temp, 4, potValue < analogRead(IN_E));
    ir_state = ~ir_state_temp;
    
    digitalWrite(SR_LATCH, LOW);
    shiftOut(SR_DAT, SR_CLK, MSBFIRST, ir_state_temp);
    digitalWrite(SR_LATCH, HIGH);
}
                    
                
