CFLAGS := -L../.. -lstart -Wl,-rpath=../.. -Wall

all: main.cpp
	g++ main.cpp $(CFLAGS) `pkg-config --libs --cflags sdl2 SDL2_image libconfig SDL2_ttf | sed 's/-mwindows//'`
	