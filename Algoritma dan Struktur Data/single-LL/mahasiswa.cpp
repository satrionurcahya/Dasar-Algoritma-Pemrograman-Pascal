// =====================================================
// TUGAS 1      : Single Linked List Data Mahasiswa
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : mahasiswa.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "mahasiswa.h"
using namespace std;

// =====================================================
// 1. CREATE LIST - Inisialisasi list kosong
// =====================================================
void createList(List &L) {
    L.First = NULL;   // First menunjuk ke NIL
}

// =====================================================
// 2. INSERT FIRST - Tambah data di awal list
// =====================================================
void insertFirst(List &L, Mahasiswa mhs) {
    // 1. Buat node baru
    Node* newNode = new Node;

    // 2. Isi data mahasiswa ke node baru
    newNode->data = mhs;

    // 3. Node baru menunjuk ke node pertama sebelumnya
    newNode->next = L.First;

    // 4. Update First agar menunjuk ke node baru
    L.First = newNode;
}

// =====================================================
// 3. DELETE LAST - Hapus node terakhir
// =====================================================
void deleteLast(List &L) {
    // Kondisi 1: list kosong
    if (L.First == NULL) {
        cout << "List kosong, tidak ada data yang dapat dihapus.\n";
        return;
    }

    // Kondisi 2: list hanya memiliki 1 node
    if (L.First->next == NULL) {
        cout << "Data yang dihapus: "
             << L.First->data.nama << " (" << L.First->data.nim << ")\n";
        delete L.First;
        L.First = NULL;
        return;
    }

    // Kondisi 3: list memiliki lebih dari 1 node
    Node* curr = L.First;
    Node* prev = NULL;

    // Telusuri sampai node sebelum terakhir
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    // Tampilkan info mahasiswa yang dihapus
    cout << "Data yang dihapus: "
         << curr->data.nama << " (" << curr->data.nim << ")\n";

    // Hapus node terakhir
    prev->next = NULL;
    delete curr;
}

// =====================================================
// 4. SEARCH NIM - Sequential Search berdasarkan NIM
// =====================================================
bool searchNIM(List L, string nimCari) {
    // Jika list kosong, langsung kembalikan FALSE
    if (L.First == NULL) return false;

    Node* curr = L.First;
    while (curr != NULL) {
        if (curr->data.nim == nimCari)
            return true;
        curr = curr->next;
    }
    return false;
}

// =====================================================
// 5. VIEW ALL - Tampilkan seluruh data mahasiswa
// =====================================================
void viewAll(List L) {
    if (L.First == NULL) {
        cout << "List belum memiliki data.\n";
        return;
    }

    cout << "\n==================================================================\n";
    cout << left << setw(5)  << "No"
         << setw(15) << "Nama"
         << setw(15) << "NIM"
         << setw(8)  << "IPK" << endl;
    cout << "==================================================================\n";

    Node* curr = L.First;   // pakai pointer bantu, First tidak berubah
    int no = 1;
    while (curr != NULL) {
        cout << left << setw(5)  << no++
             << setw(15) << curr->data.nama
             << setw(15) << curr->data.nim
             << fixed << setprecision(2) << setw(8) << curr->data.ipk << endl;
        curr = curr->next;
    }
    cout << "==================================================================\n";
}

// =====================================================
// 6. COUNT NODE - Hitung jumlah node
// =====================================================
int countNode(List L) {
    int hitung = 0;
    Node* curr = L.First;
    while (curr != NULL) {
        hitung++;
        curr = curr->next;
    }
    return hitung;
}

// =====================================================
// 7. DELETE ALL - Hapus seluruh node
// =====================================================
void deleteAll(List &L) {
    Node* curr = L.First;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;   // lepaskan memori
    }
    L.First = NULL;
}