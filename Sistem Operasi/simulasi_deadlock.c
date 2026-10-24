/* =====================================================
 * TUGAS 3      : Simulasi Deadlock & Algoritma Banker
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : simulasi_deadlock.c
 * Compile      : gcc -Wall -Wextra -std=c11 simulasi_deadlock.c -o simulasi_deadlock
 * Run          : ./simulasi_deadlock
 * ===================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =====================================================
 * KONFIGURASI
 * ===================================================== */
#define P 5   /* Jumlah proses (P0 - P4) */
#define R 3   /* Jumlah jenis sumber daya (A, B, C) */

/* Nama resource biar enak dibaca */
const char *nama_resource[R] = {"Printer(A)", "Scanner(B)", "Storage(C)"};

/* =====================================================
 * VARIABEL GLOBAL
 * ===================================================== */

/* Data Awal (Silberschatz OS Concepts) */
int Available[R] = {3, 3, 2};

int Max[P][R] = {
    {7, 5, 3},  /* P0 */
    {3, 2, 2},  /* P1 */
    {9, 0, 2},  /* P2 */
    {2, 2, 2},  /* P3 */
    {4, 3, 3}   /* P4 */
};

int Allocation[P][R] = {
    {0, 1, 0},  /* P0 */
    {2, 0, 0},  /* P1 */
    {3, 0, 2},  /* P2 */
    {2, 1, 1},  /* P3 */
    {0, 0, 2}   /* P4 */
};

int Need[P][R]; /* Akan dihitung dari Max - Allocation */

/* =====================================================
 * FUNGSI BANTU: Garis pemisah
 * ===================================================== */
void garis() {
    printf("=================================================================\n");
}

/* =====================================================
 * 1. HITUNG NEED
 *    Need[i][j] = Max[i][j] - Allocation[i][j]
 * ===================================================== */
