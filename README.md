# Mobilita (CLI-Based Game)

### This is a program completed as an assignment for IF2110 Algorithm and Data Structures at Institut Teknologi Bandung.

Dibuat dengan <span class="heart">♥</span> oleh:

- Maria Khelli
- Mohamad Daffa Argakoesoemah
- Bryan Amirul Husna
- Frederik Imanuel Louis

## Selayang Pandang Program

<hr>
Program Mobita adalah sebuah permainan berbasis Command Line Interface (CLI) yang menyimulasikan pengantaran barang. Diceritakan bahwa karena pandemi COVID-19, Mobita ingin membantu orang tuanya dengan menjadi kurir pengantar barang. Tujuan permainan ini adalah mengantarkan pesanan yang dibawa Mobita kepada masing-masing penerima pesanan dengan waktu sesingkat mungkin.

Berdasarkan latar belakang di atas, kami membuat program permainan tersebut dengan beberapa bagian, antara lain menu, mekanisme waktu, daftar pesanan, to do list, in progress list, tas, jenis item, ability, gadget, inventory gadget¸ peta, perintah yang bisa dijalankan di setiap lokasi pada peta, dan kemampuan program untuk menyimpan state permainan serta melakukan load kembali state tersebut. Program ini dibuat menggunakan bahasa C dengan memanfaatkan konsep Abstract Data Type (ADT).

## Cara Kompilasi

<hr>
Cara kompilasi program adalah dengan memanggil ”make” pada command prompt. Pada Windows dengan MinGW, dapat memanggil ”MinGW32-make” atau dengan menginstall Windows Subsystem for Linux (WSL), menginstall gcc dan make untuk memanggil ”make”. Setelah dipanggil, akan muncul file bertipe .exe yaitu executable file untuk menjalankan program utama. Jika dipanggil, tampilannya akan seperti berikut.

Pada repository ini, sudah ada main.exe. Disarankan untuk langsung menjalankan saja (tidak perlu merepotkan diri untuk kompilasi ulang).

## Pembagian Tugas

<hr>

| Nama                        | Tugas                                                                                                                                                                          |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Maria Khelli                | ADT Mesin Karakter, ADT Adjacency Matrix, ADT Map, ADT Lokasi, ADT List Dinamis, ADT Mesin Konfigurasi, Command Map, Command New Game, Command Help                            |
| Mohamad Daffa Argakoesoemah | ADT Stack, ADT To Do, ADT In Progress, ADT Mesin Kata, Command To Do, Command In Progress                                                                                      |
| Bryan Amirul Husna          | ADT Pesanan, ADT Item, ADT Queue, Command Move, Command Pick Up, Command Drop Off, VIP Item (bonus)                                                                            |
| Frederik Imanuel Louis      | ADT Mobita, ADT Point, ADT List Statis, Command Buy, Command Inventory (+ Senter, bonus), Command Save Game, Command Load Game, Command Return to Sender (BONUS), Main Program |

## Daftar Fitur

- [x] Program utama
- [x] Move
- [x] Pick up (termasuk VIP Item)
- [x] Drop off
- [x] Map
- [x] To do list
- [x] In progress list
- [x] Buy
- [x] Inventory (termasuk Senter Pengecil)
- [x] Help
- [x] Save
- [x] Load
- [x] Balance
- [x] Return to sender
