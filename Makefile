# ================================================================ #
# ======================== Some Variables ======================== #
# ================================================================ #

# Object files location. Object files will be placed in this directory during compilation
OBJDIR   = objects
# Full names of object files
OBJECTS	 = $(addprefix $(OBJDIR)/, Window.o Clock.o Texture.o Text.o Vector2.o Input.o Application.o)

# The Compiler
CC       = gcc
# and its flags
CFLAGS   = -c -g -Wall -Wextra -pedantic-errors -fPIC -O2 -ansi

# Additional libraries that need to be searched for function definitions
LDFLAGS  = `pkg-config --libs --cflags sdl2 SDL2_image libconfig SDL2_ttf` -lm

# An archiver to produce a static library
AR       = ar
# The archiver flags
ARFLAGS  = -r -s -c

# Library name
LIB_NAME = start
# The prefix for library names
PREFIX   = lib

# Aa list of all header files in the `include` directory and its subdirectories
INCLUDE  = $(wildcard include/*/*.h) $(wildcard include/*.h)

# Operating System name
OS_NAME  = $(shell uname -s)

# Default installation location
DESTDIR  ?= /usr/local

# ================================ #
# === Determining the library ==== #
# ================================ #

# If the operating system is Linux, set the variables
ifeq ($(OS_NAME), Linux)
# The suffix for static library files
    LIB_SUFFIX = .a
# The suffix for dynamic library files
    DLL_SUFFIX = .so

# If the operating system is macOS, set the variables
else ifeq ($(OS_NAME), Darwin)
# The suffix for static library files
    LIB_SUFFIX = .a
# The suffix for dynamic library files
    DLL_SUFFIX = .dylib

else
    $(error Unsupported operating system)
endif

# Constructing the name of static library
STATIC   = $(PREFIX)$(LIB_NAME)$(LIB_SUFFIX)

# Constructing the name of static library
SHARED   = $(PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================================================ #
# =========================== Targets ============================ #
# ================================================================ #

# Define a target
all: $(STATIC) $(SHARED)

# Building a static library 
$(STATIC): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

#Building a shared library
$(SHARED): $(OBJECTS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# ================================================================ #
# ======================== Start Building ======================== #
# ================================================================ #

WINDOW   = $(addprefix source/, window.c)

$(OBJDIR)/Window.o: $(WINDOW) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

CLOCK    = $(addprefix source/, clock.c)

$(OBJDIR)/Clock.o: $(CLOCK) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

TEXTURE  = $(addprefix source/, texture.c)

$(OBJDIR)/Texture.o: $(TEXTURE) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

TEXT     = $(addprefix source/, text.c)

$(OBJDIR)/Text.o: $(TEXT) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

VECTOR2  = $(addprefix source/Math/, vector2.c)

$(OBJDIR)/Vector2.o: $(VECTOR2) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

INPUT    = $(addprefix source/, input.c)

$(OBJDIR)/Input.o: $(INPUT) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ======== #

APP      = $(addprefix source/, application.c)

$(OBJDIR)/Application.o: $(APP) $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ $<

# ================================================================ #
# ======================== Other Commands ======================== #
# ================================================================ #

# Creating a directory if it does not exist. *nix
$(shell mkdir -p $(OBJDIR))

# Executing the commands regardless of whether a file named clean exists or not
.PHONY: clean install uninstall

# ================================================================ #
# ========================== INSTALLING ========================== #
# ================================================================ #

install:

# If the operating system is Linux
ifeq ($(OS_NAME), Linux)
# Installing a dynamic library
	install -Dm755 $(SHARED) $(DESTDIR)/lib/$(SHARED)
# Installing a static library
	install -Dm644 $(STATIC) $(DESTDIR)/lib/$(STATIC)

	for header in $(INCLUDE); do \
		destination=$$(echo $$header | sed 's,^include/,,' ); \
		install -Dm644 $$header $(DESTDIR)/include/start/$$destination; \
	done

# If the operating system is macOS
else ifeq ($(OS_NAME), Darwin)
# Installing a dynamic library
	install -Dm755 $(SHARED) $(DESTDIR)/lib/$(SHARED)
# Installing a static library
	install -Dm644 $(STATIC) $(DESTDIR)/lib/$(STATIC)
	
	for header in $(INCLUDE); do \
		destination=$$(echo $$header | sed 's,^include/,,' ); \
		install -Dm644 $$header $(DESTDIR)/include/start/$$destination; \
	done

else
    $(error Unsupported operating system)
endif

# ================================================================ #
# ========================= UNINSTALLING ========================= #
# ================================================================ #

uninstall:

# If the operating system is Linux
ifeq ($(OS_NAME), Linux)
# Uninstalling a dynamic library
	rm -f $(DESTDIR)/lib/$(SHARED)
# Uninstalling a static library
	rm -f $(DESTDIR)/lib/$(STATIC)

	for header in $(INCLUDE); do \
		destination=$$(echo $$header | sed 's,^include/,,' ); \
		rm -rf $(DESTDIR)/include/start/$$dest; \
	done

# If the operating system is macOS
else ifeq ($(OS_NAME), Darwin)
# Uninstalling a dynamic library
	rm -f $(DESTDIR)/lib/$(SHARED)
# Uninstalling a static library
	rm -f $(DESTDIR)/lib/$(STATIC)

	for header in $(INCLUDE); do \
		destination=$$(echo $$header | sed 's,^include/,,' ); \
		rm -rf $(DESTDIR)/include/start/$$dest; \
	done

else
    $(error Unsupported operating system)
endif

# ================================================================ #

clean:
	rm -rf ./include/*/*.gch $(OBJS) $(OBJDIR) $(STATIC) $(SHARED) *.out
