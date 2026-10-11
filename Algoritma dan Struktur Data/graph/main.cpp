// =====================================================
// TUGAS 8      : ADT Graph - Sistem Pertemanan Mahasiswa
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <string>
#include "graph.h"
using namespace std;

Graph G;

// =====================================================
// 1. TAMBAH VERTEX
// =====================================================
void menuInsertVertex() {
    string nim, nama;
    cout << "NIM  : "; getline(cin, nim);
    cout << "Nama : "; getline(cin, nama);
    insertVertex(G, createVertex(nim, nama));
}

// =====================================================
// 2. TAMBAH EDGE
// =====================================================
void menuInsertEdge() {
    string nim1, nim2;
    cout << "NIM 1 : "; getline(cin, nim1);
    cout << "NIM 2 : "; getline(cin, nim2);
    insertEdge(G, nim1, nim2);
}

// =====================================================
// 3. HAPUS EDGE
// =====================================================
void menuDeleteEdge() {
    string nim1, nim2;
    cout << "NIM 1 : "; getline(cin, nim1);
    cout << "NIM 2 : "; getline(cin, nim2);
    deleteEdge(G, nim1, nim2);
}

// =====================================================
// 4. HAPUS VERTEX
// =====================================================
void menuDeleteVertex() {
    string nim;
    cout << "NIM yang akan dihapus : "; getline(cin, nim);
    deleteVertex(G, nim);
}

// =====================================================
// 5. CARI VERTEX
// =====================================================
void menuCariVertex() {
    string nim;
    cout << "NIM yang dicari : "; getline(cin, nim);
    Vertex* V = searchVertex(G, nim);
    if (V == NULL)
        cout << "Vertex tidak ditemukan.\n";
    else
        cout << "Ditemukan: " << V->nim << " (" << V->nama << ")\n";
}

// =====================================================
// 6. DEGREE VERTEX
// =====================================================
void menuDegree() {
    string nim;
    cout << "NIM : "; getline(cin, nim);
    int d = degreeVertex(G, nim);
    if (d == -1) cout << "Vertex tidak ditemukan.\n";
    else         cout << "Derajat vertex " << nim << " = " << d << endl;
}

// =====================================================
// 7. COUNT NEIGHBORS
// =====================================================
void menuCountNeighbors() {
    string nim;
    cout << "NIM : "; getline(cin, nim);
    int n = countNeighbors(G, nim);
    if (n == -1) cout << "Vertex tidak ditemukan.\n";
    else         cout << "Jumlah tetangga unik = " << n << endl;
}

// =====================================================
// 8. ISI DATA CONTOH
// =====================================================
void isiDataContoh() {
    struct Data { string nim, nama; };
    Data d[] = {
        {"M001", "Andi"},
        {"M002", "Budi"},
        {"M003", "Citra"},
        {"M004", "Dinda"},
        {"M005", "Eko"}
    };
    int n = sizeof(d) / sizeof(d[0]);
    for (int i = 0; i < n; i++) {
        if (searchVertex(G, d[i].nim) == NULL)
            insertVertex(G, createVertex(d[i].nim, d[i].nama));
    }
    cout << "5 vertex contoh berhasil dimasukkan.\n";
}

// =====================================================
// 9. ISI EDGE CONTOH
// =====================================================
void isiEdgeContoh() {
    insertEdge(G, "M001", "M002");
    insertEdge(G, "M001", "M003");
    insertEdge(G, "M002", "M004");
    insertEdge(G, "M003", "M005");
    cout << "4 edge contoh berhasil dimasukkan.\n";
}

