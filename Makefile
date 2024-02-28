EXEC = waves
CC = gcc
CFLAGS =-Wall -Wextra -Werror -std=c11
LIBS=-lm -fopenmp
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
PPM_IMAGE=waves.ppm
all: build $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)
build: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) $(LIBS)
clean:
	rm -f $(OBJ) $(EXEC) $(PPM_IMAGE)
