dict1: dict1.o dictionary.o read.o quadTree.o
	gcc -Wall -o dict1 dict1.o dictionary.o read.o quadTree.o -g

dict1.o: dict1.c dictionary.h read.h
	gcc -Wall -o dict1.o dict1.c -g -c

# Note that because we #include recurd_struct.c we need it in our dependencies.
dictionary.o: dictionary.c dictionary.h record_struct.c record_struct.h dictionary_struct.h
	gcc -Wall -o dictionary.o dictionary.c -g -c

read.o: read.c read.h record_struct.c record_struct.h
	gcc -Wall -o read.o read.c -g -c

dict2: dict2.o dictionary.o read.o quadTree.o
	gcc -Wall -o dict2 dict2.o dictionary.o read.o quadTree.o -g

dict2.o: dict2.c dictionary.h read.h
	gcc -Wall -o dict2.o dict2.c -g -c

dict3: dict3.o dictionary.o read.o quadTree.o
	gcc -Wall -o dict3 dict3.o dictionary.o read.o quadTree.o -g

dict3.o: dict3.c dictionary.h read.h quadTree.h
	gcc -Wall -o dict3.o dict3.c -g -c

dict4: dict4.o dictionary.o read.o quadTree.o
	gcc -Wall -o dict4 dict4.o dictionary.o read.o quadTree.o -g

dict4.o: dict4.c dictionary.h read.h quadTree.h
	gcc -Wall -o dict4.o dict4.c -g -c

quadTree.o: quadTree.c quadTree.h dictionary_struct.h
	gcc -Wall -o quadTree.o quadTree.c -g -c
