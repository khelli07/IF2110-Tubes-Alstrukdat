#ifndef PESANAN_H
#define PESANAN_H

#include "../boolean.h"
#include "../location/location.h"
#include "../point/point.h"

typedef enum JenisItemEnum {NORMAL, HEAVY, PERISHABLE, VIP} JenisItem;

typedef struct {
    Location pickUp;
    Location dropOff;
    int waktuIn;
    int price;
    int timeout; // waktu expired, khusus Perishable
    int timeoutInitial; // waktu expired awal (konstan, tidak dikurang dan dioperasikan), khusus Perishable
    JenisItem jenisItem;
} Pesanan;

#define LokasiPickUp(p) (p).pickUp
#define LokasiDropOff(p) (p).dropOff
#define WaktuIn(p) (p).waktuIn
#define Price(p) (p).price
#define JenisItem(p) (p).jenisItem
#define TimeoutPerish(p) (p).timeout
#define TimeoutPerishInitial(p) (p).timeout

// Create Pesanan, harga item otomatis disimpulkan dari JenisItem
void CreatePesanan(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn);
// Create Pesanan, untuk Perishable (dengan timeout)
void CreatePesananPerish(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn, int timeout);

// Apakah pesanan sudah masuk waktu sehingga muncul di To Do
boolean isPesananMasukWaktu(Pesanan p, int waktu);
// Return true jika timout item sudah habis (khusus Perishable)
boolean isPesananExpired(Pesanan p);

boolean isPesananEqual(Pesanan p1, Pesanan p2);
// Return true jika p1 sama dengan p2



#endif