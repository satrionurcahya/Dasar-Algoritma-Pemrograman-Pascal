# Basis Data Dasar

Kumpulan tugas mata kuliah **Basis Data Dasar** menggunakan 
**Oracle 11g** — Semester 3.

## 👤 Identitas

- **Nama** : Satrio Nurcahya
- **NIM**  : 1303180078
- **Kelas**: IT-42-01

## Environment

- **DBMS**  : Oracle Database 11g
- **Tools** : Oracle SQL Developer / SQL*Plus / Oracle Live SQL

## Daftar Tugas

Deskripsi lengkap setiap tugas ada di [Tugas_Basis_Data.md](./Tugas_Basis_Data.md).

| No | Topik | File SQL | Dokumentasi |
|----|-------|----------|-------------|
| 4 | DDL & DML Dasar | [Tugas4_DDL_DML.sql](./Tugas4_DDL_DML.sql) | [README](./Tugas4_README.md) |
| 5 | Basic SQL, SELECT, WHERE, Sorting | [Tugas5_Basic_SQL.sql](./Tugas5_Basic_SQL.sql) | [README](./Tugas5_README.md) |
| 6 | Obtaining Data from Multiple Tables | [Tugas6_Multiple_Tables.sql](./Tugas6_Multiple_Tables.sql) | [README](./Tugas6_README.md) |
| 7 | Aggregate Functions | [Tugas7_Aggregate.sql](./Tugas7_Aggregate.sql) | [README](./Tugas7_README.md) |
| 8 | Subquery | [Tugas8_Subquery.sql](./Tugas8_Subquery.sql) | [README](./Tugas8_README.md) |
| 9 | Stored Procedure | [Tugas9_Stored_Procedure.sql](./Tugas9_Stored_Procedure.sql) | [README](./Tugas9_README.md) |
| **TB** | **Perancangan Basis Data Menu Asrama iGracias** | [TugasBesar_iGracias.sql](./TugasBesar_iGracias.sql) | [README](./TugasBesar_README.md) |

## Cara Menjalankan

### Oracle SQL Developer (Rekomendasi)
1. Buat koneksi ke database Oracle kampus
2. Buka file `.sql` di worksheet
3. Tekan **F5** (Run Script)
4. Lihat output di tab **Script Output**

### SQL*Plus
```bash
sqlplus username/password@host:port/service
SQL> SET SERVEROUTPUT ON;
SQL> @Tugas4_DDL_DML.sql