// =====================================================
// TUGAS 6      : Pemeriksa Palindrom
//                (Stack, Queue, Rekursif, DLL)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <string>
#include "palindrom.h"
using namespace std;

// State global supaya tidak input ulang tiap menu
List    L;
ListDLL DL;
string  teksTersimpan = "";
bool    sllSiap = false;
bool    dllSiap = false;

// =====================================================
// Menu 1 : Buat SLL dari teks
// =====================================================
void menuBuatList() {
    cout << "Masukkan kata/kalimat : ";
    getline(cin, teksTersimpan);

    buildList(L, teksTersimpan);
    sllSiap = true;
    cout << "Linked List berhasil dibentuk.\n";
    cout << "Isi List : "; viewList(L); cout << endl;
}

// =====================================================
// Menu 2 : Tampilkan SLL
// =====================================================
void menuTampilList() {
    if (!sllSiap) { cout << "[!] Belum ada list. Pilih menu 1 dulu.\n"; return; }
    cout << "Teks asli   : " << teksTersimpan << endl;
    cout << "Isi List    : "; viewList(L); cout << endl;
}

// =====================================================
// Menu 3 : Hitung karakter
// =====================================================
void menuHitungKarakter() {
    if (!sllSiap) { cout << "[!] Belum ada list. Pilih menu 1 dulu.\n"; return; }
    cout << "Jumlah karakter (setelah normalisasi) : " << countNode(L) << endl;
}

// =====================================================
// Fungsi bantu: pastikan list sudah siap
// =====================================================
bool pastikanList() {
    if (!sllSiap) {
        cout << "[!] Belum ada list. Pilih menu 1 dulu.\n";
        return false;
    }
    return true;
}

// =====================================================
// Menu 4 : Cek palindrom - Stack
// =====================================================
void menuCekStack() {
    if (!pastikanList()) return;

    // Tampilkan isi stack untuk transparansi
    Stack S; createStack(S);
    NodeSLL* p = L.First;
    while (p != NULL) { push(S, p->info); p = p->next; }
    cout << "Isi Stack : "; viewStack(S); cout << endl;
    deleteStack(S);

    bool hasil = isPalindromeStack(L);
    cout << "Hasil (Stack) : "
         << (hasil ? "PALINDROM" : "BUKAN PALINDROM") << endl;
}

// =====================================================
// Menu 5 : Cek palindrom - Queue + Stack
// =====================================================
void menuCekQueueStack() {
    if (!pastikanList()) return;

    Queue Q; Stack S;
    createQueue(Q); createStack(S);
    NodeSLL* p = L.First;
    while (p != NULL) { enqueue(Q, p->info); push(S, p->info); p = p->next; }
    cout << "Isi Queue : "; viewQueue(Q); cout << endl;
    cout << "Isi Stack : "; viewStack(S); cout << endl;
    deleteQueue(Q); deleteStack(S);

    bool hasil = isPalindromeQueueStack(L);
    cout << "Hasil (Queue + Stack) : "
         << (hasil ? "PALINDROM" : "BUKAN PALINDROM") << endl;
}

// =====================================================
// Menu 6 : Cek palindrom - Rekursif
// =====================================================
void menuCekRekursif() {
    if (!pastikanList()) return;
    bool hasil = isPalindromeRecursive(L);
    cout << "Hasil (Rekursif) : "
         << (hasil ? "PALINDROM" : "BUKAN PALINDROM") << endl;
}

// =====================================================
// Menu 7 : Buat DLL dari teks
// =====================================================
void menuBuatDLL() {
    if (teksTersimpan == "") {
        cout << "Masukkan kata/kalimat : ";
        getline(cin, teksTersimpan);
    }
    buildListDLL(DL, teksTersimpan);
    dllSiap = true;
    cout << "Double Linked List berhasil dibentuk.\n";
    cout << "Isi DLL (forward) : "; viewForward(DL); cout << endl;
}

// =====================================================
// Menu 8 : Tampilkan DLL forward
// =====================================================
void menuTampilForward() {
    if (!dllSiap) { cout << "[!] Belum ada DLL. Pilih menu 7 dulu.\n"; return; }
    cout << "Tampilan dari depan : "; viewForward(DL); cout << endl;
}

// =====================================================
// Menu 9 : Tampilkan DLL backward
// =====================================================
void menuTampilBackward() {
    if (!dllSiap) { cout << "[!] Belum ada DLL. Pilih menu 7 dulu.\n"; return; }
    cout << "Tampilan dari belakang : "; viewBackward(DL); cout << endl;
}

// =====================================================
// Menu 10 : Cek palindrom - DLL
// =====================================================
void menuCekDLL() {
    if (!dllSiap) { cout << "[!] Belum ada DLL. Pilih menu 7 dulu.\n"; return; }
    bool hasil = isPalindromeDLL(DL);
    cout << "Hasil (DLL) : "
         << (hasil ? "PALINDROM" : "BUKAN PALINDROM") << endl;
}

// =====================================================
// Menu utama
// =====================================================
void tampilMenu() {
    cout << "\n========== PEMERIKSA PALINDROM ==========\n";
    cout << "1.  Buat List dari Teks\n";
    cout << "2.  Tampilkan Teks (Linked List)\n";
    cout << "3.  Hitung Jumlah Karakter\n";
    cout << "4.  Cek Palindrom - Stack (LL)\n";
    cout << "5.  Cek Palindrom - Queue + Stack (LL)\n";
    cout << "6.  Cek Palindrom - Rekursif\n";
    cout << "7.  Buat DLL dari Teks\n";
    cout << "8.  Tampilkan DLL dari Depan\n";
    cout << "9.  Tampilkan DLL dari Belakang\n";
    cout << "10. Cek Palindrom - DLL\n";
    cout << "0.  Keluar\n";
    cout << "=========================================\n";
    cout << "Pilihan : ";
}

int main() {
    int pilih;
    do {
        tampilMenu();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:  menuBuatList();       break;
            case 2:  menuTampilList();     break;
            case 3:  menuHitungKarakter(); break;
            case 4:  menuCekStack();       break;
            case 5:  menuCekQueueStack();  break;
            case 6:  menuCekRekursif();    break;
            case 7:  menuBuatDLL();        break;
            case 8:  menuTampilForward();  break;
            case 9:  menuTampilBackward(); break;
            case 10: menuCekDLL();         break;
            case 0:  cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    // Bersihkan memori
    deleteList(L);
    deleteListDLL(DL);
    return 0;
}