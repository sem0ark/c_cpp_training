#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"



int _h=0, _w=0;

char **_g_screen;

//STATIC
void reset_scr(void) {
	printf("\x1b[2J"); // Clear screen
	printf("\x1b[H");  // Reset cursor
}



// PUBLIC
void g_init(int new_w, int new_h, char c) {

	_h = new_h;
	_w = new_w;

	_g_screen = (char **) calloc(_h, sizeof(char *));

	for (int i=0; i<=_h; i++) {
		_g_screen[i] = (char *) calloc(_w, sizeof(char));
		memset(_g_screen[i], c, _w);
	}

	return;
}

void g_show(void) {
	reset_scr();

	for (int i=0 ; i<_h; i++) {
		for (int j=0; j<_w; j++) {
			putchar(_g_screen[i][j]);
		}
		putchar('\n');
	}
	fflush(stdout);
}

void g_putchar(int x, int y, char c) {
	if (x<0 || x>=_w) return;
	if (y<0 || y>=_h) return;

	_g_screen[y][x] = c;

	return;
}

void g_draw_line(int x1, int y1, int x2, int y2, char c) {
	x1 = TRIM(x1, 0, _w-1);
	y1 = TRIM(y1, 0, _h-1);
	x2 = TRIM(x2, 0, _w-1);
	y2 = TRIM(y2, 0, _h-1);

	int dx = ABS(x2-x1);
	int sx = x1<x2? 1 : -1;
	int dy = -ABS(y2-y1);
	int sy = y1<y2? 1 : -1;

	int err = dx+dy;
	int e2 = 0;
	while (1) {
		g_putchar(x1, y1, c);

		if (x1==x2 && y1==y2) break;
		e2 = err*2;
		if (e2>=dy) {
			if (x1==x2) break;
			err += dy;
			x1 += sx;
		}
		if (e2<=dx) {
			if (y1==y2) break;
			err += dx;
			y1 += sy;
		}
	}

	return;
}

void g_draw_rect(int x1, int y1, int x2, int y2, char c) {
	x1 = TRIM(x1, 0, _w-1);
	y1 = TRIM(y1, 0, _h-1);
	x1 = TRIM(x1, 0, _w-1);
	y2 = TRIM(y2, 0, _h-1);

	if (x1>x2) i_swap(&x1, &x2);
	if (y1>y2) i_swap(&y1, &y2);

	for (int i=y1 ; i<=y2; i++)
		for (int j=x1; j<=x2; j++)
			_g_screen[i][j] = c;

	return;
}

void g_fill(char c) {
	for (int i=0; i<_h; i++) {
		memset(_g_screen[i], c, _w);
	}

	return;
}

void g_shutdown(void) {
	free(_g_screen);
	return;
}

