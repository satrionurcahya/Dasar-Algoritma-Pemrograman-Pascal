// =====================================================
// TUGAS 2      : ADT Sistem Tapping Kehadiran Pegawai
//                (Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : tapping.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "tapping.h"
using namespace std;

// =====================================================
// 1. CREATE LIST - Inisialisasi list kosong
// =====================================================
void createList(List &L) {
    L.First = NULL;
    L.Last  = NULL;
}

// =====================================================
// 2. IS NULL - Cek apakah list kosong
// =====================================================
bool isNull(List L) {
    return (L.First == NULL);
}

// =====================================================
// 3. CREATE DATA - Buat node tapping baru
//    Status: < 12.00 = "masuk", >= 12.00 = "keluar"
// =====================================================
Node* createData(string idPegawai, int jam, int menit) {
    Node* newNode = new Node;

    newNode->data.idPegawai = idPegawai;
    newNode->data.jam       = jam;
    newNode->data.menit     = menit;
    newNode->data.count     = 1;

    // Tentukan status berdasarkan jam tapping
    if (jam < 12)
        newNode->data.status = "masuk";
    else
        newNode->data.status = "keluar";

    newNode->Prev = NULL;
    newNode->Next = NULL;

    return newNode;
}

// =====================================================
// 4. INSERT ELEMEN - Tambah baru atau update data lama
// =====================================================
void insertElemen(List &L, Node* P) {
    bool Found = false;
    Node* Q = L.First;

    // Cari kombinasi idPegawai + status yang sama
    while (Q != NULL && !Found) {
        if (Q->data.idPegawai == P->data.idPegawai &&
            Q->data.status    == P->data.status) {
            Found = true;
        } else {
            Q = Q->Next;
        }
    }

    if (Found) {
        // ---- Data kombinasi ID+status sudah ada, update ----
        if (Q->data.status == "masuk") {
            // Simpan waktu paling AWAL
            if (P->data.jam < Q->data.jam ||
               (P->data.jam == Q->data.jam && P->data.menit < Q->data.menit)) {
                Q->data.jam   = P->data.jam;
                Q->data.menit = P->data.menit;
            }
        } else {
            // status "keluar": simpan waktu paling AKHIR
            if (P->data.jam > Q->data.jam ||
               (P->data.jam == Q->data.jam && P->data.menit > Q->data.menit)) {
                Q->data.jam   = P->data.jam;
                Q->data.menit = P->data.menit;
            }
        }
        Q->data.count++;    // tambah count
        delete P;           // lepaskan node baru (tidak dipakai)
    } else {
        // ---- Kombinasi belum ada, tambah ke akhir list ----
        if (L.First == NULL) {
            // List kosong
            L.First = P;
            L.Last  = P;
            P->Prev = NULL;
            P->Next = NULL;
        } else {
            // Sisipkan di akhir
            P->Prev       = L.Last;
            P->Next       = NULL;
            L.Last->Next  = P;
            L.Last        = P;
        }
    }
}

