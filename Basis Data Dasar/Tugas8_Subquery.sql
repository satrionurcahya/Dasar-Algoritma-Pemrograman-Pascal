-- =====================================================
-- TUGAS 8      : Subquery dalam SQL
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas8_Subquery.sql
-- =====================================================

-- Pastikan sudah menjalankan Tugas 4-7.
-- Tabel: kategori, produk


-- =====================================================
-- PERSIAPAN : Cek data
-- =====================================================
SELECT * FROM kategori;
SELECT * FROM produk;



-- =====================================================
-- BAGIAN 1 : SUBQUERY DENGAN OPERATOR PEMBANDING
-- =====================================================

-- 1.1 Produk dengan harga lebih tinggi dari rata-rata
SELECT nmProduk, harga
FROM produk
WHERE harga > (SELECT AVG(harga) FROM produk);

-- 1.2 Produk dengan harga lebih rendah dari rata-rata
SELECT nmProduk, harga
FROM produk
WHERE harga < (SELECT AVG(harga) FROM produk);

-- 1.3 Produk dengan stok lebih besar dari stok P001
SELECT nmProduk, stok
FROM produk
WHERE stok > (SELECT stok FROM produk WHERE idProduk = 'P001');

-- 1.4 Produk dengan harga sama dengan harga P003
SELECT nmProduk, harga
FROM produk
WHERE harga = (SELECT harga FROM produk WHERE idProduk = 'P003');

-- 1.5 Produk dengan view lebih besar dari rata-rata view
SELECT nmProduk, view
FROM produk
WHERE view > (SELECT AVG(view) FROM produk);



-- =====================================================
-- BAGIAN 2 : SUBQUERY DENGAN IN dan NOT IN
-- =====================================================

-- 2.1 Produk dari kategori bernama "Kategori 2"
SELECT nmProduk, idKategori
FROM produk
WHERE idKategori IN (
    SELECT idKategori
    FROM kategori
    WHERE nmKategori = 'Kategori 2'
);

-- 2.2 Produk dari kategori KAT001 atau KAT003
SELECT nmProduk, idKategori
FROM produk
WHERE idKategori IN ('KAT001', 'KAT003');

-- 2.2 (versi subquery) — alternatif pakai subquery
SELECT nmProduk, idKategori
FROM produk
WHERE idKategori IN (
    SELECT idKategori
    FROM kategori
    WHERE idKategori IN ('KAT001', 'KAT003')
);

-- 2.3 Kategori yang memiliki produk dengan harga di atas Rp5.000
SELECT idKategori, nmKategori
FROM kategori
WHERE idKategori IN (
    SELECT idKategori
    FROM produk
    WHERE harga > 5000
);

-- 2.4 Kategori yang belum memiliki produk (NOT IN)
SELECT idKategori, nmKategori
FROM kategori
WHERE idKategori NOT IN (
    SELECT DISTINCT idKategori
    FROM produk
    WHERE idKategori IS NOT NULL
);



-- =====================================================
-- BAGIAN 3 : SUBQUERY DENGAN FUNGSI AGREGAT
-- =====================================================

-- 3.1 Produk dengan harga tertinggi
SELECT nmProduk, harga
FROM produk
WHERE harga = (SELECT MAX(harga) FROM produk);

-- 3.2 Produk dengan harga terendah
SELECT nmProduk, harga
FROM produk
WHERE harga = (SELECT MIN(harga) FROM produk);

-- 3.3 Produk dengan stok di atas rata-rata stok
SELECT nmProduk, stok
FROM produk
WHERE stok > (SELECT AVG(stok) FROM produk);

-- 3.4 Produk dengan harga > rata-rata harga kategori yang sama
SELECT p.nmProduk, p.idKategori, p.harga
FROM produk p
WHERE p.harga > (
    SELECT AVG(p2.harga)
    FROM produk p2
    WHERE p2.idKategori = p.idKategori
);



-- =====================================================
-- BAGIAN 4 : SUBQUERY PADA KLAUSA FROM
-- =====================================================

-- 4.1 Rata-rata harga produk per kategori (pakai subquery FROM)
SELECT idKategori, rata_rata_harga
FROM (
    SELECT idKategori,
           AVG(harga) AS rata_rata_harga
    FROM produk
    GROUP BY idKategori
)
ORDER BY idKategori;

