program MesinAbstrak;
uses crt;

{ ===================================================== }
{ TUGAS BESAR : MESIN ABSTRAK - TEKS & BILANGAN         }
{ Nama  : [Tulis Nama Anda]                             }
{ NIM   : [Tulis NIM Anda]                              }
{ Kelas : [Tulis Kelas Anda]                            }
{ ===================================================== }

const
  MAX = 100;          { Kapasitas maksimum array }
  MAX_VAL = 1000;     { Batas nilai untuk Counting Sort }

type
  ArrInt = array[0..MAX-1] of integer;   { Array bilangan bulat }

var
  { Variabel mesin karakter }
  Pita_Karakter : string;
  Indeks        : integer;
  CC            : char;

  { Variabel array bilangan }
  A        : ArrInt;       { Array utama yang diproses }
  A_Asli   : ArrInt;       { Salinan array awal }
  n        : integer;      { Jumlah elemen array }
  sumber   : string;       { Keterangan sumber input }


{ ===================================================== }
{                     FUNGSI                            }
{ ===================================================== }

{ Fungsi cek apakah karakter adalah huruf vokal }
function IsVokal(c : char) : boolean;
begin
  c := upcase(c);
  IsVokal := (c = 'A') or (c = 'E') or (c = 'I') or (c = 'O') or (c = 'U');
end;

{ Fungsi cek apakah karakter adalah huruf konsonan }
function IsKonsonan(c : char) : boolean;
begin
  c := upcase(c);
  IsKonsonan := (c >= 'A') and (c <= 'Z') and (not IsVokal(c));
end;

{ Fungsi menghitung jumlah kata dalam pita karakter }
function HitungKata(pita : string) : integer;
var
  i, hitung : integer;
  dalamKata : boolean;
