w10.3: w10.3.o dijkstra.o pqueue.o digraph.o
	gcc -o w10.3 w10.3.o dijkstra.o pqueue.o digraph.o -g -Wall

w10.3-gui: w10.3-gui.o gtk.o dijkstra.o pqueue.o digraph.o
	#gcc `pkg-config --cflags gtk+-3.0` -o w10.3-gui w10.3-gui.o dijkstra.o pqueue.o digraph.o gtk.o `pkg-config --libs gtk+-3.0` -Wall -lm -g `pkg-config --static --libs --cflags igraph`

w10.3-gui.o: w10.3.c digraph.h dijkstra.h gtk.h
	#gcc -o w10.3-gui.o w10.3.c -DUSE_GUI -Wall -g -c

w10.3.o: w10.3.c digraph.h dijkstra.h gtk.h
	gcc -o w10.3.o w10.3.c -Wall -g -c

dijkstra.o: dijkstra.c dijkstra.h digraph.h pqueue.h
	gcc -o dijkstra.o dijkstra.c -Wall -g -c

pqueue.o: pqueue.c pqueue.h
	gcc -o pqueue.o pqueue.c -Wall -g -c

digraph.o: digraph.c digraph.h
	gcc -o digraph.o digraph.c -Wall -g -c

gtk.o: gtk.h gtk.c
	#gcc -g `pkg-config --cflags gtk+-3.0` -o gtk.o -Wall -c gtk.c `pkg-config --cflags igraph`