#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct cTimer_s {
	clock_t process_start, frame_start, current;
} cTimer_t;

void cTimer_init(cTimer_t *tmr);

double cTimer_elapsed(cTimer_t *tmr, char frame);

#endif
