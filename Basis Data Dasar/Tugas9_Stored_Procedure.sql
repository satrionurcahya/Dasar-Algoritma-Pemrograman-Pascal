-- =====================================================
-- TUGAS 9      : Stored Procedure
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g (PL/SQL)
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : Tugas9_Stored_Procedure.sql
-- =====================================================

-- WAJIB dijalankan sekali di awal supaya DBMS_OUTPUT bisa tampil:
SET SERVEROUTPUT ON;


-- =====================================================
-- PERSIAPAN : Cek data
-- =====================================================
SELECT * FROM kategori;
SELECT * FROM produk;



-- =====================================================
-- BAGIAN 1 : STORED PROCEDURE DASAR
-- =====================================================

-- 1.1 Procedure tampil_produk
CREATE OR REPLACE PROCEDURE tampil_produk
AS
    -- deklarasi variabel (opsional)
    v_nama_produk VARCHAR2(100);
BEGIN
    FOR rec IN (SELECT idProduk, nmProduk, harga, stok FROM produk) LOOP
        DBMS_OUTPUT.PUT_LINE(
            rec.idProduk || ' | ' ||
            rec.nmProduk || ' | Rp ' ||
            rec.harga    || ' | stok: ' ||
            rec.stok
        );
    END LOOP;
END;
/

-- 1.2 Procedure tampil_kategori
CREATE OR REPLACE PROCEDURE tampil_kategori
AS
BEGIN
    FOR rec IN (SELECT idKategori, nmKategori, deskripsi FROM kategori) LOOP
        DBMS_OUTPUT.PUT_LINE(
            rec.idKategori || ' | ' ||
            rec.nmKategori || ' | ' ||
            rec.deskripsi
        );
    END LOOP;
END;
/

-- Pemanggilan di Oracle pakai EXEC (bukan CALL seperti MySQL)
EXEC tampil_produk;
EXEC tampil_kategori;

-- Alternatif pemanggilan via PL/SQL block
-- BEGIN
--     tampil_produk;
--     tampil_kategori;
-- END;
-- /



-- =====================================================
-- BAGIAN 2 : STORED PROCEDURE DENGAN PARAMETER IN
-- =====================================================

-- 2.1 Procedure cari_produk berdasarkan ID
CREATE OR REPLACE PROCEDURE cari_produk (
    p_idProduk IN VARCHAR2
)
AS
BEGIN
    FOR rec IN (SELECT * FROM produk WHERE idProduk = p_idProduk) LOOP
        DBMS_OUTPUT.PUT_LINE('Produk ditemukan:');
        DBMS_OUTPUT.PUT_LINE('ID    : ' || rec.idProduk);
        DBMS_OUTPUT.PUT_LINE('Nama  : ' || rec.nmProduk);
        DBMS_OUTPUT.PUT_LINE('Harga : Rp ' || rec.harga);
        DBMS_OUTPUT.PUT_LINE('Stok  : ' || rec.stok);
    END LOOP;
END;
/

-- 2.2 Procedure cari_kategori berdasarkan ID
CREATE OR REPLACE PROCEDURE cari_kategori (
    p_idKategori IN VARCHAR2
)
AS
BEGIN
    FOR rec IN (SELECT * FROM kategori WHERE idKategori = p_idKategori) LOOP
        DBMS_OUTPUT.PUT_LINE('Kategori ditemukan:');
        DBMS_OUTPUT.PUT_LINE('ID        : ' || rec.idKategori);
        DBMS_OUTPUT.PUT_LINE('Nama      : ' || rec.nmKategori);
        DBMS_OUTPUT.PUT_LINE('Deskripsi : ' || rec.deskripsi);
    END LOOP;
END;
/

-- 2.3 Procedure produk_berdasarkan_harga
CREATE OR REPLACE PROCEDURE produk_berdasarkan_harga (
    p_harga IN NUMBER
)
AS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Produk dengan harga > ' || p_harga || ':');
    FOR rec IN (SELECT nmProduk, harga FROM produk WHERE harga > p_harga) LOOP
        DBMS_OUTPUT.PUT_LINE('  ' || rec.nmProduk || ' - Rp ' || rec.harga);
    END LOOP;
END;
/

