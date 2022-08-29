# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = driver.c copy.c linkedlist.c readcsv.c stage.c quicksort.c search.c array.c quadtree.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)

# Define the executable name(s)
EXE1 = dict1
EXE2 = dict2
EXE3 = dict3
EXE4 = dict4

# the first target:
$(EXE1): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ) $(LDLIBS)

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