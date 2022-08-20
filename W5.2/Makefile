w5.2: w5.2.o bst.o llqueue.o
	gcc -Wall -g -o w5.2 w5.2.o bst.o llqueue.o

w5.2.o: w5.2.c bst.h
	gcc -Wall -g -o w5.2.o w5.2.c -c

bst.o: bst.c bst.h llqueue.h drawTree.c
	gcc -Wall -g -o bst.o bst.c -c

llqueue.o: llqueue.c llqueue.h
	gcc -Wall -g -o llqueue.o llqueue.c -c

w5.2-gui: w5.2-gui.o bst-gui.o llqueue.o gtk.o
	gcc `pkg-config --cflags gtk+-3.0` -Wall -g -o w5.2-gui w5.2-gui.o bst-gui.o llqueue.o gtk.o `pkg-config --libs gtk+-3.0` -Wall -lm `pkg-config --static --libs --cflags igraph`

w5.2-interactive: w5.2-interactive.o bst-gui.o llqueue.o gtk.o
	gcc `pkg-config --cflags gtk+-3.0` -Wall -g -o w5.2-interactive w5.2-interactive.o bst-gui.o llqueue.o gtk.o `pkg-config --libs gtk+-3.0` -Wall -lm `pkg-config --static --libs --cflags igraph`

w5.2-gui.o: w5.2.c bst.h
	gcc -Wall -g -o w5.2-gui.o w5.2.c -c -DUSE_GUI

w5.2-interactive.o: w5.2.c bst.h
	gcc -Wall -g -o w5.2-interactive.o w5.2.c -c -DUSE_GUI -DGUI_INTERACTIVE

gtk.o: gtk.h gtk.c
	gcc -g `pkg-config --cflags gtk+-3.0` -o gtk.o -Wall -c gtk.c `pkg-config --cflags igraph`

bst-gui.o: bst.c bst.h llqueue.h drawTree.c
	gcc -Wall -g -o bst-gui.o bst.c -c -DUSE_GUI
