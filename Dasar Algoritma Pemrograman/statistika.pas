program Statistika;
uses crt;

{ ========================================================= }
{ TUGAS BESAR (TUBES) - APLIKASI STATISTIKA SEDERHANA       }
{ Nama      : Satrio Nurcahya                               }
{ NIM       : 1303180078                                    }
{ Kelas     : IT-42-01                                      }
{ Ketentuan : Buatlah Sebuah Program yang menerapkan CRUD   }
{ ========================================================= }

type
  { Ini record untuk menyimpan nilai dan frekuensinya }
  statistik = record
    data : integer;   // Untuk menyimpan angka yang diinput
    frek : integer;   // Untuk menyimpan berapa kali angka itu muncul
  end;

  { Ini array untuk menampung maksimal 100 data }
  Datum = array[1..100] of statistik;

var
  x : Datum;          // Variabel utama untuk menampung data statistik
  n, m : integer;     // n = total data, m = banyak variasi data (unik)
  nama : string;      // Untuk menyimpan nama data
  rata : real;        // Untuk menyimpan nilai rata-rata (mean)

{ Prosedur untuk mengurutkan data dari kecil ke besar (Ascending) }
{ Ini pakai metode Bubble Sort, standar diajarkan di semester 1 }
procedure UrutkanData;
var
  i, j : integer;
  temp : statistik;   // Variabel bantuan untuk menukar data
begin
  for i := 1 to m - 1 do
  begin
    for j := 1 to m - i do
    begin
      if x[j].data > x[j+1].data then
      begin
        // Proses menukar posisi data
        temp := x[j];
        x[j] := x[j+1];
        x[j+1] := temp;
      end;
    end;
  end;
end;

{ Prosedur untuk menginput data dari user }
procedure InputData;
var
  i, j, jumlah, tambah : integer;
  angka : integer;
  ada : boolean;
  lagi : char;
begin
  clrscr;
  writeln('=== PROGRAM PROSES ARRAY BILANGAN BULAT ===');
  write('Banyak data yang ingin diinputkan : ');
  readln(jumlah);
  
  n := 0; // Inisialisasi total data
  m := 0; // Inisialisasi variasi data
  
  // Looping untuk input data pertama
  for i := 1 to jumlah do
  begin
    write('Masukkan data ke ', i, ' = ');
    readln(angka);
    ada := false;
    
    // Cek apakah angka sudah ada di dalam array
    for j := 1 to m do
    begin
      if x[j].data = angka then
      begin
        x[j].frek := x[j].frek + 1; // Kalau ada, frekuensinya ditambah
        ada := true;
        break;
      end;
    end;
    
    // Kalau angka belum ada, simpan sebagai data baru
    if not ada then
    begin
      m := m + 1;
      x[m].data := angka;
      x[m].frek := 1;
    end;
    n := n + 1; // Total data bertambah
  end;

  // Looping untuk tanya apakah user mau nambah data lagi
  repeat
    write('Tambahkan angka lagi? (y/t) : ');
    readln(lagi);
    if (lagi = 'y') or (lagi = 'Y') then
    begin
      write('Banyak data tambahan : ');
      readln(tambah);
      for i := 1 to tambah do
      begin
        write('Masukkan data ke ', n + 1, ' = ');
        readln(angka);
        ada := false;
        for j := 1 to m do
        begin
          if x[j].data = angka then
          begin
            x[j].frek := x[j].frek + 1;
            ada := true;
            break;
          end;
        end;
        if not ada then
        begin
          m := m + 1;
          x[m].data := angka;
          x[m].frek := 1;
        end;
        n := n + 1;
      end;
    end;
  until (lagi = 't') or (lagi = 'T') or (n >= 100); // Berhenti kalau pilih 't' atau data sudah 100
end;

{ Prosedur untuk menampilkan data yang sudah diinput }
procedure TampilkanData;
var
  i : integer;
begin
  clrscr;
  writeln('Data Statistik : ', nama);
  writeln('----------------------------------------');
  for i := 1 to m do
  begin
    writeln('Nilai ', x[i].data, ' muncul sebanyak ', x[i].frek, ' kali');
  end;
  writeln('----------------------------------------');
  writeln('Total Data   : ', n);
  writeln('Variasi Data : ', m);
  writeln;
