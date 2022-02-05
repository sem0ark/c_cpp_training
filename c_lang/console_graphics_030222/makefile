CC = gcc
CFLAGS = -g -Wall -Wextra

INC = -I.

TARGET = a.out

DEPS = graph.h utils.h
SRC = main.c graph.c utils.c


OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INC)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(INC)

.PHONY: clear

clear: $(OBJ)
	rm -f $^ $(TARGET)

run: $(TARGET)
	./$(TARGET)

