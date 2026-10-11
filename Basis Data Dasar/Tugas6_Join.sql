-- =====================================================
-- TUGAS 6      : Obtaining Data from Multiple Tables
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas6_Multiple_Tables_Oracle.sql
-- =====================================================

-- CATATAN: Di Oracle, tidak ada USE db_penjualan.
-- Pastikan login sebagai user yang memiliki schema db_penjualan.


-- =====================================================
-- PERSIAPAN : Drop tabel lama (pakai PL/SQL block)
-- =====================================================

BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE produk_supplier';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/

BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE supplier';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/

BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE rentang_harga';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/

BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE pegawai';
EXCEPTION WHEN OTHERS THEN NULL;
END;
/

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
-- PERSIAPAN : Buat tabel dasar (kategori & produk)
-- =====================================================

CREATE TABLE kategori (
    idKategori  VARCHAR2(10) PRIMARY KEY,
    nmKategori  VARCHAR2(50),
    deskripsi   VARCHAR2(100)
);

CREATE TABLE produk (
    idProduk    VARCHAR2(10) PRIMARY KEY,
    idKategori  VARCHAR2(10),
    nmProduk    VARCHAR2(100),
    harga       NUMBER,
    spesifikasi VARCHAR2(100),
    view        NUMBER,
    stok        NUMBER,
    CONSTRAINT fk_produk_kat FOREIGN KEY (idKategori)
        REFERENCES kategori(idKategori)
);

-- Insert data kategori
INSERT INTO kategori VALUES ('KAT001', 'Minuman',    'Minuman');
INSERT INTO kategori VALUES ('KAT002', 'Kategori 2', 'Makanan');
INSERT INTO kategori VALUES ('KAT003', 'Kategori 3', 'ATK');
INSERT INTO kategori VALUES ('KAT004', 'Kategori 4', 'Tools');

-- Insert data produk
INSERT INTO produk VALUES ('P001', 'KAT001', 'Teh Kotak',      4500,  'Teh 250ml',       120, 50);
INSERT INTO produk VALUES ('P002', 'KAT001', 'Air Mineral',    3000,  'Botol 600ml',     200, 20);
INSERT INTO produk VALUES ('P003', 'KAT001', 'Kopi Sachet',    2500,  'Kopi instan',     150, 40);
INSERT INTO produk VALUES ('P004', 'KAT002', 'Roti Tawar',     12000, 'Roti gandum',     80,  25);
INSERT INTO produk VALUES ('P005', 'KAT002', 'Biskuit Coklat', 8000,  'Biskuit 200gr',   95,  30);
INSERT INTO produk VALUES ('P006', 'KAT002', 'Mie Instan',     3500,  'Mie goreng',      300, 60);
INSERT INTO produk VALUES ('P007', 'KAT003', 'Pulpen',         3000,  'Pulpen hitam',    60,  100);
INSERT INTO produk VALUES ('P008', 'KAT003', 'Buku Tulis',     5000,  'Buku 38 lembar',  75,  80);
INSERT INTO produk VALUES ('P009', 'KAT004', 'Obeng Set',      25000, 'Obeng 6 in 1',    40,  10);
INSERT INTO produk VALUES ('P010', 'KAT004', 'Gunting Kecil',  15000, 'Gunting Besar',   30,  12);

COMMIT;


-- =====================================================
-- PERSIAPAN : Tabel tambahan
-- =====================================================

-- Tabel pegawai (untuk SELF JOIN)
CREATE TABLE pegawai (
    idPegawai  NUMBER PRIMARY KEY,
    nmPegawai  VARCHAR2(50),
    idAtasan   NUMBER
);

INSERT INTO pegawai VALUES (1, 'Pak Direktur',   NULL);
INSERT INTO pegawai VALUES (2, 'Bu Manajer',     1);
INSERT INTO pegawai VALUES (3, 'Pak Supervisor', 2);
INSERT INTO pegawai VALUES (4, 'Andi Staff',     3);
INSERT INTO pegawai VALUES (5, 'Budi Staff',     3);
INSERT INTO pegawai VALUES (6, 'Citra Staff',    2);

-- Tabel rentang_harga (untuk NON-EQUIJOIN)
CREATE TABLE rentang_harga (
    idRentang     NUMBER PRIMARY KEY,
    kategoriHarga VARCHAR2(30),
    hargaMin      NUMBER,
    hargaMax      NUMBER
);

