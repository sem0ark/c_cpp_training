#include <time.h>
#include <stdio.h>

#include "graph.h"
#include "object.h"

void move(object *o, double dt) {
	o->x += o->vx*dt;
	o->y += o->vy*dt;

	if (o->x > 10) o->x = 0;
	if (o->y > 10) o->y = 0;
}

object obj = {0.0, 0.0, 15.0, 8.0};

void simple_animation_1(double dt) {
	move(&obj, dt);
	g_fill(' ');
	g_putchar((int) obj.x, (int) obj.y, '@');
}

void run(int w, int h, int fps) {
	clock_t cur_t, prev_t;
	prev_t = clock();
	double frame_time = 1.0 / fps;
	double dt = 0.0;
	double elapsed_from_show = 0.0;
	while (1) {
		cur_t = clock();
		dt = (cur_t - prev_t) / (double) CLOCKS_PER_SEC;
		elapsed_from_show += dt;
		simple_animation_1(dt);
		if (elapsed_from_show > frame_time) {
			g_show();
			elapsed_from_show = 0;
		}
		prev_t = cur_t;
	}

}


int main(void) {
	int h=10, w=10;
	g_init(w, h, '.');
	run(w, h, 30);
	g_show();
	g_shutdown();
	return 0;
}
