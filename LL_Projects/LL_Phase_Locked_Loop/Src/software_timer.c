/*
 * software_timer.c
 *
 *  Created on: Mar 6, 2023
 *      Author: kduljas
 */

#include "software_timer.h"


static uint32_t ms_tick = 0;

	void software_timer_task_init(software_timer_t *timer, uint32_t time)
	{
		timer->ms_tick = software_timer_get_ms_tick();
		timer->task_time = time;
	}

	uint32_t software_timer_get_ms_tick(void)
	{
		return ms_tick;
	}

	void software_timer_inc_ms_tick(void)
	{
		ms_tick++;
	}
