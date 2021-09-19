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

uint8_t queue_a, queue_b, queue_c, queue_d;
uint8_t priority[2] = {0};
static uint8_t lastButton_A_Status = GPIO_PIN_RESET;

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
	blink_led_init(BLINK_PIN_NUMBER_12);
	blink_led_init(BLINK_PIN_NUMBER_13);
	blink_led_init(BLINK_PIN_NUMBER_14);
	blink_led_init(BLINK_PIN_NUMBER_15);

	queue_a = queue_b = queue_c = queue_d = 0;

	puts("Bonjour le monde ");
	while(1){
		uint8_t currentButton_A_Status = (uint8_t) HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

		if (lastButton_A_Status != currentButton_A_Status && currentButton_A_Status != GPIO_PIN_RESET) {
			++queue_c;
//			blink_led_on(0);
			analyse_queues_situation(&queue_a, &queue_b, &queue_c, &queue_d, priority);
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			 timer_sleep(BLINK_OFF_TICKS);
//			timer_sleep(seconds == 0 ? TIMER_FREQUENCY_HZ : BLINK_ON_TICKS);
		} else {
			blink_led_off(12);
//			 timer_sleep(BLINK_OFF_TICKS);

//			      ++seconds;
		}
	}
  return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
