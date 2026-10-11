// =====================================================
// TUGAS 4      : Multi Linked List - Relasi N to M
//                (Mahasiswa dan Mata Kuliah)
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
// CREATE LIST
// =====================================================
void createListMahasiswa(ListMahasiswa &L) {
    L.firstMahasiswa = NULL;
    L.lastMahasiswa  = NULL;
}

void createListMK(ListMK &L) {
    L.firstMK = NULL;
}

// =====================================================
// CREATE DATA
// =====================================================
NodeMahasiswa* createMahasiswa(string nim, string nama) {
    NodeMahasiswa* newNode = new NodeMahasiswa;
    newNode->data.nim           = nim;
    newNode->data.namaMahasiswa = nama;
    newNode->firstRelasi        = NULL;
    newNode->prevMahasiswa      = NULL;
    newNode->nextMahasiswa      = NULL;
    return newNode;
}

NodeMK_NM* createMK_NM(string kode, string nama, int sks) {
    NodeMK_NM* newNode = new NodeMK_NM;
    newNode->data.kodeMK = kode;
    newNode->data.namaMK = nama;
    newNode->data.sks    = sks;
    newNode->nextMK      = NULL;
    return newNode;
}

NodeRelasi* createRelasi(NodeMahasiswa* m, NodeMK_NM* mk) {
    NodeRelasi* newNode = new NodeRelasi;
    newNode->mahasiswa  = m;
    newNode->mataKuliah = mk;
    newNode->nilai      = 0;     // nilai awal = 0
    newNode->nextRelasi = NULL;
    return newNode;
}

// =====================================================
// INSERT MAHASISWA (akhir list, double linked non-circular)
// =====================================================
void insertMahasiswa(ListMahasiswa &L, NodeMahasiswa* P) {
    if (searchMahasiswa(L, P->data.nim) != NULL) {
        cout << "NIM " << P->data.nim << " sudah terdaftar!\n";
        delete P;
        return;
    }

    if (L.firstMahasiswa == NULL) {
        L.firstMahasiswa = P;
        L.lastMahasiswa  = P;
    } else {
        P->prevMahasiswa      = L.lastMahasiswa;
        L.lastMahasiswa->nextMahasiswa = P;
        L.lastMahasiswa       = P;
    }
    cout << "Mahasiswa " << P->data.namaMahasiswa << " berhasil ditambahkan.\n";
}

// =====================================================
// INSERT MK (circular single linked list)
// =====================================================
void insertMK(ListMK &L, NodeMK_NM* Q) {
    if (searchMK(L, Q->data.kodeMK) != NULL) {
        cout << "MK " << Q->data.kodeMK << " sudah terdaftar!\n";
        delete Q;
        return;
    }

    if (L.firstMK == NULL) {
        L.firstMK = Q;
        Q->nextMK = Q;    // circular ke diri sendiri
    } else {
        NodeMK_NM* last = L.firstMK;
        while (last->nextMK != L.firstMK)
            last = last->nextMK;

        last->nextMK = Q;
        Q->nextMK    = L.firstMK;
    }
    cout << "MK " << Q->data.namaMK << " berhasil ditambahkan.\n";
}

// =====================================================
// INSERT RELASI
// =====================================================
void insertRelasi(ListMahasiswa &L, NodeMahasiswa* P, NodeMK_NM* Q) {
    if (P == NULL || Q == NULL) {
        cout << "Data mahasiswa atau MK tidak valid!\n";
        return;
    }
    if (searchRelasi(P, Q->data.kodeMK)) {
        cout << "Relasi " << P->data.nim << " - " << Q->data.kodeMK
             << " sudah ada!\n";
        return;
    }

    NodeRelasi* R = createRelasi(P, Q);

    // Insert di akhir list relasi milik mahasiswa
    if (P->firstRelasi == NULL) {
        P->firstRelasi = R;
    } else {
        NodeRelasi* last = P->firstRelasi;
        while (last->nextRelasi != NULL)
            last = last->nextRelasi;
        last->nextRelasi = R;
    }
    cout << "Relasi berhasil ditambahkan.\n";
}

// =====================================================
// SEARCH
// =====================================================
NodeMahasiswa* searchMahasiswa(ListMahasiswa L, string nim) {
    NodeMahasiswa* P = L.firstMahasiswa;
    while (P != NULL) {
        if (P->data.nim == nim) return P;
        P = P->nextMahasiswa;
    }
    return NULL;
}

