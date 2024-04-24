all:
	gcc -Isrc/include -Lsrc/lib -o exec sorting_visualizer.c -lmingw32 -lSDL2main -lSDL2