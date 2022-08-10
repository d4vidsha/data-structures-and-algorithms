# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = driver.c readin.c linkedlist.c data.c readcsv.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE1 = dict1
EXE2 = dict2

# the first target:
$(EXE1): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ) $(LDLIBS)

$(EXE2): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXE1)
	rm -f $(OBJ) $(EXE2)