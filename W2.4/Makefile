driver: data.o array.o
	gcc -o driver data.o array.o


data.o: data.c data.h 
	gcc -c data.c

array.o: array.c array.h  
	gcc -c array.c 

clean:
	rm -f *.o combination 

