/*
 * traffic_manager.h
 *
 *  Created on: Sep 19, 2021
 *      Author: virgocoachman
 */

#ifndef TRAFFIC_MANAGER_H_
#define TRAFFIC_MANAGER_H_



void analyse_queues_situation(uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
uint8_t display_priority_queue(uint8_t *priority);
uint8_t great_between(uint8_t a, uint8_t b);
void switching(uint8_t *priority, uint8_t index);
void display_queues(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d);


#endif /* TRAFFIC_MANAGER_H_ */
