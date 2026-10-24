/* =====================================================
 * TUGAS 2      : Simulasi Sistem Transaksi Saldo Bank
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : transaksi_bank.c
 * Compile      : gcc -Wall -Wextra transaksi_bank.c -o transaksi_bank -pthread
 * Run          : ./transaksi_bank
 * ===================================================== */

#include <stdio.h>       /* printf, fprintf */
#include <stdlib.h>      /* rand_r, exit, atoi */
#include <string.h>      /* memset */
#include <unistd.h>      /* usleep */
#include <pthread.h>     /* pthread_create, pthread_join, pthread_mutex_* */
#include <time.h>        /* time */
#include <errno.h>       /* errno */

/* =====================================================
 * KONFIGURASI
 * ===================================================== */
#define JUMLAH_THREAD      4      /* minimal 4 thread */
#define TRANSAKSI_PER_THREAD 50   /* jumlah transaksi tiap thread */
#define SALDO_AWAL         1000000
#define SETOR_MIN          10000
#define SETOR_MAX          100000
#define TARIK_MIN          5000
#define TARIK_MAX          50000

/* =====================================================
 * VARIABEL GLOBAL BERSAMA (shared resource)
 * ===================================================== */
long saldo_rekening = SALDO_AWAL;
pthread_mutex_t mutex_saldo;

/* Mode: 0 = tanpa mutex, 1 = dengan mutex */
int gunakan_mutex = 1;

/* Statistik global */
long total_setor_global = 0;
long total_tarik_global = 0;
long jumlah_transaksi_sukses = 0;
long jumlah_transaksi_gagal   = 0;
pthread_mutex_t mutex_statistik;

/* =====================================================
 * STRUKTUR DATA UNTUK SETIAP THREAD
 * ===================================================== */
typedef struct {
    int   id_thread;
    unsigned int seed;    /* seed untuk rand_r (thread-safe) */
    long  total_setor;    /* total setoran thread ini */
    long  total_tarik;    /* total penarikan thread ini */
    int   jml_transaksi;  /* jumlah transaksi berhasil */
    int   jml_gagal;      /* jumlah transaksi gagal (saldo tidak cukup) */
} ThreadData;

/* =====================================================
 * Fungsi bantu: cetak garis pemisah
 * ===================================================== */
void garis() {
    printf("================================================================\n");
}

/* =====================================================
 * Fungsi transaksi (dipanggil di dalam thread)
 * ===================================================== */
void *pekerja_thread(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    int i;

    for (i = 0; i < TRANSAKSI_PER_THREAD; i++) {
        /* Tentukan jenis transaksi: 0 = setor, 1 = tarik */
        int jenis = rand_r(&data->seed) % 2;

        /* Nominal acak */
        long nominal;
        if (jenis == 0) {
            /* Setor: 10.000 - 100.000 */
            nominal = SETOR_MIN + (rand_r(&data->seed) %
                       (SETOR_MAX - SETOR_MIN + 1));
        } else {
            /* Tarik: 5.000 - 50.000 */
            nominal = TARIK_MIN + (rand_r(&data->seed) %
                       (TARIK_MAX - TARIK_MIN + 1));
        }

        /* ---- AKSES SHARED RESOURCE ---- */
        if (gunakan_mutex) {
            pthread_mutex_lock(&mutex_saldo);
        }

        /* Simulasi jeda acak (membuat urutan eksekusi bervariasi) */
        usleep(100 + rand_r(&data->seed) % 500);

        if (jenis == 0) {
            /* ---- SETOR ---- */
            saldo_rekening += nominal;
            data->total_setor += nominal;
            data->jml_transaksi++;
        } else {
            /* ---- TARIK ---- */
            if (saldo_rekening >= nominal) {
                saldo_rekening -= nominal;
                data->total_tarik += nominal;
                data->jml_transaksi++;
            } else {
                /* Saldo tidak cukup, transaksi gagal */
                data->jml_gagal++;
            }
        }

        if (gunakan_mutex) {
            pthread_mutex_unlock(&mutex_saldo);
        }
        /* ---- SELESAI AKSES SHARED RESOURCE ---- */
    }

    /* Update statistik global (juga shared resource) */
    if (gunakan_mutex) {
        pthread_mutex_lock(&mutex_statistik);
    }
    total_setor_global += data->total_setor;
    total_tarik_global += data->total_tarik;
    jumlah_transaksi_sukses += data->jml_transaksi;
    jumlah_transaksi_gagal  += data->jml_gagal;
    if (gunakan_mutex) {
        pthread_mutex_unlock(&mutex_statistik);
    }

    return NULL;
}

/* =====================================================
 * Fungsi menjalankan simulasi (dipanggil dari main)
 * Parameter: mode_mutex (0 = tanpa mutex, 1 = dengan mutex)
 * ===================================================== */
