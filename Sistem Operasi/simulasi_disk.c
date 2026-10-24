/* =====================================================
 * TUGAS 6      : Simulasi Penjadwalan Disk (FCFS, SCAN, C-SCAN)
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : simulasi_disk.c
 * Compile      : gcc -Wall -Wextra -std=c11 simulasi_disk.c -o simulasi_disk
 * Run          : ./simulasi_disk
 * ===================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

/* =====================================================
 * VARIABEL GLOBAL
 * ===================================================== */
int permintaan[MAX];
int n_permintaan;
int head_awal;
int min_cylinder = 0;
int max_cylinder = 199;
int arah_awal; /* 1 = Kanan (lebih besar), 0 = Kiri (lebih kecil) */

/* =====================================================
 * FUNGSI BANTU
 * ===================================================== */
void garis() {
    printf("=================================================================\n");
}

void inputPermintaan() {
    int pilihan;
    garis();
    printf("  INPUT DATA PENJADWALAN DISK\n");
    garis();
    printf("1. Gunakan data default (8 permintaan, head=53, kanan)\n");
    printf("2. Input manual\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        n_permintaan = 8;
        int data[] = {98, 183, 37, 122, 14, 124, 65, 67};
        for (int i = 0; i < n_permintaan; i++) permintaan[i] = data[i];
        head_awal = 53;
        min_cylinder = 0;
        max_cylinder = 199;
        arah_awal = 1; /* Kanan */
        printf("Data default berhasil dimuat.\n");
    } else {
        printf("Jumlah permintaan disk: ");
        if (scanf("%d", &n_permintaan) != 1 || n_permintaan <= 0 || n_permintaan > MAX) {
            printf("Jumlah tidak valid!\n");
            exit(1);
        }
        printf("Masukkan nomor silinder permintaan (pisahkan spasi):\n");
        for (int i = 0; i < n_permintaan; i++) {
            if (scanf("%d", &permintaan[i]) != 1 || permintaan[i] < 0) {
                printf("Input tidak valid!\n");
                exit(1);
            }
        }
        printf("Posisi awal head: ");
        scanf("%d", &head_awal);
        printf("Batas minimum silinder (0): ");
        scanf("%d", &min_cylinder);
        printf("Batas maksimum silinder (199): ");
        scanf("%d", &max_cylinder);
        printf("Arah awal (1 = Kanan, 0 = Kiri): ");
        scanf("%d", &arah_awal);
        
        /* Validasi */
        if (head_awal < min_cylinder || head_awal > max_cylinder) {
            printf("Posisi head di luar batas!\n");
            exit(1);
        }
        for (int i = 0; i < n_permintaan; i++) {
            if (permintaan[i] < min_cylinder || permintaan[i] > max_cylinder) {
                printf("Permintaan %d di luar batas!\n", permintaan[i]);
                exit(1);
            }
        }
    }
}

