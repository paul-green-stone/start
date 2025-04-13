all: main.c
	gcc main.c -L../.. -lstart -Wl,-rpath=../.. `pkg-config --libs --cflags sdl2 SDL2_image libconfig SDL2_ttf`