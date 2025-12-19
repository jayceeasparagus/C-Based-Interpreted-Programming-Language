CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/*.c
OUT = myhdl

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
