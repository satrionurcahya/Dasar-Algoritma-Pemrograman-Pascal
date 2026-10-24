/* =====================================================
 * TUGAS 5      : Simulasi Manajemen Penjadwalan Proses
 * MK           : Sistem Operasi
 * Nama         : Satrio Nurcahya
 * NIM          : 1303180078
 * Kelas        : IT-42-01
 * File         : simulasi_penjadwalan.c
 * Compile      : gcc -Wall -Wextra -std=c11 simulasi_penjadwalan.c -o simulasi_penjadwalan
 * Run          : ./simulasi_penjadwalan
 * ===================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =====================================================
 * KONFIGURASI
 * ===================================================== */
#define MAX 20

/* =====================================================
 * STRUKTUR DATA PROSES
 * ===================================================== */
typedef struct {
    int id;
    int at;      // Arrival Time
    int bt;      // Burst Time
    int pr;      // Priority (semakin kecil semakin tinggi)
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
    int st;      // Start Time (pertama kali dieksekusi)
    int rt;      // Response Time
    int rem_bt;  // Remaining Burst Time (untuk RR)
} Process;

Process proses[MAX];
int n;

/* Array global untuk Gantt Chart */
int gantt_ids[MAX * MAX];
int gantt_times[MAX * MAX];
int gantt_count;

/* =====================================================
 * FUNGSI BANTU
 * ===================================================== */
void garis() {
    printf("=================================================================\n");
}

void reset_gantt() {
    gantt_count = 0;
}

void tambah_gantt(int id, int time_start, int time_end) {
    if (gantt_count > 0 && gantt_ids[gantt_count - 1] == id) {
        gantt_times[gantt_count] = time_end; // Extend blok yang sama
    } else {
        gantt_ids[gantt_count] = id;
        gantt_times[gantt_count] = time_start;
        gantt_count++;
        gantt_times[gantt_count] = time_end;
    }
}

void tampilkanGanttChart() {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_count; i++) {
        if (gantt_ids[i] == 0) printf("| Idle ");
        else printf("|  P%d  ", gantt_ids[i]);
    }
    printf("|\n");
    for (int i = 0; i <= gantt_count; i++) {
        printf("%-6d", gantt_times[i]);
    }
    printf("\n");
}

void cetak_tabel(Process p[], int n, const char* nama_algo) {
    garis();
    printf("  HASIL PENJADWALAN - %s\n", nama_algo);
    garis();
    printf("%-5s %-5s %-5s %-5s | %-5s %-5s %-5s %-5s %-5s\n",
           "ID", "AT", "BT", "PR", "CT", "TAT", "WT", "RT", "ST");
    printf("-----------------------------------------------------\n");
    
    float total_tat = 0, total_wt = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%-4d %-5d %-5d %-5d | %-5d %-5d %-5d %-5d %-5d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr, 
               p[i].ct, p[i].tat, p[i].wt, p[i].rt, p[i].st);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
    }
    printf("-----------------------------------------------------\n");
    printf("Rata-rata TAT : %.2f\n", total_tat / n);
    printf("Rata-rata WT  : %.2f\n", total_wt / n);
    printf("Rata-rata RT  : %.2f\n\n", total_rt / n);
}

