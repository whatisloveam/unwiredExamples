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

xtimer_ticks32_t last_wakeup,last_wakeup2;

#define UNWD_GPIO_4 GPIO_PIN(PORT_A, 4)
#define UNWD_GPIO_5 GPIO_PIN(PORT_A, 5)
#define UNWD_GPIO_6 GPIO_PIN(PORT_B, 8)
#define UNWD_GPIO_7 GPIO_PIN(PORT_B, 9)

static gpio_t buttons[4] = {UNWD_GPIO_4, UNWD_GPIO_5, UNWD_GPIO_6, UNWD_GPIO_7};

int step = 0;
int digit = 0;
int password[] = {1, 4, 8, 8};
int mypass[] = {0, 0, 0, 0};

volatile int state = 0;
int shift = 0;

static void btn_handler(void *arg)
{	
	int btn_num = (int) arg;	
	

	gpio_irq_disable(buttons[btn_num]);
	
	if(xtimer_usec_from_ticks(xtimer_diff(xtimer_now(),last_wakeup))> 500000)
	{
		last_wakeup = xtimer_now();
		if(btn_num == 0)
		{
			digit--;
			if(digit < 0) digit = 0;
			mypass[shift] = digit;
			printf("%d\n", mypass[0]*1000+mypass[1]*100+mypass[2]*10+mypass[3]);
		}
		if(btn_num == 1)
		{
			digit = (digit + 1) % 10;
			mypass[shift] = digit;
			printf("%d\n", mypass[0]*1000+mypass[1]*100+mypass[2]*10+mypass[3]);
		}
		if(btn_num == 2)
		{
			shift = (shift+1) % 4;
		}
		if(btn_num == 3)
		{
			state = 1;
			for(int i = 0; i< 4; i++)
				if(password[i] != mypass[i])
				{
					state = 2;
					break;
				}
		}

	}	

	gpio_irq_enable(buttons[btn_num]); 
}

int main(void)
{
	last_wakeup = xtimer_now();
	last_wakeup2 = xtimer_now();
	gpio_init(GPIO_PIN(PORT_B, 3), GPIO_OUT);
	gpio_init(GPIO_PIN(PORT_A, 15), GPIO_OUT);
	printf("%d\n", mypass[0]*1000+mypass[1]*100+mypass[2]*10+mypass[3]);

	for (int i = 0; i < 4; i++) {
	    gpio_init_int(buttons[i], GPIO_IN_PU, GPIO_FALLING, btn_handler, (void *) i);
	}

	while(1)
	{
		
		if(state == 0)
		{
			if(xtimer_usec_from_ticks(xtimer_diff(xtimer_now(),last_wakeup2))> 4000000)
			{
				last_wakeup2 = xtimer_now();
				gpio_clear(GPIO_PIN(PORT_A, 15));
				//gpio_clear(GPIO_PIN(PORT_B, 3));
			state = 0;
			}
		}
		else if(state == 1)
		{
			printf("access granted! \n");
			gpio_set(GPIO_PIN(PORT_B, 3));
			state = 0;
		}
		else if(state == 2)
		{
			printf("access denied \n");
			gpio_set(GPIO_PIN(PORT_A, 15));
			last_wakeup2 = xtimer_now();
			state = 0;
		}
	}
	return 0;
}

