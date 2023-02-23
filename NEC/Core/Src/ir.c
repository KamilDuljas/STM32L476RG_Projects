/*
 * ir.c
 *
 *  Created on: Feb 16, 2023
 *      Author: kduljas
 */
#include "tim.h"
#include "ir.h"
#include <stdio.h>
static volatile uint32_t received_value;
static int received_bits;
static int i = 0;
typedef enum {
	PULSE_9MS,
	PULSE_4MS,
	PULSE_2MS,
	PULSE_LONG,
	PULSE_SHORT,
	PULSE_ERROR,
}pulse_t;

static pulse_t calc_pulse(uint32_t time)
{
	if (time < 250)
		return PULSE_ERROR;
	else if (time < 1200)
		return PULSE_SHORT;
	else if (time < 2000)
		return PULSE_LONG;
	else if (time < 3000)
		return PULSE_2MS;
	else if (time < 6000)
		return PULSE_4MS;
	else if (time < 12000)
		return PULSE_9MS;
	else
		return PULSE_ERROR;
}

static const char *stringFromPulse(pulse_t pulse)
{
	static const char *strings[] = {
			"PULSE_9MS",
			"PULSE_4MS",
			"PULSE_2MS",
			"PULSE_LONG",
			"PULSE_SHORT",
			"PULSE_ERROR",};
	return strings[pulse];
}

void ir_tim_interrupt(void)
{
	pulse_t pulse;

	if (received_bits >= 32)
		return;
	uint32_t captured_value = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
	pulse = calc_pulse(captured_value);

	switch (pulse) {
	case PULSE_SHORT:
		received_value = received_value >> 1;
		received_bits++;
		break;
	case PULSE_LONG:
		received_value = (received_value >> 1) | 0x80000000;
		received_bits++;
		break;
	case PULSE_4MS:
		received_value = 0;
		received_bits = 0;
		break;
	case PULSE_2MS:
		if (received_bits == 0)
			received_bits = 32;
		break;
	default:
		received_bits = 0;
		break;
	}
	printf("%ld: %ld us (%s)\n",i++, captured_value, stringFromPulse(calc_pulse(captured_value)));
}

void ir_init(void)
{
	  HAL_TIM_Base_Start(&htim2);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
}

int ir_read(void)
{
	if (received_bits != 32)
		return -1;

	uint8_t value = received_value >> 16;
	received_bits = 0;
	return value;
}
