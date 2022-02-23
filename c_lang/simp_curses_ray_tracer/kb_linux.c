#ifdef __linux__

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

#include "kb_linux.h"

void kb_readEv(cKeyboard_t *kb) {
  int bytes = read(kb->keyboard_fd, kb->keyboard_ev, sizeof(*kb->keyboard_ev));
  if (bytes > 0) {
    if (kb->keyboard_ev->type & EV_KEY) {
      kb->keyboard_st->keys[kb->keyboard_ev->code] = kb->keyboard_ev->value;
    }
  }
}

void* kb_loop(void *obj) {
	while (((cKeyboard_t *)obj)->active) {
		kb_readEv((cKeyboard_t *)obj);
	}
  return NULL;
}

void cKeyboard_init(cKeyboard_t *kb) {
  kb->active = 0;
  kb->keyboard_fd = 0;
  kb->keyboard_ev = &(struct input_event) {0};
  kb->keyboard_st = &(struct keyboard_state) {0};
  kb->keyboard_fd = open(KEYBOARD_DEV, O_RDONLY | O_NONBLOCK);
  if (kb->keyboard_fd > 0) {
    ioctl(kb->keyboard_fd, EVIOCGNAME(256), kb->name);
    kb->active = 1;
    pthread_create(&kb->thrd, 0, &kb_loop, kb);
  }
}

void cKeyboard_shutdown(cKeyboard_t *kb) {
  if (kb->keyboard_fd > 0) {
    kb->active = 0;
    pthread_join(kb->thrd, 0);
    close(kb->keyboard_fd);
  }
  free(kb->keyboard_st);
  free(kb->keyboard_ev);
  kb->keyboard_fd = 0;
}

int cKeyboard_getKeyState(cKeyboard_t *kb, int key) {
  return kb->keyboard_st->keys[key];
}

#endif

