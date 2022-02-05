CC = gcc

CFLAGS = -Wall -Wextra -g

IFLAGS = -I.
LFLAGS = -lncurses

DEPS = ''
SRC = main.c

TARGET = a.out



OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) $(LFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(IFLAGS) $(LFLAGS)

run: $(TARGET)
	./$(TARGET)


.PHONY: clean
clean: $(OBJ)
	rm -f $^ $(TARGET)


