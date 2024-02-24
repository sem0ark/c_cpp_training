#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"

/* PIrint pixels to file */
void pixels2file(options_t *options, V3f_t *pixels);
/* Initialize ncurses creen */
void init_screen(options_t *options);
/* Show pixels on console */
void print_screen(options_t *options, V3f_t *pixels);
/* Shut down ncurses screen */
void shut_down(void);

#endif
