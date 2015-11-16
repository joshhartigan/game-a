CFLAGS += -Wall -Wextra -Wformat -Wno-missing-braces -pedantic -Werror -std=gnu11
INCFLAGS = -I./h
LIBFLAGS = -lncurses

BINDIR := bin

SRCFILES := $(wildcard src/*.c)

game:
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(SRCFILES) -o $(BINDIR)/game

clean:
	find $(BINDIR) -maxdepth 1 -type f -delete
