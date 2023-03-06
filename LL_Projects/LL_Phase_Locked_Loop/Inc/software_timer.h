/*
 * software_timer.h
 *
 *  Created on: Mar 6, 2023
 *      Author: kduljas
 */

#ifndef SOFTWARE_TIMER_H_
#define SOFTWARE_TIMER_H_

#include "main.h"

typedef struct
{
		uint32_t ms_tick;
		uint32_t task_time;
}software_timer_t;

void software_timer_task_init(software_timer_t *timer, uint32_t time);
void software_timer_inc_ms_tick(void);
uint32_t software_timer_get_ms_tick(void);

#endif /* SOFTWARE_TIMER_H_ */
