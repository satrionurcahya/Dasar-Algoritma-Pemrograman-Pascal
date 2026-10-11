# Daftar Tugas - Organisasi dan Arsitektur Komputer

Kumpulan soal tugas mata kuliah **Organisasi dan Arsitektur Komputer** 
yang sudah disederhanakan. Semua program menggunakan **Assembly MIPS** 
dan dijalankan dengan simulator MARS / QtSPIM.

---

## Tugas 13 — Pemrograman Assembly MIPS

### 13.1 — Operasi Aritmetika

**Soal 1:** Hitung `a = b + c` dan `d = a − e` dengan b=20, c=10, e=5.
**Soal 2:** Hitung `f = (g + h) − (i + j)` dengan g=15, h=8, i=6, j=3.

**File:** `13.1_soal1.asm`, `13.1_soal2.asm`  
**Instruksi kunci:** `add`, `sub`

---

### 13.2 — Array dan Akses Memori

**Soal 1:** Hitung `g = h + A[3]` dengan A={10,20,30,40,50}, h=5.  
**Soal 2:** Hitung `A[2] = A[0] + A[1]` dengan A={4,7,10,12,15}.

**File:** `13.2_soal1.asm`, `13.2_soal2.asm`  
**Instruksi kunci:** `lw`, `sw`, perhitungan offset `i * 4`

---

### 13.3 — Percabangan Kondisional

**Soal 1:** `if (a > b) hasil = a; else hasil = b;` dengan a=25, b=18.  
**Soal 2:** `if (nilai >= 75) status = 1; else status = 0;` — uji 80 & 60.

**File:** `13.3_soal1.asm`, `13.3_soal2.asm`  
**Instruksi kunci:** `slt`, `beq`, `j`

---

### 13.4 — Perulangan dan Array

**Soal 1:** Hitung `jumlah = Σ A[i]` untuk A={2,4,6,8,10}.  
**Soal 2:** Hitung `jumlah = 1 + 2 + ... + n` dengan n=10.

**File:** `13.4_soal1.asm`, `13.4_soal2.asm`  
**Instruksi kunci:** label loop, `bge`, `bgt`, `j`

---

### 13.5 — Operasi Perkalian dan Kombinasi Aritmetika

**Soal 1:** `hasil = a × b` dengan a=12, b=8.  
**Soal 2:** `hasil = (a × b) + c` dengan a=7, b=6, c=10.  
**Soal 3:** `luas = panjang × lebar` dengan panjang=15, lebar=8.  
**Soal 4:** `hasil = (a × b) − (c × d)` dengan a=9, b=5, c=4, d=3.  
**Soal 5:** `hasil = n × n` dengan n=12.

**File:** `13.5_soal1.asm` s/d `13.5_soal5.asm`  
**Instruksi kunci:** `mult`, `mflo`, `add`, `sub`

---

## 📌 Ringkasan Konsep per Subtugas

| Subtugas | Konsep Utama | Instruksi |
|----------|--------------|-----------|
| 13.1 | Aritmetika dasar | `add`, `sub` |
| 13.2 | Akses memori array | `lw`, `sw`, `sll` |
| 13.3 | Percabangan | `slt`, `beq`, `j` |
| 13.4 | Perulangan | label, `bge`, `bgt`, `j` |
| 13.5 | Perkalian | `mult`, `mflo` |

---

## 🧠 Tips Mengerjakan

1. **Selalu mulai dari `.data`** — deklarasikan variabel dan string.
2. **Gunakan label yang deskriptif** — `loop`, `selesai`, `else_branch`.
3. **Beri komentar di setiap instruksi penting** — nilai yang disimpan, tujuan.
4. **Register yang sering dipakai:**
   - `$t0-$t9` → nilai sementara
   - `$s0-$s7` → nilai yang perlu disimpan
   - `$v0`, `$a0` → untuk syscall
5. **Untuk array**, alamat elemen ke-i = `base + i*4` (karena word = 4 byte).
6. **Perkalian** di MIPS menghasilkan 64-bit di HI:LO → ambil hasil dari LO via `mflo`.

---

## 📝 Format Pengumpulan

- 13 file `.asm` (satu per soal)
- Screenshot output setiap program
- Dijalankan di MARS / QtSPIM