// =====================================================
// 10. TAMPILKAN HASIL PEMERIKSAAN
// =====================================================
void tampilPemeriksaan() {
    cout << "\n--- Pemeriksaan Graph ---\n";
    cout << "Jumlah vertex       : " << countVertex(G) << endl;
    cout << "Jumlah edge         : " << countEdges(G) << endl;
    cout << "hasLoop             : " << (hasLoop(G) ? "TRUE" : "FALSE") << endl;
    cout << "hasMultipleEdges    : " << (hasMultipleEdges(G) ? "TRUE" : "FALSE") << endl;
    cout << "isSimpleGraph       : " << (isSimpleGraph(G) ? "TRUE" : "FALSE") << endl;
    cout << "isConnected         : " << (isConnected(G) ? "TRUE" : "FALSE") << endl;
}

// =====================================================
// 11. MENU TRAVERSAL
// =====================================================
void menuDFS() {
    string nim;
    cout << "NIM awal DFS : "; getline(cin, nim);
    DFS(G, nim);
}

void menuBFS() {
    string nim;
    cout << "NIM awal BFS : "; getline(cin, nim);
    BFS(G, nim);
}

// =====================================================
// 12. VIEW NEIGHBORS
// =====================================================
void menuViewNeighbors() {
    string nim;
    cout << "NIM : "; getline(cin, nim);
    viewNeighbors(G, nim);
}

// =====================================================
// MENU UTAMA
// =====================================================
void tampilMenu() {
    cout << "\n========== SISTEM PERTEMANAN MAHASISWA ==========\n";
    cout << "1.  Tambah Vertex (Mahasiswa)\n";
    cout << "2.  Tambah Edge (Pertemanan)\n";
    cout << "3.  Hapus Edge\n";
    cout << "4.  Hapus Vertex\n";
    cout << "5.  Cari Vertex berdasarkan NIM\n";
    cout << "6.  Tampilkan Seluruh Graph\n";
    cout << "7.  Tampilkan Tetangga Mahasiswa\n";
    cout << "8.  Hitung Jumlah Vertex\n";
    cout << "9.  Hitung Jumlah Edge\n";
    cout << "10. Hitung Derajat Vertex\n";
    cout << "11. Cek hasLoop\n";
    cout << "12. Cek hasMultipleEdges\n";
    cout << "13. Cek isSimpleGraph\n";
    cout << "14. Traversal DFS\n";
    cout << "15. Traversal BFS\n";
    cout << "16. Cek isConnected\n";
    cout << "17. Tampilkan Isolated Vertices\n";
    cout << "18. Hitung Jumlah Tetangga Unik\n";
    cout << "19. Isi Data Contoh (Vertex + Edge)\n";
    cout << "20. Tampilkan Semua Pemeriksaan\n";
    cout << "0.  Keluar\n";
    cout << "=================================================\n";
    cout << "Pilihan : ";
}

int main() {
    createGraph(G);

    int pilih;
    do {
        tampilMenu();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:  menuInsertVertex();       break;
            case 2:  menuInsertEdge();         break;
            case 3:  menuDeleteEdge();         break;
            case 4:  menuDeleteVertex();       break;
            case 5:  menuCariVertex();         break;
            case 6:  viewGraph(G);             break;
            case 7:  menuViewNeighbors();      break;
            case 8:  cout << "Jumlah vertex : " << countVertex(G) << endl; break;
            case 9:  cout << "Jumlah edge   : " << countEdges(G) << endl;  break;
            case 10: menuDegree();             break;
            case 11: cout << "hasLoop : " << (hasLoop(G) ? "TRUE" : "FALSE") << endl; break;
            case 12: cout << "hasMultipleEdges : " << (hasMultipleEdges(G) ? "TRUE" : "FALSE") << endl; break;
            case 13: cout << "isSimpleGraph : " << (isSimpleGraph(G) ? "TRUE" : "FALSE") << endl; break;
            case 14: menuDFS();                break;
            case 15: menuBFS();                break;
            case 16: cout << "isConnected : " << (isConnected(G) ? "TRUE" : "FALSE") << endl; break;
            case 17: viewIsolatedVertices(G);  break;
            case 18: menuCountNeighbors();     break;
            case 19: isiDataContoh(); isiEdgeContoh(); break;
            case 20: tampilPemeriksaan();      break;
            case 0:  cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    return 0;
}