-- Pemanggilan dengan nilai parameter berbeda
EXEC cari_produk('P001');
EXEC cari_produk('P005');
EXEC cari_kategori('KAT001');
EXEC produk_berdasarkan_harga(5000);
EXEC produk_berdasarkan_harga(10000);



-- =====================================================
-- BAGIAN 3 : STORED PROCEDURE UNTUK INSERT
-- =====================================================

CREATE OR REPLACE PROCEDURE tambah_produk (
    p_idProduk    IN VARCHAR2,
    p_idKategori  IN VARCHAR2,
    p_nmProduk    IN VARCHAR2,
    p_harga       IN NUMBER,
    p_spesifikasi IN VARCHAR2,
    p_view        IN NUMBER,
    p_stok        IN NUMBER
)
AS
BEGIN
    INSERT INTO produk (idProduk, idKategori, nmProduk, harga,
                        spesifikasi, view, stok)
    VALUES (p_idProduk, p_idKategori, p_nmProduk, p_harga,
            p_spesifikasi, p_view, p_stok);

    COMMIT;

    DBMS_OUTPUT.PUT_LINE('Produk ' || p_nmProduk || ' berhasil ditambahkan.');
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        DBMS_OUTPUT.PUT_LINE('ERROR: ID Produk ' || p_idProduk || ' sudah ada!');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('ERROR: ' || SQLERRM);
END;
/

-- Pemanggilan: tambah 2 produk baru
EXEC tambah_produk('P011', 'KAT001', 'Teh Botol',    5000, '350 ml',      0, 10);
EXEC tambah_produk('P012', 'KAT002', 'Keripik Kentang', 12000, '100 gr',  0, 15);

-- Cek hasil
SELECT * FROM produk WHERE idProduk IN ('P011', 'P012');



-- =====================================================
-- BAGIAN 4 : STORED PROCEDURE UNTUK UPDATE
-- =====================================================

-- 4.1 Procedure ubah_harga_produk
CREATE OR REPLACE PROCEDURE ubah_harga_produk (
    p_idProduk   IN VARCHAR2,
    p_hargaBaru  IN NUMBER
)
AS
    v_jumlah NUMBER;
BEGIN
    -- cek dulu produk ada atau tidak
    SELECT COUNT(*) INTO v_jumlah
    FROM produk
    WHERE idProduk = p_idProduk;

    IF v_jumlah = 0 THEN
        DBMS_OUTPUT.PUT_LINE('ERROR: Produk ' || p_idProduk || ' tidak ditemukan!');
    ELSE
        UPDATE produk
        SET harga = p_hargaBaru
        WHERE idProduk = p_idProduk;

        COMMIT;
        DBMS_OUTPUT.PUT_LINE('Harga produk ' || p_idProduk ||
                             ' berhasil diubah menjadi Rp ' || p_hargaBaru);
    END IF;
END;
/

-- 4.2 Procedure ubah_stok_produk
CREATE OR REPLACE PROCEDURE ubah_stok_produk (
    p_idProduk  IN VARCHAR2,
    p_stokBaru  IN NUMBER
)
AS
    v_jumlah NUMBER;
BEGIN
    SELECT COUNT(*) INTO v_jumlah
    FROM produk
    WHERE idProduk = p_idProduk;

    IF v_jumlah = 0 THEN
        DBMS_OUTPUT.PUT_LINE('ERROR: Produk ' || p_idProduk || ' tidak ditemukan!');
    ELSE
        UPDATE produk
        SET stok = p_stokBaru
        WHERE idProduk = p_idProduk;

        COMMIT;
        DBMS_OUTPUT.PUT_LINE('Stok produk ' || p_idProduk ||
                             ' berhasil diubah menjadi ' || p_stokBaru);
    END IF;
END;
/

-- Pemanggilan
EXEC ubah_harga_produk('P001', 4500);
EXEC ubah_stok_produk('P002', 20);

-- Cek hasil
SELECT idProduk, nmProduk, harga, stok FROM produk
WHERE idProduk IN ('P001', 'P002');



-- =====================================================
-- BAGIAN 5 : STORED PROCEDURE UNTUK DELETE
-- =====================================================

CREATE OR REPLACE PROCEDURE hapus_produk (
    p_idProduk IN VARCHAR2
)
AS
    v_jumlah NUMBER;
