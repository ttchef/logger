
CC := gcc
CFLAGS_DEBUG := -Wall -Wextra -pedantic -fsanitize=address -g -std=c11
CFLAGS_RELEASE := -o3 -std=c11

all:
	$(CC) $(CFLAGS_RELEASE) main.c -o main
