CC = gcc

CFLG = -g -Wall -Wextra
IFLG = -I.
LFLG = -lm

TARGET = ray_tracer

HDR = utils.h ray_tracer.h object.h screen.h camera.h
# headers
SRC = main.c object.c utils.c screen.c ray_tracer.c camera.c
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

