w9.3: w9.3.o merge.o ll.o queue.o
	gcc -Wall -o w9.3 w9.3.o merge.o ll.o queue.o

w9.3.o: w9.3.c merge.h ll.h
	gcc -Wall -o w9.3.o w9.3.c -g -c
	
merge.o: merge.c merge.h ll.h queue.h
	gcc -Wall -o merge.o merge.c -g -c

ll.o: ll.c ll.h
	gcc -Wall -o ll.o ll.c -g -c

queue.o: queue.h queue.c ll.h
	gcc -Wall -o queue.o queue.c -g -c
