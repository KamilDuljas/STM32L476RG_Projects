/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"

int main(void)
{

	// Initialize clock
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_RCC_MSI_EnableRangeSelection();
	LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_8);
	LL_SetSystemCoreClock(16000000);
	LL_Init1msTick(16000000);


	// Initialize Led
	LL_GPIO_SetPinOutputType(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_MODE_OUTPUT);

	while (1)
	{
	     LL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	     LL_mDelay(1000);
	}
}
