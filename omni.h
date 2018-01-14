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

#define MIN_SPEED	5//any speed not greater than this is treated as zero to protect motors 
#define PI		3.142
#define WHEEL_DIAMETER	48// in mm
#define SEC_REV		1.2//seconds per wheel revoultion
#define SPEED_FACTOR	1.73//factor by which the actual speed is faster than any motor


#define STOP_ALL	stopMotor(MOTOR_1);stopMotor(MOTOR_2);stopMotor(MOTOR_3);//stops pulse train for all motors, better than 0 speed

void writeI2C(uint8_t Bus, uint8_t Addr, uint8_t Reg, uint8_t Data);
void write12 (uint8_t Reg, uint16_t Val);
void initController(void);
void motorSpeed(uint8_t Motor, int8_t Speed);
void xySpeed(int16_t XPart, int16_t YPart, uint8_t velocity);
void spin(int8_t Spin);
void vectorMove(int16_t Heading, uint8_t Velocity);
void stopMotor(uint8_t);
void xyTravel(int32_t XDist, int32_t YDist,  uint8_t Speed);

#endif
