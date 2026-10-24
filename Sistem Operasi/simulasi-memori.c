/* =====================================================
 * TUGAS 4      : Simulasi Manajemen Memori & Page Replacement
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : simulasi_memori.c
 * Compile      : gcc -Wall -Wextra -std=c11 simulasi_memori.c -o simulasi_memori
 * Run          : ./simulasi_memori
 * ===================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =====================================================
 * KONFIGURASI
 * ===================================================== */
#define MAX_FRAMES  10
#define MAX_PAGES   50

/* =====================================================
 * FUNGSI BANTU
 * ===================================================== */
void garis() {
    printf("=================================================================\n");
}

/* =====================================================
 * 1. SIMULASI CONTIGUOUS ALLOCATION (FIRST FIT)
 * ===================================================== */
void simulasiFirstFit() {
    int jumlah_blok, jumlah_proses;
    int block_size[20], process_size[20];
    int alokasi[20]; /* -1 jika gagal, selain itu index blok */
    int i, j;

    garis();
    printf("  SIMULASI CONTIGUOUS ALLOCATION - FIRST FIT\n");
    garis();

    printf("Masukkan jumlah blok memori (1-20): ");
    if (scanf("%d", &jumlah_blok) != 1 || jumlah_blok <= 0 || jumlah_blok > 20) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Masukkan ukuran setiap blok memori:\n");
    for (i = 0; i < jumlah_blok; i++) {
        printf("  Blok %d: ", i + 1);
        if (scanf("%d", &block_size[i]) != 1 || block_size[i] <= 0) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n');
            return;
        }
    }

    printf("Masukkan jumlah proses (1-20): ");
    if (scanf("%d", &jumlah_proses) != 1 || jumlah_proses <= 0 || jumlah_proses > 20) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Masukkan ukuran setiap proses:\n");
    for (i = 0; i < jumlah_proses; i++) {
        printf("  Proses %d: ", i + 1);
        if (scanf("%d", &process_size[i]) != 1 || process_size[i] <= 0) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n');
            return;
        }
        alokasi[i] = -1; /* belum dialokasikan */
    }

    /* Alokasi First Fit */
    for (i = 0; i < jumlah_proses; i++) {
        for (j = 0; j < jumlah_blok; j++) {
            if (block_size[j] >= process_size[i]) {
                alokasi[i] = j;
                block_size[j] -= process_size[i]; /* kurangi ukuran blok */
                break;
            }
        }
    }

    /* Tampilkan Hasil */
    printf("\n--- Hasil Alokasi First Fit ---\n");
    printf("%-10s %-15s %-15s %-15s\n", "Proses", "Ukuran (KB)", "Blok ID", "Sisa Blok (KB)");
    for (i = 0; i < jumlah_proses; i++) {
        printf("P%-9d %-15d ", i + 1, process_size[i]);
        if (alokasi[i] != -1) {
            printf("%-15d %-15d\n", alokasi[i] + 1, block_size[alokasi[i]]);
        } else {
            printf("%-15s %-15s\n", "Tidak ada", "-");
        }
    }

    /* Ringkasan Fragmentasi Eksternal */
    printf("\nSisa ruang di setiap blok (potensi fragmentasi eksternal):\n");
    int total_sisa = 0;
    for (j = 0; j < jumlah_blok; j++) {
        printf("  Blok %d: %d KB\n", j + 1, block_size[j]);
        total_sisa += block_size[j];
    }
    printf("Total sisa memori: %d KB\n\n", total_sisa);
}

/* =====================================================
 * 2. SIMULASI PAGING - FIFO
 * ===================================================== */
void simulasiFIFO(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int fifo_ptr = 0;
    int faults = 0, hits = 0;
    int i, j;

    for (i = 0; i < frames; i++) frame[i] = -1;

    garis();
    printf("  ALGORITMA FIFO (Frame: %d)\n", frames);
    garis();
    printf("%-5s | ", "Page");
    for (i = 0; i < frames; i++) printf("F%-3d | ", i + 1);
    printf("Status\n");
    printf("------|");
    for (i = 0; i < frames; i++) printf("------|");
    printf("--------\n");

    for (i = 0; i < n; i++) {
        bool is_hit = false;

        /* Cek apakah ada di frame (HIT) */
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                is_hit = true;
                break;
            }
        }

        if (is_hit) {
            hits++;
        } else {
            faults++;
            frame[fifo_ptr] = pages[i];
            fifo_ptr = (fifo_ptr + 1) % frames;
        }

        /* Cetak state */
        printf("%-5d | ", pages[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("-    | ");
            else printf("%-4d | ", frame[j]);
        }
        printf("%s\n", is_hit ? "HIT" : "FAULT");
    }

    printf("\nPage Fault: %d\n", faults);
    printf("Page Hit  : %d\n", hits);
    printf("Fault Rate: %.2f%%\n", (float)faults / n * 100);
    printf("Hit Rate  : %.2f%%\n\n", (float)hits / n * 100);
}

