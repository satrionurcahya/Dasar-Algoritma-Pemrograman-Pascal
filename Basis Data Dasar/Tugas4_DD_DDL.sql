-- =====================================================
-- TUGAS 4      : DDL dan DML Dasar
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas4_DDL_DML.sql
-- =====================================================

-- CATATAN: Di Oracle, tidak ada CREATE DATABASE / USE.
-- Pastikan login sebagai user/schema db_penjualan.


-- =====================================================
-- PERSIAPAN : Drop tabel lama kalau ada
-- =====================================================
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE produk';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/

BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE kategori';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/


-- =====================================================
-- BAGIAN A : DDL (Data Definition Language)
-- =====================================================

-- 1. Membuat tabel kategori
CREATE TABLE kategori (
    idKategori  VARCHAR2(10) PRIMARY KEY,
    nmKategori  VARCHAR2(50),
    deskripsi   VARCHAR2(100)
);


-- 2. Membuat tabel produk dengan foreign key ke kategori
CREATE TABLE produk (
    idProduk    VARCHAR2(10) PRIMARY KEY,
    idKategori  VARCHAR2(10),
    nmProduk    VARCHAR2(50),
    harga       NUMBER,
    spesifikasi VARCHAR2(100),
    view        NUMBER,
    stok        NUMBER,
    CONSTRAINT fk_produk_kategori
        FOREIGN KEY (idKategori) REFERENCES kategori(idKategori)
);


-- 3. Menambahkan kolom tanggalInput pada tabel produk
ALTER TABLE produk
ADD tanggalInput DATE;


-- 4. Mengubah tipe data kolom nmProduk menjadi VARCHAR2(100)
ALTER TABLE produk
MODIFY nmProduk VARCHAR2(100);


-- 5. Menghapus kolom tanggalInput dari tabel produk
ALTER TABLE produk
DROP COLUMN tanggalInput;


-- 6. Membuat tabel supplier
CREATE TABLE supplier (
    idSupplier  VARCHAR2(10) PRIMARY KEY,
    nmSupplier  VARCHAR2(50),
    alamat      VARCHAR2(100)
);


-- 7. Menghapus tabel supplier
DROP TABLE supplier;



-- =====================================================
-- BAGIAN B : DML (Data Manipulation Language)
-- =====================================================

-- -----------------------------------------------------
-- B.1 INSERT — Menambahkan data
-- -----------------------------------------------------

-- 1. Memasukkan 4 data kategori
INSERT INTO kategori (idKategori, nmKategori, deskripsi) VALUES
    ('KAT001', 'Kategori 1', 'Minuman');
INSERT INTO kategori (idKategori, nmKategori, deskripsi) VALUES
    ('KAT002', 'Kategori 2', 'Makanan');
INSERT INTO kategori (idKategori, nmKategori, deskripsi) VALUES
    ('KAT003', 'Kategori 3', 'ATK');
INSERT INTO kategori (idKategori, nmKategori, deskripsi) VALUES
    ('KAT004', 'Kategori 4', 'Tools');

-- 2. Memasukkan 10 data produk
INSERT INTO produk VALUES ('P001', 'KAT001', 'Teh Kotak',      5000,  'Teh 250ml',      120, 50);
INSERT INTO produk VALUES ('P002', 'KAT001', 'Air Mineral',    3000,  'Botol 600ml',    200, 15);
INSERT INTO produk VALUES ('P003', 'KAT001', 'Kopi Sachet',    2500,  'Kopi instan',    150, 40);
INSERT INTO produk VALUES ('P004', 'KAT002', 'Roti Tawar',     12000, 'Roti gandum',    80,  25);
INSERT INTO produk VALUES ('P005', 'KAT002', 'Biskuit Coklat', 8000,  'Biskuit 200gr',  95,  30);
INSERT INTO produk VALUES ('P006', 'KAT002', 'Mie Instan',     3500,  'Mie goreng',     300, 60);
INSERT INTO produk VALUES ('P007', 'KAT003', 'Pulpen',         3000,  'Pulpen hitam',   60,  100);
INSERT INTO produk VALUES ('P008', 'KAT003', 'Buku Tulis',     5000,  'Buku 38 lembar', 75,  80);
INSERT INTO produk VALUES ('P009', 'KAT004', 'Obeng Set',      25000, 'Obeng 6 in 1',   40,  10);
INSERT INTO produk VALUES ('P010', 'KAT004', 'Gunting Kecil',  15000, 'Gunting sedang', 30,  12);

-- WAJIB: Simpan perubahan
COMMIT;


-- -----------------------------------------------------
-- B.2 UPDATE — Mengubah data
-- -----------------------------------------------------

-- 1. Mengubah nama kategori KAT001 menjadi "Minuman"
UPDATE kategori
SET nmKategori = 'Minuman'
WHERE idKategori = 'KAT001';

-- 2. Mengubah harga produk P001 menjadi 4500
UPDATE produk
SET harga = 4500
WHERE idProduk = 'P001';

-- 3. Mengubah stok produk P002 menjadi 20
UPDATE produk
SET stok = 20
WHERE idProduk = 'P002';

-- 4. Mengubah spesifikasi produk P010 menjadi "Gunting Besar"
UPDATE produk
SET spesifikasi = 'Gunting Besar'
WHERE idProduk = 'P010';

COMMIT;


-- -----------------------------------------------------
-- B.3 DELETE — Menghapus data
-- -----------------------------------------------------

-- 1. Menghapus produk dengan ID P009
DELETE FROM produk
WHERE idProduk = 'P009';

-- 2. Menghapus produk dengan ID P010
DELETE FROM produk
WHERE idProduk = 'P010';

-- 3. Menghapus kategori KAT004 (setelah produk terkait dihapus)
DELETE FROM kategori
WHERE idKategori = 'KAT004';

COMMIT;


-- =====================================================
-- CEK HASIL AKHIR
-- =====================================================

SELECT * FROM kategori;
SELECT * FROM produk;