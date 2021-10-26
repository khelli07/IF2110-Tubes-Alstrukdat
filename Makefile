queuepesanan.o: queuepesanan/queuepesanan.c
	gcc -c queuepesanan/queuepesanan.c
pesanan.o: pesanan/pesanan.c
	gcc -c pesanan/pesanan.c
point.o: point/point.c
	gcc -c point/point.c
location.o: location/location.c
	gcc -c location/location.c

# Contoh compile driver; Syntax command: mingw32-make namatarget; contoh: mingw32-make queuepesanan/queuepesanan_driver
pesanan/pesanan_driver: pesanan/pesanan_driver.c pesanan.o point.o location.o
	gcc pesanan/pesanan_driver.c pesanan.o point.o location.o -o pesanan/pesanan_driver
queuepesanan/queuepesanan_driver: queuepesanan/queuepesanan.c queuepesanan.o pesanan.o point.o location.o
	gcc queuepesanan/queuepesanan_driver.c queuepesanan.o pesanan.o point.o location.o -o queuepesanan/queuepesanan_driver