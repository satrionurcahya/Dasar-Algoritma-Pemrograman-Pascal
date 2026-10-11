// =====================================================
// TUGAS 3      : Sistem Pengelolaan Aktivitas Akademik
//                (Circular Single & Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <string>
#include "bimbingan.h"
#include "presentasi.h"
using namespace std;

// =====================================================
// Menu Antrean Bimbingan
// =====================================================
void menuBimbingan(ListBimbingan &L, int &nomorTerakhir) {
    int pilih;
    do {
        cout << "\n===== ANTREAN BIMBINGAN AKADEMIK =====\n";
        cout << "1. Tambah Mahasiswa ke Antrean\n";
        cout << "2. Layani Mahasiswa Pertama\n";
        cout << "3. Cari Mahasiswa berdasarkan NIM\n";
        cout << "4. Tampilkan Seluruh Antrean\n";
        cout << "5. Hitung Jumlah Mahasiswa\n";
        cout << "6. Cek Apakah Antrean Kosong\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "======================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: {
                string nim, nama, keperluan;
                cout << "NIM       : "; getline(cin, nim);
                cout << "Nama      : "; getline(cin, nama);
                cout << "Keperluan : "; getline(cin, keperluan);
                nomorTerakhir++;
                NodeBimbingan* P = createDataBimbingan(nim, nama, keperluan, nomorTerakhir);
                insertLastBimbingan(L, P);
                cout << "Mahasiswa ditambahkan ke antrean dengan nomor "
                     << nomorTerakhir << ".\n";
                break;
            }
            case 2:
                deleteFirstBimbingan(L);
                break;
            case 3: {
                string nimCari;
                cout << "Masukkan NIM yang dicari : ";
                getline(cin, nimCari);
                if (searchNIM(L, nimCari))
                    cout << "NIM " << nimCari << " DITEMUKAN dalam antrean.\n";
                else
                    cout << "NIM " << nimCari << " TIDAK ditemukan.\n";
                break;
            }
            case 4:
                viewAllBimbingan(L);
                break;
            case 5:
                cout << "Jumlah mahasiswa dalam antrean : "
                     << countNodeBimbingan(L) << endl;
                break;
            case 6:
                cout << (isNullBimbingan(L) ? "Antrean KOSONG.\n"
                                             : "Antrean TIDAK kosong.\n");
                break;
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
}

// =====================================================
// Menu Jadwal Presentasi
// =====================================================
void menuPresentasi(ListPresentasi &L) {
    int pilih;
    do {
        cout << "\n===== JADWAL PRESENTASI KELOMPOK =====\n";
        cout << "1.  Tambah Kelompok di Awal\n";
        cout << "2.  Tambah Kelompok di Akhir\n";
        cout << "3.  Pindah ke Kelompok Berikutnya\n";
        cout << "4.  Pindah ke Kelompok Sebelumnya\n";
        cout << "5.  Cari Kelompok berdasarkan Kode\n";
        cout << "6.  Ubah Status Presentasi\n";
        cout << "7.  Hapus Kelompok berdasarkan Kode\n";
        cout << "8.  Tampilkan Seluruh Kelompok\n";
        cout << "9.  Hitung Jumlah Kelompok\n";
        cout << "10. Cek Apakah List Kosong\n";
        cout << "0.  Kembali ke Menu Utama\n";
        cout << "======================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
            case 2: {
                string kode, ketua, topik;
                cout << "Kode Kelompok : "; getline(cin, kode);
                cout << "Nama Ketua    : "; getline(cin, ketua);
                cout << "Topik         : "; getline(cin, topik);
                NodePresentasi* P = createDataPresentasi(kode, ketua, topik);
                if (pilih == 1)
                    insertFirstPresentasi(L, P);
                else
                    insertLastPresentasi(L, P);
                cout << "Kelompok berhasil ditambahkan.\n";
                break;
            }
            case 3:
                nextGroup(L);
                break;
            case 4:
                prevGroup(L);
                break;
            case 5: {
                string kode;
                cout << "Kode kelompok yang dicari : ";
                getline(cin, kode);
                if (searchKelompok(L, kode))
                    cout << "Kelompok " << kode << " DITEMUKAN.\n";
                else
                    cout << "Kelompok " << kode << " TIDAK ditemukan.\n";
                break;
            }
            case 6: {
                string kode, statusBaru;
                cout << "Kode Kelompok   : "; getline(cin, kode);
                cout << "Status baru (berlangsung/selesai) : ";
                getline(cin, statusBaru);
                if (statusBaru != "berlangsung" && statusBaru != "selesai") {
                    cout << "Status tidak valid!\n";
                    break;
                }
                updateStatus(L, kode, statusBaru);
                break;
            }
            case 7: {
                string kode;
                cout << "Kode kelompok yang akan dihapus : ";
                getline(cin, kode);
                deleteByKode(L, kode);
                break;
            }
            case 8:
                viewAllPresentasi(L);
                break;
            case 9:
                cout << "Jumlah kelompok dalam jadwal : "
                     << countNodePresentasi(L) << endl;
                break;
            case 10:
                cout << (isNullPresentasi(L) ? "List KOSONG.\n"
                                              : "List TIDAK kosong.\n");
                break;
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
}

// =====================================================
// PROGRAM UTAMA
// =====================================================
int main() {
    ListBimbingan  L1;
    ListPresentasi L2;

    createListBimbingan(L1);
    createListPresentasi(L2);

    int nomorTerakhir = 0;   // counter nomor antrean
    int pilih;

    do {
        cout << "\n=========== SISTEM AKADEMIK ===========\n";
        cout << "1. Kelola Antrean Bimbingan Akademik\n";
        cout << "2. Kelola Jadwal Presentasi Kelompok\n";
        cout << "0. Keluar\n";
        cout << "=======================================\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: menuBimbingan(L1, nomorTerakhir); break;
            case 2: menuPresentasi(L2); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    return 0;
}