end;

{ Prosedur untuk menampilkan data yang sudah diurutkan }
procedure TampilUrut;
var
  i, j : integer;
begin
  UrutkanData; // Panggil prosedur urutkan dulu
  clrscr;
  write('Urut Naik  : ');
  for i := 1 to m do
    for j := 1 to x[i].frek do
      write(x[i].data, ' ');
  writeln;
  
  write('Urut Turun : ');
  for i := m downto 1 do
    for j := 1 to x[i].frek do
      write(x[i].data, ' ');
  writeln;
end;

{ Prosedur untuk menghitung Mean (Rata-rata) }
procedure HitungMean;
var
  i : integer;
  total : real;
begin
  total := 0;
  for i := 1 to m do
  begin
    total := total + (x[i].data * x[i].frek);
  end;
  rata := total / n;
  writeln('Mean (Rata-rata) = ', rata:0:2);
end;

{ Prosedur untuk menghitung Median (Nilai Tengah) }
procedure HitungMedian;
var
  i, j, k : integer;
  dataUrut : array[1..100] of integer;
  tengah : integer;
  med : real;
begin
  UrutkanData; // Pastikan data urut dulu
  k := 0;
  
  // Kita kembalikan data ke bentuk array biasa agar mudah dicari tengahnya
  for i := 1 to m do
  begin
    for j := 1 to x[i].frek do
    begin
      k := k + 1;
      dataUrut[k] := x[i].data;
    end;
  end;
  
  // Cari nilai tengah
  if k mod 2 = 1 then
    med := dataUrut[(k div 2) + 1]
  else
    med := (dataUrut[k div 2] + dataUrut[(k div 2) + 1]) / 2;
    
  writeln('Median = ', med:0:2);
  writeln('Nilai Terkecil = ', dataUrut[1]);
  writeln('Nilai Terbesar = ', dataUrut[k]);
end;

{ Prosedur untuk menghitung Modus (Nilai yang paling sering muncul) }
procedure HitungModus;
var
  i, posisiMax : integer;
begin
  posisiMax := 1;
  for i := 2 to m do
  begin
    if x[i].frek > x[posisiMax].frek then
      posisiMax := i;
  end;
  writeln('Modus = ', x[posisiMax].data, ' (Muncul ', x[posisiMax].frek, ' kali)');
end;

{ Prosedur untuk menghitung Standar Deviasi }
procedure HitungDeviasi;
var
  i : integer;
  total : real;
begin
  total := 0;
  for i := 1 to m do
  begin
    total := total + (x[i].frek * sqr(x[i].data - rata));
  end;
  total := sqrt(total / n);
  writeln('Standar Deviasi = ', total:0:2);
end;

{ ================= PROGRAM UTAMA ================= }
var
  pilihan : integer;
begin
  clrscr;
  write('Masukkan nama data/statistika : ');
  readln(nama);
  
  InputData; // Panggil prosedur input
  writeln;
  TampilkanData; // Tampilkan hasil input
  readln;
  
  // Looping menu utama
  repeat
    clrscr;
    writeln('Data yang anda buat mengenai : ', nama);
    writeln('1. Urutkan Data');
    writeln('2. Tampilkan Data');
    writeln('3. Ukuran Pemusatan Data (Mean, Median, Modus)');
    writeln('4. Standar Deviasi');
    writeln('0. Keluar Program');
    writeln;
    write('Masukkan Pilihan : ');
    readln(pilihan);
    
    // Case untuk memilih menu
    case pilihan of
      1 : TampilUrut;
      2 : TampilkanData;
      3 : begin
            HitungMean;
            writeln;
            HitungMedian;
            writeln;
            HitungModus;
          end;
      4 : begin
            HitungMean; // Hitung mean dulu karena deviasi butuh nilai rata-rata
            HitungDeviasi;
          end;
      0 : writeln('TERIMA KASIH');
    end;
    
    readln; // Supaya layar tidak langsung tertutup
  until (pilihan = 0);
end.