// =====================================================
// TUGAS 5      : Pengolahan Ekspresi Postfix
//                (Stack, Queue, Rekursif)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include <string>
#include "stack.h"
#include "queue.h"
#include "expression.h"
using namespace std;

// tree global supaya bisa diakses antar menu
ExpressionNode* gTree = NULL;

// =====================================================
// MENU 1: UJI STACK
// =====================================================
void ujiStack() {
    Stack S;
    createStack(S);
    int pilih;
    string token;

    do {
        cout << "\n===== UJI STACK =====\n";
        cout << "1. Push\n2. Pop\n3. Peek\n4. View\n";
        cout << "5. Cek kosong\n6. Cek penuh\n0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                cout << "Token : "; getline(cin, token);
                push(S, token);
                cout << "Isi stack : "; viewStack(S); cout << endl;
                break;
            case 2:
                if (isEmptyStack(S)) cout << "Stack kosong!\n";
                else {
                    token = pop(S);
                    cout << "Pop : " << token << endl;
                    cout << "Isi stack : "; viewStack(S); cout << endl;
                }
                break;
            case 3:
                if (isEmptyStack(S)) cout << "Stack kosong!\n";
                else cout << "Peek : " << peek(S) << endl;
                break;
            case 4:
                cout << "Isi stack : "; viewStack(S); cout << endl;
                break;
            case 5:
                cout << (isEmptyStack(S) ? "Stack KOSONG" : "Stack TIDAK kosong") << endl;
                break;
            case 6:
                cout << (isFullStack(S) ? "Stack PENUH" : "Stack TIDAK penuh") << endl;
                break;
        }
    } while (pilih != 0);
}

// =====================================================
// MENU 2: UJI QUEUE
// =====================================================
void ujiQueue() {
    Queue Q;
    createQueue(Q);
    int pilih;
    string token;

    do {
        cout << "\n===== UJI QUEUE =====\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Front\n4. View\n";
        cout << "5. Cek kosong\n6. Cek penuh\n0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                cout << "Token : "; getline(cin, token);
                enqueue(Q, token);
                cout << "Isi queue : "; viewQueue(Q); cout << endl;
                break;
            case 2:
                if (isEmptyQueue(Q)) cout << "Queue kosong!\n";
                else {
                    token = dequeue(Q);
                    cout << "Dequeue : " << token << endl;
                    cout << "Isi queue : "; viewQueue(Q); cout << endl;
                }
                break;
            case 3:
                if (isEmptyQueue(Q)) cout << "Queue kosong!\n";
                else cout << "Front : " << frontQueue(Q) << endl;
                break;
            case 4:
                cout << "Isi queue : "; viewQueue(Q); cout << endl;
                break;
            case 5:
                cout << (isEmptyQueue(Q) ? "Queue KOSONG" : "Queue TIDAK kosong") << endl;
                break;
            case 6:
                cout << (isFullQueue(Q) ? "Queue PENUH" : "Queue TIDAK penuh") << endl;
                break;
        }
    } while (pilih != 0);
}

// =====================================================
// MENU 3: EVALUASI ITERATIF (dengan trace)
// =====================================================
void menuEvaluasiIteratif() {
    string expr;
    cout << "Masukkan ekspresi postfix : ";
    getline(cin, expr);

    string tokens[MAX_STACK];
    int n;
    tokenize(expr, tokens, n);
    if (n == 0) { cout << "Ekspresi kosong!\n"; return; }

    cout << "\nToken : ";
    for (int i = 0; i < n; i++) cout << tokens[i] << " ";
    cout << endl;

    Stack S;
    createStack(S);
    bool error = false;

    for (int i = 0; i < n; i++) {
        string token = tokens[i];
        cout << "\nToken ke-" << (i + 1) << " : " << token << endl;

        if (isOperand(token)) {
            if (!isDigitToken(token)) {
                cout << "  [!] Operand huruf, gunakan menu 8.\n";
                error = true; break;
            }
            push(S, token);
            cout << "  Push -> "; viewStack(S); cout << endl;
        } else if (isOperator(token)) {
            if (S.top < 1) {
                cout << "  [!] Operand tidak mencukupi!\n";
                error = true; break;
            }
            double b = atof(pop(S).c_str());
            double a = atof(pop(S).c_str());
            double r; string err;
            if (!hitung(a, b, token, r, err)) {
                cout << "  [!] " << err << endl;
                error = true; break;
            }
            char buf[64]; sprintf(buf, "%.6f", r);
            push(S, string(buf));
            cout << "  Hitung " << a << " " << token << " " << b
                 << " = " << r << endl;
            cout << "  Push hasil -> "; viewStack(S); cout << endl;
        } else {
            cout << "  [!] Token tidak valid!\n";
            error = true; break;
        }
    }

    if (!error) {
        if (S.top != 0) {
            cout << "\n[!] Ekspresi tidak menghasilkan satu nilai akhir.\n";
        } else {
            cout << "\n>>> HASIL AKHIR = " << atof(pop(S).c_str()) << endl;
        }
    }
}

// =====================================================
// MENU 4: KONVERSI INFIX -> POSTFIX
// =====================================================
void menuInfixToPostfix() {
    string infix;
    cout << "Masukkan ekspresi infix (mis. A + B * C) : ";
    getline(cin, infix);

    string postfix[MAX_STACK];
    int n;
    infixToPostfix(infix, postfix, n);

    cout << "Postfix : ";
    for (int i = 0; i < n; i++) cout << postfix[i] << " ";
    cout << endl;
}