void inputProses() {
    int pilihan;
    garis();
    printf("  INPUT DATA PROSES\n");
    garis();
    printf("1. Gunakan data default (5 proses)\n");
    printf("2. Input manual\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        n = 5;
        int at[] = {0, 1, 2, 3, 4};
        int bt[] = {5, 3, 8, 6, 2};
        int pr[] = {3, 1, 4, 2, 5};
        for (int i = 0; i < n; i++) {
            proses[i].id = i + 1;
            proses[i].at = at[i];
            proses[i].bt = bt[i];
            proses[i].pr = pr[i];
        }
        printf("Data default berhasil dimuat.\n");
    } else {
        printf("Jumlah proses (max %d): ", MAX);
        if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
            printf("Input tidak valid!\n");
            exit(1);
        }
        for (int i = 0; i < n; i++) {
            proses[i].id = i + 1;
            printf("\nProses P%d:\n", i + 1);
            printf("  Arrival Time (>=0): ");
            while(scanf("%d", &proses[i].at) != 1 || proses[i].at < 0) {
                printf("  Invalid! Masukkan >=0: ");
                while(getchar() != '\n');
            }
            printf("  Burst Time (>0)   : ");
            while(scanf("%d", &proses[i].bt) != 1 || proses[i].bt <= 0) {
                printf("  Invalid! Masukkan >0: ");
                while(getchar() != '\n');
            }
            printf("  Priority (>0)     : ");
            while(scanf("%d", &proses[i].pr) != 1 || proses[i].pr <= 0) {
                printf("  Invalid! Masukkan >0: ");
                while(getchar() != '\n');
            }
        }
    }
}

/* =====================================================
 * 1. ALGORITMA FCFS (First Come First Served)
 * ===================================================== */
void simulasiFCFS() {
    Process p[MAX];
    for (int i = 0; i < n; i++) p[i] = proses[i];

    // Urutkan berdasarkan Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || 
               (p[j].at == p[j + 1].at && p[j].id > p[j + 1].id)) {
                Process temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    reset_gantt();
    gantt_times[0] = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at;
            tambah_gantt(0, gantt_times[gantt_count], current_time); // Idle
        }
        p[i].st = current_time;
        p[i].rt = p[i].st - p[i].at;
        
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        tambah_gantt(p[i].id, p[i].st, p[i].ct);
    }
    tampilkanGanttChart();
    cetak_tabel(p, n, "FCFS");
}

/* =====================================================
 * 2. ALGORITMA ROUND ROBIN
 * ===================================================== */
