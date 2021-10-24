pesanan.o: pesanan/pesanan.c pesanan/pesanan.h
	gcc -c pesanan/pesanan.c
queuepesanan.o: queuepesanan/queuepesanan.c queuepesanan/queuepesanan.h pesanan/pesanan.h
	gcc -c queuepesanan/queuepesanan.c