// =====================================================
// MENU 5: EVALUASI REKURSIF
// =====================================================
void menuEvaluasiRekursif() {
    string expr;
    cout << "Masukkan ekspresi postfix : ";
    getline(cin, expr);

    string tokens[MAX_STACK];
    int n;
    tokenize(expr, tokens, n);
    if (n == 0) { cout << "Ekspresi kosong!\n"; return; }

    Stack S;
    createStack(S);
    double hasil; string err;
    if (evaluatePostfixRecursive(tokens, n, 0, S, hasil, err))
        cout << "Hasil (rekursif) = " << hasil << endl;
    else
        cout << "[!] Error : " << err << endl;
}

// =====================================================
// MENU 6: BENTUK POHON EKSPRESI
// =====================================================
void menuBentukPohon() {
    string expr;
    cout << "Masukkan ekspresi postfix : ";
    getline(cin, expr);

    string tokens[MAX_STACK];
    int n;
    tokenize(expr, tokens, n);
    if (n == 0) { cout << "Ekspresi kosong!\n"; return; }

    // hapus tree lama
    if (gTree != NULL) { deleteTree(gTree); gTree = NULL; }

    bool sukses;
    gTree = buildExpressionTree(tokens, n, sukses);
    if (!sukses || gTree == NULL) {
        cout << "[!] Gagal membentuk pohon ekspresi.\n";
        if (gTree != NULL) { deleteTree(gTree); gTree = NULL; }
        return;
    }
    cout << "Pohon ekspresi berhasil dibentuk.\n";
    cout << "Gunakan menu 7 untuk menampilkan traversal.\n";
}

// =====================================================
// MENU 7: TAMPILKAN TRAVERSAL POHON
// =====================================================
void menuTraversal() {
    if (gTree == NULL) {
        cout << "[!] Belum ada pohon ekspresi. Pilih menu 6 dulu.\n";
        return;
    }
    cout << "\n--- HASIL TRAVERSAL ---\n";
    cout << "Infix   : "; inorder(gTree);   cout << endl;
    cout << "Prefix  : "; preorder(gTree);  cout << endl;
    cout << "Postfix : "; postorder(gTree); cout << endl;
}

// =====================================================
// MENU 8: EVALUASI DENGAN VARIABEL
// =====================================================
void menuEvaluasiVariabel() {
    string expr;
    cout << "Masukkan ekspresi postfix : ";
    getline(cin, expr);

    string tokens[MAX_STACK];
    int n;
    tokenize(expr, tokens, n);
    if (n == 0) { cout << "Ekspresi kosong!\n"; return; }

    // kumpulkan variabel unik
    VarValue vars[26];
    int nVar = 0;
    for (int i = 0; i < n; i++) {
        string t = tokens[i];
        if (isOperand(t) && !isDigitToken(t)) {
            char c = t[0];
            bool found = false;
            for (int j = 0; j < nVar; j++)
                if (vars[j].name == c) { found = true; break; }
            if (!found) {
                vars[nVar].name = c;
                cout << "Nilai " << c << " : ";
                cin >> vars[nVar].value;
                nVar++;
            }
        }
    }
    cin.ignore();

    double hasil; string err;
    if (processPostfixWithVars(tokens, n, vars, nVar, hasil, err))
        cout << "\n>>> HASIL = " << hasil << endl;
    else
        cout << "[!] Error : " << err << endl;
}

// =====================================================
// MENU 9: BANDINGKAN ITERATIF vs REKURSIF
// =====================================================
void menuBandingkan() {
    string expr;
    cout << "Masukkan ekspresi postfix (digit) : ";
    getline(cin, expr);

    string tokens[MAX_STACK];
    int n;
    tokenize(expr, tokens, n);
    if (n == 0) { cout << "Ekspresi kosong!\n"; return; }

    double h1, h2; string err1, err2;

    bool ok1 = processPostfix(tokens, n, h1, err1);

    Stack S;
    createStack(S);
    bool ok2 = evaluatePostfixRecursive(tokens, n, 0, S, h2, err2);

    cout << "\n--- HASIL PERBANDINGAN ---\n";
    if (ok1) cout << "Iteratif : " << h1 << endl;
    else     cout << "Iteratif : ERROR - " << err1 << endl;

    if (ok2) cout << "Rekursif : " << h2 << endl;
    else     cout << "Rekursif : ERROR - " << err2 << endl;

    if (ok1 && ok2)
        cout << "Kesimpulan : " << (h1 == h2 ? "SAMA" : "BERBEDA") << endl;
}

// =====================================================
// MENU UTAMA
// =====================================================
void tampilMenu() {
    cout << "\n========= PENGOLAHAN EKSPRESI POSTFIX =========\n";
    cout << "1. Uji Operasi Stack\n";
    cout << "2. Uji Operasi Queue\n";
    cout << "3. Evaluasi Postfix (Iteratif + Trace)\n";
    cout << "4. Konversi Infix ke Postfix\n";
    cout << "5. Evaluasi Postfix (Rekursif)\n";
    cout << "6. Bentuk Pohon Ekspresi dari Postfix\n";
    cout << "7. Tampilkan Traversal Pohon Ekspresi\n";
    cout << "8. Evaluasi dengan Variabel\n";
    cout << "9. Bandingkan Iteratif vs Rekursif\n";
    cout << "0. Keluar\n";
    cout << "===============================================\n";
    cout << "Pilihan : ";
}

int main() {
    int pilih;
    do {
        tampilMenu();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: ujiStack(); break;
            case 2: ujiQueue(); break;
            case 3: menuEvaluasiIteratif(); break;
            case 4: menuInfixToPostfix(); break;
            case 5: menuEvaluasiRekursif(); break;
            case 6: menuBentukPohon(); break;
            case 7: menuTraversal(); break;
            case 8: menuEvaluasiVariabel(); break;
            case 9: menuBandingkan(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    if (gTree != NULL) deleteTree(gTree);
    return 0;
}