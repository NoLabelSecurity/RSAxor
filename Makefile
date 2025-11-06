CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = RSAxor

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o build/$(TARGET) $(OBJ)

clean:
	rm -f src/*.o build/$(TARGET)

run: all
	./build/$(TARGET)
