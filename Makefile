CC = gcc

SUBDIR = adt_mesin adt_point 
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

output: $(SRCS)
	$(CC) $(SRCS) -o output