/* =====================================================
 * 3. SIMULASI PAGING - LRU
 * ===================================================== */
void simulasiLRU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int faults = 0, hits = 0;
    int i, j, time = 0;

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        last_used[i] = -1;
    }

    garis();
    printf("  ALGORITMA LRU (Frame: %d)\n", frames);
    garis();
    printf("%-5s | ", "Page");
    for (i = 0; i < frames; i++) printf("F%-3d | ", i + 1);
    printf("Status\n");
    printf("------|");
    for (i = 0; i < frames; i++) printf("------|");
    printf("--------\n");

    for (i = 0; i < n; i++) {
        bool is_hit = false;
        int hit_idx = -1;

        /* Cek HIT */
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                is_hit = true;
                hit_idx = j;
                break;
            }
        }

        if (is_hit) {
            hits++;
            last_used[hit_idx] = time++;
        } else {
            faults++;
            /* Cari frame kosong atau LRU */
            int min_time = 999999;
            int replace_idx = 0;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace_idx = j;
                    break;
                }
                if (last_used[j] < min_time) {
                    min_time = last_used[j];
                    replace_idx = j;
                }
            }
            frame[replace_idx] = pages[i];
            last_used[replace_idx] = time++;
        }

        /* Cetak state */
        printf("%-5d | ", pages[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("-    | ");
            else printf("%-4d | ", frame[j]);
        }
        printf("%s\n", is_hit ? "HIT" : "FAULT");
    }

    printf("\nPage Fault: %d\n", faults);
    printf("Page Hit  : %d\n", hits);
    printf("Fault Rate: %.2f%%\n", (float)faults / n * 100);
    printf("Hit Rate  : %.2f%%\n\n", (float)hits / n * 100);
}

/* =====================================================
 * 4. SIMULASI PAGING - OPTIMAL
 * ===================================================== */
void simulasiOptimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int faults = 0, hits = 0;
    int i, j, k;

    for (i = 0; i < frames; i++) frame[i] = -1;

    garis();
    printf("  ALGORITMA OPTIMAL (Frame: %d)\n", frames);
    garis();
    printf("%-5s | ", "Page");
    for (i = 0; i < frames; i++) printf("F%-3d | ", i + 1);
    printf("Status\n");
    printf("------|");
    for (i = 0; i < frames; i++) printf("------|");
    printf("--------\n");

    for (i = 0; i < n; i++) {
        bool is_hit = false;

        /* Cek HIT */
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                is_hit = true;
                break;
            }
        }

        if (is_hit) {
            hits++;
        } else {
            faults++;
            /* Cari frame kosong */
            bool ada_kosong = false;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    ada_kosong = true;
                    break;
                }
            }

            if (!ada_kosong) {
                /* Cari halaman yang paling jauh digunakan di masa depan */
                int max_future = -1;
                int replace_idx = 0;
                for (j = 0; j < frames; j++) {
                    int next_use = 999999;
                    for (k = i + 1; k < n; k++) {
                        if (pages[k] == frame[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use > max_future) {
                        max_future = next_use;
                        replace_idx = j;
                    }
                }
                frame[replace_idx] = pages[i];
            }
        }

        /* Cetak state */
        printf("%-5d | ", pages[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("-    | ");
            else printf("%-4d | ", frame[j]);
        }
        printf("%s\n", is_hit ? "HIT" : "FAULT");
    }

    printf("\nPage Fault: %d\n", faults);
    printf("Page Hit  : %d\n", hits);
    printf("Fault Rate: %.2f%%\n", (float)faults / n * 100);
    printf("Hit Rate  : %.2f%%\n\n", (float)hits / n * 100);
}

/* =====================================================
 * 5. TAMPILKAN PERBANDINGAN
 * ===================================================== */
