/* =====================================================
 * TUGAS 1      : Pengantar Pemrograman C untuk Sistem Operasi
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : pengantar.c
 * Compile      : gcc pengantar.c -o pengantar
 * Run          : ./pengantar
 * ===================================================== */

#include <stdio.h>      /* printf, scanf, fopen, fclose */
#include <stdlib.h>     /* malloc, free, exit, atoi */
#include <string.h>     /* strlen, strcpy, strcmp */
#include <unistd.h>     /* getpid, getppid, sleep, fork */
#include <sys/types.h>  /* tipe data pid_t */

/* =====================================================
 * Fungsi bantu: cetak garis pemisah
 * ===================================================== */
void garis() {
    printf("==================================================\n");
}

/* =====================================================
 * 1. Program Hello World — dasar output
 * ===================================================== */
void helloWorld() {
    garis();
    printf("1. HELLO WORLD\n");
    garis();
    printf("Hello, World!\n");
    printf("Selamat datang di praktikum Sistem Operasi.\n\n");
}

/* =====================================================
 * 2. Variabel dan Tipe Data dasar di C
 * ===================================================== */
void variabelTipeData() {
    int     umur       = 20;
    float   ipk        = 3.75;
    double  pi         = 3.14159265359;
    char    inisial    = 'S';
    char    nama[50]   = "Satrio Nurcahya";

    garis();
    printf("2. VARIABEL DAN TIPE DATA\n");
    garis();
    printf("Nama       : %s\n", nama);
    printf("Inisial    : %c\n", inisial);
    printf("Umur       : %d tahun\n", umur);
    printf("IPK        : %.2f\n", ipk);
    printf("Nilai Pi   : %.5f\n\n", pi);
}

/* =====================================================
 * 3. Operator dan Ekspresi
 * ===================================================== */
void operatorDasar() {
    int a = 10, b = 3;

    garis();
    printf("3. OPERATOR DASAR\n");
    garis();
    printf("a = %d, b = %d\n", a, b);
    printf("a + b   = %d\n", a + b);
    printf("a - b   = %d\n", a - b);
    printf("a * b   = %d\n", a * b);
    printf("a / b   = %d  (integer division)\n", a / b);
    printf("a %% b   = %d  (modulus/sisa)\n", a % b);
    printf("a > b   = %d\n", a > b);
    printf("a == b  = %d\n\n", a == b);
}

/* =====================================================
 * 4. Kondisi (if-else)
 * ===================================================== */
void kondisiIfElse() {
    int nilai = 80;

    garis();
    printf("4. KONDISI IF-ELSE\n");
    garis();
    printf("Nilai mahasiswa : %d\n", nilai);

    if (nilai >= 85) {
        printf("Predikat : A\n");
    } else if (nilai >= 75) {
        printf("Predikat : B\n");
    } else if (nilai >= 60) {
        printf("Predikat : C\n");
    } else {
        printf("Predikat : D\n");
    }
    printf("\n");
}

/* =====================================================
 * 5. Perulangan (for, while)
 * ===================================================== */
void perulangan() {
    int i;

    garis();
    printf("5. PERULANGAN\n");
    garis();

    printf("For loop (1 sampai 5)  : ");
    for (i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("While loop (5 sampai 1) : ");
    i = 5;
    while (i >= 1) {
        printf("%d ", i);
        i--;
    }
    printf("\n\n");
}

/* =====================================================
 * 6. Array — struktur data dasar
 * ===================================================== */
void arrayDasar() {
    int angka[5] = {10, 20, 30, 40, 50};
    int i, jumlah = 0;

    garis();
    printf("6. ARRAY\n");
    garis();
    printf("Isi array : ");
    for (i = 0; i < 5; i++) {
        printf("%d ", angka[i]);
        jumlah += angka[i];
    }
    printf("\nJumlah    : %d\n", jumlah);
    printf("Rata-rata : %.2f\n\n", (float) jumlah / 5);
}

/* =====================================================
 * 7. Fungsi — modular programming
 * ===================================================== */
/* Fungsi menghitung faktorial secara rekursif */
int faktorial(int n) {
    if (n <= 1) return 1;
    return n * faktorial(n - 1);
}

void demoFungsi() {
    int n = 5;

    garis();
    printf("7. FUNGSI\n");
    garis();
    printf("Faktorial dari %d = %d\n\n", n, faktorial(n));
}

/* =====================================================
 * 8. Pointer — dasar-dasar
 * ===================================================== */
void demoPointer() {
    int nilai = 100;
    int *ptr  = &nilai;      /* ptr menyimpan alamat nilai */

    garis();
    printf("8. POINTER\n");
    garis();
    printf("Nilai variabel   : %d\n", nilai);
    printf("Alamat variabel  : %p\n", (void*) &nilai);
    printf("Isi pointer      : %p\n", (void*) ptr);
    printf("Nilai via pointer: %d\n", *ptr);

    /* Ubah nilai via pointer */
    *ptr = 200;
    printf("Setelah *ptr = 200, nilai = %d\n\n", nilai);
}

/* =====================================================
 * 9. System Call: getpid dan getppid
 *    Menampilkan PID (Process ID) dan PPID (Parent PID)
 * ===================================================== */
void demoSystemCall() {
    pid_t pid  = getpid();
    pid_t ppid = getppid();

    garis();
    printf("9. SYSTEM CALL (getpid, getppid)\n");
    garis();
    printf("PID  proses ini   : %d\n", pid);
    printf("PPID proses ini   : %d\n", ppid);
    printf("(PID = Process ID, PPID = Parent Process ID)\n\n");
}

/* =====================================================
 * 10. fork() — membuat proses baru
 *     fork() mengembalikan:
 *      - 0   : di proses anak
 *      - > 0 : di proses induk (nilainya adalah PID anak)
 *      - -1  : gagal
 * ===================================================== */
void demoFork() {
    pid_t pid;

    garis();
    printf("10. FORK - Membuat Proses Baru\n");
    garis();

    pid = fork();

    if (pid < 0) {
        /* fork gagal */
        fprintf(stderr, "Fork gagal!\n");
        exit(1);
    } else if (pid == 0) {
        /* == Bagian anak == */
        printf("  [ANAK]  PID saya = %d, PID induk saya = %d\n",
               getpid(), getppid());
    } else {
        /* == Bagian induk == */
        printf("  [INDUK] PID saya = %d, PID anak saya = %d\n",
               getpid(), pid);
    }
    printf("\n");
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    printf("\n");
    garis();
    printf("     PENGANTAR PEMROGRAMAN C UNTUK SISTEM OPERASI\n");
    printf("     Nama  : Satrio Nurcahya\n");
    printf("     NIM   : 1303180078\n");
    garis();
    printf("\n");

    /* Panggil semua demo secara berurutan */
    helloWorld();
    variabelTipeData();
    operatorDasar();
    kondisiIfElse();
    perulangan();
    arrayDasar();
    demoFungsi();
    demoPointer();
    demoSystemCall();
    demoFork();

    garis();
    printf("PROGRAM SELESAI.\n");
    garis();

    return 0;
}