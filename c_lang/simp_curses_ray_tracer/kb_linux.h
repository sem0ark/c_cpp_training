#ifndef KB_LINUX_H
#define KB_LINUX_H

#include <pthread.h>
#include <linux/input.h>

#define KEYBOARD_DEV "/dev/input/event2"

struct keyboard_state {
  int keys[KEY_CNT];
};

typedef struct cKeyboard_s {
  pthread_t thrd;
  char active;
  int keyboard_fd;
  struct input_event *keyboard_ev;
  struct keyboard_state *keyboard_st;
  char name[256];
} cKeyboard_t;

void cKeyboard_init(cKeyboard_t *kb);
void cKeyboard_shutdown(cKeyboard_t *kb);

int cKeyboard_getKeyState(cKeyboard_t *kb, int key);

#endif
