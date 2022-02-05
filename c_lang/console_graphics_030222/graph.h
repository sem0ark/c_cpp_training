#ifndef GRAPH_H
#define GRAPH_H

/*
 * Simple Graphics library by sem0ark
 * can be used to draw symple char pictures
 * in command prompt */


// BASIC FUNCTIONS

/* Initialises window grid to draw */
void g_init(int w, int h, char c);

/* Prints window to stdout */
void g_show(void);


// CLEANING

/* frees window from memory */
void g_shutdown(void);

/* fills window with specified char */
void g_fill(char c);


// DRAWING

/* draws line on specified coordinates */
void g_draw_line(int x1, int y1, int x2, int y2, char c);

/* puts char to specified location if it is in boorders of screen */
void g_putchar(int x, int y, char c);

/* fills specified region with c */
void g_draw_rect(int x1, int y1, int x2, int y2, char c);


#endif
