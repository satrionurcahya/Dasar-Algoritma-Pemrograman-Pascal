
---

## File 2: `Tugas_ADS.md`

```markdown
# Daftar Tugas - Algoritma dan Struktur Data

Kumpulan soal tugas mata kuliah **Algoritma dan Struktur Data (ASD)** 
yang sudah disederhanakan. Setiap tugas menguji konsep struktur data 
dan algoritma tertentu.

---

## Tugas 1 — Pengenalan C++

**Topik:** Array, Struct, Fungsi, Sorting, Searching

**Soal:**
Buat program untuk mengelola data mahasiswa (kapasitas maks 1000) dengan 
atribut: NRP, nama, nilai Matematika, Kimia, Fisika, Biologi.

**Ketentuan:**
- Hitung nilai total dan rata-rata, tentukan predikat (A/B/C/D).
- Validasi input: jumlah mahasiswa 1–1000, nilai 0–100.
- Terapkan **Bubble Sort** dan **Selection Sort** (descending by total).
- Terapkan **Sequential Search** dan **Binary Search** (by NRP).

---

## Tugas 2 — Single Linked List

**Topik:** ADT Single Linked List (non-circular)

**Soal:**
Buat program untuk menyimpan data mahasiswa (Nama, NIM, IPK) menggunakan 
Single Linked List dengan pointer `First`.

**Ketentuan:**
- Operasi: `createList`, `insertFirst`, `deleteLast`, `searchNIM`, 
  `viewAll`, `countNode`, `deleteAll`.
- `searchNIM` pakai Sequential Search.
- Program pakai menu interaktif.

---

## Tugas 3 — Double Linked List

**Topik:** ADT Double Linked List (non-circular)

**Soal:**
Simulasi sistem tapping kehadiran pegawai. Setiap tapping menyimpan 
ID pegawai, jam, menit, status ("masuk"/"keluar"), dan count.

**Ketentuan:**
- Tapping sebelum 12.00 → status "masuk"; ≥ 12.00 → "keluar".
- Kombinasi ID + status hanya disimpan **satu elemen**.
- Untuk "masuk": simpan waktu **paling awal**; "keluar": **paling akhir**.
- Count bertambah tiap tapping dengan kombinasi sama.
- Operasi: `createList`, `isNull`, `createData`, `insertElemen`, 
  `tampilData`, `countElemen`, `searchPegawai`, `deleteAfter`, `deleteAll`.

---

## Tugas 4 — Circular Linked List

**Topik:** Circular Single Linked List (CSLL) & Circular Double Linked List (CDLL)

**Soal:**
Sistem pengelolaan aktivitas akademik mahasiswa dengan dua bagian:
- **Antrean Bimbingan Akademik** (CSLL)
- **Jadwal Presentasi Kelompok** (CDLL)

**Ketentuan CSLL:** operasi `createList`, `insertLast`, `deleteFirst`, 
`searchNIM`, `viewAll`, `countNode`.

**Ketentuan CDLL:** operasi `insertFirst`, `insertLast`, `nextGroup`, 
`prevGroup`, `searchKelompok`, `updateStatus`, `deleteByKode`, `viewAll`.

---

## Tugas 5 — Multi Linked List

**Topik:** Relasi 1 to N dan N to M

**Soal:**
Sistem informasi akademik dengan dua relasi:
- **1 to N**: Dosen → Mata Kuliah (parent-child)
- **N to M**: Mahasiswa ↔ Mata Kuliah (pakai relationship node)

**Ketentuan 1 to N:**
- Operasi: `insertDosen`, `insertMK`, `searchDosen`, `searchMK`, 
  `deleteMK`, `deleteDosen`, `viewAllDosen`, `countDosen`, `countMK`.

**Ketentuan N to M:**
- List mahasiswa (DLL non-circular), list MK (SLL circular), list relasi (SLL non-circular).
- Operasi: `insertMahasiswa`, `insertMK`, `insertRelasi`, `updateNilai`, 
  `deleteRelasi`, `deleteMahasiswa`, `deleteMK`, `viewMKMahasiswa`, 
  `viewMahasiswaMK`, dan fungsi count.

---

## Tugas 6 — Stack & Queue

**Topik:** ADT Stack & Queue + Ekspresi Postfix

**Soal:**
Buat program pengolahan ekspresi postfix menggunakan Stack dan Queue.

**Ketentuan:**
- ADT Stack: `createStack`, `isEmpty`, `isFull`, `push`, `pop`, `peek`, `viewStack`.
- ADT Queue: `createQueue`, `isEmpty`, `isFull`, `enqueue`, `dequeue`, 
  `front`, `viewQueue` (implementasi circular array).
- Prosedur `processPostfix`: konversi & evaluasi postfix.
- Prosedur `infixToPostfix`: konversi infix ke postfix (memperhatikan prioritas: 
  `^` prioritas 3 kanan→kiri; `*`, `/` prioritas 2; `+`, `-` prioritas 1).
- Fungsi rekursif `evaluatePostfixRecursive`.
- Struktur `ExpressionNode` untuk membangun pohon ekspresi.
- Traversal rekursif: `inorder`, `preorder`, `postorder`.
- Prosedur `inputVariables` untuk nilai variabel huruf (A–Z).

---

## Tugas 7 — Pemeriksa Palindrom

**Topik:** SLL, DLL, Stack LL, Queue LL, Rekursif

**Soal:**
Buat program untuk memeriksa apakah sebuah kata/kalimat merupakan palindrom.

**Ketentuan:**
- Normalisasi: abaikan spasi, ubah ke huruf kecil.
- Implementasi 4 metode:
  1. Stack berbasis Linked List
  2. Queue + Stack berbasis Linked List
  3. Rekursi (tanpa struktur tambahan)
  4. Double Linked List (bandingkan dari depan & belakang)
- Tangani teks kosong dan teks hanya spasi.

---

## Tugas 8 — Binary Search Tree

**Topik:** Linked List + BST (Sinkronisasi Data)

**Soal:**
Sistem pengelolaan data mahasiswa yang menyimpan data di **dua struktur 
sekaligus**: Linked List dan Binary Search Tree.

**Ketentuan:**
- Setiap operasi (insert, update, delete) harus **sinkron** di kedua struktur.
- Linked List: operasi dasar + `sortByNIM`, `averageIPK`.
- BST: `insertBST`, `searchBST`, `deleteBST`, `inOrder`, `preOrder`, 
  `postOrder`, `findMin`, `findMax`, `countNodeBST`, `countLeaf`, 
  `countInternal`, `heightBST`.
- Sediakan fungsi cek konsistensi antara LL dan BST.

---

## Tugas 9 — Graph

**Topik:** ADT Graph (Adjacency List berbasis Linked List)

**Soal:**
Sistem pertemanan mahasiswa menggunakan undirected graph.

**Ketentuan:**
- Struktur: `Vertex` (NIM, nama, firstEdge, nextVertex) dan 
  `Edge` (destNIM, nextEdge).
- Operasi: `createGraph`, `insertVertex`, `insertEdge`, `deleteEdge`, 
  `deleteVertex`, `viewGraph`, `viewNeighbors`, `degreeVertex`, 
  `countVertex`, `countEdges`.
- Fungsi pemeriksaan: `hasLoop`, `hasMultipleEdges`, `isSimpleGraph`.
- Traversal: `DFS` dan `BFS` berbasis Linked List / Queue.
- Fungsi `isConnected` untuk cek keterhubungan graph.

---

## Tugas Besar — Multi Linked List Penjualan

**Topik:** Penerapan Multi Linked List pada Program Penjualan

**Soal:**
Buat program penjualan toko yang mengelola data kategori, barang, 
pelanggan, dan transaksi dengan konsep **Multi-Linked List**.

**Ketentuan:**
- **Kategori → Barang** (1:N): setiap kategori punya daftar barang.
- **Pelanggan → Transaksi** (1:N): setiap pelanggan punya riwayat transaksi.
- **Transaksi → Detail** (1:N): setiap transaksi punya daftar barang dibeli.
- **Detail → Barang** (N:M): pointer ke Barang asli (bukan copy).

**Fitur:**
1. CRUD Kategori
2. CRUD Barang (kode, nama, harga, stok)
3. CRUD Pelanggan (ID, nama, kontak)
4. Buat transaksi: pilih pelanggan, tambah barang + jumlah, hitung total, 
   kurangi stok otomatis.
5. Laporan penjualan: total pendapatan, rata-rata transaksi.
6. Laporan barang terjual: qty & total per barang.
