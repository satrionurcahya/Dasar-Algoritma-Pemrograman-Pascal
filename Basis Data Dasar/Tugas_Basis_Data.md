
---

## File 2: `Tugas_Basis_Data.md`

```markdown
# Daftar Tugas - Basis Data Dasar

Kumpulan soal tugas mata kuliah **Basis Data Dasar** yang sudah 
disederhanakan. Semua tugas dikerjakan menggunakan **Oracle 11g**.

---

## Tugas 4 — DDL dan DML Dasar

**Topik:** Data Definition Language & Data Manipulation Language

**Soal:**
Buat database `db_penjualan` dengan dua tabel:
- `kategori` (idKategori, nmKategori, deskripsi)
- `produk` (idProduk, idKategori, nmProduk, harga, spesifikasi, view, stok)

**Ketentuan DDL:**
- Buat tabel dengan primary key dan foreign key.
- Tambah kolom `tanggalInput` (DATE) ke tabel produk, lalu hapus lagi.
- Ubah tipe `nmProduk` menjadi VARCHAR2(100).
- Buat tabel `supplier`, lalu hapus.

**Ketentuan DML:**
- Insert 4 kategori dan 10 produk.
- Update nama kategori, harga produk, stok produk, spesifikasi produk.
- Delete produk P009, P010, dan kategori KAT004.

---

## Tugas 5 — Basic SQL, SELECT, WHERE, Sorting

**Topik:** Query dasar SQL

**Soal:**
Gunakan tabel `kategori` dan `produk` dari Tugas 4.

**Ketentuan:**
- Tampilkan data dengan `SELECT` (semua kolom, sebagian kolom).
- Gunakan operator aritmatika: `+`, `-`, `*`, `/`.
  - Harga + 2000, harga - 500, harga × stok, diskon, harga / 2.
- Filter dengan `WHERE`:
  - Perbandingan: `>`, `<`, `>=`, `<=`.
  - `BETWEEN`, `IN`, `LIKE`, `AND`, `OR`.
- Urutkan dengan `ORDER BY`:
  - Harga ASC/DESC, nama ASC, stok ASC.
  - Multi kolom: kategori ASC lalu harga DESC.

---

## Tugas 6 — Obtaining Data from Multiple Tables (JOIN)

**Topik:** Menggabungkan data dari beberapa tabel

**Soal:**
Gunakan tabel dari Tugas 4 + tambahan (pegawai, supplier, rentang_harga).

**Ketentuan:**
- **Cartesian Product** — semua kombinasi produk × kategori.
- **CROSS JOIN** — sama seperti Cartesian Product.
- **NATURAL JOIN** — join otomatis berdasarkan kolom bernama sama.
- **INNER JOIN / EQUIJOIN** — hanya baris yang cocok.
- **LEFT / RIGHT / FULL OUTER JOIN** — termasuk yang tidak punya pasangan.
- **SELF JOIN** — tabel pegawai (pegawai + atasannya).
- **NON-EQUIJOIN** — join dengan kondisi `BETWEEN` (produk + rentang harga).

---

## Tugas 7 — Aggregate Functions

**Topik:** Fungsi agregat dan GROUP BY

**Soal:**
Gunakan tabel `kategori` dan `produk`.

**Ketentuan:**
- **COUNT()** — jumlah produk, kategori, produk per kondisi.
- **SUM()** — total stok, total nilai persediaan, total per kategori.
- **AVG()** — rata-rata harga, stok, view.
- **MAX() / MIN()** — harga tertinggi/terendah, stok terbesar, view terkecil.
- **GROUP BY** — kelompokkan per kategori.
- **HAVING** — filter hasil agregasi (misal: kategori dengan >2 produk).
- Kombinasi agregat + JOIN + GROUP BY + HAVING.

---

## Tugas 8 — Subquery

**Topik:** Query di dalam query

**Soal:**
Gunakan tabel `kategori` dan `produk`.

**Ketentuan:**
- **Subquery dengan operator pembanding** (`>`, `<`, `=`) — bandingkan 
  dengan hasil subquery agregat.
- **IN / NOT IN** — filter berdasarkan daftar nilai dari subquery.
- **Subquery dengan fungsi agregat** — MAX, MIN, AVG untuk filter.
- **Subquery pada FROM** — membuat tabel virtual.
- **EXISTS / NOT EXISTS** — cek keberadaan baris.
- **ANY / ALL** — perbandingan dengan multi-row subquery.
- **Nested subquery** — subquery di dalam subquery.

---

## Tugas 9 — Stored Procedure

**Topik:** Procedure di Oracle PL/SQL

**Soal:**
Gunakan tabel `kategori` dan `produk`.

**Ketentuan:**
- **Procedure dasar** tanpa parameter — tampilkan data.
- **Parameter IN** — cari produk berdasarkan ID / harga.
- **INSERT via procedure** — tambah produk baru.
- **UPDATE via procedure** — ubah harga / stok.
- **DELETE via procedure** — hapus produk berdasarkan ID.
- **Parameter OUT** — kembalikan nilai (jumlah produk, total stok).
- **Parameter IN OUT** — modifikasi nilai input.
- **Kondisi IF** — cek stok (menipis / aman).

---

## Tugas Besar — Perancangan Basis Data Menu Asrama iGracias

**Topik:** Perancangan basis data relasional (analisis + implementasi)

**Soal:**
Rancang basis data untuk menu **Asrama** pada sistem informasi iGracias.

**Ketentuan:**
1. **Analisis proses bisnis** — alur mahasiswa mengakses layanan asrama.
2. **Aturan bisnis** — ketentuan yang mengatur relasi antarentitas.
3. **Identifikasi entitas & atribut** — minimal 7 entitas utama.
4. **Relasi & kardinalitas** — 1:1, 1:N, M:N.
5. **Rancangan relasional** — tabel, PK, FK, integritas data.
6. **Implementasi SQL** di Oracle 11g.

**Entitas Utama:**
- `Mahasiswa`
- `Asrama_Mahasiswa`
- `InformasiTtgAsrama`
- `Help_desk`
- `Kemahasiswaan`
- `Form_Pindahkmr`
- `Informasikamarasrama`
- `PenangananPindahKamar` (tabel penghubung M:N)

**Output:**
- File SQL implementasi: `TugasBesar_iGracias.sql`
- Dokumentasi BAB I–VII: `TugasBesar_README.md`
- ERD dan skema relasional: `TugasBesar_ERD.md`

---

## Ringkasan Konsep per Tugas

| Tugas | Konsep Utama |
|-------|--------------|
| 4 | DDL (`CREATE`, `ALTER`, `DROP`), DML (`INSERT`, `UPDATE`, `DELETE`), PK & FK |
| 5 | `SELECT`, operator aritmatika, `WHERE`, `ORDER BY` |
| 6 | `JOIN` (7 jenis), Cartesian Product, SELF JOIN, NON-EQUIJOIN |
| 7 | `COUNT`, `SUM`, `AVG`, `MAX`, `MIN`, `GROUP BY`, `HAVING` |
| 8 | Subquery (WHERE, FROM, SELECT), `IN`, `EXISTS`, `ANY`, `ALL` |
| 9 | PL/SQL Procedure, parameter IN/OUT/IN OUT, `IF`, Exception |
| TB | Analisis proses bisnis, ERD, normalisasi, implementasi relasional |

---

## Tools yang Digunakan

- **Oracle SQL Developer** — untuk run script & lihat output
- **SQL*Plus** — command line interface
- **Oracle Live SQL** — online (https://livesql.oracle.com)
- **Draw.io / dbdiagram.io** — untuk ERD (opsional)