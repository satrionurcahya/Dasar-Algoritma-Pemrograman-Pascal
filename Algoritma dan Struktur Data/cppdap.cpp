// =====================================================
// TUGAS 1      : Pengolahan Data Mahasiswa
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// Ketentuan    : Buatkan program dengan menerapkan DAP
// =====================================================

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 1000;   // Kapasitas maksimum mahasiswa

// ---------- TIPE DATA BENTUKAN ----------
struct Mahasiswa {
    string nrp;
    string nama;
    int ma, ki, fi, bi;   // nilai Matematika, Kimia, Fisika, Biologi
    int total;            // nilai total
    float rata;           // rata-rata
    char predikat;        // A / B / C / D
};

// Array untuk menampung data mahasiswa
Mahasiswa dataMhs[MAX];
int jumlah = 0;   // jumlah mahasiswa yang sudah diinput


// =====================================================
//                    FUNGSI
// =====================================================

// Fungsi menghitung nilai total
int hitungTotal(int ma, int ki, int fi, int bi) {
    return ma + ki + fi + bi;
}

// Fungsi menghitung rata-rata
float hitungRata(int total) {
    return total / 4.0;
}

// Fungsi menentukan predikat berdasarkan rata-rata
char tentukanPredikat(float rata) {
    if (rata >= 85 && rata <= 100)
        return 'A';
    else if (rata >= 75 && rata < 85)
        return 'B';
    else if (rata >= 60 && rata < 75)
        return 'C';
    else
        return 'D';
}


// =====================================================
//                    PROSEDUR
// =====================================================

// Prosedur input jumlah mahasiswa (dengan validasi)
void inputJumlah() {
    do {
        cout << "Masukkan jumlah mahasiswa (1-1000) : ";
        cin >> jumlah;
        if (jumlah < 1 || jumlah > MAX)
            cout << "Jumlah tidak valid! Masukkan lagi.\n";
    } while (jumlah < 1 || jumlah > MAX);
}

// Prosedur input data mahasiswa
void inputData() {
    inputJumlah();
    cin.ignore();   // membersihkan buffer setelah cin >> jumlah

    for (int i = 0; i < jumlah; i++) {
        cout << "\n--- Data Mahasiswa ke-" << (i + 1) << " ---\n";
        cout << "NRP   : ";
        getline(cin, dataMhs[i].nrp);
        cout << "Nama  : ";
        getline(cin, dataMhs[i].nama);

        // Input nilai dengan validasi 0-100
        int nilai[4];
        string mapel[4] = {"Matematika", "Kimia", "Fisika", "Biologi"};
        for (int j = 0; j < 4; j++) {
            do {
                cout << "Nilai " << mapel[j] << " (0-100) : ";
                cin >> nilai[j];
                if (nilai[j] < 0 || nilai[j] > 100)
                    cout << "Nilai tidak valid! Masukkan lagi.\n";
            } while (nilai[j] < 0 || nilai[j] > 100);
        }
        cin.ignore();

        dataMhs[i].ma = nilai[0];
        dataMhs[i].ki = nilai[1];
        dataMhs[i].fi = nilai[2];
        dataMhs[i].bi = nilai[3];

        // Hitung total, rata-rata, dan predikat
        dataMhs[i].total = hitungTotal(nilai[0], nilai[1], nilai[2], nilai[3]);
        dataMhs[i].rata  = hitungRata(dataMhs[i].total);
        dataMhs[i].predikat = tentukanPredikat(dataMhs[i].rata);
    }
    cout << "\nData berhasil diinput!\n";
}

// Prosedur menampilkan seluruh data mahasiswa
void tampilData() {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << "\n===================================================================\n";
    cout << left << setw(12) << "NRP"
         << setw(20) << "Nama"
         << setw(5)  << "Ma"
         << setw(5)  << "Ki"
         << setw(5)  << "Fi"
         << setw(5)  << "Bi"
         << setw(7)  << "Total"
         << setw(8)  << "Rata"
         << setw(9)  << "Predikat" << endl;
    cout << "===================================================================\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(12) << dataMhs[i].nrp
             << setw(20) << dataMhs[i].nama
             << setw(5)  << dataMhs[i].ma
             << setw(5)  << dataMhs[i].ki
             << setw(5)  << dataMhs[i].fi
             << setw(5)  << dataMhs[i].bi
             << setw(7)  << dataMhs[i].total
             << setw(8)  << fixed << setprecision(2) << dataMhs[i].rata
             << setw(9)  << dataMhs[i].predikat << endl;
    }
    cout << "===================================================================\n";
}

// Prosedur menampilkan total dan predikat tiap mahasiswa
void tampilTotalPredikat() {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << "\n--- Nilai Total dan Predikat ---\n";
    for (int i = 0; i < jumlah; i++) {
        cout << dataMhs[i].nama << " (NRP: " << dataMhs[i].nrp << ")"
             << " -> Total = " << dataMhs[i].total
             << ", Rata-rata = " << fixed << setprecision(2) << dataMhs[i].rata
             << ", Predikat = " << dataMhs[i].predikat << endl;
    }
}

