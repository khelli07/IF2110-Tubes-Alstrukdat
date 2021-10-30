CC = gcc

SUBDIR = list_biasa list_linked matriks mesin mobita pesanan point tas utilities
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

output: $(SRCS)
	$(CC) $(SRCS) -o main
