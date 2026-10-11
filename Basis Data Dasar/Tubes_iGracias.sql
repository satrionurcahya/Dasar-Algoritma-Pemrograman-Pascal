-- =====================================================
-- TUGAS BESAR  : Perancangan Basis Data Menu Asrama
--                Sistem Informasi iGracias
-- MK           : Basis Data Dasar
-- DBMS         : Oracle 11g
-- Nama         : Satrio Nurcahya
-- NIM          : 1303180078
-- Kelas        : IT-42-01
-- File         : TugasBesar_iGracias.sql
-- =====================================================

SET SERVEROUTPUT ON;


-- =====================================================
-- BAGIAN 0 : DROP TABEL (kalau sudah ada)
-- =====================================================
BEGIN EXECUTE IMMEDIATE 'DROP TABLE PenangananPindahKamar CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Form_Pindahkmr        CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Informasikamarasrama  CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Asrama_Mahasiswa      CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE InformasiTtgAsrama    CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Help_desk             CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Kemahasiswaan         CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/
BEGIN EXECUTE IMMEDIATE 'DROP TABLE Mahasiswa             CASCADE CONSTRAINTS'; EXCEPTION WHEN OTHERS THEN NULL; END;
/


-- =====================================================
-- BAGIAN 1 : DDL — MEMBUAT TABEL
-- =====================================================

-- 1. Tabel MAHASISWA
CREATE TABLE Mahasiswa (
    NIM              VARCHAR2(15)  PRIMARY KEY,
    Nama_mhs         VARCHAR2(50)  NOT NULL,
    TglLahir         DATE,
    Tempat_lahir     VARCHAR2(30),
    Jenis_kelamin    CHAR(1)       CHECK (Jenis_kelamin IN ('L','P')),
    Golongan_Darah   CHAR(2),
    Agama            VARCHAR2(20),
    Nomorhp          VARCHAR2(15),
    Email            VARCHAR2(50),
    Provinsi_asal    VARCHAR2(30),
    Kabkotaasal      VARCHAR2(30),
    Kodepos_asal     VARCHAR2(6),
    Alamat_bandung   VARCHAR2(100),
    Nama_wilayah     VARCHAR2(50),
    Kodepos_bandung  VARCHAR2(6),
    Angkatan         NUMBER(4)
);

-- 2. Tabel ASRAMA_MAHASISWA
CREATE TABLE Asrama_Mahasiswa (
    Asrama_Id      VARCHAR2(10) PRIMARY KEY,
    Gedung_asrama  VARCHAR2(30) NOT NULL,
    Ruang_asrama   VARCHAR2(10),
    Lantai_asrama  NUMBER(2),
    Id_helpdesk    VARCHAR2(10)      -- FK ke Help_desk
);

-- 3. Tabel INFORMASI_TTG_ASRAMA
CREATE TABLE InformasiTtgAsrama (
    IdInformasiasrama       VARCHAR2(10) PRIMARY KEY,
    Denah                   VARCHAR2(200),
    UserManualFor_Dormitory VARCHAR2(200),
    InformasiUndurasrama    VARCHAR2(500)
);

-- 4. Tabel HELP_DESK
CREATE TABLE Help_desk (
    Id_helpdesk      VARCHAR2(10) PRIMARY KEY,
    Nama_helpdesk    VARCHAR2(50) NOT NULL,
    Jenis_kelaminhd  CHAR(1) CHECK (Jenis_kelaminhd IN ('L','P'))
);

-- 5. Tabel KEMAHASISWAAN
CREATE TABLE Kemahasiswaan (
    Id_kemahasiswaan  VARCHAR2(10) PRIMARY KEY,
    Nama_admin        VARCHAR2(50) NOT NULL
);

-- 6. Tabel FORM_PINDAHKMR
CREATE TABLE Form_Pindahkmr (
    Id_formpindah         VARCHAR2(10) PRIMARY KEY,
    NIM                   VARCHAR2(15) NOT NULL,
    Alasan                VARCHAR2(200),
    Ruang_br              VARCHAR2(10),
    Gedung_br             VARCHAR2(30),
    Tanggal_pengajuan     DATE DEFAULT SYSDATE,
    Status_permohonan     VARCHAR2(15)
        CHECK (Status_permohonan IN ('Menunggu','Disetujui','Ditolak')),
    Catatan_kemahasiswaan VARCHAR2(200),
    CONSTRAINT fk_form_mhs FOREIGN KEY (NIM) REFERENCES Mahasiswa(NIM)
);

