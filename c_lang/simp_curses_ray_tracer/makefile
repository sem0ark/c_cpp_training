CC = gcc

CFLG = -g -Wall -Wextra
IFLG = -I.
LFLG = -lm

TARGET = ray_tracer.exe

HDR = utils.h light_utils.h camera.h screen.h object.h ray_tracer.h
# headers
SRC = test.c utils.c light_utils.c camera.c ray_tracer.c object.c main.c screen.c
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