BEGIN
    SELECT COUNT(*) INTO v_jumlah
    FROM produk
    WHERE idProduk = p_idProduk;

    IF v_jumlah = 0 THEN
        DBMS_OUTPUT.PUT_LINE('ERROR: Produk ' || p_idProduk || ' tidak ditemukan!');
    ELSE
        DELETE FROM produk
        WHERE idProduk = p_idProduk;

        COMMIT;
        DBMS_OUTPUT.PUT_LINE('Produk ' || p_idProduk || ' berhasil dihapus.');
    END IF;
END;
/

-- Pemanggilan: hapus P012
EXEC hapus_produk('P012');

-- Cek hasil
SELECT * FROM produk WHERE idProduk = 'P012';   -- seharusnya kosong



-- =====================================================
-- BAGIAN 6 : STORED PROCEDURE DENGAN PARAMETER OUT
-- =====================================================

-- 6.1 Procedure hitung_jumlah_produk
CREATE OR REPLACE PROCEDURE hitung_jumlah_produk (
    p_jumlah OUT NUMBER
)
AS
BEGIN
    SELECT COUNT(*) INTO p_jumlah FROM produk;
END;
/

-- 6.2 Procedure hitung_total_stok
CREATE OR REPLACE PROCEDURE hitung_total_stok (
    p_totalStok OUT NUMBER
)
AS
BEGIN
    SELECT NVL(SUM(stok), 0) INTO p_totalStok FROM produk;
END;
/

-- Pemanggilan di Oracle: pakai VARIABLE untuk menampung output
VARIABLE v_jumlah NUMBER;
VARIABLE v_total  NUMBER;

EXEC hitung_jumlah_produk(:v_jumlah);
EXEC hitung_total_stok(:v_total);

PRINT v_jumlah;
PRINT v_total;

-- Alternatif pemanggilan via PL/SQL block
-- DECLARE
--     v_jml NUMBER;
--     v_tot NUMBER;
-- BEGIN
--     hitung_jumlah_produk(v_jml);
--     hitung_total_stok(v_tot);
--     DBMS_OUTPUT.PUT_LINE('Jumlah produk : ' || v_jml);
--     DBMS_OUTPUT.PUT_LINE('Total stok    : ' || v_tot);
-- END;
-- /



-- =====================================================
-- BAGIAN 7 : STORED PROCEDURE DENGAN PARAMETER IN OUT
-- =====================================================

CREATE OR REPLACE PROCEDURE tambah_nilai (
    p_nilai IN OUT NUMBER
)
AS
BEGIN
    p_nilai := p_nilai + 10;
END;
/

-- Pemanggilan dengan nilai awal 50
VARIABLE v_angka NUMBER;

BEGIN
    :v_angka := 50;
END;
/

EXEC tambah_nilai(:v_angka);
PRINT v_angka;      -- hasil: 60



-- =====================================================
-- BAGIAN 8 : STORED PROCEDURE DENGAN KONDISI IF
-- =====================================================

CREATE OR REPLACE PROCEDURE cek_stok (
    p_idProduk IN VARCHAR2
)
AS
    v_stok     NUMBER;
    v_nama     VARCHAR2(100);
BEGIN
    -- ambil stok dan nama produk
    BEGIN
        SELECT stok, nmProduk
        INTO v_stok, v_nama
        FROM produk
        WHERE idProduk = p_idProduk;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Produk ' || p_idProduk || ' tidak ditemukan.');
            RETURN;
    END;

    -- cek kondisi stok
    IF v_stok < 5 THEN
        DBMS_OUTPUT.PUT_LINE(v_nama || ' (stok: ' || v_stok || ') -> Stok Menipis');
    ELSE
        DBMS_OUTPUT.PUT_LINE(v_nama || ' (stok: ' || v_stok || ') -> Stok Aman');
    END IF;
END;
/

-- Uji dengan beberapa produk
EXEC cek_stok('P001');
EXEC cek_stok('P002');
EXEC cek_stok('P003');
EXEC cek_stok('P999');   -- produk tidak ada



-- =====================================================
-- CEK AKHIR
-- =====================================================

SELECT * FROM produk ORDER BY idProduk;