# define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# define libraries to be linked (for example -lm)
LDLIBS = 

# define sets of source files and object files
SRC = w8.4.c mergeInt.c queue.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)

# define the executable names
EXE1 = w8.4

# the first target
$(EXE1): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXE1)