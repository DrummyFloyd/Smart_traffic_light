/*
 * traffic_manager.c
 *
 *  Created on: Sep 19, 2021
 *      Author: virgocoachman
 */

#include <stdio.h>
#include <stdlib.h>
#include "traffic_manager.h"
#include "diag/trace.h"
#include "led.h"

uint8_t great_between(uint8_t a, uint8_t b){
	if(a >= b)
		return a;
	return b;
}

void switching(uint8_t *priority, uint8_t index){
	priority[index] = 1;
	switch(index){
	case 0:
		priority[1] = 0;
		break;
	case 1:
		priority[0] = 0;
		break;
	default:
		puts("\nValeur d'index incorrecte, deux valeurs seulement sont possibles : 0 ou 1\n\n");
	}
}

void analyse_queues_situation(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d, uint8_t *priority){
	uint8_t queue_1 = great_between(*a, *b);
	uint8_t queue_2 = great_between(*c, *d);
	if(queue_1 == great_between(queue_1, queue_2)){
		switching(priority, 0);
	} else{
		switching(priority, 1);
	}
	display_queues(a, b, c, d);
	uint8_t i = display_priority_queue(priority);
	blink_led_on(i);
}

void display_queues(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d){
	trace_printf("Voie_a : %u et voie_b : %u\nVoie_c : %u et voie_d : %u\n"
			"====================================================\n", *a, *b, *c, *d);
}

uint8_t display_priority_queue(uint8_t *priority)
{
	trace_printf("Voie_1 : %u et voie_2 : %u\n", priority[0], priority[1]);
	if(priority[0]>= priority[1])
		return 0;
	return 1;
}