NodeMK_NM* searchMK(ListMK L, string kodeMK) {
    if (L.firstMK == NULL) return NULL;

    NodeMK_NM* P = L.firstMK;
    do {
        if (P->data.kodeMK == kodeMK) return P;
        P = P->nextMK;
    } while (P != L.firstMK);

    return NULL;
}

bool searchRelasi(NodeMahasiswa* m, string kodeMK) {
    if (m == NULL) return false;
    NodeRelasi* R = m->firstRelasi;
    while (R != NULL) {
        if (R->mataKuliah->data.kodeMK == kodeMK) return true;
        R = R->nextRelasi;
    }
    return false;
}

// =====================================================
// UPDATE NILAI
// =====================================================
void updateNilai(ListMahasiswa &L, string nim, string kodeMK, double nilaiBaru) {
    NodeMahasiswa* m = searchMahasiswa(L, nim);
    if (m == NULL) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
        return;
    }

    NodeRelasi* R = m->firstRelasi;
    while (R != NULL) {
        if (R->mataKuliah->data.kodeMK == kodeMK) {
            R->nilai = nilaiBaru;
            cout << "Nilai berhasil diubah menjadi " << nilaiBaru << ".\n";
            return;
        }
        R = R->nextRelasi;
    }
    cout << "Mahasiswa belum mengambil MK " << kodeMK << ".\n";
}

// =====================================================
// VIEW ALL MAHASISWA
// =====================================================
void viewAllMahasiswa(ListMahasiswa L) {
    if (L.firstMahasiswa == NULL) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    NodeMahasiswa* P = L.firstMahasiswa;
    int no = 1;
    while (P != NULL) {
        cout << no++ << ". " << P->data.nim << " - "
             << P->data.namaMahasiswa << endl;
        P = P->nextMahasiswa;
    }
}

// =====================================================
// VIEW ALL MK
// =====================================================
void viewAllMK(ListMK L) {
    if (L.firstMK == NULL) {
        cout << "Belum ada data mata kuliah.\n";
        return;
    }

    NodeMK_NM* P = L.firstMK;
    int no = 1;
    do {
        cout << no++ << ". " << P->data.kodeMK << " - "
             << P->data.namaMK << " (" << P->data.sks << " SKS)" << endl;
        P = P->nextMK;
    } while (P != L.firstMK);
}

// =====================================================
// VIEW MK YANG DIAMBIL SEORANG MAHASISWA
// =====================================================
void viewMKMahasiswa(ListMahasiswa L, string nim) {
    NodeMahasiswa* m = searchMahasiswa(L, nim);
    if (m == NULL) {
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }

    cout << "\nMahasiswa : " << m->data.namaMahasiswa
         << " (NIM " << m->data.nim << ")\n";
    cout << "Mata Kuliah:\n";

    if (m->firstRelasi == NULL) {
        cout << "  (Belum mengambil mata kuliah)\n";
        return;
    }

    NodeRelasi* R = m->firstRelasi;
    while (R != NULL) {
        cout << "  - " << R->mataKuliah->data.kodeMK << " "
             << R->mataKuliah->data.namaMK
             << ", Nilai: " << fixed << setprecision(1) << R->nilai << endl;
        R = R->nextRelasi;
    }
}

// =====================================================
// VIEW MAHASISWA YANG MENGAMBIL SUATU MK
// =====================================================
void viewMahasiswaMK(ListMahasiswa L, string kodeMK) {
    // Cari dulu apakah MK ada
    bool adaMK = false;
    NodeMahasiswa* P = L.firstMahasiswa;
    while (P != NULL) {
        NodeRelasi* R = P->firstRelasi;
        while (R != NULL) {
            if (R->mataKuliah->data.kodeMK == kodeMK) {
                if (!adaMK) {
                    cout << "\nMata Kuliah : " << R->mataKuliah->data.kodeMK
                         << " " << R->mataKuliah->data.namaMK << endl;
                    cout << "Mahasiswa:\n";
                    adaMK = true;
                }
                cout << "  - " << P->data.namaMahasiswa
                     << ", NIM " << P->data.nim
                     << ", Nilai: " << fixed << setprecision(1)
                     << R->nilai << endl;
            }
            R = R->nextRelasi;
        }
        P = P->nextMahasiswa;
    }

    if (!adaMK) cout << "Belum ada mahasiswa yang mengambil MK ini.\n";
}

