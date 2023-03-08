/*
 * main.h
 *
 *  Created on: Mar 2, 2023
 *      Author: kduljas
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"

#include "software_timer.h"

#define LED_GREEN_Pin LL_GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA

#define USER_BUTTON_Pin LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC

#endif /* MAIN_H_ */
