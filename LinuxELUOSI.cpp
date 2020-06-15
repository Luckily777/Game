#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <keyboard.h>

#define FC 5
#define BC 7

struct data {
	int x;
	int y;
};

#define W 10
#define H 20


struct shape {
	int s[5][5];
};

int background[H][W] = {};
int idx = 0;

struct data t = { .x = 5, .y = 5 };
struct shape shape_arr[7] = {
		{ 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, },
		{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0, }
};

void drap_element(int x, int y, int c) {
	x = x * 2;
	x++;
	y++;
	printf("\033[%d;%dH\033[3%dm\033[4%dm[]\033[?25l\033[0m", y, x, c, c);
	fflush(stdout);
}

void draw_back() {
	int i, j;

	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			if (background[i][j] == 0)
				drap_element(j, i, BC);
			else
				drap_element(j, i, FC);
		}
	}
}

void drap_shape(int x, int y, struct shape p, int c) {
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (p.s[i][j] != 0) {
				drap_element(x + j, y + i, c);
			}
		}
	}
}

int can_move(int x, int y, struct shape p) {
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (p.s[i][j] == 0) continue;
			if (x + j >= W) return 0;
			if (x + j < 0) return 0;
			if (y + i >= H) return 0;
			if (background[y + i][x + j] != 0) return 0;
		}
	}
	return 1;
}

void set_back(struct data* t, struct shape p) {
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (p.s[i][j] != 0) {
				background[t->y + i][t->x + j] = 1;
			}
		}
	}
}

void clear_line() {
	int i, j;

	for (i = 0; i < H; i++) {
		int total = 0;
		for (j = 0; j < W; j++) {
			if (background[i][j] != 0)
				total++;
		}

		if (total == W) {
			int k;
			for (k = i; k >= 1; k--) {
				memcpy(background[k], background[k - 1], sizeof(background[i]));
			}

			memset(background[0], 0x00, sizeof(background[0]));
		}
	}
}

void tetris_timer(struct data* t) {
	drap_shape(t->x, t->y, shape_arr[idx], BC);
	if (can_move(t->x, t->y + 1, shape_arr[idx])) {
		t->y++;
		drap_shape(t->x, t->y, shape_arr[idx], FC);
	}
	else {
		drap_shape(t->x, t->y, shape_arr[idx], FC);
		set_back(t, shape_arr[idx]);
		clear_line();
		draw_back();
		idx = rand() % 7;
		t->y = 0;
		t->x = 4;
	}
}

void handler(int s) {
	tetris_timer(&t);
}

void handler_int(int s) {
	printf("\033[?25h");
	recover_keyboard();
	exit(0);
}

struct shape trun_90(struct shape p) {
	struct shape tmp;
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++)
			tmp.s[i][j] = p.s[4 - j][i];
	}
	return tmp;
}

void tetris(struct data* t) {
	int ch = get_key();
	if (is_up(ch)) {
		drap_shape(t->x, t->y, shape_arr[idx], BC);
		shape_arr[idx] = trun_90(shape_arr[idx]);
		if (can_move(t->x, t->y, shape_arr[idx]) == 0) {
			shape_arr[idx] = trun_90(shape_arr[idx]);
			shape_arr[idx] = trun_90(shape_arr[idx]);
			shape_arr[idx] = trun_90(shape_arr[idx]);
		}
		drap_shape(t->x, t->y, shape_arr[idx], FC);
	}
	else if (is_down(ch)) {
		drap_shape(t->x, t->y, shape_arr[idx], BC);
		if (can_move(t->x, t->y + 1, shape_arr[idx])) {
			t->y++;
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
		else {
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
	}
	else if (is_left(ch)) {
		drap_shape(t->x, t->y, shape_arr[idx], BC);
		if (can_move(t->x - 1, t->y, shape_arr[idx])) {
			t->x--;
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
		else {
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
	}
	else if (is_right(ch)) {
		drap_shape(t->x, t->y, shape_arr[idx], BC);
		if (can_move(t->x + 1, t->y, shape_arr[idx])) {
			t->x++;
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
		else {
			drap_shape(t->x, t->y, shape_arr[idx], FC);
		}
	}
}


int main(void) {
	int i;
	signal(SIGALRM, handler);
	signal(SIGINT, handler_int);
	draw_back();

	srand(time(NULL));
	init_keyboard();
	struct itimerval it;
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 1;
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &it, NULL);

	for (; ; ) {
		tetris(&t);
	}
}