// Prosedur Bubble Sort (descending berdasarkan total)
void bubbleSort() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            // Tukar jika total kiri < total kanan (agar turun)
            if (dataMhs[j].total < dataMhs[j + 1].total) {
                Mahasiswa temp = dataMhs[j];
                dataMhs[j] = dataMhs[j + 1];
                dataMhs[j + 1] = temp;
            }
        }
    }
    cout << "Data berhasil diurutkan dengan Bubble Sort (total descending).\n";
}

// Prosedur Selection Sort (descending berdasarkan total)
void selectionSort() {
    for (int i = 0; i < jumlah - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < jumlah; j++) {
            if (dataMhs[j].total > dataMhs[maxIdx].total)
                maxIdx = j;
        }
        if (maxIdx != i) {
            Mahasiswa temp = dataMhs[i];
            dataMhs[i] = dataMhs[maxIdx];
            dataMhs[maxIdx] = temp;
        }
    }
    cout << "Data berhasil diurutkan dengan Selection Sort (total descending).\n";
}

// Prosedur urutkan berdasarkan NRP ascending (untuk Binary Search)
void urutNRP() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (dataMhs[j].nrp > dataMhs[j + 1].nrp) {
                Mahasiswa temp = dataMhs[j];
                dataMhs[j] = dataMhs[j + 1];
                dataMhs[j + 1] = temp;
            }
        }
    }
}

// Fungsi Sequential Search berdasarkan NRP
int sequentialSearch(string nrpCari) {
    for (int i = 0; i < jumlah; i++) {
        if (dataMhs[i].nrp == nrpCari)
            return i;   // ditemukan, kembalikan indeks
    }
    return -1;   // tidak ditemukan
}

// Fungsi Binary Search berdasarkan NRP (data harus urut NRP ascending)
int binarySearch(string nrpCari) {
    int kiri = 0, kanan = jumlah - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (dataMhs[tengah].nrp == nrpCari)
            return tengah;
        else if (dataMhs[tengah].nrp < nrpCari)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }
    return -1;
}

// Prosedur menampilkan mahasiswa dengan total tertinggi
void tampilTertinggi() {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    int idxMax = 0;
    for (int i = 1; i < jumlah; i++) {
        if (dataMhs[i].total > dataMhs[idxMax].total)
            idxMax = i;
    }

    cout << "\n--- Mahasiswa dengan Nilai Total Tertinggi ---\n";
    cout << "NRP       : " << dataMhs[idxMax].nrp << endl;
    cout << "Nama      : " << dataMhs[idxMax].nama << endl;
    cout << "Total     : " << dataMhs[idxMax].total << endl;
    cout << "Rata-rata : " << fixed << setprecision(2) << dataMhs[idxMax].rata << endl;
    cout << "Predikat  : " << dataMhs[idxMax].predikat << endl;
}

// Prosedur menu utama
void tampilMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Input Data Mahasiswa\n";
    cout << "2. Tampilkan Data\n";
    cout << "3. Tampilkan Total & Predikat\n";
    cout << "4. Bubble Sort (Total Descending)\n";
    cout << "5. Selection Sort (Total Descending)\n";
    cout << "6. Sequential Search (NRP)\n";
    cout << "7. Binary Search (NRP)\n";
    cout << "8. Tampilkan Nilai Tertinggi\n";
    cout << "0. Keluar\n";
    cout << "==========================\n";
}


// =====================================================
//                  PROGRAM UTAMA
// =====================================================
int main() {
    int pilih;
    string nrpCari;

    do {
        tampilMenu();
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                inputData();
                break;
            case 2:
                tampilData();
                break;
            case 3:
                tampilTotalPredikat();
                break;
            case 4:
                bubbleSort();
                tampilData();
                break;
            case 5:
                selectionSort();
                tampilData();
                break;
            case 6: {
                cout << "Masukkan NRP yang dicari : ";
                getline(cin, nrpCari);
                int pos = sequentialSearch(nrpCari);
                if (pos != -1) {
                    cout << "Data ditemukan pada indeks ke-" << pos << endl;
                    cout << "Nama : " << dataMhs[pos].nama << endl;
                } else {
                    cout << "Data dengan NRP " << nrpCari << " TIDAK ditemukan.\n";
                }
                break;
            }
            case 7: {
                cout << "Masukkan NRP yang dicari : ";
                getline(cin, nrpCari);
                urutNRP();   // urutkan dulu berdasarkan NRP
                int pos = binarySearch(nrpCari);
                if (pos != -1) {
                    cout << "Data ditemukan pada indeks ke-" << pos << endl;
                    cout << "Nama : " << dataMhs[pos].nama << endl;
                } else {
                    cout << "Data dengan NRP " << nrpCari << " TIDAK ditemukan.\n";
                }
                break;
            }
            case 8:
                tampilTertinggi();
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    return 0;
}