-- 7. Tabel INFORMASIKAMARASRAMA
CREATE TABLE Informasikamarasrama (
    Id_kamar      VARCHAR2(10) PRIMARY KEY,
    AsramaId      VARCHAR2(10) NOT NULL,
    No_kasur      VARCHAR2(10),
    Nomor_kamar   VARCHAR2(10),
    Lantai_kamar  NUMBER(2),
    Status_kamar  VARCHAR2(15)
        CHECK (Status_kamar IN ('Tersedia','Terisi','Perbaikan')),
    CONSTRAINT fk_kamar_asrama FOREIGN KEY (AsramaId)
        REFERENCES Asrama_Mahasiswa(Asrama_Id)
);

-- 8. Tabel PENANGANAN_PINDAH_KAMAR (tabel penghubung M:N)
CREATE TABLE PenangananPindahKamar (
    Id_penanganan    VARCHAR2(10) PRIMARY KEY,
    Id_formpindah    VARCHAR2(10) NOT NULL,
    Id_kemahasiswaan VARCHAR2(10) NOT NULL,
    Tanggal_respon   DATE,
    Status_respon    VARCHAR2(15)
        CHECK (Status_respon IN ('Diproses','Disetujui','Ditolak')),
    Catatan_respon   VARCHAR2(200),
    CONSTRAINT fk_pen_form FOREIGN KEY (Id_formpindah)
        REFERENCES Form_Pindahkmr(Id_formpindah),
    CONSTRAINT fk_pen_kemah FOREIGN KEY (Id_kemahasiswaan)
        REFERENCES Kemahasiswaan(Id_kemahasiswaan)
);

-- FK Asrama_Mahasiswa.Id_helpdesk → Help_desk (relasi 1:1)
ALTER TABLE Asrama_Mahasiswa
ADD CONSTRAINT fk_asrama_helpdesk
FOREIGN KEY (Id_helpdesk) REFERENCES Help_desk(Id_helpdesk);


-- =====================================================
-- BAGIAN 2 : DML — SAMPLE DATA
-- =====================================================

-- 1. Insert Mahasiswa
INSERT INTO Mahasiswa VALUES
('1303180078','Satrio Nurcahya', TO_DATE('2003-05-12','YYYY-MM-DD'),
 'Jakarta','L','O','Islam','081234567890','satrio@student.telkomuniversity.ac.id',
 'DKI Jakarta','Jakarta Selatan','12140','Jl. Sukabirus No. 12','Sukabirus','40287',2021);

INSERT INTO Mahasiswa VALUES
('1303180079','Andi Pratama', TO_DATE('2003-08-20','YYYY-MM-DD'),
 'Bandung','L','A','Kristen','081234567891','andi@student.telkomuniversity.ac.id',
 'Jawa Barat','Bandung','40111','Jl. Cihampelas No. 5','Cihampelas','40116',2021);

INSERT INTO Mahasiswa VALUES
('1303180080','Citra Dewi', TO_DATE('2003-03-15','YYYY-MM-DD'),
 'Surabaya','P','B','Hindu','081234567892','citra@student.telkomuniversity.ac.id',
 'Jawa Timur','Surabaya','60111','Jl. Dago No. 8','Dago','40135',2021);

INSERT INTO Mahasiswa VALUES
('1303180081','Budi Santoso', TO_DATE('2002-11-10','YYYY-MM-DD'),
 'Medan','L','AB','Budha','081234567893','budi@student.telkomuniversity.ac.id',
 'Sumatera Utara','Medan','20111','Jl. Setiabudi No. 20','Setiabudi','40143',2020);

-- 2. Insert Help_desk
INSERT INTO Help_desk VALUES ('HD01', 'Rina Wulandari', 'P');
INSERT INTO Help_desk VALUES ('HD02', 'Dimas Ardian',   'L');
INSERT INTO Help_desk VALUES ('HD03', 'Sari Melati',    'P');

