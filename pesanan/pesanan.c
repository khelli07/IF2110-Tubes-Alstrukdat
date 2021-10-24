#include "pesanan.h"

void CreatePesanan(Pesanan *p, JenisItem jenisItem, Lokasi pickUp, Lokasi dropOff, int waktuIn){
    JenisItem(*p) = jenisItem;
    LokasiPickUp(*p) = pickUp;
    LokasiDropOff(*p) = dropOff;
    WaktuIn(*p) = waktuIn;
    TimeoutPerish(*p) = -1;
    TimeoutPerishInitial(*p) = -1;

    int harga;
    switch (jenisItem)
        {
        case NORMAL:
            harga = 200;
            break;
        case HEAVY:
            harga = 400;
            break;
        case PERISHABLE:
            harga = 400;
            break;
        case VIP:
            harga = 600;
            break;
        default:
            harga = 0;
            break;
        }
    Price(*p) = harga;
}
// Create Pesanan, untuk Perishable (dengan timeout)
void CreatePesananPerish(Pesanan *p, JenisItem jenisItem, Lokasi pickUp, Lokasi dropOff, int waktuIn, int timeout){
    JenisItem(*p) = jenisItem;
    LokasiPickUp(*p) = pickUp;
    LokasiDropOff(*p) = dropOff;
    WaktuIn(*p) = waktuIn;
    TimeoutPerish(*p) = timeout;
    TimeoutPerishInitial(*p) = timeout;

    int harga;
    switch (jenisItem)
        {
        case NORMAL:
            harga = 200;
            break;
        case HEAVY:
            harga = 400;
            break;
        case PERISHABLE:
            harga = 400;
            break;
        case VIP:
            harga = 600;
            break;
        default:
            harga = 0;
            break;
        }
    Price(*p) = harga;
}

// Apakah pesanan sudah masuk waktu sehingga muncul di To Do
boolean isPesananMasukWaktu(Pesanan p, int waktu){
    return waktu >= WaktuIn(p);
}
// Return true jika timout item sudah habis (khusus Perishable)
boolean isPesananExpired(Pesanan p){
    return TimeoutPerish(p) <= 0;
}