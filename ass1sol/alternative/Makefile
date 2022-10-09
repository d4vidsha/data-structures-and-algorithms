dict1: main.o dict.o ll.o da.o data.o
	gcc -o dict1 main.o dict.o ll.o da.o data.o

dict2: main.o dict.o ll.o da.o data.o
	gcc -o dict2 main.o dict.o ll.o da.o data.o

main.o: main.c
	gcc -c main.c

dict.o: dict.c dict.h ll.o da.o data.o
	gcc -c dict.c dict.h 

ll.o: ll.c ll.h data.o
	gcc -c ll.c ll.h

da.o: da.c da.h data.o
	gcc -c da.c da.h

data.o: data.c data.h
	gcc -c data.c data.h

run:
	make clean
	make dict1
	./dict1 1 tests/dataset_1000.csv tests/test1000.1.outMY <tests/test1000.1.in >tests/test1000.1.stdout.outMY
	make dict2
	./dict2 2 tests/dataset_1000.csv tests/test1000.2.outMY <tests/test1000.2.in >tests/test1000.2.stdout.outMY

clean:
	rm -f *.o 

test:
	make clean
	gcc -c maintest.c
	make data.o
	gcc -o testprog maintest.o data.o 
	./testprog
