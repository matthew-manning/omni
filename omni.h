#include <stdint.h>

#ifndef __OMNI_H__
#define __OMNI_H__

#define MOTOR_BASE	307 //EQUIVLENT OF 1.5 MS
#define MOTOR_FULL	102 //EQUIVLENT OF 0.5 MS
#define MOTOR_1 	0X08//addr of off_l for pwm
#define MOTOR_2		0x0C
#define MOTOR_3		0x10

#define CLOCK_DIV	0x7A//gives 50 Hz needed for servos
#define MODE_1A		0x11//clock of to set prescaler
#define MODE_1B		0x01//clock on
#define MODE_2		0x04//invert waveform
#define BUS		0x01
#define ADDR		0x70


void writeI2C(uint8_t Bus, uint8_t Addr, uint8_t Reg, uint8_t Data);
void write12 (uint8_t Reg, uint16_t Val);
void initController(void);
void motorSpeed(uint8_t Motor, int8_t Speed);
void xySpeed(int8_t XSpeed, int8_t YSpeed);
void spin(int8_t Spin);

#endif
