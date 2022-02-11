CC = gcc

CFLG = -g -Wall -Wextra
IFLG = -I.
LFLG = -lm

TARGET = ray_tracer.exe

HDR = utils.h light_utils.h camera.h screen.h object.h material.h ray_tr_whitted.h
# headers
SRC = test.c utils.c light_utils.c camera.c ray_tr_whitted.c object.c material.c screen.c
# source files

OBJ = $(SRC:.c=.o)

%.o: %.c $(HDR)
	$(CC) -c -o $@ $< $(CFLG) $(IFLG) $(LFLG)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLG) $(IFLG) $(LFLG)

run: $(TARGET)
	./$(TARGET)

.PHONY: clear
clear:
	rm -f $(TARGET) $(OBJ)
