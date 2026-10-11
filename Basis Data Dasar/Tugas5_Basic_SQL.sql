-- =====================================================
-- TUGAS 5      : Basic SQL, SELECT, Arithmetic, WHERE, Sorting
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas5_Basic_SQL.sql
-- =====================================================

-- Pastikan sudah menjalankan Tugas 4 terlebih dahulu.


-- =====================================================
-- PERSIAPAN : Pastikan data tersedia
-- =====================================================

SELECT * FROM kategori;
SELECT * FROM produk;

-- Tambahkan kembali data yang mungkin terhapus (opsional)
-- Pakai MERGE untuk menghindari duplikat
MERGE INTO kategori k
USING (SELECT 'KAT004' AS idKategori, 'Kategori 4' AS nmKategori, 'Tools' AS deskripsi FROM dual) s
ON (k.idKategori = s.idKategori)
WHEN NOT MATCHED THEN
   INSERT (idKategori, nmKategori, deskripsi)
   VALUES (s.idKategori, s.nmKategori, s.deskripsi);

MERGE INTO produk p
USING (SELECT 'P009' AS idProduk, 'KAT004' AS idKategori, 'Obeng Set' AS nmProduk,
              25000 AS harga, 'Obeng 6 in 1' AS spesifikasi, 40 AS view, 10 AS stok FROM dual) s
ON (p.idProduk = s.idProduk)
WHEN NOT MATCHED THEN
   INSERT VALUES (s.idProduk, s.idKategori, s.nmProduk, s.harga, s.spesifikasi, s.view, s.stok);

MERGE INTO produk p
USING (SELECT 'P010' AS idProduk, 'KAT004' AS idKategori, 'Gunting Kecil' AS nmProduk,
              15000 AS harga, 'Gunting Besar' AS spesifikasi, 30 AS view, 12 AS stok FROM dual) s
ON (p.idProduk = s.idProduk)
WHEN NOT MATCHED THEN
   INSERT VALUES (s.idProduk, s.idKategori, s.nmProduk, s.harga, s.spesifikasi, s.view, s.stok);

COMMIT;



-- =====================================================
-- BAGIAN 1 : BASIC SQL dan SELECT STATEMENT
-- =====================================================

-- 1.1 Seluruh data dari tabel kategori
SELECT * FROM kategori;

-- 1.2 Seluruh data dari tabel produk
SELECT * FROM produk;

-- 1.3 Kolom idProduk, nmProduk, dan harga
SELECT idProduk, nmProduk, harga FROM produk;

-- 1.4 Kolom nmProduk, spesifikasi, dan stok
SELECT nmProduk, spesifikasi, stok FROM produk;

-- 1.5 Kolom idKategori dan nmKategori dari kategori
SELECT idKategori, nmKategori FROM kategori;



-- =====================================================
-- BAGIAN 2 : ARITHMETIC OPERATORS
-- =====================================================

-- 2.1 Harga + Rp2.000
SELECT nmProduk,
       harga,
       harga + 2000 AS harga_setelah_tambah
FROM produk;

-- 2.2 Harga - Rp500
SELECT nmProduk,
       harga,
       harga - 500 AS harga_setelah_kurang
FROM produk;

-- 2.3 Total persediaan (harga * stok)
SELECT nmProduk,
       harga,
       stok,
       harga * stok AS total_persediaan
FROM produk;

-- 2.4 Harga setelah diskon Rp1.000
SELECT nmProduk,
       harga,
       harga - 1000 AS harga_setelah_diskon
FROM produk;

-- 2.5 Harga per dua unit
SELECT nmProduk,
       harga,
       harga / 2 AS harga_per_dua_unit
FROM produk;



-- =====================================================
-- BAGIAN 3 : WHERE CLAUSE
-- =====================================================

-- 3.1 Produk dengan harga > 5000
SELECT * FROM produk WHERE harga > 5000;

-- 3.2 Produk dengan harga < 5000
SELECT * FROM produk WHERE harga < 5000;

-- 3.3 Produk dengan stok >= 5
SELECT * FROM produk WHERE stok >= 5;

-- 3.4 Produk dengan stok < 5
SELECT * FROM produk WHERE stok < 5;

-- 3.5 Produk dengan kategori KAT002
SELECT * FROM produk WHERE idKategori = 'KAT002';

-- 3.6 Produk dengan harga antara Rp2.000 - Rp7.000
SELECT * FROM produk WHERE harga BETWEEN 2000 AND 7000;

-- 3.7 Produk dengan kategori KAT001 atau KAT003
SELECT * FROM produk WHERE idKategori IN ('KAT001', 'KAT003');

-- 3.8 Produk dengan nama diawali huruf I
SELECT * FROM produk WHERE nmProduk LIKE 'I%';

-- 3.9 Harga > 3000 AND stok > 3
SELECT * FROM produk WHERE harga > 3000 AND stok > 3;

-- 3.10 Harga < 3000 OR stok > 5
SELECT * FROM produk WHERE harga < 3000 OR stok > 5;



-- =====================================================
-- BAGIAN 4 : SORTING (ORDER BY)
-- =====================================================

-- 4.1 Harga termurah → termahal
SELECT * FROM produk ORDER BY harga ASC;

-- 4.2 Harga termahal → termurah
SELECT * FROM produk ORDER BY harga DESC;

-- 4.3 Nama alfabetis A → Z
SELECT * FROM produk ORDER BY nmProduk ASC;

-- 4.4 Stok paling sedikit → paling banyak
SELECT * FROM produk ORDER BY stok ASC;

-- 4.5 Kategori ASC, lalu harga DESC
SELECT * FROM produk ORDER BY idKategori ASC, harga DESC;