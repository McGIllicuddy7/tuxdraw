make: main.c texlib.c 
	gcc main.c texlib.c mathtils.c -l raylib -std=c2x -g3