-- 3. Insert Asrama_Mahasiswa (FK ke Help_desk)
INSERT INTO Asrama_Mahasiswa VALUES ('ASM01','Gedung A','A-101', 1, 'HD01');
INSERT INTO Asrama_Mahasiswa VALUES ('ASM02','Gedung A','A-102', 1, 'HD01');
INSERT INTO Asrama_Mahasiswa VALUES ('ASM03','Gedung B','B-201', 2, 'HD02');
INSERT INTO Asrama_Mahasiswa VALUES ('ASM04','Gedung B','B-202', 2, 'HD02');
INSERT INTO Asrama_Mahasiswa VALUES ('ASM05','Gedung C','C-301', 3, 'HD03');

-- 4. Insert Kemahasiswaan
INSERT INTO Kemahasiswaan VALUES ('KEM01', 'Pak Ahmad Fauzi');
INSERT INTO Kemahasiswaan VALUES ('KEM02', 'Bu Lestari Handayani');
INSERT INTO Kemahasiswaan VALUES ('KEM03', 'Pak Rudi Hartono');

-- 5. Insert InformasiTtgAsrama
INSERT INTO InformasiTtgAsrama VALUES
('INFO01', 'denah_asrama_2024.pdf', 'panduan_asrama.pdf',
 'Prosedur undur diri: hubungi BK via email bk@telkomuniversity.ac.id');

INSERT INTO InformasiTtgAsrama VALUES
('INFO02', 'denah_gedung_B.pdf', 'panduan_gedung_B.pdf',
 'Prosedur undur diri gedung B: datang ke kantor BK lantai 2');

-- 6. Insert Informasikamarasrama
INSERT INTO Informasikamarasrama VALUES
('KMR001','ASM01','KS-01','A-101',1,'Terisi');
INSERT INTO Informasikamarasrama VALUES
('KMR002','ASM01','KS-02','A-101',1,'Tersedia');
INSERT INTO Informasikamarasrama VALUES
('KMR003','ASM02','KS-03','A-102',1,'Tersedia');
INSERT INTO Informasikamarasrama VALUES
('KMR004','ASM03','KS-04','B-201',2,'Terisi');
INSERT INTO Informasikamarasrama VALUES
('KMR005','ASM03','KS-05','B-201',2,'Tersedia');
INSERT INTO Informasikamarasrama VALUES
('KMR006','ASM05','KS-06','C-301',3,'Perbaikan');

-- 7. Insert Form_Pindahkmr
INSERT INTO Form_Pindahkmr VALUES
('FRM001','1303180078','Ingin lebih dekat dengan kampus',
 'B-201','Gedung B', TO_DATE('2024-09-01','YYYY-MM-DD'),
 'Menunggu', NULL);

INSERT INTO Form_Pindahkmr VALUES
('FRM002','1303180079','Kamar saat ini terlalu berisik',
 'C-301','Gedung C', TO_DATE('2024-09-05','YYYY-MM-DD'),
 'Disetujui', 'Disetujui karena alasan valid');

INSERT INTO Form_Pindahkmr VALUES
('FRM003','1303180080','Butuh kamar dengan AC',
 'A-101','Gedung A', TO_DATE('2024-09-10','YYYY-MM-DD'),
 'Menunggu', NULL);

-- 8. Insert PenangananPindahKamar (tabel penghubung M:N)
INSERT INTO PenangananPindahKamar VALUES
('PNG001','FRM001','KEM01', TO_DATE('2024-09-02','YYYY-MM-DD'),
 'Diproses', 'Sedang dalam review');

INSERT INTO PenangananPindahKamar VALUES
('PNG002','FRM002','KEM01', TO_DATE('2024-09-06','YYYY-MM-DD'),
 'Disetujui', 'Permohonan disetujui');

INSERT INTO PenangananPindahKamar VALUES
('PNG003','FRM002','KEM02', TO_DATE('2024-09-07','YYYY-MM-DD'),
 'Disetujui', 'Konfirmasi dari pihak gedung');

COMMIT;

DBMS_OUTPUT.PUT_LINE('Semua data berhasil dimasukkan.');


