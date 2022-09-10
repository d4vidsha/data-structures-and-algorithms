w8.3: w8.3.o merge.o ll.o
	gcc -Wall -o w8.3 w8.3.o merge.o ll.o

w8.3.o: w8.3.c merge.h ll.h
	gcc -Wall -o w8.3.o w8.3.c -g -c
	
merge.o: merge.c merge.h ll.h
	gcc -Wall -o merge.o merge.c -g -c

ll.o: ll.c ll.h
	gcc -Wall -o ll.o ll.c -g -c