void tampilkanUrutan(int urutan[], int n, const char* nama_algo, int total_movement) {
    garis();
    printf("  HASIL - %s\n", nama_algo);
    garis();
    printf("Urutan pelayanan: ");
    for (int i = 0; i < n; i++) {
        printf("%d", urutan[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");
    printf("Total pergerakan head: %d\n", total_movement);
    printf("Rata-rata pergerakan : %.2f\n\n", (float)total_movement / n_permintaan);
}

/* =====================================================
 * 1. ALGORITMA FCFS
 * ===================================================== */
void simulasiFCFS() {
    int head = head_awal;
    int total_movement = 0;
    int urutan[MAX];
    
    for (int i = 0; i < n_permintaan; i++) {
        urutan[i] = permintaan[i];
        total_movement += abs(head - permintaan[i]);
        head = permintaan[i];
    }
    tampilkanUrutan(urutan, n_permintaan, "FCFS (First Come First Served)", total_movement);
}

/* =====================================================
 * FUNGSI SORT UNTUK SCAN & C-SCAN
 * ===================================================== */
void sortAsc(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }
}

/* =====================================================
 * 2. ALGORITMA SCAN (Algoritma Elevator)
 * ===================================================== */
void simulasiSCAN() {
    int head = head_awal;
    int total_movement = 0;
    int urutan[MAX];
    int idx = 0;

    /* Salin dan urutkan */
    int temp[MAX];
    for (int i = 0; i < n_permintaan; i++) temp[i] = permintaan[i];
    sortAsc(temp, n_permintaan);

    /* Cari index pemisah berdasarkan posisi head */
    int split = 0;
    while (split < n_permintaan && temp[split] < head) split++;

    if (arah_awal == 1) {
        /* Bergerak ke Kanan */
        for (int i = split; i < n_permintaan; i++) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
        /* Capai ujung kanan */
        if (head != max_cylinder) {
            total_movement += abs(head - max_cylinder);
            head = max_cylinder;
        }
        /* Balik ke Kiri */
        for (int i = split - 1; i >= 0; i--) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
    } else {
        /* Bergerak ke Kiri */
        for (int i = split - 1; i >= 0; i--) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
        /* Capai ujung kiri */
        if (head != min_cylinder) {
            total_movement += abs(head - min_cylinder);
            head = min_cylinder;
        }
        /* Balik ke Kanan */
        for (int i = split; i < n_permintaan; i++) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
    }
    tampilkanUrutan(urutan, n_permintaan, "SCAN", total_movement);
}

/* =====================================================
 * 3. ALGORITMA C-SCAN (Circular SCAN)
 * ===================================================== */
void simulasiCSCAN() {
    int head = head_awal;
    int total_movement = 0;
    int urutan[MAX];
    int idx = 0;

    int temp[MAX];
    for (int i = 0; i < n_permintaan; i++) temp[i] = permintaan[i];
    sortAsc(temp, n_permintaan);

    int split = 0;
    while (split < n_permintaan && temp[split] < head) split++;

    if (arah_awal == 1) {
        /* Bergerak ke Kanan, layani yang >= head */
        for (int i = split; i < n_permintaan; i++) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
        /* Capai ujung kanan */
        if (head != max_cylinder) {
            total_movement += abs(head - max_cylinder);
            head = max_cylinder;
        }
        /* Jumper ke ujung kiri (tetap dihitung) */
        total_movement += abs(max_cylinder - min_cylinder);
        head = min_cylinder;
        /* Lanjut layani sisa di Kiri (tapi arah gerak tetap KANAN) */
        for (int i = 0; i < split; i++) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
    } else {
        /* Bergerak ke Kiri, layani yang < head */
        for (int i = split - 1; i >= 0; i--) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
        /* Capai ujung kiri */
        if (head != min_cylinder) {
            total_movement += abs(head - min_cylinder);
            head = min_cylinder;
        }
        /* Jumper ke ujung kanan (tetap dihitung) */
        total_movement += abs(min_cylinder - max_cylinder);
        head = max_cylinder;
        /* Lanjut layani sisa di Kanan */
        for (int i = n_permintaan - 1; i >= split; i--) {
            urutan[idx++] = temp[i];
            total_movement += abs(head - temp[i]);
            head = temp[i];
        }
    }
    tampilkanUrutan(urutan, n_permintaan, "C-SCAN", total_movement);
}

/* =====================================================
 * 4. PERBANDINGAN
 * ===================================================== */
void tampilkanPerbandingan() {
    garis();
    printf("  TABEL PERBANDINGAN ALGORITMA\n");
    garis();
    printf("%-15s | %-20s | %-20s\n", "Algoritma", "Total Pergerakan", "Rata-rata Pergerakan");
    printf("----------------|----------------------|---------------------\n");

    /* FCFS */
    int h = head_awal, mv = 0;
    for (int i = 0; i < n_permintaan; i++) { mv += abs(h - permintaan[i]); h = permintaan[i]; }
    printf("%-15s | %-20d | %-20.2f\n", "FCFS", mv, (float)mv / n_permintaan);

    /* SCAN */
    h = head_awal; mv = 0;
    int temp[MAX]; for (int i = 0; i < n_permintaan; i++) temp[i] = permintaan[i];
    sortAsc(temp, n_permintaan);
    int split = 0; while (split < n_permintaan && temp[split] < h) split++;
    if (arah_awal == 1) {
        for (int i = split; i < n_permintaan; i++) { mv += abs(h - temp[i]); h = temp[i]; }
        if (h != max_cylinder) { mv += abs(h - max_cylinder); h = max_cylinder; }
        for (int i = split - 1; i >= 0; i--) { mv += abs(h - temp[i]); h = temp[i]; }
    } else {
        for (int i = split - 1; i >= 0; i--) { mv += abs(h - temp[i]); h = temp[i]; }
        if (h != min_cylinder) { mv += abs(h - min_cylinder); h = min_cylinder; }
        for (int i = split; i < n_permintaan; i++) { mv += abs(h - temp[i]); h = temp[i]; }
    }
    printf("%-15s | %-20d | %-20.2f\n", "SCAN", mv, (float)mv / n_permintaan);

    /* C-SCAN */
    h = head_awal; mv = 0;
    split = 0; while (split < n_permintaan && temp[split] < h) split++;
    if (arah_awal == 1) {
        for (int i = split; i < n_permintaan; i++) { mv += abs(h - temp[i]); h = temp[i]; }
        if (h != max_cylinder) { mv += abs(h - max_cylinder); h = max_cylinder; }
        mv += abs(max_cylinder - min_cylinder); h = min_cylinder;
        for (int i = 0; i < split; i++) { mv += abs(h - temp[i]); h = temp[i]; }
    } else {
        for (int i = split - 1; i >= 0; i--) { mv += abs(h - temp[i]); h = temp[i]; }
        if (h != min_cylinder) { mv += abs(h - min_cylinder); h = min_cylinder; }
        mv += abs(min_cylinder - max_cylinder); h = max_cylinder;
        for (int i = n_permintaan - 1; i >= split; i--) { mv += abs(h - temp[i]); h = temp[i]; }
    }
    printf("%-15s | %-20d | %-20.2f\n", "C-SCAN", mv, (float)mv / n_permintaan);
    printf("----------------|----------------------|---------------------\n\n");
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    int pilihan;

    printf("\n");
    garis();
    printf("   SIMULASI PENJADWALAN DISK\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    inputPermintaan();

    do {
        printf("\n");
        garis();
        printf("  MENU ALGORITMA DISK\n");
        garis();
        printf("1. FCFS (First Come First Served)\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. Tampilkan Perbandingan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }

        switch (pilihan) {
            case 1: simulasiFCFS(); break;
            case 2: simulasiSCAN(); break;
            case 3: simulasiCSCAN(); break;
            case 4: tampilkanPerbandingan(); break;
            case 0: printf("Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}