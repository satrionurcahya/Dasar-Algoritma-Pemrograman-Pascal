// =====================================================
// TUGAS 2      : ADT Sistem Tapping Kehadiran Pegawai
//                (Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include <string>
#include "tapping.h"
using namespace std;

// =====================================================
// Menu utama
// =====================================================
void tampilMenu() {
    cout << "\n========= MENU TAPPING KEHADIRAN =========\n";
    cout << "1. Buat List Baru\n";
    cout << "2. Input Data Tapping\n";
    cout << "3. Tampilkan Rekap Kehadiran\n";
    cout << "4. Cari Pegawai berdasarkan ID\n";
    cout << "5. Tampilkan Jumlah Elemen\n";
    cout << "6. Cek Apakah List Kosong\n";
    cout << "7. Hapus Elemen Setelah Elemen Tertentu\n";
    cout << "8. Hapus Semua Data\n";
    cout << "9. Isi Data Contoh (dari soal)\n";
    cout << "0. Keluar\n";
    cout << "==========================================\n";
}

// =====================================================
// Isi data contoh dari soal
// =====================================================
void isiDataContoh(List &L) {
    struct DataContoh { string id; int jam; int menit; };
    DataContoh data[] = {
        {"ID001",  8, 45},
        {"ID003",  9, 10},
        {"ID001",  8, 30},
        {"ID007", 16, 40},
        {"ID001", 12, 27},
        {"ID003", 12, 15},
        {"ID001",  8, 35},
        {"ID001", 12, 20}
    };

    int jumlah = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < jumlah; i++) {
        Node* P = createData(data[i].id, data[i].jam, data[i].menit);
        insertElemen(L, P);
    }
    cout << "Data contoh berhasil dimasukkan.\n";
}

// =====================================================
// PROGRAM UTAMA
// =====================================================
int main() {
    List L;
    createList(L);

    int pilih;

    do {
        tampilMenu();
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: {
                if (!isNull(L)) {
                    char konfirmasi;
                    cout << "List masih berisi " << countElemen(L)
                         << " elemen. Hapus dulu? (y/t): ";
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
                string id;
                int jam, menit;

                cout << "ID Pegawai : ";
                getline(cin, id);
                cout << "Jam (0-23) : ";
                cin >> jam;
                cout << "Menit (0-59): ";
                cin >> menit;
                cin.ignore();

                if (jam < 0 || jam > 23 || menit < 0 || menit > 59) {
                    cout << "Waktu tidak valid!\n";
                    break;
                }

                Node* P = createData(id, jam, menit);
                insertElemen(L, P);
                cout << "Data tapping berhasil diproses.\n";
                break;
            }
            case 3:
                tampilData(L);
                break;
            case 4: {
                string idCari;
                cout << "Masukkan ID Pegawai : ";
                getline(cin, idCari);
                if (searchPegawai(L, idCari))
                    cout << "ID " << idCari << " DITEMUKAN dalam list.\n";
                else
                    cout << "ID " << idCari << " TIDAK ditemukan.\n";
                break;
            }
            case 5:
                cout << "Jumlah elemen dalam list : " << countElemen(L) << endl;
                break;
            case 6:
                if (isNull(L))
                    cout << "List KOSONG.\n";
                else
                    cout << "List TIDAK kosong (berisi "
                         << countElemen(L) << " elemen).\n";
                break;
            case 7: {
                string idAcuan;
                cout << "Masukkan ID pegawai sebagai acuan: ";
                getline(cin, idAcuan);

                // Cari node dengan ID tersebut
                Node* P = L.First;
                Node* target = NULL;
                while (P != NULL) {
                    if (P->data.idPegawai == idAcuan) {
                        target = P;
                        break;
                    }
                    P = P->Next;
                }
                if (target == NULL)
                    cout << "ID acuan tidak ditemukan.\n";
                else
                    deleteAfter(L, target);
                break;
            }
            case 8:
                deleteAll(L);
                cout << "Seluruh data berhasil dihapus.\n";
                break;
            case 9:
                isiDataContoh(L);
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    deleteAll(L);
    return 0;
}