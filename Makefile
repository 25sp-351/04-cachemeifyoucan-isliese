# Defines variables
CC = gcc
CFLAGS = -Wall -g

# Target and Building Rules
all: rod_cut_lru rod_cut_fifo

# rod_cut_lru Target
rod_cut_lru: rod_cut.c cache_lru.c
	$(CC) $(CFLAGS) -o rod_cut_lru rod_cut.c cache_lru.c

# rod_cut_fifo Target
rod_cut_fifo: rod_cut.c cache_fifo.c
	$(CC) $(CFLAGS) -o rod_cut_fifo rod_cut.c cache_fifo.c

# clean Target
clean:
	rm -f rod_cut_lru rod_cut_fifo
