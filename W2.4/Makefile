# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = driver.c factorial.c combination.c 
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = combination

# The first target:
combination: driver.o factorial.o combination.o
	gcc -o combination driver.o factorial.o combination.o

# Other targets specify how to get the .o files
driver.o: driver.c 
	gcc -c driver.c 

factorial.o: factorial.c factorial.h 
	gcc -c factorial.c 

combination.o: combination.c combination.h  
	gcc -c combination.c 

clean:
	rm -f *.o combination 

