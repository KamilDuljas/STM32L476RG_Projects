/*
 * ir.h
 *
 *  Created on: Feb 16, 2023
 *      Author: kduljas
 */

#ifndef INC_IR_H_
#define INC_IR_H_
#pragma once

#include "stm32l476xx.h"

// Procedura obsługi przerwania
void ir_tim_interrupt(void);

// Inicjalizacja modułu
void ir_init(void);

// Funkcja odczytująca dane
// return - kod klawisza lub -1
int ir_read(void);

#endif /* INC_IR_H_ */
