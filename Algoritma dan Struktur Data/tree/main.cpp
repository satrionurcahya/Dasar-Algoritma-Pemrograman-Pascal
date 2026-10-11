// =====================================================
// TUGAS 7      : Sistem Data Mahasiswa
//                (Linked List + Binary Search Tree)
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

ListLL L;
BST    T;

void headerTabel() {
    cout << "=====================================================================\n";
    cout << left << setw(12) << "NIM"
         << setw(15) << "Nama"
         << setw(20) << "Program Studi"
         << setw(8)  << "IPK" << endl;
    cout << "=====================================================================\n";
}

// 1. TAMBAH MAHASISWA (sinkron LL + BST)
void tambahMahasiswa() {
    string nim, nama, prodi;
    double ipk;

    cout << "NIM           : "; getline(cin, nim);
    cout << "Nama          : "; getline(cin, nama);
    cout << "Program Studi : "; getline(cin, prodi);
    cout << "IPK (0-4)     : "; cin >> ipk; cin.ignore();

    if (ipk < 0 || ipk > 4.0) { cout << "IPK tidak valid!\n"; return; }
    if (isNIMExist(L, nim)) { cout << "NIM sudah terdaftar!\n"; return; }

    insertLast(L, createData(nim, nama, prodi, ipk));
    T.root = insertBST(T.root, createNodeBST(nim, nama, prodi, ipk));
    cout << "Mahasiswa berhasil ditambahkan ke LL dan BST.\n";
}

// 2. UBAH MAHASISWA (sinkron)
void ubahMahasiswa() {
    string nim, nama, prodi;
    double ipk;

    cout << "NIM yang akan diubah : "; getline(cin, nim);

    NodeLL*   p = searchNIM(L, nim);
    NodeTree* q = searchBST(T.root, nim);
    if (p == NULL || q == NULL) {
        cout << "Mahasiswa tidak ditemukan di salah satu struktur!\n";
        return;
    }

    cout << "Nama baru          : "; getline(cin, nama);
    cout << "Program Studi baru : "; getline(cin, prodi);
    cout << "IPK baru           : "; cin >> ipk; cin.ignore();

    p->info.nama = nama; p->info.programStudi = prodi; p->info.ipk = ipk;
    q->info.nama = nama; q->info.programStudi = prodi; q->info.ipk = ipk;
    cout << "Data berhasil diubah pada kedua struktur.\n";
}

// 3. HAPUS MAHASISWA (sinkron)
void hapusMahasiswa() {
    string nim;
    cout << "NIM yang akan dihapus : "; getline(cin, nim);

    NodeLL*   p = searchNIM(L, nim);
    NodeTree* q = searchBST(T.root, nim);
    if (p == NULL && q == NULL) { cout << "Mahasiswa tidak ditemukan!\n"; return; }

    deleteMahasiswa(L, nim);
    T.root = deleteBST(T.root, nim);
    cout << "Mahasiswa berhasil dihapus dari kedua struktur.\n";
}

// 4. CARI MAHASISWA
void cariMahasiswa() {
    string nim;
    cout << "NIM yang dicari : "; getline(cin, nim);

    NodeLL*   p = searchNIM(L, nim);
    NodeTree* q = searchBST(T.root, nim);

    cout << "\n--- Hasil Pencarian ---\n";
    if (p == NULL) cout << "Linked List : TIDAK ditemukan\n";
    else cout << "Linked List : Ditemukan (" << p->info.nama
              << ", IPK " << p->info.ipk << ")\n";
    if (q == NULL) cout << "BST         : TIDAK ditemukan\n";
    else cout << "BST         : Ditemukan (" << q->info.nama
              << ", IPK " << q->info.ipk << ")\n";
}

void tampilInOrder() {
    if (isEmptyBST(T)) { cout << "BST kosong.\n"; return; }
    cout << "\n--- BST InOrder (NIM menaik) ---\n";
    headerTabel(); inOrder(T.root);
    cout << "=====================================================================\n";
}

void tampilPreOrder() {
    if (isEmptyBST(T)) { cout << "BST kosong.\n"; return; }
    cout << "\n--- BST PreOrder ---\n";
    headerTabel(); preOrder(T.root);
    cout << "=====================================================================\n";
}

void tampilPostOrder() {
    if (isEmptyBST(T)) { cout << "BST kosong.\n"; return; }
    cout << "\n--- BST PostOrder ---\n";
    headerTabel(); postOrder(T.root);
    cout << "=====================================================================\n";
}

void tampilMinMax() {
    if (isEmptyBST(T)) { cout << "BST kosong.\n"; return; }
    NodeTree* mn = findMin(T.root);
    NodeTree* mx = findMax(T.root);
    cout << "\n--- NIM Terkecil & Terbesar ---\n";
    cout << "Terkecil : " << mn->info.nim << " (" << mn->info.nama << ")\n";
    cout << "Terbesar : " << mx->info.nim << " (" << mx->info.nama << ")\n";
}

