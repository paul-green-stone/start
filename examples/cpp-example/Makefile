# Operating System name
OS_NAME  = $(shell uname -s)

# If the operating system is Linux, set the variables
ifeq ($(OS_NAME), Linux)
# Compiler's flags
	CFLAGS := -L../.. -lstart -Wl,-rpath=../.. -Wall

# If the operating system is macOS, set the variables
else ifeq ($(OS_NAME), Darwin)
# Compiler's flags
	CFLAGS += -L../.. -lstart -Wl,-rpath,@loader_path../..
endif

all: main.cpp
	g++ main.cpp $(CFLAGS) `pkg-config --libs --cflags sdl2 SDL2_image libconfig SDL2_ttf | sed 's/-mwindows//'` -std=c++11
	