void hitungNeed() {
    int i, j;
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

/* =====================================================
 * 2. TAMPILKAN DATA (Matriks Allocation, Max, Need, Available)
 * ===================================================== */
void tampilkanData() {
    int i, j;

    garis();
    printf("  TABEL ALOKASI SUMBER DAYA\n");
    garis();

    /* Header */
    printf("%-8s", "Proses");
    for (j = 0; j < R; j++) printf("  Alloc%-6s", nama_resource[j]);
    printf("|");
    for (j = 0; j < R; j++) printf("  Max%-6s", nama_resource[j]);
    printf("|");
    for (j = 0; j < R; j++) printf("  Need%-6s", nama_resource[j]);
    printf("\n");

    printf("-----------------------------------------------------------------\n");

    /* Isi matriks */
    for (i = 0; i < P; i++) {
        printf("P%-7d", i);
        for (j = 0; j < R; j++) printf("  %-12d", Allocation[i][j]);
        printf("|");
        for (j = 0; j < R; j++) printf("  %-12d", Max[i][j]);
        printf("|");
        for (j = 0; j < R; j++) printf("  %-12d", Need[i][j]);
        printf("\n");
    }

    printf("-----------------------------------------------------------------\n");

    /* Available */
    printf("Available: ");
    for (j = 0; j < R; j++) {
        printf("%s=%d ", nama_resource[j], Available[j]);
    }
    printf("\n\n");
}

/* =====================================================
 * 3. CEK SAFE STATE (Algoritma Banker)
 *    Return: 1 jika SAFE, 0 jika UNSAFE
 *    safeSeq[] akan berisi urutan proses yang aman
 * ===================================================== */
int cekSafeState(int safeSeq[], int cetakProses) {
    int work[R];
    bool finish[P] = {false};
    int i, j, count = 0;

    /* Salin Available ke Work */
    for (j = 0; j < R; j++) {
        work[j] = Available[j];
    }

    if (cetakProses) {
        printf("--- Pemeriksaan Safe State (Algoritma Banker) ---\n");
    }

    while (count < P) {
        bool found = false;

        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                /* Cek apakah Need[i] <= Work */
                bool bisa = true;
                for (j = 0; j < R; j++) {
                    if (Need[i][j] > work[j]) {
                        bisa = false;
                        break;
                    }
                }

                if (bisa) {
                    /* Alokasikan dan selesaikan proses i */
                    if (cetakProses) {
                        printf("  P%d dapat selesai. Work: [%d,%d,%d] -> ",
                               i, work[0], work[1], work[2]);
                    }
                    for (j = 0; j < R; j++) {
                        work[j] += Allocation[i][j];
                    }
                    if (cetakProses) {
                        printf("[%d,%d,%d]\n", work[0], work[1], work[2]);
                    }
                    finish[i] = true;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }

        if (!found) {
            /* Tidak ada proses yang bisa jalan -> deadlock risk */
            if (cetakProses) {
                printf("  Tidak ada proses yang dapat dilanjutkan.\n");
            }
            return 0; /* UNSAFE */
        }
    }

    return 1; /* SAFE */
}

/* =====================================================
 * 4. TAMPILKAN SAFE SEQUENCE
 * ===================================================== */
void tampilkanSafeSequence(int safeSeq[]) {
    int i;
    printf("\n>>> SAFE SEQUENCE : ");
    for (i = 0; i < P; i++) {
        printf("P%d", safeSeq[i]);
        if (i < P - 1) printf(" -> ");
    }
    printf("\n\n");
}

/* =====================================================
 * 5. AJUKAN REQUEST (Simulasi Permintaan Sumber Daya)
 * ===================================================== */
int ajukanRequest(int proses, int req[]) {
    int j;
    int i;

    printf("\n--- Memproses Permintaan P%d ---\n", proses);
    printf("Request: [%d, %d, %d]\n", req[0], req[1], req[2]);

    /* Langkah 1: Cek request <= Need */
    for (j = 0; j < R; j++) {
        if (req[j] > Need[proses][j]) {
            printf("[GAGAL] Request melebihi Need proses!\n");
            printf("        Need P%d saat ini: [%d, %d, %d]\n",
                   proses, Need[proses][0], Need[proses][1], Need[proses][2]);
            return 0;
        }
    }

    /* Langkah 2: Cek request <= Available */
    for (j = 0; j < R; j++) {
        if (req[j] > Available[j]) {
            printf("[GAGAL] Request melebihi Available!\n");
            printf("        Available saat ini: [%d, %d, %d]\n",
                   Available[0], Available[1], Available[2]);
            return 0;
        }
    }

    /* Langkah 3: Simulasi alokasi sementara */
    int backupAvail[R];
    int backupAlloc[R];
    int backupNeed[R];

    for (j = 0; j < R; j++) {
        backupAvail[j] = Available[j];
        backupAlloc[j] = Allocation[proses][j];
        backupNeed[j] = Need[proses][j];

        Available[j]         -= req[j];
        Allocation[proses][j] += req[j];
        Need[proses][j]       -= req[j];
    }

    /* Langkah 4: Cek apakah tetap SAFE */
    int safeSeq[P];
    int hasil = cekSafeState(safeSeq, 0);

    if (hasil) {
        printf("[BERHASIL] Request dialokasikan. Sistem tetap SAFE.\n");
        tampilkanSafeSequence(safeSeq);
        return 1;
    } else {
        /* Rollback */
        printf("[GAGAL] Request menyebabkan UNSAFE STATE. Rollback!\n");
        for (j = 0; j < R; j++) {
            Available[j]         = backupAvail[j];
            Allocation[proses][j] = backupAlloc[j];
            Need[proses][j]       = backupNeed[j];
        }
        return 0;
    }
}

/* =====================================================
 * 6. SIMULASI CONTOH DEADLOCK
 * ===================================================== */
void demoPenjelasanDeadlock() {
    garis();
    printf("  CONTOH SKENARIO DEADLOCK (Ilustrasi)\n");
    garis();
    printf("Bayangkan 2 proses dengan 2 resource:\n");
    printf("  - P1 memegang Printer, menunggu Scanner.\n");
    printf("  - P2 memegang Scanner, menunggu Printer.\n\n");
    printf("Kondisi yang terjadi:\n");
    printf("  1. Mutual Exclusion   : Printer & Scanner hanya bisa dipakai 1 proses.\n");
    printf("  2. Hold and Wait      : P1 sudah pegang Printer sambil nunggu Scanner.\n");
    printf("  3. No Preemption      : Resource tidak bisa dirampas paksa.\n");
    printf("  4. Circular Wait      : P1 nunggu P2, P2 nunggu P1 (siklus).\n\n");
    printf("Algoritma Banker mencegah alokasi yang menghasilkan 'unsafe state',\n");
    printf("namun UNSAFE STATE tidak selalu berarti deadlock sedang terjadi.\n");
    printf("Unsafestate = 'kemungkinan' deadlock di masa depan jika semua proses\n");
    printf("meminta resource secara maksimal.\n\n");
}

/* =====================================================
 * 7. RESET KE DATA AWAL
 * ===================================================== */
void resetData() {
    int awalAvail[R] = {3, 3, 2};
    int awalMax[P][R] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}
    };
    int awalAlloc[P][R] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
    };
    int i, j;
    for (j = 0; j < R; j++) Available[j] = awalAvail[j];
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            Max[i][j]        = awalMax[i][j];
            Allocation[i][j] = awalAlloc[i][j];
        }
    }
    hitungNeed();
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    int pilihan;
    int i;

    printf("\n");
    garis();
    printf("   SIMULASI DEADLOCK & ALGORITMA BANKER\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    /* Hitung Need awal */
    hitungNeed();

    /* Cek status awal */
    tampilkanData();

    int safeSeq[P];
    if (cekSafeState(safeSeq, 1)) {
        printf("\n>>> Status awal: SAFE STATE\n");
        tampilkanSafeSequence(safeSeq);
    } else {
        printf("\n>>> Status awal: UNSAFE STATE\n\n");
    }

    /* Menu interaktif */
    do {
        garis();
        printf("  MENU\n");
        garis();
        printf("1. Tampilkan Data Matriks\n");
        printf("2. Cek Safe State\n");
        printf("3. Ajukan Request Sumber Daya\n");
        printf("4. Contoh Penjelasan Deadlock\n");
        printf("5. Reset Data ke Awal\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        /* Validasi input */
        if (pilihan < 0 || pilihan > 5) {
            printf("Pilihan tidak valid!\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                tampilkanData();
                break;

            case 2: {
                int seq[P];
                printf("\n");
                if (cekSafeState(seq, 1)) {
                    printf("\n>>> Status saat ini: SAFE STATE\n");
                    tampilkanSafeSequence(seq);
                } else {
                    printf("\n>>> Status saat ini: UNSAFE STATE\n\n");
                }
                break;
            }

            case 3: {
                int proses;
                int req[R];
                int valid = 1;

                printf("\nMasukkan ID Proses (0-%d): ", P - 1);
                if (scanf("%d", &proses) != 1 || proses < 0 || proses >= P) {
                    printf("ID proses tidak valid!\n");
                    while (getchar() != '\n');
                    break;
                }

                printf("Masukkan request (format: A B C), contoh '1 0 2':\n");
                for (i = 0; i < R; i++) {
                    if (scanf("%d", &req[i]) != 1 || req[i] < 0) {
                        printf("Nilai request tidak valid!\n");
                        valid = 0;
                        while (getchar() != '\n');
                        break;
                    }
                }
                if (!valid) break;

                if (ajukanRequest(proses, req)) {
                    tampilkanData();
                }
                break;
            }

            case 4:
                demoPenjelasanDeadlock();
                break;

            case 5:
                resetData();
                printf("Data direset ke kondisi awal.\n");
                tampilkanData();
                break;

            case 0:
                printf("\nTerima kasih! Program selesai.\n");
                break;
        }

    } while (pilihan != 0);

    return 0;
}