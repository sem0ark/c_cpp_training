#include <unistd.h>

#include <ncurses.h>

#define DELAY 30000

int main(int argc, char *argv[]) {
	int x = 0, y = 0, vx = 1, vy = 2;
	int max_x = 0, max_y = 0;

	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, max_y, max_x);

	int n_x=0, n_y=0;
	while(1) {
//		clear();
		mvaddch(y, x, 'o');
		refresh();

		usleep(DELAY);

		n_x = x + vx;
		n_y = y + vy;


		if (n_x >= max_x || n_x < 0) { vx *= -1; }
		else { x += vx; }

		if (n_y >= max_y || n_y < 0) { vy *= -1; }
		else { y += vy; }

	}

	endwin();
}

