CC = gcc

CFLG = -g -Wall -Wextra -O3
IFLG = -I.
LFLG = -lm -lncurses -lpthread

TARGET = ray_tracer.exe

HDR = utils.h light_utils.h camera.h screen.h object.h material.h ray_tr_whitted.h kb_linux.h timer.h
# headers
SRC = test.c utils.c light_utils.c camera.c ray_tr_whitted.c object.c material.c screen.c kb_linux.c timer.c
# source files

OBJ = $(SRC:.c=.o)

%.o: %.c $(HDR)
	$(CC) -c -o $@ $< $(CFLG) $(IFLG) $(LFLG)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLG) $(IFLG) $(LFLG)

run: $(TARGET)
	sudo ./$(TARGET)

.PHONY: clear
clear:
	rm -f $(TARGET) $(OBJ)
