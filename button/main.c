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

/*#include "stdio.h"
#include "timex.h"
#include "xtimer.h"
#include "thread.h"*/

#include "stdio.h"
#include "timex.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "thread.h"

#include "board.h"

#include "umdk-ids.h"

#include "thread.h"
#include "lptimer.h"


#define INTERVAL (1U * US_PER_SEC)

xtimer_ticks32_t last_wakeup;

#define UNWD_GPIO_4 GPIO_PIN(PORT_A, 4)
#define UNWD_GPIO_5 GPIO_PIN(PORT_A, 5)
#define UNWD_GPIO_6 GPIO_PIN(PORT_B, 8)
#define UNWD_GPIO_7 GPIO_PIN(PORT_B, 9)

static gpio_t buttons[4] = {UNWD_GPIO_4, UNWD_GPIO_5, UNWD_GPIO_6, UNWD_GPIO_7};

int step = 0;

static void btn_handler(void *arg)
{	
	int btn_num = (int) arg;	
	

	gpio_irq_disable(buttons[btn_num]);

	printf("kek %d\n", btn_num);
	
	if(xtimer_usec_from_ticks(xtimer_diff(xtimer_now(),last_wakeup))> 500000)
	{
		last_wakeup = xtimer_now();
		if(step == btn_num) step++;
		else step = 0;
		if(step == 3) 
		{
			printf("Ty Pidor");
				step = 0;
		}
	}	

	gpio_irq_enable(buttons[btn_num]); 
}

int main(void)
{
	last_wakeup = xtimer_now();

	for (int i = 0; i < 4; i++) {
	    gpio_init_int(buttons[i], GPIO_IN_PU, GPIO_FALLING, btn_handler, (void *) i);
	}

	return 0;
}

