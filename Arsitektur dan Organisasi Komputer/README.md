# Organisasi dan Arsitektur Komputer

Kumpulan tugas mata kuliah **Organisasi dan Arsitektur Komputer (COA)** 
menggunakan **Assembly MIPS** — Semester 3.

## 👤 Identitas

- **Nama** : Satrio Nurcahya
- **NIM**  : 1303180078
- **Kelas**: IT-42-01

## Environment

- **Bahasa** : Assembly MIPS
- **Simulator** : MARS / QtSPIM
- **Editor** : Visual Studio Code

## Daftar Tugas

Deskripsi lengkap setiap tugas ada di [Tugas_13.md](./Tugas_13.md).

| No | Topik | Folder |
|----|-------|--------|
| 13 | Pemrograman Assembly MIPS | [Tugas13/](./Tugas13/) |

## Cara Menjalankan

### MARS Simulator
1. Download MARS dari [courses.missouristate.edu](http://courses.missouristate.edu/KenVollmar/mars/)
2. Buka MARS → **File → Open** → pilih file `.asm`
3. Tekan **F3** (Assemble) lalu **F5** (Run)
4. Lihat output di tab **Run I/O**

### QtSPIM
1. Download QtSPIM dari [spimsimulator.sourceforge.net](http://spimsimulator.sourceforge.net/)
2. Buka QtSPIM → **File → Load File** → pilih `.asm`
3. Tekan **F5** (Run)
4. Lihat output di console

### VS Code (dengan extension)
1. Install ekstensi **MIPS Support** atau **MIPS Assembly**
2. Install MARS / QtSPIM
3. Jalankan `.asm` via task atau terminal

## Catatan Register MIPS

| Register | Nama | Fungsi |
|----------|------|--------|
| `$zero` | 0 | Konstanta 0 |
| `$t0-$t9` | Temp | Nilai sementara |
| `$s0-$s7` | Saved | Nilai yang disimpan |
| `$a0-$a3` | Argument | Argumen fungsi / parameter syscall |
| `$v0-$v1` | Value | Nilai kembalian / kode syscall |
| `$ra` | Return | Alamat kembali |
| `$sp` | Stack Pointer | Pointer stack |

## Kode Syscall yang Sering Dipakai

| Kode `$v0` | Fungsi |
|------------|--------|
| 1 | `print_int` — cetak integer di `$a0` |
| 4 | `print_string` — cetak string dari `$a0` |
| 5 | `read_int` — baca integer ke `$v0` |
| 10 | `exit` — keluar program |

## Instruksi Penting

| Instruksi | Kegunaan |
|-----------|----------|
| `add`, `sub` | Aritmetika dasar |
| `mult`, `mflo` | Perkalian (LO:HI) |
| `lw`, `sw` | Load/Store word |
| `beq`, `bne` | Branch if (not) equal |
| `slt`, `slti` | Set less than |
| `bge`, `bgt`, `ble`, `blt` | Branch perbandingan |
| `j` | Jump tak bersyarat |
| `sll`, `srl` | Shift left/right |