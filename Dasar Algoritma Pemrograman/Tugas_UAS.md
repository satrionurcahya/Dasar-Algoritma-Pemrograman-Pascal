# Tugas Pengantar UAS — Mesin Abstrak

## Deskripsi
Buatlah program yang menerapkan **mesin abstrak** untuk memproses data 
berupa **teks** dan **bilangan**.

## Ketentuan
1. **Input** dapat berasal dari dua sumber:
   - Manual melalui keyboard (akhiri dengan titik `.`)
   - File teks (`.txt`) dibaca sampai `EOF`
2. **Mesin Karakter** menggunakan variabel:
   - `Pita_Karakter : string`
   - `Indeks : integer`
   - `CC : char`
3. **Analisis Teks** menghitung:
   - Jumlah karakter, vokal, konsonan, spasi, dan kata
4. **Array** digunakan untuk menyimpan kumpulan bilangan.
5. Terapkan **4 algoritma sorting**:
   - Counting Sort
   - Bubble Sort
   - Insertion Sort
   - Selection Sort
6. Terapkan **2 algoritma searching**:
   - Sequential Search
   - Binary Search
7. Sorting dan searching **wajib dibuat sendiri**, tidak boleh pakai fungsi bawaan.

## Prosedur yang Wajib Dibuat

| Nama Prosedur | Tanggung Jawab |
|---------------|----------------|
| `START` | Memulai pembacaan mesin karakter dari awal pita |
| `ADV` | Memajukan pembacaan ke karakter berikutnya |
| `InputManual` | Menerima input teks/bilangan dari keyboard |
| `BacaFile` | Membaca data dari file teks |
| `AnalisisKarakter` | Menghitung karakter, vokal, konsonan, spasi, kata |
| `TampilArray` | Menampilkan isi array |
| `CountingSort` | Mengurutkan array dengan Counting Sort |
| `BubbleSort` | Mengurutkan array dengan Bubble Sort |
| `InsertionSort` | Mengurutkan array dengan Insertion Sort |
| `SelectionSort` | Mengurutkan array dengan Selection Sort |
| `TampilMenu` | Menampilkan pilihan operasi program |
| `TampilHasilPencarian` | Menampilkan nilai yang dicari & hasilnya |

## Fungsi yang Wajib Dibuat

| Nama Fungsi | Nilai Kembalian |
|-------------|-----------------|
| `IsVokal(CC)` | Boolean — benar jika karakter adalah huruf vokal |
| `IsKonsonan(CC)` | Boolean — benar jika karakter adalah huruf konsonan |
| `HitungKata(Pita_Karakter)` | Integer — jumlah kata dalam teks |
| `SequentialSearch(A, n, x)` | Integer — posisi data ditemukan, atau -1 |
| `BinarySearch(A, n, x)` | Integer — posisi data ditemukan, atau -1 |

**Keterangan parameter:**
- `A` : array bilangan
- `n` : jumlah elemen array
- `x` : nilai yang dicari
- `CC`: karakter yang sedang diproses

## Output
- Hasil analisis teks
- Array sebelum & sesudah sorting
- Hasil pencarian (posisi data / pesan tidak ditemukan)

## Pengumpulan
- File program: `mesin_abstrak.pas`