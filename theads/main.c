/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include "stdio.h"
#include "timex.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "thread.h"

#define INTERVAL (1U * US_PER_SEC)

xtimer_ticks32_t last_wakeup;

void *thread_handler500(void *arg)
{
	(void) arg;
	while(1)
	{
		xtimer_periodic_wakeup(&last_wakeup, INTERVAL/2);
		gpio_toggle(GPIO_PIN(PORT_C, 9));
	}
	return NULL;
}

void *thread_handler200(void *arg)
{
	(void) arg;
	while(1)
	{
		xtimer_periodic_wakeup(&last_wakeup, INTERVAL);
		gpio_toggle(GPIO_PIN(PORT_C, 8));
	}
	return NULL;
}




char stack[THREAD_STACKSIZE_MAIN];
char stack2[THREAD_STACKSIZE_MAIN];

int main(void)
{
	gpio_init(GPIO_PIN(PORT_C, 9), GPIO_OUT);
	gpio_init(GPIO_PIN(PORT_C, 8), GPIO_OUT);


	last_wakeup = xtimer_now();
	thread_create(stack, sizeof(stack),	THREAD_PRIORITY_MAIN - 1,THREAD_CREATE_STACKTEST,
	thread_handler500,	NULL, "thread");

	thread_create(stack2, sizeof(stack2),	THREAD_PRIORITY_MAIN - 1,THREAD_CREATE_STACKTEST,
	thread_handler200,	NULL, "KEK");
		
	while(1) 
	{
		
	}

    return 0;
}

