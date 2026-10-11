// =====================================================
// TUGAS 4      : Sistem Informasi Akademik
//                (Multi Linked List - 1 to N & N to M)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <string>
#include "dosen.h"
#include "mahasiswa.h"
using namespace std;

// =====================================================
// MENU RELASI 1 TO N (DOSEN - MK)
// =====================================================
void menuDosen(ListDosen &L) {
    int pilih;
    do {
        cout << "\n====== RELASI 1 to N : DOSEN - MATA KULIAH ======\n";
        cout << "1. Tambah Dosen\n";
        cout << "2. Tambah Mata Kuliah ke Dosen\n";
        cout << "3. Tampilkan Semua Dosen & MK-nya\n";
        cout << "4. Cari Dosen berdasarkan NIDN\n";
        cout << "5. Cari MK pada Dosen\n";
        cout << "6. Hapus MK dari Dosen\n";
        cout << "7. Hapus Dosen (beserta MK-nya)\n";
        cout << "8. Hitung Jumlah Dosen\n";
        cout << "9. Hitung Jumlah MK Seorang Dosen\n";
        cout << "0. Kembali\n";
        cout << "=================================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: {
                string nidn, nama;
                cout << "NIDN : "; getline(cin, nidn);
                cout << "Nama : "; getline(cin, nama);
                insertDosen(L, createDosen(nidn, nama));
                break;
            }
            case 2: {
                string nidn, kode, nama;
                int sks;
                cout << "NIDN dosen : "; getline(cin, nidn);
                cout << "Kode MK    : "; getline(cin, kode);
                cout << "Nama MK    : "; getline(cin, nama);
                cout << "SKS        : "; cin >> sks; cin.ignore();
                insertMK(L, nidn, createMK1N(kode, nama, sks));
                break;
            }
            case 3:
                viewAllDosen(L);
                break;
            case 4: {
                string nidn;
                cout << "NIDN : "; getline(cin, nidn);
                NodeDosen* d = searchDosen(L, nidn);
                if (d != NULL)
                    cout << "Ditemukan: " << d->data.namaDosen << endl;
                else
                    cout << "Dosen tidak ditemukan.\n";
                break;
            }
            case 5: {
                string nidn, kode;
                cout << "NIDN : "; getline(cin, nidn);
                cout << "Kode MK : "; getline(cin, kode);
                NodeDosen* d = searchDosen(L, nidn);
                if (d == NULL) cout << "Dosen tidak ditemukan.\n";
                else if (searchMK(d, kode)) cout << "MK ditemukan.\n";
                else cout << "MK tidak ditemukan.\n";
                break;
            }
            case 6: {
                string nidn, kode;
                cout << "NIDN : "; getline(cin, nidn);
                cout << "Kode MK : "; getline(cin, kode);
                deleteMK(L, nidn, kode);
                break;
            }
            case 7: {
                string nidn;
                cout << "NIDN : "; getline(cin, nidn);
                deleteDosen(L, nidn);
                break;
            }
            case 8:
                cout << "Jumlah dosen : " << countDosen(L) << endl;
                break;
            case 9: {
                string nidn;
                cout << "NIDN : "; getline(cin, nidn);
                NodeDosen* d = searchDosen(L, nidn);
                if (d != NULL)
                    cout << "Jumlah MK : " << countMK(d) << endl;
                else
                    cout << "Dosen tidak ditemukan.\n";
                break;
            }
            case 0: break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
}

