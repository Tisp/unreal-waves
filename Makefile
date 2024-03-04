EXEC = waves
CC = gcc
CFLAGS =-O3 -Wall -Wextra -Werror -std=c11
LIBS=-lm -fopenmp
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
PPM_IMAGE = $(wildcard images/*.ppm)
all: clean build $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)
build: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) $(LIBS)
clean:
	rm -f $(OBJ) $(EXEC) $(PPM_IMAGE)