// =====================================================
// 5. TAMPIL DATA - Rekap kehadiran per pegawai
// =====================================================
void tampilData(List L) {
    if (isNull(L)) {
        cout << "Belum ada data tapping.\n";
        return;
    }

    cout << "\n=======================================================================\n";
    cout << left << setw(10) << "ID"
         << setw(12) << "Masuk"
         << setw(12) << "Keluar"
         << setw(15) << "Lama (Jam:Menit)"
         << setw(10) << "Total" << endl;
    cout << "=======================================================================\n";

    Node* P = L.First;
    while (P != NULL) {
        // Cek apakah ID P sudah pernah ditampilkan sebelumnya
        bool sudahTampil = false;
        Node* cek = L.First;
        while (cek != P) {
            if (cek->data.idPegawai == P->data.idPegawai) {
                sudahTampil = true;
                break;
            }
            cek = cek->Next;
        }

        if (!sudahTampil) {
            // ---- Ini ID baru, tampilkan rekap ----
            string id = P->data.idPegawai;

            // Cari data masuk dan keluar untuk ID ini
            Node* masuk   = NULL;
            Node* keluar  = NULL;
            Node* scan    = L.First;
            while (scan != NULL) {
                if (scan->data.idPegawai == id) {
                    if (scan->data.status == "masuk")
                        masuk = scan;
                    else
                        keluar = scan;
                }
                scan = scan->Next;
            }

            // Format string waktu
            string strMasuk = "-";
            string strKeluar = "-";
            string strLama = "-";
            int total = 0;

            if (masuk != NULL) {
                strMasuk = to_string(masuk->data.jam) + ":" +
                          (masuk->data.menit < 10 ? "0" : "") +
                           to_string(masuk->data.menit);
                total += masuk->data.count;
            }

            if (keluar != NULL) {
                strKeluar = to_string(keluar->data.jam) + ":" +
                           (keluar->data.menit < 10 ? "0" : "") +
                            to_string(keluar->data.menit);
                total += keluar->data.count;
            }

            // Hitung lama masuk jika kedua status ada
            if (masuk != NULL && keluar != NULL) {
                int totalMenitMasuk  = masuk->data.jam  * 60 + masuk->data.menit;
                int totalMenitKeluar = keluar->data.jam * 60 + keluar->data.menit;
                int selisih = totalMenitKeluar - totalMenitMasuk;

                int lamaJam   = selisih / 60;
                int lamaMenit = selisih % 60;

                strLama = to_string(lamaJam) + ":" +
                         (lamaMenit < 10 ? "0" : "") +
                          to_string(lamaMenit);
            }

            cout << left << setw(10) << id
                 << setw(12) << strMasuk
                 << setw(12) << strKeluar
                 << setw(15) << strLama
                 << setw(10) << total << endl;
        }
        P = P->Next;
    }
    cout << "=======================================================================\n";
}

// =====================================================
// 6. COUNT ELEMEN - Hitung jumlah node
// =====================================================
int countElemen(List L) {
    int hitung = 0;
    Node* P = L.First;
    while (P != NULL) {
        hitung++;
        P = P->Next;
    }
    return hitung;
}

// =====================================================
// 7. SEARCH PEGAWAI - Sequential Search by ID
// =====================================================
bool searchPegawai(List L, string idCari) {
    if (isNull(L)) return false;

    Node* P = L.First;
    while (P != NULL) {
        if (P->data.idPegawai == idCari)
            return true;
        P = P->Next;
    }
    return false;
}

// =====================================================
// 8. DELETE AFTER - Hapus elemen setelah P
// =====================================================
void deleteAfter(List &L, Node* P) {
    // Cek list kosong
    if (isNull(L)) {
        cout << "List kosong, tidak ada elemen yang dapat dihapus.\n";
        return;
    }

    // Cek P valid
    if (P == NULL) {
        cout << "Address acuan tidak valid.\n";
        return;
    }

    // Cek apakah P benar-benar bagian dari list
    Node* cek = L.First;
    bool  valid = false;
    while (cek != NULL) {
        if (cek == P) { valid = true; break; }
        cek = cek->Next;
    }
    if (!valid) {
        cout << "Address acuan bukan bagian dari list.\n";
        return;
    }

    // Cek apakah ada elemen setelah P
    if (P->Next == NULL) {
        cout << "Tidak ada elemen setelah elemen acuan.\n";
        return;
    }

    // ---- Hapus elemen setelah P ----
    Node* Q = P->Next;         // elemen yang akan dihapus
    Node* R = Q->Next;         // elemen setelah Q

    cout << "Data yang dihapus: ID=" << Q->data.idPegawai
         << " Status=" << Q->data.status
         << " Jam=" << Q->data.jam << ":"
         << (Q->data.menit < 10 ? "0" : "") << Q->data.menit << endl;

    P->Next = R;
    if (R != NULL)
        R->Prev = P;
    else
        L.Last = P;   // Q adalah elemen terakhir, update Last

    delete Q;
}

// =====================================================
// 9. DELETE ALL - Hapus seluruh elemen
// =====================================================
void deleteAll(List &L) {
    Node* P = L.First;
    while (P != NULL) {
        Node* temp = P;
        P = P->Next;
        delete temp;
    }
    L.First = NULL;
    L.Last  = NULL;
}