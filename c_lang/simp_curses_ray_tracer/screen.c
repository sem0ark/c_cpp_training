#include <stdio.h>
#include <stdlib.h>

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

