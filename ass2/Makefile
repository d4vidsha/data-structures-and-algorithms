# define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# define libraries to be linked (for example -lm)
LDLIBS = 

# define sets of source files and object files
SRC = driver.c copy.c linkedlist.c readcsv.c stage.c quicksort.c search.c array.c quadtree.c print.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)

# define the executable names
EXE1 = dict1
EXE2 = dict2
EXE3 = dict3
EXE4 = dict4

# the first target
$(EXE1): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ) $(LDLIBS)

# other targets
$(EXE2): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ) $(LDLIBS)

$(EXE3): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE3) $(OBJ) $(LDLIBS)

$(EXE4): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE4) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXE1)
	rm -f $(OBJ) $(EXE2)
	rm -f $(OBJ) $(EXE3)
	rm -f $(OBJ) $(EXE4)