// =====================================================
// TUGAS 3      : Sistem Pengelolaan Aktivitas Akademik
//                (Circular Single Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : bimbingan.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "bimbingan.h"
using namespace std;

// =====================================================
// 1. CREATE LIST - Inisialisasi list kosong
// =====================================================
void createListBimbingan(ListBimbingan &L) {
    L.First = NULL;
}

// =====================================================
// 2. IS NULL - Cek apakah list kosong
// =====================================================
bool isNullBimbingan(ListBimbingan L) {
    return (L.First == NULL);
}

// =====================================================
// 3. CREATE DATA - Buat node mahasiswa baru
// =====================================================
NodeBimbingan* createDataBimbingan(string nim, string nama, string keperluan, int noAntrean) {
    NodeBimbingan* newNode = new NodeBimbingan;

    newNode->data.nim          = nim;
    newNode->data.nama         = nama;
    newNode->data.keperluan    = keperluan;
    newNode->data.nomorAntrean = noAntrean;
    newNode->Next              = NULL;

    return newNode;
}

// =====================================================
// 4. INSERT LAST - Tambah mahasiswa di akhir antrean
// =====================================================
void insertLastBimbingan(ListBimbingan &L, NodeBimbingan* P) {
    if (L.First == NULL) {
        // List kosong: node baru menunjuk ke dirinya sendiri
        L.First = P;
        P->Next = P;
    } else {
        // Cari elemen terakhir (yang Next-nya menunjuk ke First)
        NodeBimbingan* last = L.First;
        while (last->Next != L.First) {
            last = last->Next;
        }

        // Sisipkan P setelah last
        last->Next = P;
        P->Next    = L.First;   // tetap circular
    }
}

// =====================================================
// 5. DELETE FIRST - Layani mahasiswa pertama (hapus)
// =====================================================
void deleteFirstBimbingan(ListBimbingan &L) {
    if (L.First == NULL) {
        cout << "Antrean kosong, tidak ada mahasiswa yang bisa dilayani.\n";
        return;
    }

    NodeBimbingan* hapus = L.First;

    if (L.First->Next == L.First) {
        // Hanya ada satu elemen
        cout << "Mahasiswa yang dilayani: "
             << hapus->data.nama << " (" << hapus->data.nim << ")\n";
        L.First = NULL;
        delete hapus;
    } else {
        // Ada beberapa elemen
        // Cari elemen terakhir supaya Next-nya diarahkan ke First baru
        NodeBimbingan* last = L.First;
        while (last->Next != L.First) {
            last = last->Next;
        }

        cout << "Mahasiswa yang dilayani: "
             << hapus->data.nama << " (" << hapus->data.nim << ")\n";

        L.First   = L.First->Next;   // First pindah ke elemen berikutnya
        last->Next = L.First;         // update circular

        delete hapus;
    }
}

// =====================================================
// 6. SEARCH NIM - Sequential Search
// =====================================================
bool searchNIM(ListBimbingan L, string nimCari) {
    if (L.First == NULL) return false;

    NodeBimbingan* P = L.First;
    do {
        if (P->data.nim == nimCari) return true;
        P = P->Next;
    } while (P != L.First);

    return false;
}

// =====================================================
// 7. VIEW ALL - Tampilkan seluruh antrean
// =====================================================
void viewAllBimbingan(ListBimbingan L) {
    if (L.First == NULL) {
        cout << "Antrean bimbingan masih kosong.\n";
        return;
    }

    cout << "\n====================================================================\n";
    cout << left << setw(8)  << "No"
         << setw(15) << "NIM"
         << setw(20) << "Nama"
         << setw(30) << "Keperluan" << endl;
    cout << "====================================================================\n";

    NodeBimbingan* P = L.First;
    do {
        cout << left << setw(8)  << P->data.nomorAntrean
             << setw(15) << P->data.nim
             << setw(20) << P->data.nama
             << setw(30) << P->data.keperluan << endl;
        P = P->Next;
    } while (P != L.First);

    cout << "====================================================================\n";
}

// =====================================================
// 8. COUNT NODE - Hitung jumlah mahasiswa
// =====================================================
int countNodeBimbingan(ListBimbingan L) {
    if (L.First == NULL) return 0;

    int hitung = 0;
    NodeBimbingan* P = L.First;
    do {
        hitung++;
        P = P->Next;
    } while (P != L.First);

    return hitung;
}