void tampilStatistik() {
    cout << "\n--- Statistik ---\n";
    cout << "Jumlah mahasiswa (LL)  : " << countNode(L) << endl;
    cout << "Jumlah mahasiswa (BST) : " << countNodeBST(T.root) << endl;
    cout << "Jumlah daun BST        : " << countLeaf(T.root) << endl;
    cout << "Jumlah node internal   : " << countInternal(T.root) << endl;
    cout << "Tinggi BST             : " << heightBST(T.root) << endl;
    cout << "Rata-rata IPK (LL)     : " << fixed << setprecision(2)
         << averageIPK(L) << endl;
    cout << "Rata-rata IPK (BST)    : " << averageIPK_BST(T) << endl;
}

void cekKonsistensi() {
    int nLL  = countNode(L);
    int nBST = countNodeBST(T.root);

    cout << "\n--- Cek Konsistensi ---\n";
    cout << "Jumlah data di LL  : " << nLL << endl;
    cout << "Jumlah data di BST : " << nBST << endl;

    if (nLL != nBST) {
        cout << ">> TIDAK KONSISTEN (jumlah berbeda)!\n";
        return;
    }
    bool konsisten = true;
    NodeLL* p = L.First;
    while (p != NULL) {
        NodeTree* q = searchBST(T.root, p->info.nim);
        if (q == NULL ||
            q->info.nama         != p->info.nama ||
            q->info.programStudi != p->info.programStudi ||
            q->info.ipk          != p->info.ipk) {
            konsisten = false; break;
        }
        p = p->next;
    }
    cout << (konsisten ? ">> Data KONSISTEN.\n" : ">> Data TIDAK KONSISTEN!\n");
}

void isiDataContoh() {
    struct Data { string nim, nama, prodi; double ipk; };
    Data d[] = {
        {"2301005", "Andi",  "Informatika",      3.50},
        {"2301003", "Budi",  "Sistem Informasi", 3.75},
        {"2301007", "Citra", "Informatika",      3.20},
        {"2301002", "Dinda", "Teknik Komputer",  3.80},
        {"2301004", "Eko",   "Informatika",      3.40},
        {"2301006", "Farah", "Sistem Informasi", 3.65},
        {"2301008", "Galih", "Teknik Komputer",  3.25}
    };
    int n = sizeof(d) / sizeof(d[0]);
    for (int i = 0; i < n; i++) {
        if (!isNIMExist(L, d[i].nim)) {
            insertLast(L, createData(d[i].nim, d[i].nama, d[i].prodi, d[i].ipk));
            T.root = insertBST(T.root,
                     createNodeBST(d[i].nim, d[i].nama, d[i].prodi, d[i].ipk));
        }
    }
    cout << n << " data contoh berhasil dimasukkan.\n";
}

void tampilMenu() {
    cout << "\n========== SISTEM DATA MAHASISWA ==========\n";
    cout << "1.  Tambah Mahasiswa\n";
    cout << "2.  Ubah Data Mahasiswa\n";
    cout << "3.  Hapus Mahasiswa\n";
    cout << "4.  Cari Mahasiswa berdasarkan NIM\n";
    cout << "5.  Tampilkan Semua (Linked List)\n";
    cout << "6.  Tampilkan BST - InOrder\n";
    cout << "7.  Tampilkan BST - PreOrder\n";
    cout << "8.  Tampilkan BST - PostOrder\n";
    cout << "9.  Tampilkan NIM Terkecil & Terbesar\n";
    cout << "10. Statistik (Jumlah, Daun, Tinggi, IPK)\n";
    cout << "11. Cek Konsistensi LL & BST\n";
    cout << "12. Isi Data Contoh\n";
    cout << "13. Urutkan LL berdasarkan NIM\n";
    cout << "0.  Keluar\n";
    cout << "===========================================\n";
    cout << "Pilihan : ";
}

int main() {
    createList(L);
    createBST(T);

    int pilih;
    do {
        tampilMenu();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:  tambahMahasiswa();  break;
            case 2:  ubahMahasiswa();    break;
            case 3:  hapusMahasiswa();   break;
            case 4:  cariMahasiswa();    break;
            case 5:  viewAll(L);         break;
            case 6:  tampilInOrder();    break;
            case 7:  tampilPreOrder();   break;
            case 8:  tampilPostOrder();  break;
            case 9:  tampilMinMax();     break;
            case 10: tampilStatistik();  break;
            case 11: cekKonsistensi();   break;
            case 12: isiDataContoh();    break;
            case 13: sortByNIM(L);       break;
            case 0:  cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    deleteAllList(L);
    deleteAllBST(T.root);
    return 0;
}