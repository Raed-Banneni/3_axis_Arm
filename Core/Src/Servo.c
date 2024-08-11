/*
 * Servo.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Mega-PC
 */
#include "main.h"
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern 	volatile PREV_POS pp;
int time=40;

int Map(int value)
{
	int y=((value/180)*200) + 50;
    return y;
}

void Servo_Write(int angle, SERVO x)
{
	int mapped= Map(angle);
	switch (x){
	case BASE : //PA0
		htim2.Instance->CCR1 = mapped;
		break;
	case SHOULDER_L : //PA1
		htim2.Instance->CCR2 = mapped;
		break;
	case SHOULDER_R : //PB10
		htim2.Instance->CCR3 = mapped;
		break;
	case PINCER_L : //PA6
		htim3.Instance->CCR1 = mapped;
		break;
	case PINCER_R ://PA7
		htim3.Instance->CCR2 = mapped;
		break;
	}
}

void Hand_Init(void)
{
	Start_PWM(BASE);
	Servo_Write(90,BASE);
	HAL_Delay(time);
//	Stop_PWM(BASE);
//	Stop_PWM(SHOULDER_L);
//	Stop_PWM(SHOULDER_R);
	Start_PWM(PINCER_L);
	Servo_Write(0,PINCER_L);
	HAL_Delay(time);
//	Stop_PWM(PINCER_L);
	Start_PWM(PINCER_R);
	Servo_Write(120,PINCER_R);
	HAL_Delay(time);
//	Stop_PWM(PINCER_R);

}
void Mvt_Test(void)
{

	Start_All();
	int i;
	for(i=90;i<=120;i++)
	{
		Servo_Write(i,BASE);
		HAL_Delay(time);
	}
	for(i=120;i>=60;i--)
	{
		Servo_Write(i,BASE);
		HAL_Delay(time);
	}
	for(i=60;i<=90;i++)
	{
		Servo_Write(i,BASE);
		HAL_Delay(time);
	}
	for(i=91;i<=120;i++)
	{
		Servo_Write(i,SHOULDER_R);
		Servo_Write((182-i),SHOULDER_L);
		HAL_Delay(10);
	}
	for(i=120;i>=91;i--)
	{
		Servo_Write(i,SHOULDER_R);
		Servo_Write((182-i),SHOULDER_L);
		HAL_Delay(10);
	}
	Stop_All();
}
void Mv_Left(void)
{
	pp.Base_p--;
//	Start_PWM(BASE);
	Servo_Write(pp.Base_p, BASE);
	HAL_Delay(time);
//	Stop_PWM(BASE);
}

void Mv_Right(void)
{
	pp.Base_p++;
	Start_PWM(BASE);
	Servo_Write(pp.Base_p, BASE);
	Stop_PWM(BASE);
}

void Start_PWM(SERVO x)
{
	switch (x){
	case BASE :
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		break;
	case SHOULDER_L :
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		break;
	case SHOULDER_R :
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		break;
	case PINCER_L :
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		break;
	case PINCER_R :
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
		break;
	}
}

void Stop_All(void){
	Stop_PWM(BASE);
	Stop_PWM(SHOULDER_L);
	Stop_PWM(SHOULDER_R);
	Stop_PWM(PINCER_L);
	Stop_PWM(PINCER_R);
}

void Start_All(void){
	Start_PWM(BASE);
	Start_PWM(SHOULDER_L);
	Start_PWM(SHOULDER_R);
	Start_PWM(PINCER_L);
	Start_PWM(PINCER_R);
}

void Stop_PWM(SERVO x)
{
	switch (x){
	case BASE :
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
		break;
	case SHOULDER_L :
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
		break;
	case SHOULDER_R :
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
		break;
	case PINCER_L :
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
		break;
	case PINCER_R :
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
		break;
	}
}