void simulasiRR(int quantum) {
    Process p[MAX];
    for (int i = 0; i < n; i++) {
        p[i] = proses[i];
        p[i].rem_bt = p[i].bt;
        p[i].st = -1;
    }

    // Sort by AT untuk memudahkan queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || 
               (p[j].at == p[j + 1].at && p[j].id > p[j + 1].id)) {
                Process temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    int completed = 0;
    int queue[MAX], front = 0, rear = 0;
    bool in_queue[MAX] = {false};
    int idx = 0;

    reset_gantt();
    gantt_times[0] = 0;

    // Masukkan proses yang tiba di t=0
    while (idx < n && p[idx].at <= current_time) {
        queue[rear++] = idx; in_queue[idx] = true; idx++;
    }

    while (completed < n) {
        if (front == rear) {
            // Queue kosong, lompat ke kedatangan berikutnya
            if (idx < n) {
                if (current_time < p[idx].at) {
                    current_time = p[idx].at;
                    tambah_gantt(0, gantt_times[gantt_count], current_time);
                }
                while (idx < n && p[idx].at <= current_time) {
                    queue[rear++] = idx; in_queue[idx] = true; idx++;
                }
            }
            continue;
        }

        int i = queue[front++];
        in_queue[i] = false;

        if (p[i].st == -1) {
            p[i].st = current_time;
            p[i].rt = p[i].st - p[i].at;
        }

        int exec_time = (p[i].rem_bt > quantum) ? quantum : p[i].rem_bt;
        current_time += exec_time;
        p[i].rem_bt -= exec_time;
        
        tambah_gantt(p[i].id, current_time - exec_time, current_time);

        // Masukkan proses baru yang tiba selama eksekusi
        while (idx < n && p[idx].at <= current_time) {
            queue[rear++] = idx; in_queue[idx] = true; idx++;
        }

        if (p[i].rem_bt > 0) {
            queue[rear++] = i; // Masukkan kembali ke antrean
            in_queue[i] = true;
        } else {
            p[i].ct = current_time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }
    
    char nama[30];
    sprintf(nama, "Round Robin (Q=%d)", quantum);
    tampilkanGanttChart();
    cetak_tabel(p, n, nama);
}

/* =====================================================
 * 3. ALGORITMA PRIORITY SCHEDULING (Non-Preemptive)
 * ===================================================== */
void simulasiPriority() {
    Process p[MAX];
    for (int i = 0; i < n; i++) {
        p[i] = proses[i];
        p[i].rem_bt = p[i].bt;
    }

    int current_time = 0;
    int completed = 0;
    bool is_completed[MAX] = {false};

    reset_gantt();
    gantt_times[0] = 0;

    while (completed < n) {
        int idx_terpilih = -1;
        int prioritas_terbaik = 999999;

        // Cari proses yang sudah tiba dan belum selesai
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && p[i].at <= current_time) {
                // Semakin kecil angka prioritas, semakin tinggi prioritasnya
                if (p[i].pr < prioritas_terbaik) {
                    prioritas_terbaik = p[i].pr;
                    idx_terpilih = i;
                } else if (p[i].pr == prioritas_terbaik) {
                    // Tie-breaker: Arrival Time lebih awal
                    if (p[i].at < p[idx_terpilih].at) {
                        idx_terpilih = i;
                    } else if (p[i].at == p[idx_terpilih].at && p[i].id < p[idx_terpilih].id) {
                        idx_terpilih = i;
                    }
                }
            }
        }

        if (idx_terpilih != -1) {
            // Eksekusi sampai selesai (Non-preemptive)
            p[idx_terpilih].st = current_time;
            p[idx_terpilih].rt = p[idx_terpilih].st - p[idx_terpilih].at;
            
            current_time += p[idx_terpilih].bt;
            p[idx_terpilih].ct = current_time;
            p[idx_terpilih].tat = p[idx_terpilih].ct - p[idx_terpilih].at;
            p[idx_terpilih].wt = p[idx_terpilih].tat - p[idx_terpilih].bt;
            
            tambah_gantt(p[idx_terpilih].id, 
                         current_time - p[idx_terpilih].bt, 
                         current_time);
            
            is_completed[idx_terpilih] = true;
            completed++;
        } else {
            // Tidak ada proses yang tersedia, maju waktu
            int next_at = 999999;
            for (int i = 0; i < n; i++) {
                if (!is_completed[i] && p[i].at > current_time && p[i].at < next_at) {
                    next_at = p[i].at;
                }
            }
            if (next_at != 999999) {
                tambah_gantt(0, current_time, next_at);
                current_time = next_at;
            }
        }
    }
    tampilkanGanttChart();
    cetak_tabel(p, n, "Priority Scheduling (Non-Preemptive)");
}

/* =====================================================
 * PROGRAM UTAMA
 * ===================================================== */
int main() {
    int pilihan, quantum;

    printf("\n");
    garis();
    printf("   SIMULASI PENJADWALAN PROSES\n");
    printf("   Nama  : Satrio Nurcahya\n");
    printf("   NIM   : 1303180078\n");
    printf("   Kelas : IT-42-01\n");
    garis();
    printf("\n");

    inputProses();

    do {
        printf("\n");
        garis();
        printf("  MENU ALGORITMA\n");
        garis();
        printf("1. FCFS (First Come First Served)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Priority Scheduling (Non-Preemptive)\n");
        printf("4. Tampilkan Perbandingan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }

        switch (pilihan) {
            case 1:
                simulasiFCFS();
                break;
            case 2:
                printf("Masukkan Time Quantum: ");
                if (scanf("%d", &quantum) != 1 || quantum <= 0) {
                    printf("Quantum harus > 0!\n");
                    break;
                }
                simulasiRR(quantum);
                break;
            case 3:
                simulasiPriority();
                break;
            case 4:
                printf("\n>>> Jalankan ketiga algoritma untuk melihat perbandingan <<<\n");
                simulasiFCFS();
                simulasiRR(2);
                simulasiPriority();
                break;
            case 0:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}