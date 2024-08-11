/*
 * Servo.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Mega-PC
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

typedef enum{
	BASE = 0x00U,
	SHOULDER_L = 0x01U,
	SHOULDER_R = 0x02U,
	PINCER_L = 0x03U,
	PINCER_R = 0x04U
}SERVO;

typedef struct{
	int Base_p;
	int Shoulder_p;
	int Pincer_p;
}PREV_POS;

int Map(int value);
void Servo_Write(int angle, SERVO x);
void Hand_Init(void);
void Mvt_Test(void);
void Mv_Left(void);
void Mv_Right(void);
int Mv_Up(int y);
int Mv_Down(int y);
void Start_PWM(SERVO x);
void Stop_All(void);
void Start_All(void);
void Stop_PWM(SERVO x);


#endif /* INC_SERVO_H_ */
