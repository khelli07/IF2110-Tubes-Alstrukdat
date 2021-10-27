CC = gcc

SUBDIR = list matriks mesin pesanan point queuepesanan utilities
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

output: $(SRCS)
	$(CC) $(SRCS) -o main
