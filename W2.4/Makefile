qStud: driver.o data.o array.o
	gcc -o qStud driver.o data.o array.o

driver: driver.c
	gcc -c driver.c

data.o: data.c data.h 
	gcc -c data.c

array.o: array.c array.h  
	gcc -c array.c 

clean:
	rm -f *.o driver 