void jalankan_simulasi(int mode_mutex) {
    pthread_t threads[JUMLAH_THREAD];
    ThreadData data[JUMLAH_THREAD];
    int i;

    /* Set mode global */
    gunakan_mutex = mode_mutex;

    /* Reset state */
    saldo_rekening = SALDO_AWAL;
    total_setor_global = 0;
    total_tarik_global = 0;
    jumlah_transaksi_sukses = 0;
    jumlah_transaksi_gagal  = 0;

    /* Inisialisasi mutex */
    if (pthread_mutex_init(&mutex_saldo, NULL) != 0) {
        perror("pthread_mutex_init mutex_saldo gagal");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_init(&mutex_statistik, NULL) != 0) {
        perror("pthread_mutex_init mutex_statistik gagal");
        exit(EXIT_FAILURE);
    }

    /* Header */
    garis();
    if (mode_mutex) {
        printf("   SIMULASI DENGAN MUTEX (Thread-Safe)\n");
    } else {
        printf("   SIMULASI TANPA MUTEX (Race Condition)\n");
    }
    garis();
    printf("Saldo awal         : Rp %ld\n", SALDO_AWAL);
    printf("Jumlah thread      : %d\n", JUMLAH_THREAD);
    printf("Transaksi / thread : %d\n", TRANSAKSI_PER_THREAD);
    printf("Total transaksi    : %d\n", JUMLAH_THREAD * TRANSAKSI_PER_THREAD);
    printf("\n");
    printf("--- Memulai thread ---\n");

    /* ---- 1. CREATE THREAD ---- */
    for (i = 0; i < JUMLAH_THREAD; i++) {
        data[i].id_thread      = i + 1;
        data[i].seed           = (unsigned int)(time(NULL) + i * 12345);
        data[i].total_setor    = 0;
        data[i].total_tarik    = 0;
        data[i].jml_transaksi  = 0;
        data[i].jml_gagal      = 0;

        if (pthread_create(&threads[i], NULL,
                           pekerja_thread, (void *) &data[i]) != 0) {
            perror("pthread_create gagal");
            exit(EXIT_FAILURE);
        }
        printf("  Thread %d dibuat (TID internal belum tampil di sini)\n", i + 1);
    }

    /* ---- 2. JOIN THREAD (tunggu semua selesai) ---- */
    printf("\n--- Menunggu thread selesai (pthread_join) ---\n");
    for (i = 0; i < JUMLAH_THREAD; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join gagal");
            exit(EXIT_FAILURE);
        }
    }
    printf("Semua thread selesai.\n\n");

    /* ---- 3. HITUNG SALDO HARAPAN ---- */
    long saldo_harapan = SALDO_AWAL + total_setor_global - total_tarik_global;
    long selisih       = saldo_rekening - saldo_harapan;

    /* ---- 4. TAMPILKAN HASIL ---- */
    garis();
    printf("HASIL SIMULASI\n");
    garis();
    printf("Saldo awal         : Rp %ld\n", SALDO_AWAL);
    printf("Total setoran      : Rp %ld\n", total_setor_global);
    printf("Total penarikan    : Rp %ld\n", total_tarik_global);
    printf("Saldo harapan      : Rp %ld\n", saldo_harapan);
    printf("Saldo aktual       : Rp %ld\n", saldo_rekening);
    printf("Selisih            : Rp %ld\n", selisih);
    printf("\n");
    printf("Transaksi berhasil : %ld\n", jumlah_transaksi_sukses);
    printf("Transaksi gagal    : %ld\n", jumlah_transaksi_gagal);
    printf("\n");

    if (selisih == 0) {
        printf("STATUS: KONSISTEN (saldo aktual = saldo harapan)\n");
    } else {
        printf("STATUS: TIDAK KONSISTEN (terjadi race condition!)\n");
        printf("        Selisih Rp %ld menunjukkan kehilangan/duplikasi update.\n",
               selisih);
    }

    /* ---- 5. DESTROY MUTEX ---- */
    pthread_mutex_destroy(&mutex_saldo);
    pthread_mutex_destroy(&mutex_statistik);

    printf("\n");
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main(int argc, char *argv[]) {
    int mode;

    printf("\n");
    garis();
    printf("   SIMULASI TRANSAKSI SALDO BANK (PTHREADS)\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    /* Pilih mode dari argumen command line (opsional) */
    if (argc >= 2) {
        mode = atoi(argv[1]);
        if (mode != 0 && mode != 1) {
            printf("Usage: %s [0|1]\n", argv[0]);
            printf("  0 = tanpa mutex\n");
            printf("  1 = dengan mutex\n");
            return 1;
        }
        jalankan_simulasi(mode);
    } else {
        /* Kalau tidak ada argumen, jalankan KEDUA mode untuk perbandingan */
        printf(">>> Menjalankan 2 skenario: TANPA mutex dan DENGAN mutex <<<\n");
        printf(">>> Tekan Ctrl+C kalau ingin berhenti lebih awal <<<\n\n");
        sleep(2);

        jalankan_simulasi(0);   /* tanpa mutex */
        sleep(2);
        jalankan_simulasi(1);   /* dengan mutex */

        /* Ringkasan perbandingan */
        garis();
        printf("RINGKASAN PERBANDINGAN\n");
        garis();
        printf("Jalankan program berulang kali untuk melihat perbedaan.\n");
        printf("  - Tanpa mutex: saldo sering tidak konsisten (selisih != 0).\n");
        printf("  - Dengan mutex: saldo SELALU konsisten (selisih = 0).\n");
        printf("\n");
    }

    return 0;
}