// =====================================================
// DELETE RELASI
// =====================================================
void deleteRelasi(ListMahasiswa &L, string nim, string kodeMK) {
    NodeMahasiswa* m = searchMahasiswa(L, nim);
    if (m == NULL) {
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }

    NodeRelasi* R = m->firstRelasi;
    NodeRelasi* prev = NULL;

    while (R != NULL && R->mataKuliah->data.kodeMK != kodeMK) {
        prev = R;
        R = R->nextRelasi;
    }

    if (R == NULL) {
        cout << "Relasi tidak ditemukan.\n";
        return;
    }

    if (prev == NULL)
        m->firstRelasi = R->nextRelasi;
    else
        prev->nextRelasi = R->nextRelasi;

    cout << "Relasi berhasil dihapus.\n";
    delete R;
}

// =====================================================
// DELETE MAHASISWA beserta relasinya
// =====================================================
void deleteMahasiswa(ListMahasiswa &L, string nim) {
    NodeMahasiswa* m = searchMahasiswa(L, nim);
    if (m == NULL) {
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }

    // Hapus seluruh relasi milik mahasiswa ini
    NodeRelasi* R = m->firstRelasi;
    while (R != NULL) {
        NodeRelasi* temp = R;
        R = R->nextRelasi;
        delete temp;
    }

    // Hapus dari list mahasiswa
    if (m->prevMahasiswa == NULL)
        L.firstMahasiswa = m->nextMahasiswa;
    else
        m->prevMahasiswa->nextMahasiswa = m->nextMahasiswa;

    if (m->nextMahasiswa == NULL)
        L.lastMahasiswa = m->prevMahasiswa;
    else
        m->nextMahasiswa->prevMahasiswa = m->prevMahasiswa;

    cout << "Mahasiswa " << m->data.namaMahasiswa << " berhasil dihapus.\n";
    delete m;
}

// =====================================================
// DELETE MK beserta seluruh relasinya
// =====================================================
void deleteMK(ListMahasiswa &L, ListMK &LMK, string kodeMK) {
    if (LMK.firstMK == NULL) {
        cout << "Belum ada MK.\n";
        return;
    }

    // Cari node MK
    NodeMK_NM* Q = searchMK(LMK, kodeMK);
    if (Q == NULL) {
        cout << "MK tidak ditemukan.\n";
        return;
    }

    // Hapus semua relasi yang menunjuk ke MK ini
    NodeMahasiswa* m = L.firstMahasiswa;
    while (m != NULL) {
        NodeRelasi* R = m->firstRelasi;
        NodeRelasi* prev = NULL;
        while (R != NULL) {
            if (R->mataKuliah == Q) {
                NodeRelasi* hapus = R;
                if (prev == NULL)
                    m->firstRelasi = R->nextRelasi;
                else
                    prev->nextRelasi = R->nextRelasi;
                R = R->nextRelasi;
                delete hapus;
            } else {
                prev = R;
                R = R->nextRelasi;
            }
        }
        m = m->nextMahasiswa;
    }

    // Hapus MK dari list circular
    if (Q->nextMK == Q) {
        LMK.firstMK = NULL;
    } else {
        NodeMK_NM* last = LMK.firstMK;
        while (last->nextMK != Q)
            last = last->nextMK;
        if (Q == LMK.firstMK)
            LMK.firstMK = Q->nextMK;
        last->nextMK = Q->nextMK;
    }

    cout << "MK " << Q->data.namaMK << " berhasil dihapus.\n";
    delete Q;
}

// =====================================================
// COUNT
// =====================================================
int countMahasiswa(ListMahasiswa L) {
    int hitung = 0;
    NodeMahasiswa* P = L.firstMahasiswa;
    while (P != NULL) {
        hitung++;
        P = P->nextMahasiswa;
    }
    return hitung;
}

int countMK(ListMK L) {
    if (L.firstMK == NULL) return 0;
    int hitung = 0;
    NodeMK_NM* P = L.firstMK;
    do {
        hitung++;
        P = P->nextMK;
    } while (P != L.firstMK);
    return hitung;
}

int countMKMahasiswa(NodeMahasiswa* m) {
    if (m == NULL) return 0;
    int hitung = 0;
    NodeRelasi* R = m->firstRelasi;
    while (R != NULL) {
        hitung++;
        R = R->nextRelasi;
    }
    return hitung;
}

int countMahasiswaMK(ListMahasiswa L, string kodeMK) {
    int hitung = 0;
    NodeMahasiswa* P = L.firstMahasiswa;
    while (P != NULL) {
        NodeRelasi* R = P->firstRelasi;
        while (R != NULL) {
            if (R->mataKuliah->data.kodeMK == kodeMK)
                hitung++;
            R = R->nextRelasi;
        }
        P = P->nextMahasiswa;
    }
    return hitung;
}