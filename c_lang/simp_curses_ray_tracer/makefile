CC = gcc

CFLG = -g -Wall -Wextra -O3

IFLG = -I./inc
LFLG = -lm -lpthread

TARGET = ray_tracer.exe

HDR = $(wildcard ./inc/*.h)


# HDR = utils.h light_utils.h camera.h screen.h object.h material.h ray_tr_whitted.h kb_linux.h timer.h

# headers

# SRC = test.c utils.c light_utils.c camera.c ray_tr_whitted.c object.c material.c screen.c kb_linux.c timer.c
# source files

OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(wildcard ./src/*.c))

obj/%.o: src/%.c $(HDR)
	$(CC) -c -o $@ $< $(CFLG) $(IFLG) $(LFLG)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLG) $(IFLG) $(LFLG)

run: $(TARGET)
	./$(TARGET)

.PHONY: clear
clear:
	del $(TARGET)
	rmdir /s ./obj