// =====================================================
// MENU RELASI N TO M (MAHASISWA - MK)
// =====================================================
void menuMahasiswa(ListMahasiswa &LM, ListMK &LMK) {
    int pilih;
    do {
        cout << "\n====== RELASI N to M : MAHASISWA - MK ======\n";
        cout << "1.  Tambah Mahasiswa\n";
        cout << "2.  Tambah Mata Kuliah\n";
        cout << "3.  Hubungkan Mahasiswa dengan MK\n";
        cout << "4.  Tampilkan Semua Mahasiswa\n";
        cout << "5.  Tampilkan Semua MK\n";
        cout << "6.  Tampilkan MK yang diambil seorang Mahasiswa\n";
        cout << "7.  Tampilkan Mahasiswa yang mengambil suatu MK\n";
        cout << "8.  Ubah Nilai\n";
        cout << "9.  Hapus Relasi\n";
        cout << "10. Hapus Mahasiswa\n";
        cout << "11. Hapus MK\n";
        cout << "12. Hitung Jumlah Mahasiswa\n";
        cout << "13. Hitung Jumlah MK\n";
        cout << "0.  Kembali\n";
        cout << "============================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: {
                string nim, nama;
                cout << "NIM  : "; getline(cin, nim);
                cout << "Nama : "; getline(cin, nama);
                insertMahasiswa(LM, createMahasiswa(nim, nama));
                break;
            }
            case 2: {
                string kode, nama;
                int sks;
                cout << "Kode MK : "; getline(cin, kode);
                cout << "Nama MK : "; getline(cin, nama);
                cout << "SKS     : "; cin >> sks; cin.ignore();
                insertMK(LMK, createMK_NM(kode, nama, sks));
                break;
            }
            case 3: {
                string nim, kode;
                cout << "NIM     : "; getline(cin, nim);
                cout << "Kode MK : "; getline(cin, kode);
                NodeMahasiswa* m = searchMahasiswa(LM, nim);
                NodeMK_NM*     q = searchMK(LMK, kode);
                if (m == NULL) cout << "Mahasiswa tidak ditemukan.\n";
                else if (q == NULL) cout << "MK tidak ditemukan.\n";
                else insertRelasi(LM, m, q);
                break;
            }
            case 4: viewAllMahasiswa(LM); break;
            case 5: viewAllMK(LMK); break;
            case 6: {
                string nim;
                cout << "NIM : "; getline(cin, nim);
                viewMKMahasiswa(LM, nim);
                break;
            }
            case 7: {
                string kode;
                cout << "Kode MK : "; getline(cin, kode);
                viewMahasiswaMK(LM, kode);
                break;
            }
            case 8: {
                string nim, kode;
                double nilai;
                cout << "NIM     : "; getline(cin, nim);
                cout << "Kode MK : "; getline(cin, kode);
                cout << "Nilai   : "; cin >> nilai; cin.ignore();
                updateNilai(LM, nim, kode, nilai);
                break;
            }
            case 9: {
                string nim, kode;
                cout << "NIM     : "; getline(cin, nim);
                cout << "Kode MK : "; getline(cin, kode);
                deleteRelasi(LM, nim, kode);
                break;
            }
            case 10: {
                string nim;
                cout << "NIM : "; getline(cin, nim);
                deleteMahasiswa(LM, nim);
                break;
            }
            case 11: {
                string kode;
                cout << "Kode MK : "; getline(cin, kode);
                deleteMK(LM, LMK, kode);
                break;
            }
            case 12:
                cout << "Jumlah mahasiswa : " << countMahasiswa(LM) << endl;
                break;
            case 13:
                cout << "Jumlah MK : " << countMK(LMK) << endl;
                break;
            case 0: break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
}

// =====================================================
// PROGRAM UTAMA
// =====================================================
int main() {
    ListDosen     LD;
    ListMahasiswa LM;
    ListMK        LMK;

    createListDosen(LD);
    createListMahasiswa(LM);
    createListMK(LMK);

    int pilih;
    do {
        cout << "\n========== SISTEM INFORMASI AKADEMIK ==========\n";
        cout << "1. Pengelolaan Dosen & Mata Kuliah (1 to N)\n";
        cout << "2. Pengelolaan Mahasiswa & MK (N to M)\n";
        cout << "0. Keluar\n";
        cout << "===============================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: menuDosen(LD); break;
            case 2: menuMahasiswa(LM, LMK); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    return 0;
}