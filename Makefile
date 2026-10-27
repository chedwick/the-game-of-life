# The Game of Life - Main Build System
# Delegates to framework-specific makefiles based on target

.PHONY: all clean debug help ncurses sdl2 sdl3 sfml raylib

# Default target is ncurses
all: ncurses

help:
	@echo "The Game of Life - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  make ncurses  Build with ncurses (default)"
	@echo "  make sdl2     Build with SDL2"
	@echo "  make sdl*     Build with SDL3"
	@echo "  make sfml*     Build with SFML"
	@echo "  make raylib*   Build with Raylib"
	@echo "  make clean    Clean all build artifacts"
	@echo "  make debug    Show build configuration"
	@echo "  make help     Show this message"
	@echo ""
	@echo "(*) not yet supported"
ncurses:
	$(MAKE) -f Makefile_ncurses all

sdl2:
	$(MAKE) -f Makefile_sdl2 all

sdl3:
	@echo "SDL3 support not yet available"

sfml:
	@echo "SFML support not yet available"

raylib:
	@echo "Raylib support not yet available"

clean:
	$(MAKE) -f Makefile_ncurses clean
	$(MAKE) -f Makefile_sdl2 clean

debug:
	@echo "=== ncurses build configuration ==="
	@$(MAKE) -f Makefile_ncurses debug
	@echo ""
	@echo "=== SDL2 build configuration ==="
	@$(MAKE) -f Makefile_sdl2 debug
