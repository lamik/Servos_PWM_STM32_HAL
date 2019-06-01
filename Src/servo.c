/*
 * servo.c
 *
 *		The MIT License.
 *  Created on: 01.08.2018
 *      Author: Mateusz Salamon
 *      www.msalamon.pl
 *		mateusz@msalamon.pl
 *
 *      Website: https://msalamon.pl/jak-pomachac-swoim-orczykiem-stm32-spotyka-sie-z-serwem/
 *      GitHub:  https://github.com/lamik/Servos_PWM_STM32_HAL
 */
#include "main.h"
#include "tim.h"

#include "servo.h"

//
//	Servo innitialization
//
void Servo_Init(servo_t *servo, TIM_HandleTypeDef *_htim, uint32_t _channel)
{
	servo->htim = _htim;
	servo->channel = _channel;

	HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

//
//	map help function
//
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//
//	Servo set angle function
//
void Servo_SetAngle(servo_t *servo, uint16_t angle)
{
	if(angle < 0) angle = 0;
	if(angle > 180) angle = 180;

	  uint16_t tmp = map(angle, ANGLE_MIN, ANGLE_MAX, SERVO_MIN, SERVO_MAX);
	  __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, tmp);
}

//
//	Servo set angle fine function
//
void Servo_SetAngleFine(servo_t *servo, float angle)
{
	if(angle < 0) angle = 0;
	if(angle > 180) angle = 180;

	  uint16_t tmp = map(angle, ANGLE_MIN, ANGLE_MAX, SERVO_MIN, SERVO_MAX);
	  __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, tmp);
}

