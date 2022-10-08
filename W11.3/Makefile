w11.3: w11.3.o gtk.o fw.o adjmatrix.o
	gcc -o w11.3 w11.3.o fw.o adjmatrix.o -g -Wall

w11.3-gui: w11.3-gui.o gtk.o fw.o adjmatrix.o
	gcc `pkg-config --cflags gtk+-3.0` -o w11.3-gui w11.3-gui.o fw.o adjmatrix.o gtk.o `pkg-config --libs gtk+-3.0` -Wall -lm -g `pkg-config --static --libs --cflags igraph`

w11.3-gui.o: w11.3.c adjmatrix.h fw.h gtk.h
	gcc -o w11.3-gui.o w11.3.c -DUSE_GUI -Wall -g -c

w11.3.o: w11.3.c adjmatrix.h fw.h gtk.h
	gcc -o w11.3.o w11.3.c -Wall -g -c

fw.o: fw.c fw.h adjmatrix.h
	gcc -o fw.o fw.c -Wall -g -c

adjmatrix.o: adjmatrix.c adjmatrix.h
	gcc -o adjmatrix.o adjmatrix.c -Wall -g -c

gtk.o: gtk.h gtk.c adjmatrix.h
	gcc -g `pkg-config --cflags gtk+-3.0` -o gtk.o -Wall -c gtk.c `pkg-config --cflags igraph`
