CFLAGS := -L../.. -lstart -Wl,-rpath=../.. -Wall

all: main.c
	emcc main.c $(CFLAGS) -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' -o index.js -s WASM=1 --preload-file res/* --emrun
	