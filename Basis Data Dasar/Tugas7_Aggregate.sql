-- =====================================================
-- TUGAS 7      : Aggregate Functions
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas7_Aggregate.sql
-- =====================================================

-- Pastikan sudah menjalankan Tugas 4-6 terlebih dahulu.
-- Tabel yang digunakan: kategori, produk


-- =====================================================
-- PERSIAPAN : Cek data tersedia
-- =====================================================
SELECT * FROM kategori;
SELECT * FROM produk;

-- Pastikan ada minimal 10 produk
SELECT COUNT(*) AS jumlah_produk FROM produk;



-- =====================================================
-- BAGIAN 1 : COUNT() — Menghitung jumlah data
-- =====================================================

-- 1.1 Jumlah seluruh produk
SELECT COUNT(*) AS jumlah_produk
FROM produk;

-- 1.2 Jumlah produk kategori KAT002
SELECT COUNT(*) AS jumlah_produk_kat002
FROM produk
WHERE idKategori = 'KAT002';

-- 1.3 Jumlah kategori
SELECT COUNT(*) AS jumlah_kategori
FROM kategori;

-- 1.4 Jumlah produk dengan stok > 5
SELECT COUNT(*) AS jumlah_produk_stok_lebih_5
FROM produk
WHERE stok > 5;



-- =====================================================
-- BAGIAN 2 : SUM() — Menghitung total nilai
-- =====================================================

-- 2.1 Total seluruh stok produk
SELECT SUM(stok) AS total_stok
FROM produk;

-- 2.2 Total nilai persediaan setiap produk (harga * stok)
SELECT nmProduk,
       harga,
       stok,
       harga * stok AS nilai_persediaan
FROM produk;

-- 2.3 Total nilai persediaan seluruh produk
SELECT SUM(harga * stok) AS total_nilai_persediaan
FROM produk;

-- 2.4 Total stok produk untuk kategori KAT003
SELECT SUM(stok) AS total_stok_kat003
FROM produk
WHERE idKategori = 'KAT003';



-- =====================================================
-- BAGIAN 3 : AVG() — Menghitung nilai rata-rata
-- =====================================================

-- 3.1 Rata-rata harga seluruh produk
SELECT AVG(harga) AS rata_rata_harga
FROM produk;

-- 3.2 Rata-rata stok seluruh produk
SELECT AVG(stok) AS rata_rata_stok
FROM produk;

-- 3.3 Rata-rata harga produk kategori KAT002
SELECT AVG(harga) AS rata_rata_harga_kat002
FROM produk
WHERE idKategori = 'KAT002';

-- 3.4 Rata-rata jumlah view seluruh produk
SELECT AVG(view) AS rata_rata_view
FROM produk;



-- =====================================================
-- BAGIAN 4 : MAX() dan MIN() — Nilai tertinggi & terendah
-- =====================================================

-- 4.1 Harga produk tertinggi
SELECT MAX(harga) AS harga_tertinggi
FROM produk;

-- 4.2 Harga produk terendah
SELECT MIN(harga) AS harga_terendah
FROM produk;

-- 4.3 Jumlah stok terbesar
SELECT MAX(stok) AS stok_terbesar
FROM produk;

-- 4.4 Jumlah view terkecil
SELECT MIN(view) AS view_terkecil
FROM produk;

-- 4.5 Harga tertinggi & terendah untuk kategori KAT003
SELECT MAX(harga) AS harga_tertinggi_kat003,
       MIN(harga) AS harga_terendah_kat003
FROM produk
WHERE idKategori = 'KAT003';



-- =====================================================
-- BAGIAN 5 : GROUP BY — Mengelompokkan data
-- =====================================================

-- 5.1 Jumlah produk untuk setiap kategori
SELECT idKategori,
       COUNT(*) AS jumlah_produk
FROM produk
GROUP BY idKategori
ORDER BY idKategori;

-- 5.2 Total stok untuk setiap kategori
SELECT idKategori,
       SUM(stok) AS total_stok
FROM produk
GROUP BY idKategori
ORDER BY idKategori;

-- 5.3 Rata-rata harga produk untuk setiap kategori
SELECT idKategori,
       AVG(harga) AS rata_rata_harga
FROM produk
GROUP BY idKategori
ORDER BY idKategori;

-- 5.4 Total nilai persediaan untuk setiap kategori
SELECT idKategori,
       SUM(harga * stok) AS total_nilai_persediaan
FROM produk
GROUP BY idKategori
ORDER BY idKategori;

-- 5.5 Jumlah produk berdasarkan kategori, urut idKategori
SELECT idKategori,
       COUNT(*) AS jumlah_produk
FROM produk
GROUP BY idKategori
ORDER BY idKategori ASC;



-- =====================================================
-- BAGIAN 6 : HAVING — Menyaring hasil pengelompokan
-- =====================================================

-- 6.1 Kategori dengan lebih dari 2 produk
SELECT idKategori,
       COUNT(*) AS jumlah_produk
FROM produk
GROUP BY idKategori
HAVING COUNT(*) > 2;

-- 6.2 Kategori dengan total stok lebih dari 10
SELECT idKategori,
       SUM(stok) AS total_stok
FROM produk
GROUP BY idKategori
HAVING SUM(stok) > 10;

-- 6.3 Kategori dengan rata-rata harga > Rp5.000
SELECT idKategori,
       AVG(harga) AS rata_rata_harga
FROM produk
GROUP BY idKategori
HAVING AVG(harga) > 5000;

-- 6.4 Kategori dengan total nilai persediaan > Rp50.000
SELECT idKategori,
       SUM(harga * stok) AS total_nilai_persediaan
FROM produk
GROUP BY idKategori
HAVING SUM(harga * stok) > 50000;



-- =====================================================
-- BAGIAN 7 : Kombinasi Aggregate Functions
-- =====================================================

-- 7.1 Jumlah produk, rata-rata harga, harga tertinggi & terendah per kategori
SELECT idKategori,
       COUNT(*)     AS jumlah_produk,
       AVG(harga)   AS rata_rata_harga,
       MAX(harga)   AS harga_tertinggi,
       MIN(harga)   AS harga_terendah
FROM produk
GROUP BY idKategori
ORDER BY idKategori;

-- 7.2 Kategori + jumlah produk + total stok (JOIN + GROUP BY)
SELECT k.idKategori,
       k.nmKategori,
       COUNT(p.idProduk) AS jumlah_produk,
       SUM(p.stok)       AS total_stok
FROM kategori k
LEFT JOIN produk p ON k.idKategori = p.idKategori
GROUP BY k.idKategori, k.nmKategori
ORDER BY k.idKategori;

-- 7.3 Kategori dengan >2 produk DAN rata-rata harga > Rp3.000
SELECT k.idKategori,
       k.nmKategori,
       COUNT(p.idProduk) AS jumlah_produk,
       AVG(p.harga)      AS rata_rata_harga
FROM kategori k
JOIN produk p ON k.idKategori = p.idKategori
GROUP BY k.idKategori, k.nmKategori
HAVING COUNT(p.idProduk) > 2
   AND AVG(p.harga) > 3000
ORDER BY k.idKategori;