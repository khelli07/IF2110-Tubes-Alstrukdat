CC = gcc
output:
	$(CC) -o main main.c utilities/pcolor.c mesin/inputmachine.c mesin/charmachine.c mesin/wordmachine.c list_linked/linked_list_to_do.c list_linked/linked_list_in_progress.c list_biasa/gadgetlist.c list_biasa/dynamiclist.c matriks/adjmat.c matriks/map.c tas/stack.c pesanan/pesanan.c pesanan/queuepesanan.c point/location.c point/point.c list_linked/node.c mobita/mobita.c  -o main