INSERT INTO rentang_harga VALUES (1, 'Murah',  0,    3000);
INSERT INTO rentang_harga VALUES (2, 'Sedang', 3001, 7000);
INSERT INTO rentang_harga VALUES (3, 'Mahal',  7001, 100000);

-- Tabel supplier
CREATE TABLE supplier (
    idSupplier  VARCHAR2(10) PRIMARY KEY,
    nmSupplier  VARCHAR2(50),
    kota        VARCHAR2(30)
);

INSERT INTO supplier VALUES ('SUP01', 'PT Sumber Rejeki', 'Jakarta');
INSERT INTO supplier VALUES ('SUP02', 'CV Maju Jaya',     'Bandung');
INSERT INTO supplier VALUES ('SUP03', 'UD Sejahtera',     'Surabaya');

-- Tabel produk_supplier (many-to-many)
CREATE TABLE produk_supplier (
    idProduk   VARCHAR2(10),
    idSupplier VARCHAR2(10),
    CONSTRAINT pk_prod_sup PRIMARY KEY (idProduk, idSupplier),
    CONSTRAINT fk_ps_produk FOREIGN KEY (idProduk)
        REFERENCES produk(idProduk),
    CONSTRAINT fk_ps_supplier FOREIGN KEY (idSupplier)
        REFERENCES supplier(idSupplier)
);

INSERT INTO produk_supplier VALUES ('P001', 'SUP01');
INSERT INTO produk_supplier VALUES ('P002', 'SUP01');
INSERT INTO produk_supplier VALUES ('P003', 'SUP02');
INSERT INTO produk_supplier VALUES ('P004', 'SUP02');
INSERT INTO produk_supplier VALUES ('P005', 'SUP03');
INSERT INTO produk_supplier VALUES ('P006', 'SUP01');
INSERT INTO produk_supplier VALUES ('P007', 'SUP03');

COMMIT;



-- =====================================================
-- BAGIAN 1 : OBTAINING DATA FROM MULTIPLE TABLES
-- =====================================================

-- 1.1 Produk + nama kategori (implicit join)
SELECT p.idProduk, p.nmProduk, p.harga, k.nmKategori
FROM produk p, kategori k
WHERE p.idKategori = k.idKategori;

-- 1.2 idProduk, nmProduk, harga, nmKategori
SELECT p.idProduk, p.nmProduk, p.harga, k.nmKategori
FROM produk p
JOIN kategori k ON p.idKategori = k.idKategori;

-- 1.3 Semua kolom produk + deskripsi kategori
SELECT p.*, k.deskripsi
FROM produk p
JOIN kategori k ON p.idKategori = k.idKategori;



-- =====================================================
-- BAGIAN 2 : CARTESIAN PRODUCT
-- =====================================================

-- 2.1 Seluruh kombinasi produk × kategori
SELECT *
FROM produk, kategori;

-- 2.2 Hitung jumlah baris Cartesian Product
SELECT COUNT(*) AS jumlah_kombinasi
FROM produk, kategori;

-- 2.3 Cek jumlah baris tiap tabel
SELECT
    (SELECT COUNT(*) FROM produk)   AS jumlah_produk,
    (SELECT COUNT(*) FROM kategori) AS jumlah_kategori
FROM dual;
-- Catatan: Oracle butuh FROM dual untuk SELECT tanpa tabel.



-- =====================================================
-- BAGIAN 3 : CROSS JOIN
-- =====================================================

-- 3.1 Cross Join produk × kategori
SELECT p.nmProduk, k.nmKategori
FROM produk p
CROSS JOIN kategori k;

-- 3.2 Cross Join supplier × rentang_harga
SELECT s.nmSupplier, r.kategoriHarga
FROM supplier s
CROSS JOIN rentang_harga r;



-- =====================================================
-- BAGIAN 4 : NATURAL JOIN
-- =====================================================

-- 4.1 Natural Join produk & kategori
SELECT nmProduk, harga, nmKategori
FROM produk
NATURAL JOIN kategori;



-- =====================================================
-- BAGIAN 5 : INNER JOIN / EQUIJOIN
-- =====================================================

-- 5.1 Nama produk, harga, stok, nama kategori
SELECT p.nmProduk, p.harga, p.stok, k.nmKategori
FROM produk p
INNER JOIN kategori k ON p.idKategori = k.idKategori;