-- =====================================================
-- BAGIAN 3 : QUERY DEMONSTRASI
-- =====================================================

-- 3.1 Tampilkan semua mahasiswa
SELECT NIM, Nama_mhs, Jenis_kelamin, Angkatan
FROM Mahasiswa
ORDER BY NIM;

-- 3.2 Tampilkan daftar asrama + help desk yang bertanggung jawab
SELECT a.Asrama_Id, a.Gedung_asrama, a.Ruang_asrama,
       h.Nama_helpdesk
FROM Asrama_Mahasiswa a
JOIN Help_desk h ON a.Id_helpdesk = h.Id_helpdesk
ORDER BY a.Asrama_Id;

-- 3.3 Tampilkan semua kamar + info asrama (JOIN)
SELECT k.Id_kamar, k.Nomor_kamar, k.Status_kamar,
       a.Gedung_asrama, a.Ruang_asrama
FROM Informasikamarasrama k
JOIN Asrama_Mahasiswa a ON k.AsramaId = a.Asrama_Id
ORDER BY k.Id_kamar;

-- 3.4 Tampilkan permohonan pindah kamar + data mahasiswa
SELECT f.Id_formpindah, m.Nama_mhs, f.Gedung_br, f.Ruang_br,
       f.Alasan, f.Status_permohonan, f.Tanggal_pengajuan
FROM Form_Pindahkmr f
JOIN Mahasiswa m ON f.NIM = m.NIM
ORDER BY f.Id_formpindah;

-- 3.5 Tampilkan riwayat penanganan permohonan (JOIN 3 tabel)
SELECT p.Id_penanganan,
       f.Id_formpindah,
       m.Nama_mhs,
       k.Nama_admin,
       p.Status_respon,
       p.Tanggal_respon,
       p.Catatan_respon
FROM PenangananPindahKamar p
JOIN Form_Pindahkmr  f ON p.Id_formpindah    = f.Id_formpindah
JOIN Mahasiswa       m ON f.NIM              = m.NIM
JOIN Kemahasiswaan   k ON p.Id_kemahasiswaan = k.Id_kemahasiswaan
ORDER BY p.Id_penanganan;

-- 3.6 Hitung jumlah permohonan per status
SELECT Status_permohonan,
       COUNT(*) AS jumlah
FROM Form_Pindahkmr
GROUP BY Status_permohonan
ORDER BY Status_permohonan;

-- 3.7 Cari mahasiswa yang belum pernah mengajukan pindah kamar
SELECT m.NIM, m.Nama_mhs
FROM Mahasiswa m
WHERE NOT EXISTS (
    SELECT 1
    FROM Form_Pindahkmr f
    WHERE f.NIM = m.NIM
);

-- 3.8 Tampilkan kamar yang masih tersedia
SELECT k.Id_kamar, k.Nomor_kamar, k.Lantai_kamar,
       a.Gedung_asrama
FROM Informasikamarasrama k
JOIN Asrama_Mahasiswa a ON k.AsramaId = a.Asrama_Id
WHERE k.Status_kamar = 'Tersedia';

-- 3.9 Hitung jumlah kamar per gedung
SELECT a.Gedung_asrama,
       COUNT(k.Id_kamar) AS jumlah_kamar,
       SUM(CASE WHEN k.Status_kamar = 'Tersedia' THEN 1 ELSE 0 END) AS tersedia
FROM Asrama_Mahasiswa a
LEFT JOIN Informasikamarasrama k ON k.AsramaId = a.Asrama_Id
GROUP BY a.Gedung_asrama
ORDER BY a.Gedung_asrama;

-- 3.10 Tampilkan mahasiswa yang permohonannya sudah disetujui
SELECT m.NIM, m.Nama_mhs, f.Id_formpindah,
       f.Gedung_br, f.Ruang_br,
       k.Nama_admin, p.Tanggal_respon
FROM Mahasiswa m
JOIN Form_Pindahkmr f ON m.NIM = f.NIM
LEFT JOIN PenangananPindahKamar p ON f.Id_formpindah = p.Id_formpindah
LEFT JOIN Kemahasiswaan k ON p.Id_kemahasiswaan = k.Id_kemahasiswaan
WHERE f.Status_permohonan = 'Disetujui';