program PemecahanUang;
uses crt;

{ ========================================================= }
{ TUGAS UTS : Program Pemecahan Uang                        }     }
{ Nama      : Satrio Nurcahya                               }
{ NIM       : 1303180078                                    }
{ Kelas     : IT-42-01                                      }
{ Ketentuan : Buatlah Program sesuai dengan Ketentuan       }
{ ========================================================= }

type
  { Tipe data bentukan untuk menyimpan hasil pemecahan uang }
  HasilPecahan = record
    lembar50 : integer;   // Jumlah lembar Rp50.000
    lembar20 : integer;   // Jumlah lembar Rp20.000
    lembar5  : integer;   // Jumlah lembar Rp5.000
    valid    : boolean;   // Status apakah pecahan berhasil atau tidak
  end;

var
  nominal : integer;         // Nominal uang yang diinput user
  hasil   : HasilPecahan;    // Variabel untuk menampung hasil pemecahan

{ ---------- FUNGSI 1 : Cek apakah nominal kelipatan 5000 ---------- }
function CekKelipatan(n : integer) : boolean;
begin
  if (n mod 5000 = 0) and (n > 0) then
    CekKelipatan := true
  else
    CekKelipatan := false;
end;

{ ---------- FUNGSI 2 : Hitung hasil pemecahan uang ---------- }
function HitungPecahan(n : integer) : HasilPecahan;
var
  sisa : integer;
  h : HasilPecahan;
begin
  sisa := n;

  // Prioritas 1 : pecah ke Rp50.000 sebanyak mungkin
  h.lembar50 := sisa div 50000;
  sisa := sisa mod 50000;

  // Prioritas 2 : pecah ke Rp20.000 sebanyak mungkin dari sisa
  h.lembar20 := sisa div 20000;
  sisa := sisa mod 20000;

  // Prioritas 3 : pecah ke Rp5.000 dari sisa terakhir
  h.lembar5 := sisa div 5000;
  sisa := sisa mod 5000;

  // Tandai valid karena sudah pasti kelipatan 5000
  h.valid := true;

  HitungPecahan := h;
end;

{ ---------- PROSEDUR 1 : Input nominal uang ---------- }
procedure InputNominal(var n : integer);
begin
  write('Masukkan nominal uang (Rp) : ');
  readln(n);
end;

{ ---------- PROSEDUR 2 : Proses & tampilkan hasil ---------- }
procedure ProsesPecahan(n : integer);
var
  h : HasilPecahan;
begin
  writeln;
  writeln('--- HASIL PEMECAHAN UANG ---');

  // Cek validitas dulu
  if not CekKelipatan(n) then
  begin
    writeln('Nominal Rp', n, ' BUKAN kelipatan Rp5.000.');
    writeln('Pemecahan uang tidak dapat dilakukan.');
  end
  else
  begin
    // Hitung pemecahan
    h := HitungPecahan(n);

    // Tampilkan hasil
    writeln('Nominal awal        : Rp', n);
    writeln('Lembar Rp50.000     : ', h.lembar50, ' lembar');
    writeln('Lembar Rp20.000     : ', h.lembar20, ' lembar');
    writeln('Lembar Rp5.000      : ', h.lembar5,  ' lembar');
  end;
  writeln;
end;

{ ================= PROGRAM UTAMA ================= }
var
  pilihan : integer;
begin
  repeat
    clrscr;
    writeln('==========================================');
    writeln('     PROGRAM PEMECAHAN UANG');
    writeln('==========================================');
    writeln('1. Pecah Uang');
    writeln('0. Keluar');
    writeln('------------------------------------------');
    write('Pilihan Anda : ');
    readln(pilihan);

    case pilihan of
      1 : begin
            InputNominal(nominal);   // Input
            ProsesPecahan(nominal);  // Proses + Output
            writeln('Tekan Enter untuk kembali ke menu...');
            readln;
          end;
      0 : writeln('Terima kasih telah menggunakan program ini.');
    else
      writeln('Pilihan tidak tersedia!');
      readln;
    end;

  until (pilihan = 0);
end.