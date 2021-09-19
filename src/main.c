/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "led.h"
#include "diag/trace.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------
//
// Semihosting STM32F4 empty sample (trace via STDOUT).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the STDOUT output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

void Init_PushButton(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef pushButton;
	pushButton.Pin = GPIO_PIN_0;
	pushButton.Mode = GPIO_MODE_INPUT;
	pushButton.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &pushButton);
}


int
main(int argc, char* argv[])
{
	Init_PushButton();
	blink_led_init();
	uint32_t seconds = 0;

	puts("Bonjour le monde ");
	while(1){
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {
			blink_led_on();
//			timer_sleep(seconds == 0 ? TIMER_FREQUENCY_HZ : BLINK_ON_TICKS);
		} else {
			blink_led_off();
//			 timer_sleep(BLINK_OFF_TICKS);

//			      ++seconds;
		}
	}
  return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