begin
  hitung := 0;
  dalamKata := false;
  for i := 1 to length(pita) do
  begin
    if (pita[i] <> ' ') and (pita[i] <> '.') and (pita[i] <> #9) then
    begin
      if not dalamKata then
      begin
        hitung := hitung + 1;
        dalamKata := true;
      end;
    end
    else
      dalamKata := false;
  end;
  HitungKata := hitung;
end;

{ Fungsi Sequential Search - cek satu per satu }
function SequentialSearch(arr : ArrInt; jml : integer; x : integer) : integer;
var
  i : integer;
  ketemu : boolean;
begin
  i := 0;
  ketemu := false;
  SequentialSearch := -1;
  while (i < jml) and (not ketemu) do
  begin
    if arr[i] = x then
    begin
      SequentialSearch := i;
      ketemu := true;
    end
    else
      i := i + 1;
  end;
end;

{ Fungsi Binary Search - array harus sudah terurut }
function BinarySearch(arr : ArrInt; jml : integer; x : integer) : integer;
var
  kiri, kanan, tengah : integer;
  ketemu : boolean;
begin
  kiri := 0;
  kanan := jml - 1;
  ketemu := false;
  BinarySearch := -1;
  while (kiri <= kanan) and (not ketemu) do
  begin
    tengah := (kiri + kanan) div 2;
    if arr[tengah] = x then
    begin
      BinarySearch := tengah;
      ketemu := true;
    end
    else if arr[tengah] < x then
      kiri := tengah + 1
    else
      kanan := tengah - 1;
  end;
end;


{ ===================================================== }
{                MESIN KARAKTER                         }
{ ===================================================== }

{ Prosedur START : mulai baca pita dari karakter pertama }
procedure START;
begin
  Indeks := 1;
  if length(Pita_Karakter) >= 1 then
    CC := Pita_Karakter[1]
  else
    CC := '.';
end;

{ Prosedur ADV : maju ke karakter berikutnya }
procedure ADV;
begin
  if Indeks < length(Pita_Karakter) then
  begin
    Indeks := Indeks + 1;
    CC := Pita_Karakter[Indeks];
  end
  else
  begin
    Indeks := length(Pita_Karakter) + 1;
    CC := '.';  { Tanda akhir pita }
  end;
end;


{ ===================================================== }
{                     PROSEDUR                          }
{ ===================================================== }

{ Tampilkan menu operasi }
procedure TampilMenu;
begin
  writeln('=========== MENU OPERASI ===========');
  writeln('1. Analisis Teks (Mesin Karakter)');
  writeln('2. Tampilkan Array');
  writeln('3. Counting Sort');
  writeln('4. Bubble Sort');
  writeln('5. Insertion Sort');
  writeln('6. Selection Sort');
  writeln('7. Sequential Search');
  writeln('8. Binary Search');
  writeln('0. Keluar');
  writeln('====================================');
end;

{ Tampilkan isi array }
procedure TampilArray(arr : ArrInt; jml : integer);
var
  i : integer;
begin
  write('Isi Array : ');
  if jml = 0 then
    write('(kosong)')
  else
    for i := 0 to jml - 1 do
      write(arr[i], ' ');
  writeln;
end;

{ Input manual dari keyboard }
procedure InputManual;
var
  i, x : integer;
begin
  clrscr;
  writeln('--- INPUT MANUAL ---');
  writeln('Masukkan teks (akhiri dengan titik "."):');
  readln(Pita_Karakter);
  
  { Pastikan ada titik di akhir }
  if (length(Pita_Karakter) = 0) or (Pita_Karakter[length(Pita_Karakter)] <> '.') then
    Pita_Karakter := Pita_Karakter + '.';
  
  writeln;
  write('Banyak bilangan yang ingin diinput : ');
  readln(n);
  
  { Validasi jumlah data }
  if n > MAX then
  begin
    writeln('Jumlah melebihi kapasitas! Dibatasi ', MAX);
    n := MAX;
  end;
  if n < 0 then n := 0;
  
  writeln('Masukkan ', n, ' bilangan (0..', MAX_VAL, '):');
  for i := 0 to n - 1 do
  begin
    write('Data ke-', i + 1, ' : ');
    readln(x);
    { Validasi rentang nilai }
    if (x < 0) or (x > MAX_VAL) then
    begin
      writeln('Nilai di luar rentang! Diisi 0.');
      x := 0;
    end;
    A[i] := x;
    A_Asli[i] := x;
  end;
  sumber := 'Manual (Keyboard)';
end;

{ Baca data dari file .txt }
procedure BacaFile;
var
  f : text;
  namaFile : string;
  i, x : integer;
begin
  clrscr;
  writeln('--- INPUT DARI FILE ---');
  write('Nama file (.txt) : ');
  readln(namaFile);
  
  assign(f, namaFile);
  {$I-}
  reset(f);
  {$I+}
  
  { Cek apakah file berhasil dibuka }
  if IOResult <> 0 then
  begin
    writeln('ERROR: File tidak ditemukan atau tidak dapat dibaca!');
    Pita_Karakter := '';
    n := 0;
    sumber := 'File (gagal dibaca)';
    exit;
  end;
  
  { Baca baris pertama sebagai teks }
  Pita_Karakter := '';
  if not eof(f) then
    readln(f, Pita_Karakter);
  
  { Cek apakah file kosong }
  if Pita_Karakter = '' then
  begin
    writeln('ERROR: File kosong atau tidak memiliki teks!');
    close(f);
    n := 0;
    sumber := 'File (kosong)';
    exit;
  end;
  
  { Pastikan ada titik di akhir }
  if Pita_Karakter[length(Pita_Karakter)] <> '.' then
    Pita_Karakter := Pita_Karakter + '.';
  
  { Baca bilangan dari sisa file }
  n := 0;
  while (not eof(f)) and (n < MAX) do
  begin
    {$I-}
    read(f, x);
    {$I+}
    if IOResult = 0 then
    begin
      if (x >= 0) and (x <= MAX_VAL) then
      begin
        A[n] := x;
        A_Asli[n] := x;
        n := n + 1;
      end;
    end
    else
      break;
  end;
  
  close(f);
  sumber := 'File: ' + namaFile;
  writeln('File berhasil dibaca!');
  writeln('Jumlah data terbaca : ', n);
end;

{ Analisis teks menggunakan mesin karakter }
procedure AnalisisKarakter;
var
  jmlKarakter, jmlVokal, jmlKonsonan, jmlSpasi, jmlKata : integer;
begin
  clrscr;
  writeln('=== ANALISIS TEKS (MESIN KARAKTER) ===');
  writeln('Pita Karakter : ', Pita_Karakter);
  writeln('Panjang Pita  : ', length(Pita_Karakter));
  writeln;
  
  jmlKarakter := 0;
  jmlVokal := 0;
  jmlKonsonan := 0;
  jmlSpasi := 0;
  
  { Jalankan mesin karakter }
  if length(Pita_Karakter) > 0 then
  begin
    START;
    while (CC <> '.') and (Indeks <= length(Pita_Karakter)) do
    begin
      jmlKarakter := jmlKarakter + 1;
      if CC = ' ' then
        jmlSpasi := jmlSpasi + 1
      else if IsVokal(CC) then
        jmlVokal := jmlVokal + 1
      else if IsKonsonan(CC) then
        jmlKonsonan := jmlKonsonan + 1;
      ADV;
    end;
  end;
  
  jmlKata := HitungKata(Pita_Karakter);
  
  writeln('--- HASIL ANALISIS ---');
  writeln('Jumlah Karakter   : ', jmlKarakter);
  writeln('Jumlah Vokal      : ', jmlVokal);
  writeln('Jumlah Konsonan   : ', jmlKonsonan);
  writeln('Jumlah Spasi      : ', jmlSpasi);
  writeln('Jumlah Kata       : ', jmlKata);
  writeln;
end;

{ Counting Sort }
procedure CountingSort;
var
  count : array[0..MAX_VAL] of integer;
  hasil : ArrInt;
  i : integer;
begin
  clrscr;
  writeln('=== COUNTING SORT ===');
  write('Data sebelum : '); TampilArray(A, n);
  
  { Inisialisasi array count }
  for i := 0 to MAX_VAL do
    count[i] := 0;
  
  { Hitung frekuensi setiap nilai }
  for i := 0 to n - 1 do
    count[A[i]] := count[A[i]] + 1;
  
  { Akumulasi posisi }
  for i := 1 to MAX_VAL do
    count[i] := count[i] + count[i-1];
  
  { Susun hasil (dari belakang agar stabil) }
  for i := n - 1 downto 0 do
  begin
    count[A[i]] := count[A[i]] - 1;
    hasil[count[A[i]]] := A[i];
  end;
  
  { Salin kembali ke array utama }
  for i := 0 to n - 1 do
    A[i] := hasil[i];
  
  write('Data sesudah : '); TampilArray(A, n);
end;

{ Bubble Sort }
procedure BubbleSort;
var
  i, j, temp : integer;
begin
  clrscr;
  writeln('=== BUBBLE SORT ===');
  write('Data sebelum : '); TampilArray(A, n);
  
  for i := 0 to n - 2 do
    for j := 0 to n - 2 - i do
      if A[j] > A[j+1] then
      begin
        temp := A[j];
        A[j] := A[j+1];
        A[j+1] := temp;
      end;
  
  write('Data sesudah : '); TampilArray(A, n);
end;

{ Insertion Sort }
procedure InsertionSort;
var
  i, j, key : integer;
begin
  clrscr;
  writeln('=== INSERTION SORT ===');
  write('Data sebelum : '); TampilArray(A, n);
  
  for i := 1 to n - 1 do
  begin
    key := A[i];
    j := i - 1;
    while (j >= 0) and (A[j] > key) do
    begin
      A[j+1] := A[j];
      j := j - 1;
    end;
    A[j+1] := key;
  end;
  
  write('Data sesudah : '); TampilArray(A, n);
end;

{ Selection Sort }
procedure SelectionSort;
var
  i, j, minIdx, temp : integer;
begin
  clrscr;
  writeln('=== SELECTION SORT ===');
  write('Data sebelum : '); TampilArray(A, n);
  
  for i := 0 to n - 2 do
  begin
    minIdx := i;
    for j := i + 1 to n - 1 do
      if A[j] < A[minIdx] then
        minIdx := j;
    { Tukar posisi }
    temp := A[i];
    A[i] := A[minIdx];
    A[minIdx] := temp;
  end;
  
  write('Data sesudah : '); TampilArray(A, n);
end;

{ Tampilkan hasil pencarian }
procedure TampilHasilPencarian(algo : string; x, pos : integer);
begin
  writeln('Algoritma     : ', algo);
  writeln('Nilai dicari  : ', x);
  if pos = -1 then
    writeln('Hasil         : Data TIDAK ditemukan')
  else
    writeln('Hasil         : Data ditemukan di posisi ke-', pos + 1,
            ' (indeks array: ', pos, ')');
  writeln;
end;

{ Urutkan array untuk keperluan Binary Search }
procedure UrutkanUntukBinary;
var
  i, j, temp : integer;
begin
  for i := 0 to n - 2 do
    for j := 0 to n - 2 - i do
      if A[j] > A[j+1] then
      begin
        temp := A[j];
        A[j] := A[j+1];
        A[j+1] := temp;
      end;
end;


{ ===================================================== }
{                  PROGRAM UTAMA                        }
{ ===================================================== }
var
  pilihInput, pilih, x, pos : integer;
begin
  clrscr;
  writeln('==========================================');
  writeln('     MESIN ABSTRAK - TEKS & BILANGAN');
  writeln('==========================================');
  writeln('Pilih sumber input:');
  writeln('1. Input Manual (keyboard)');
  writeln('2. Input dari File (.txt)');
  write('Pilihan : ');
  readln(pilihInput);
  
  { Panggil prosedur input sesuai pilihan }
  if pilihInput = 1 then
    InputManual
  else if pilihInput = 2 then
    BacaFile
  else
  begin
    writeln('Pilihan tidak valid!');
    exit;
  end;
  
  writeln;
  writeln('Sumber input : ', sumber);
  writeln('Tekan Enter untuk lanjut ke menu...');
  readln;
  
  { Loop menu operasi }
  repeat
    clrscr;
    writeln('Sumber input : ', sumber);
    writeln;
    TampilMenu;
    write('Pilihan : ');
    readln(pilih);
    
    case pilih of
      1 : AnalisisKarakter;
      2 : begin
            clrscr;
            writeln('=== ISI ARRAY ===');
            TampilArray(A, n);
          end;
      3 : CountingSort;
      4 : BubbleSort;
      5 : InsertionSort;
      6 : SelectionSort;
      7 : begin
            clrscr;
            writeln('=== SEQUENTIAL SEARCH ===');
            TampilArray(A, n);
            if n > 0 then
            begin
              write('Nilai yang dicari : ');
              readln(x);
              pos := SequentialSearch(A, n, x);
              TampilHasilPencarian('Sequential Search', x, pos);
            end
            else
              writeln('Array kosong, tidak ada yang bisa dicari.');
          end;
      8 : begin
            clrscr;
            writeln('=== BINARY SEARCH ===');
            if n > 0 then
            begin
              UrutkanUntukBinary;
              writeln('(Array diurutkan dulu sebelum Binary Search)');
              TampilArray(A, n);
              write('Nilai yang dicari : ');
              readln(x);
              pos := BinarySearch(A, n, x);
              TampilHasilPencarian('Binary Search', x, pos);
            end
            else
              writeln('Array kosong, tidak ada yang bisa dicari.');
          end;
      0 : writeln('Terima kasih telah menggunakan program ini!');
    else
      writeln('Pilihan tidak valid!');
    end;
    
    if pilih <> 0 then
    begin
      writeln('Tekan Enter untuk kembali ke menu...');
      readln;
    end;
  until pilih = 0;
end.