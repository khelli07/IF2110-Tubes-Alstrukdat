pesanan.o: pesanan/pesanan.c pesanan/pesanan.h
	gcc -c pesanan/pesanan.c
queuepesanan.o: queuepesanan/queuepesanan.c queuepesanan/queuepesanan.h pesanan/pesanan.h
	gcc -c queuepesanan/queuepesanan.c
point.o: point/point.c point/point.h
	gcc -c point/point.c
location.o: location/location.c location/location.h point/point.h
	gcc -c location/location.c