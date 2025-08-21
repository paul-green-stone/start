CFLAGS := -L../.. -lstart -Wl,-rpath=../.. -Wall

all: main.c
	gcc main.c -g $(CFLAGS) `pkg-config --libs --cflags sdl2 SDL2_image libconfig SDL2_ttf`
	