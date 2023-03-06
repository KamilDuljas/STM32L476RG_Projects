/*
 * stm32l4xx_it.c
 *
 *  Created on: Mar 6, 2023
 *      Author: kduljas
 */

#include "main.h"

void SysTick_Handler(void)
{
	software_timer_inc_ms_tick();
}