-- 4.2 Kategori dengan rata-rata harga > Rp5.000
SELECT idKategori, rata_rata_harga
FROM (
    SELECT idKategori,
           AVG(harga) AS rata_rata_harga
    FROM produk
    GROUP BY idKategori
)
WHERE rata_rata_harga > 5000;

-- 4.3 Kategori beserta total stoknya (pakai subquery FROM)
SELECT k.idKategori,
       k.nmKategori,
       NVL(d.total_stok, 0) AS total_stok
FROM kategori k
LEFT JOIN (
    SELECT idKategori, SUM(stok) AS total_stok
    FROM produk
    GROUP BY idKategori
) d ON k.idKategori = d.idKategori
ORDER BY k.idKategori;



-- =====================================================
-- BAGIAN 5 : SUBQUERY DENGAN EXISTS dan NOT EXISTS
-- =====================================================

-- 5.1 Kategori yang punya minimal 1 produk (EXISTS)
SELECT k.idKategori, k.nmKategori
FROM kategori k
WHERE EXISTS (
    SELECT 1
    FROM produk p
    WHERE p.idKategori = k.idKategori
);

-- 5.2 Kategori yang tidak punya produk (NOT EXISTS)
SELECT k.idKategori, k.nmKategori
FROM kategori k
WHERE NOT EXISTS (
    SELECT 1
    FROM produk p
    WHERE p.idKategori = k.idKategori
);

-- 5.3 Produk yang kategorinya punya minimal 1 produk lain dengan harga > 5000
SELECT p.nmProduk, p.idKategori, p.harga
FROM produk p
WHERE EXISTS (
    SELECT 1
    FROM produk p2
    WHERE p2.idKategori = p.idKategori
      AND p2.harga > 5000
      AND p2.idProduk <> p.idProduk
);



-- =====================================================
-- BAGIAN 6 : SUBQUERY DENGAN ANY dan ALL
-- =====================================================

-- 6.1 Produk dengan harga > salah satu harga produk KAT002 (ANY)
SELECT nmProduk, harga
FROM produk
WHERE harga > ANY (
    SELECT harga
    FROM produk
    WHERE idKategori = 'KAT002'
);
-- Sama dengan: harga > MIN(harga) pada KAT002

-- 6.2 Produk dengan harga > seluruh harga produk KAT002 (ALL)
SELECT nmProduk, harga
FROM produk
WHERE harga > ALL (
    SELECT harga
    FROM produk
    WHERE idKategori = 'KAT002'
);
-- Sama dengan: harga > MAX(harga) pada KAT002

-- 6.3 Produk dengan stok < seluruh stok produk KAT003 (ALL)
SELECT nmProduk, stok
FROM produk
WHERE stok < ALL (
    SELECT stok
    FROM produk
    WHERE idKategori = 'KAT003'
);
-- Sama dengan: stok < MIN(stok) pada KAT003



-- =====================================================
-- BAGIAN 7 : NESTED SUBQUERY
-- =====================================================

-- 7.1 Produk dari kategori dengan rata-rata harga tertinggi
SELECT nmProduk, idKategori, harga
FROM produk
WHERE idKategori = (
    SELECT idKategori
    FROM (
        SELECT idKategori,
               AVG(harga) AS rata2
        FROM produk
        GROUP BY idKategori
        ORDER BY rata2 DESC
    )
    WHERE ROWNUM = 1
);

-- 7.2 Kategori yang memiliki produk dengan harga tertinggi
SELECT k.idKategori, k.nmKategori
FROM kategori k
WHERE k.idKategori IN (
    SELECT idKategori
    FROM produk
    WHERE harga = (SELECT MAX(harga) FROM produk)
);

-- 7.3 Produk dengan harga > rata-rata harga kategori yang jumlah produknya terbanyak
SELECT nmProduk, idKategori, harga
FROM produk
WHERE harga > (
    SELECT AVG(harga)
    FROM produk
    WHERE idKategori = (
        SELECT idKategori
        FROM (
            SELECT idKategori, COUNT(*) AS jumlah
            FROM produk
            GROUP BY idKategori
            ORDER BY jumlah DESC
        )
        WHERE ROWNUM = 1
    )
);