# Sistem Operasi

Kumpulan tugas mata kuliah **Sistem Operasi** menggunakan bahasa **C**, 
**POSIX Threads**, dan **Bash Scripting** di lingkungan **Linux** — Semester 3.

## 👤 Identitas

- **Nama** : Satrio Nurcahya
- **NIM**  : 1303180078
- **Kelas**: IT-42-01

## Environment

- **OS** : Linux (Ubuntu)
- **Bahasa** : C, Bash Scripting
- **Compiler** : GCC
- **Library** : POSIX Threads (pthread), OpenSSL (libcrypto)
- **Tools** : GPG, Crontab, At

## Daftar Tugas

Deskripsi lengkap setiap tugas ada di [Tugas_Sistem_Operasi.md](./Tugas_Sistem_Operasi.md).

| No | Topik | File Utama | Dokumentasi |
|----|-------|------------|-------------|
| 1 | Manajemen Proses Linux | `manajemen-proses.c` | [Tugas1/](./Tugas1/) |
| 2 | Simulasi Transaksi Bank (Pthreads) | `transaksi_bank.c` | [Tugas2/](./Tugas2/) |
| 3 | Simulasi Deadlock & Banker | `simulasi_deadlock.c` | [Tugas3/](./Tugas3/) |
| 4 | Manajemen Memori & Page Replacement | `simulasi-memori.c` | [Tugas4/](./Tugas4/) |
| 5 | Penjadwalan Proses & Crontab | `simulasi-penjadwalan.c` | [Tugas5/](./Tugas5/) |
| 6 | Penjadwalan Disk & File System | `simulasi_disk.c` | [Tugas6/](./Tugas6/) |
| 7 | Keamanan File (SHA-256 & GPG) | `simulasi_keamanan.c` | [Tugas7/](./Tugas7/) |
| 8 | Otomatisasi Administrasi Linux | `admin_lab.sh` | [Tugas8/](./Tugas8/) |

## Cara Compile & Jalankan

### Program C (Tugas 1–7)
```bash
# Compile standar
gcc -Wall -Wextra -std=c11 nama_file.c -o nama_file

# Jalankan
./nama_file