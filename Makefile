CC = gcc

SUBDIR = list matriks mesin point utilities
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

output: $(SRCS)
	$(CC) $(SRCS) -o output