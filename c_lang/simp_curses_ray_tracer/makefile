CC = gcc

CFLG = -g -Wall -Wextra -O3

IFLG = -I./inc
LFLG = -lm

TARGET = ray_tracer.exe

HDR = $(wildcard ./inc/*.h)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(wildcard ./src/*.c))

obj/%.o: src/%.c $(HDR)
	$(CC) -c -o $@ $< $(CFLG) $(IFLG) $(LFLG)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLG) $(IFLG) $(LFLG)

run: ./$(TARGET)
	$(TARGET)