void tampilkanPerbandingan(int pages[], int n, int frames) {
    int frame_fifo[MAX_FRAMES], frame_lru[MAX_FRAMES], frame_opt[MAX_FRAMES];
    int fifo_ptr = 0, last_used[MAX_FRAMES];
    int i, j, k;
    int fault_fifo = 0, fault_lru = 0, fault_opt = 0;
    int time_lru = 0;

    for (i = 0; i < frames; i++) {
        frame_fifo[i] = frame_lru[i] = frame_opt[i] = -1;
        last_used[i] = -1;
    }

    /* Hitung FIFO */
    for (i = 0; i < n; i++) {
        bool hit = false;
        for (j = 0; j < frames; j++) if (frame_fifo[j] == pages[i]) { hit = true; break; }
        if (!hit) { fault_fifo++; frame_fifo[fifo_ptr] = pages[i]; fifo_ptr = (fifo_ptr + 1) % frames; }
    }

    /* Hitung LRU */
    for (i = 0; i < n; i++) {
        bool hit = false; int hit_idx = -1;
        for (j = 0; j < frames; j++) if (frame_lru[j] == pages[i]) { hit = true; hit_idx = j; break; }
        if (hit) { last_used[hit_idx] = time_lru++; }
        else {
            fault_lru++;
            int min_t = 999999, rep = 0;
            for (j = 0; j < frames; j++) {
                if (frame_lru[j] == -1) { rep = j; break; }
                if (last_used[j] < min_t) { min_t = last_used[j]; rep = j; }
            }
            frame_lru[rep] = pages[i]; last_used[rep] = time_lru++;
        }
    }

    /* Hitung Optimal */
    for (i = 0; i < n; i++) {
        bool hit = false;
        for (j = 0; j < frames; j++) if (frame_opt[j] == pages[i]) { hit = true; break; }
        if (!hit) {
            fault_opt++;
            bool ada_kosong = false;
            for (j = 0; j < frames; j++) if (frame_opt[j] == -1) { frame_opt[j] = pages[i]; ada_kosong = true; break; }
            if (!ada_kosong) {
                int max_fut = -1, rep = 0;
                for (j = 0; j < frames; j++) {
                    int nxt = 999999;
                    for (k = i + 1; k < n; k++) if (pages[k] == frame_opt[j]) { nxt = k; break; }
                    if (nxt > max_fut) { max_fut = nxt; rep = j; }
                }
                frame_opt[rep] = pages[i];
            }
        }
    }

    garis();
    printf("  PERBANDINGAN ALGORITMA PAGE REPLACEMENT\n");
    garis();
    printf("%-15s | %-10s | %-10s | %-12s\n", "Algoritma", "Page Fault", "Page Hit", "Fault Rate (%)");
    printf("----------------|------------|------------|---------------\n");
    printf("%-15s | %-10d | %-10d | %-12.2f\n", "FIFO", fault_fifo, n - fault_fifo, (float)fault_fifo / n * 100);
    printf("%-15s | %-10d | %-10d | %-12.2f\n", "LRU", fault_lru, n - fault_lru, (float)fault_lru / n * 100);
    printf("%-15s | %-10d | %-10d | %-12.2f\n", "Optimal", fault_opt, n - fault_opt, (float)fault_opt / n * 100);
    printf("----------------|------------|------------|---------------\n");
    printf("Total Akses: %d, Jumlah Frame: %d\n\n", n, frames);
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    int pages[MAX_PAGES];
    int n, frames;
    int pilihan;
    int i;

    printf("\n");
    garis();
    printf("   SIMULASI MANAJEMEN MEMORI & PAGE REPLACEMENT\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    /* Input Reference String */
    printf("Masukkan jumlah halaman (reference string) (max %d): ", MAX_PAGES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PAGES) {
        printf("Input tidak valid!\n");
        return 1;
    }

    printf("Masukkan urutan halaman (pisahkan dengan spasi):\n");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &pages[i]) != 1 || pages[i] < 0) {
            printf("Input halaman tidak valid!\n");
            return 1;
        }
    }

    printf("Masukkan jumlah frame (max %d): ", MAX_FRAMES);
    if (scanf("%d", &frames) != 1 || frames <= 0 || frames > MAX_FRAMES) {
        printf("Input frame tidak valid!\n");
        return 1;
    }

    do {
        printf("\n");
        garis();
        printf("  MENU\n");
        garis();
        printf("1. Simulasi Contiguous Allocation (First Fit)\n");
        printf("2. Simulasi Paging - FIFO\n");
        printf("3. Simulasi Paging - LRU\n");
        printf("4. Simulasi Paging - Optimal\n");
        printf("5. Tampilkan Perbandingan (FIFO vs LRU vs Optimal)\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (pilihan) {
            case 1: simulasiFirstFit(); break;
            case 2: simulasiFIFO(pages, n, frames); break;
            case 3: simulasiLRU(pages, n, frames); break;
            case 4: simulasiOptimal(pages, n, frames); break;
            case 5: tampilkanPerbandingan(pages, n, frames); break;
            case 0: printf("\nTerima kasih! Program selesai.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}