/* =====================================================
 * TUGAS 1      : Manajemen Proses pada Linux
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : manajemen_proses.c
 * Compile      : gcc -Wall -Wextra manajemen_proses.c -o manajemen_proses
 * Run          : ./manajemen_proses
 * ===================================================== */

#include <stdio.h>       /* printf, fprintf, perror */
#include <stdlib.h>      /* exit, atoi */
#include <string.h>      /* strlen, strcpy */
#include <unistd.h>      /* fork, getpid, getppid, exec, sleep, _exit */
#include <sys/types.h>   /* pid_t */
#include <sys/wait.h>    /* wait, waitpid */
#include <sys/resource.h>/* getpriority, setpriority */
#include <signal.h>      /* signal, sigaction, kill */
#include <errno.h>       /* errno */
#include <time.h>        /* time */

/* =====================================================
 * Variabel global untuk penanganan sinyal
 * ===================================================== */
volatile sig_atomic_t sinyal_diterima = 0;
volatile sig_atomic_t jenis_sinyal    = 0;

/* =====================================================
 * Signal Handler untuk SIGINT (Ctrl+C) dan SIGTERM
 * ===================================================== */
void handler_sinyal(int signum) {
    sinyal_diterima = 1;
    jenis_sinyal    = signum;

    if (signum == SIGINT) {
        const char msg[] = "\n[SIGNAL] Menerima SIGINT (Ctrl+C). Program akan berhenti dengan bersih.\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    } else if (signum == SIGTERM) {
        const char msg[] = "\n[SIGNAL] Menerima SIGTERM. Program akan berhenti dengan bersih.\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    }
}

/* =====================================================
 * Fungsi bantu: cetak garis pemisah
 * ===================================================== */
void garis() {
    printf("==================================================\n");
}

/* =====================================================
 * 1. Menampilkan identitas proses (PID & PPID)
 * ===================================================== */
void tampilkan_identitas() {
    pid_t pid  = getpid();
    pid_t ppid = getppid();

    garis();
    printf("1. IDENTITAS PROSES UTAMA\n");
    garis();
    printf("PID  (Process ID)         : %d\n", (int) pid);
    printf("PPID (Parent Process ID)  : %d\n", (int) ppid);
    printf("\n");
}

/* =====================================================
 * 2. Pembuatan proses dengan fork()
 *    Induk dan anak menampilkan pesan berbeda
 * ===================================================== */
void demo_fork() {
    pid_t pid;

    garis();
    printf("2. PEMBUATAN PROSES DENGAN fork()\n");
    garis();

    pid = fork();

    if (pid < 0) {
        /* fork gagal */
        perror("fork gagal");
        return;
    } else if (pid == 0) {
        /* ===== Bagian ANAK ===== */
        printf("[ANAK ] PID saya = %d, PPID saya = %d\n",
               (int) getpid(), (int) getppid());
        printf("[ANAK ] Saya adalah proses hasil fork().\n");

        /* Anak tidur sebentar supaya induk bisa menunggu */
        sleep(2);

        printf("[ANAK ] Selesai, keluar.\n");
        _exit(0);   /* WAJIB pakai _exit() di anak supaya tidak dobel flush */
    } else {
        /* ===== Bagian INDUK ===== */
        int status;
        pid_t selesai;

        printf("[INDUK] PID saya = %d\n", (int) getpid());
        printf("[INDUK] PID anak saya = %d\n", (int) pid);

        /* 8. SINKRONISASI: tunggu anak selesai */
        selesai = waitpid(pid, &status, 0);

        if (selesai < 0) {
            perror("waitpid gagal");
        } else if (WIFEXITED(status)) {
            printf("[INDUK] Anak dengan PID %d selesai dengan status %d\n",
                   (int) selesai, WEXITSTATUS(status));
        }
    }
    printf("\n");
}

/* =====================================================
 * 3. Menjalankan program eksternal dengan exec()
 * ===================================================== */
void demo_exec() {
    pid_t pid;

    garis();
    printf("3. MENJALANKAN PROGRAM EKSTERNAL DENGAN exec()\n");
    garis();
    printf("Menjalankan 'ls -l' dari proses anak...\n\n");

    pid = fork();

    if (pid < 0) {
        perror("fork gagal");
        return;
    } else if (pid == 0) {
        /* ===== Bagian ANAK ===== */
        /* exec() menggantikan image proses anak dengan program baru */
        execlp("ls", "ls", "-l", NULL);

        /* Kalau exec() berhasil, baris ini TIDAK akan dijalankan */
        perror("exec gagal");
        _exit(1);
    } else {
        /* ===== Bagian INDUK ===== */
        int status;
        waitpid(pid, &status, 0);
        printf("\n[INDUK] Program 'ls -l' selesai dijalankan.\n");
    }
    printf("\n");
}

/* =====================================================
 * 4. Pengaturan prioritas: getpriority() & setpriority()
 * ===================================================== */
void demo_prioritas() {
    int nice_sekarang;
    int nice_baru = 5;
    int hasil;

    garis();
    printf("4. PENGATURAN PRIORITAS PROSES\n");
    garis();

    /* Ambil nilai nice saat ini */
    errno = 0;
    nice_sekarang = getpriority(PRIO_PROCESS, 0);
    if (nice_sekarang == -1 && errno != 0) {
        perror("getpriority gagal");
    } else {
        printf("Nilai nice saat ini : %d\n", nice_sekarang);
    }

    /* Ubah nilai nice */
    hasil = setpriority(PRIO_PROCESS, 0, nice_baru);
    if (hasil < 0) {
        perror("setpriority gagal (mungkin butuh sudo)");
    } else {
        printf("Nilai nice diubah menjadi : %d\n", nice_baru);
    }

    /* Cek ulang */
    errno = 0;
    nice_sekarang = getpriority(PRIO_PROCESS, 0);
    if (nice_sekarang == -1 && errno != 0) {
        perror("getpriority gagal");
    } else {
        printf("Nilai nice setelah diubah : %d\n", nice_sekarang);
    }

    printf("\nCatatan:\n");
    printf("  - Nilai nice berkisar dari -20 (prioritas TINGGI) sampai +19 (prioritas RENDAH).\n");
    printf("  - Hanya root yang bisa menurunkan nilai nice (< 0).\n");
    printf("  - Proses biasa hanya bisa menaikkan nilai nice (menurunkan prioritas).\n\n");
}

/* =====================================================
 * 5. Menampilkan PID untuk pengujian kill
 * ===================================================== */
void tampilkan_pid_untuk_kill() {
    garis();
    printf("5. PID UNTUK PENGUJIAN KILL\n");
    garis();
    printf("PID program ini : %d\n", (int) getpid());
    printf("Untuk menghentikan program ini dari terminal lain:\n");
    printf("  kill -TERM %d   (SIGTERM - terminasi normal)\n", (int) getpid());
    printf("  kill -INT  %d   (SIGINT  - sama seperti Ctrl+C)\n", (int) getpid());
    printf("  kill -KILL %d   (SIGKILL - paksa, tidak bisa ditangani)\n", (int) getpid());
    printf("\n");
}

/* =====================================================
 * 6. Menunggu sinyal dari user
 * ===================================================== */
void tunggu_sinyal() {
    int detik = 0;

    garis();
    printf("6. MENUNGGU SINYAL (SIGINT / SIGTERM)\n");
    garis();
    printf("Program akan menunggu. Kirim sinyal dengan:\n");
    printf("  - Ctrl+C dari terminal ini, atau\n");
    printf("  - kill -TERM %d dari terminal lain\n", (int) getpid());
    printf("\nMenunggu maksimal 30 detik...\n\n");

    while (!sinyal_diterima && detik < 30) {
        sleep(1);
        detik++;
        if (detik % 5 == 0) {
            printf("[%2d detik] Masih menunggu sinyal...\n", detik);
        }
    }

    if (sinyal_diterima) {
        printf("\nSinyal nomor %d diterima. Program keluar dengan bersih.\n",
               jenis_sinyal);
    } else {
        printf("\nWaktu habis (30 detik). Tidak ada sinyal yang diterima.\n");
    }
    printf("\n");
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    struct sigaction sa;

    printf("\n");
    garis();
    printf("   PROGRAM MANAJEMEN PROSES SEDERHANA (LINUX)\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    /* ---- 7. Daftarkan signal handler dengan sigaction() ---- */
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_sinyal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction SIGINT gagal");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTERM, &sa, NULL) < 0) {
        perror("sigaction SIGTERM gagal");
        exit(EXIT_FAILURE);
    }

    /* Jalankan semua demo secara berurutan */
    tampilkan_identitas();
    demo_fork();
    demo_exec();
    demo_prioritas();
    tampilkan_pid_untuk_kill();
    tunggu_sinyal();

    garis();
    printf("PROGRAM SELESAI.\n");
    garis();
    printf("\n");

    return 0;
}