#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "utils.h"

void pixels2file(options_t *options, V3f_t *pixels) {
	FILE *fp;
	int n_pix = options->width * options->height;
	char *ppm = (char*)malloc(sizeof(char) * n_pix);
	fp = fopen("test1.ppm", "w");
	fprintf(fp, "P6 %d %d %d\n",  options->width, options->height, 255);
	for (int c=0; c<n_pix; c++) {
		pixels[c] = clamp_v3(pixels[c], 0.0f, 1.0f);
		fprintf(fp, "%c%c%c", (char)(pixels[c].x*255.0),
			(char)(pixels[c].y*255.0), (char)(pixels[c].z*255.0));
	}
	fclose(fp);
	free(ppm);
}

int len = 9;
char *brightness = " .:+*=#%@";

void init_screen(options_t *options) {
	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx(stdscr, options->height, options->width);
}

void print_screen(options_t *options, V3f_t *pixels) {
	move(0,0);
	int c = options->height * options->width;
	V3f_t *pix = pixels;
	for (int i=0; i<c; i++) {
		float l = sqrt(len_sq_v3(*pix) / 3.0f);
		addch(brightness[(int)CLAMP(len * l, 0, len-1)]);
		pix++;
	}

	refresh();
}

void shut_down(void) {
	endwin();
}

