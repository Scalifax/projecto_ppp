CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = src/main.c
OUT = bin/main

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)