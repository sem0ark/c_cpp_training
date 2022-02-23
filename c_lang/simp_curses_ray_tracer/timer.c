#include <time.h>

#include "timer.h"

void cTimer_init(cTimer_t *tmr) {
  tmr->process_start = clock();
  tmr->frame_start = tmr->process_start;
}

double cTimer_elapsed(cTimer_t *tmr, char frame) {
  tmr->current = clock();
  double elapsed = frame ?
    (tmr->current - tmr->frame_start) / (double) CLOCKS_PER_SEC :
    (tmr->current - tmr->process_start) / (double) CLOCKS_PER_SEC;
  tmr->frame_start = tmr->current;
  return elapsed;
}


