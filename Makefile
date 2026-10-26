# The Game of Life

CC = gcc
CFLAGS = -Wall -g -std=c11

SRCDIR = src
BUILDDIR = build

TARGET = $(BUILDDIR)/gol

SOURCES = main.c game.c gol.c ncurses.c
OBJECTS = $(SOURCES:%.c=$(SRCDIR)/%.o)

all: $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(OBJECTS) -lncursesw -o $(TARGET)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rmdir $(BUILDDIR) 2>/dev/null || true

debug:
	echo TARGET: $(TARGET)
	echo OBJECTS: $(OBJECTS)
	echo SOURCES: $(SOURCES)
	echo CFLAGS: $(CFLAGS)

.PHONY: all clean debug
