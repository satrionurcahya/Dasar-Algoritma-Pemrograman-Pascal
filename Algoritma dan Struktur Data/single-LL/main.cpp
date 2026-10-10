// =====================================================
// TUGAS 1      : Single Linked List Data Mahasiswa
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include <string>
#include "mahasiswa.h"
using namespace std;

// =====================================================
// Fungsi bantu: input data mahasiswa dari keyboard
// =====================================================
Mahasiswa inputMahasiswa() {
    Mahasiswa mhs;
    cout << "Nama  : ";
    getline(cin, mhs.nama);
    cout << "NIM   : ";
    getline(cin, mhs.nim);
    cout << "IPK   : ";
    cin >> mhs.ipk;
    cin.ignore();
    return mhs;
}

// =====================================================
// Fungsi bantu: isi data awal (6 mahasiswa dari soal)
// =====================================================
void isiDataAwal(List &L) {
    // Data dimasukkan urut sesuai soal, tapi karena insertFirst
    // maka urutan di list jadi terbalik (Ali dulu, Budi terakhir)
    Mahasiswa arr[6] = {
        {"Budi",  "11030005", 3.30},
        {"David", "11030013", 3.71},
        {"Eko",   "11030012", 3.50},
        {"Caca",  "11030025", 4.00},
        {"Fuad",  "11030011", 3.40},
        {"Ali",   "11030034", 3.45}
    };

    for (int i = 0; i < 6; i++) {
        insertFirst(L, arr[i]);
    }
    cout << "Data awal berhasil dimasukkan.\n";
}

// =====================================================
// Menu utama
// =====================================================
void tampilMenu() {
    cout << "\n============ MENU LINKED LIST ============\n";
    cout << "1. Buat List Baru\n";
    cout << "2. Tambah Mahasiswa di Awal (insertFirst)\n";
    cout << "3. Hapus Mahasiswa Terakhir (deleteLast)\n";
    cout << "4. Cari Mahasiswa berdasarkan NIM (searchNIM)\n";
    cout << "5. Tampilkan Seluruh Data (viewAll)\n";
    cout << "6. Hitung Jumlah Mahasiswa (countNode)\n";
    cout << "7. Hapus Semua Data (deleteAll)\n";
    cout << "8. Isi Data Awal (6 Mahasiswa)\n";
    cout << "0. Keluar\n";
    cout << "==========================================\n";
}

// =====================================================
// PROGRAM UTAMA
// =====================================================
int main() {
    List L;
    createList(L);   // list kosong saat pertama jalan

    int pilih;
    string nimCari;

    do {
        tampilMenu();
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: {
                // Cek jika list masih berisi data
                if (L.First != NULL) {
                    char konfirmasi;
                    cout << "List masih berisi " << countNode(L)
                         << " data. Hapus dulu? (y/t): ";
                    cin >> konfirmasi;
                    cin.ignore();
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        deleteAll(L);
                        cout << "Data lama berhasil dihapus.\n";
                    } else {
                        cout << "Dibatalkan.\n";
                        break;
                    }
                }
                createList(L);
                cout << "List baru berhasil dibuat.\n";
                break;
            }
            case 2: {
                cout << "\n--- Input Data Mahasiswa ---\n";
                Mahasiswa mhs = inputMahasiswa();
                insertFirst(L, mhs);
                cout << "Data berhasil ditambahkan di awal list.\n";
                break;
            }
            case 3:
                deleteLast(L);
                break;
            case 4: {
                cout << "Masukkan NIM yang dicari : ";
                getline(cin, nimCari);
                if (searchNIM(L, nimCari))
                    cout << "NIM " << nimCari << " DITEMUKAN dalam list.\n";
                else
                    cout << "NIM " << nimCari << " TIDAK ditemukan.\n";
                break;
            }
            case 5:
                viewAll(L);
                break;
            case 6:
                cout << "Jumlah mahasiswa dalam list : "
                     << countNode(L) << " orang\n";
                break;
            case 7:
                deleteAll(L);
                cout << "Seluruh data berhasil dihapus.\n";
                break;
            case 8:
                isiDataAwal(L);
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    // Bersihkan memori sebelum keluar
    deleteAll(L);
    return 0;
}