-- 5.2 Produk kategori KAT002
SELECT p.nmProduk, p.harga, p.stok, k.nmKategori
FROM produk p
INNER JOIN kategori k ON p.idKategori = k.idKategori
WHERE p.idKategori = 'KAT002';

-- 5.3 INNER JOIN pakai nama tabel penuh
SELECT produk.idProduk, produk.nmProduk, kategori.nmKategori
FROM produk
INNER JOIN kategori
    ON produk.idKategori = kategori.idKategori;



-- =====================================================
-- BAGIAN 6 : OUTER JOIN (Oracle support FULL OUTER)
-- =====================================================

-- 6.1 FULL OUTER JOIN langsung (tanpa UNION)
SELECT p.nmProduk, k.nmKategori
FROM produk p
FULL OUTER JOIN kategori k ON p.idKategori = k.idKategori;



-- =====================================================
-- BAGIAN 7 : LEFT OUTER JOIN
-- =====================================================

-- 7.1 Semua kategori + produknya
SELECT k.nmKategori, p.nmProduk, p.harga
FROM kategori k
LEFT JOIN produk p ON k.idKategori = p.idKategori;

-- 7.2 Kategori yang belum punya produk
SELECT k.idKategori, k.nmKategori
FROM kategori k
LEFT JOIN produk p ON k.idKategori = p.idKategori
WHERE p.idProduk IS NULL;

-- 7.3 Pakai NVL (bukan IFNULL)
SELECT k.nmKategori,
       NVL(p.nmProduk, '(belum ada produk)') AS nmProduk,
       p.harga
FROM kategori k
LEFT JOIN produk p ON k.idKategori = p.idKategori;



-- =====================================================
-- BAGIAN 8 : RIGHT OUTER JOIN
-- =====================================================

-- 8.1 Semua produk + nama kategori
SELECT p.nmProduk, p.harga, k.nmKategori
FROM produk p
RIGHT JOIN kategori k ON p.idKategori = k.idKategori;

-- 8.2 Semua produk
SELECT p.nmProduk, k.nmKategori
FROM kategori k
RIGHT JOIN produk p ON p.idKategori = k.idKategori;



-- =====================================================
-- BAGIAN 9 : FULL OUTER JOIN
-- =====================================================

-- 9.1 FULL OUTER JOIN (Oracle support langsung!)
SELECT k.nmKategori, p.nmProduk, p.harga
FROM kategori k
FULL OUTER JOIN produk p ON k.idKategori = p.idKategori;

-- 9.2 Alternatif pakai UNION (kalau mau sama seperti MySQL)
SELECT k.nmKategori, p.nmProduk, p.harga
FROM kategori k
LEFT JOIN produk p ON k.idKategori = p.idKategori
UNION
SELECT k.nmKategori, p.nmProduk, p.harga
FROM kategori k
RIGHT JOIN produk p ON k.idKategori = p.idKategori;



-- =====================================================
-- BAGIAN 10 : SELF JOIN
-- =====================================================

-- 10.1 Pegawai + nama atasannya
SELECT p.nmPegawai  AS pegawai,
       a.nmPegawai  AS atasan
FROM pegawai p
LEFT JOIN pegawai a ON p.idAtasan = a.idPegawai;

-- 10.2 Pegawai tanpa atasan
SELECT p.nmPegawai
FROM pegawai p
LEFT JOIN pegawai a ON p.idAtasan = a.idPegawai
WHERE a.idPegawai IS NULL;



-- =====================================================
-- BAGIAN 11 : NON-EQUIJOIN
-- =====================================================

-- 11.1 Produk + kategori harga (BETWEEN)
SELECT p.nmProduk, p.harga, r.kategoriHarga
FROM produk p
JOIN rentang_harga r
    ON p.harga BETWEEN r.hargaMin AND r.hargaMax;

-- 11.2 Produk kategori harga "Mahal"
SELECT p.nmProduk, p.harga, r.kategoriHarga
FROM produk p
JOIN rentang_harga r
    ON p.harga BETWEEN r.hargaMin AND r.hargaMax
WHERE r.kategoriHarga = 'Mahal';

-- 11.3 Gabungan 3 tabel
SELECT k.nmKategori,
       p.nmProduk,
       p.harga,
       r.kategoriHarga
FROM produk p
JOIN kategori k      ON p.idKategori = k.idKategori
JOIN rentang_harga r ON p.harga BETWEEN r.hargaMin AND r.hargaMax
ORDER BY k.nmKategori, p.harga;