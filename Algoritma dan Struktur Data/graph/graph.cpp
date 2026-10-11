// =====================================================
// File : graph.cpp
// Berisi implementasi ADT Graph
// =====================================================

#include <iostream>
#include <iomanip>
#include "graph.h"
using namespace std;

// =====================================================
// 1. CREATE GRAPH
// =====================================================
void createGraph(Graph &G) {
    G.firstVertex = NULL;
}

bool isEmptyGraph(Graph G) {
    return (G.firstVertex == NULL);
}

// =====================================================
// 2. CREATE VERTEX
// =====================================================
Vertex* createVertex(string nim, string nama) {
    Vertex* V = new Vertex;
    V->nim        = nim;
    V->nama       = nama;
    V->firstEdge  = NULL;
    V->nextVertex = NULL;
    return V;
}

// =====================================================
// 3. INSERT VERTEX (di akhir, NIM harus unik)
// =====================================================
void insertVertex(Graph &G, Vertex* V) {
    if (searchVertex(G, V->nim) != NULL) {
        cout << "NIM " << V->nim << " sudah terdaftar!\n";
        delete V;
        return;
    }
    if (G.firstVertex == NULL) {
        G.firstVertex = V;
    } else {
        Vertex* p = G.firstVertex;
        while (p->nextVertex != NULL) p = p->nextVertex;
        p->nextVertex = V;
    }
    cout << "Vertex " << V->nama << " berhasil ditambahkan.\n";
}

// =====================================================
// 4. SEARCH VERTEX
// =====================================================
Vertex* searchVertex(Graph G, string nimCari) {
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        if (V->nim == nimCari) return V;
        V = V->nextVertex;
    }
    return NULL;
}

// =====================================================
// 5. CREATE EDGE
// =====================================================
Edge* createEdge(string destNIM) {
    Edge* E = new Edge;
    E->destNIM  = destNIM;
    E->nextEdge = NULL;
    return E;
}

// =====================================================
// 6. INSERT EDGE (undirected)
// =====================================================
void insertEdge(Graph &G, string nim1, string nim2) {
    Vertex* V1 = searchVertex(G, nim1);
    Vertex* V2 = searchVertex(G, nim2);

    if (V1 == NULL || V2 == NULL) {
        cout << "Vertex sumber atau tujuan belum terdaftar!\n";
        return;
    }

    // Tambah edge ke adjacency list V1
    Edge* E1 = createEdge(nim2);
    if (V1->firstEdge == NULL) {
        V1->firstEdge = E1;
    } else {
        Edge* p = V1->firstEdge;
        while (p->nextEdge != NULL) p = p->nextEdge;
        p->nextEdge = E1;
    }

    // Jika bukan self-loop, tambahkan juga ke V2
    if (nim1 != nim2) {
        Edge* E2 = createEdge(nim1);
        if (V2->firstEdge == NULL) {
            V2->firstEdge = E2;
        } else {
            Edge* p = V2->firstEdge;
            while (p->nextEdge != NULL) p = p->nextEdge;
            p->nextEdge = E2;
        }
    }
    cout << "Edge " << nim1 << " -- " << nim2 << " ditambahkan.\n";
}

// =====================================================
// 7. DELETE EDGE (hapus satu kemunculan)
// =====================================================
void deleteEdge(Graph &G, string nim1, string nim2) {
    Vertex* V1 = searchVertex(G, nim1);
    Vertex* V2 = searchVertex(G, nim2);

    if (V1 == NULL || V2 == NULL) {
        cout << "Vertex tidak ditemukan!\n";
        return;
    }

    // Cari & hapus edge nim2 di adjacency list V1
    Edge* p    = V1->firstEdge;
    Edge* prev = NULL;
    bool  found1 = false;
    while (p != NULL && !found1) {
        if (p->destNIM == nim2) {
            if (prev == NULL) V1->firstEdge = p->nextEdge;
            else              prev->nextEdge = p->nextEdge;
            delete p;
            found1 = true;
        } else {
            prev = p;
            p    = p->nextEdge;
        }
    }

    if (!found1) {
        cout << "Edge tidak ditemukan.\n";
        return;
    }

    // Jika bukan self-loop, hapus juga di V2
    if (nim1 != nim2) {
        Edge* q    = V2->firstEdge;
        Edge* prevq = NULL;
        bool  found2 = false;
        while (q != NULL && !found2) {
            if (q->destNIM == nim1) {
                if (prevq == NULL) V2->firstEdge = q->nextEdge;
                else               prevq->nextEdge = q->nextEdge;
                delete q;
                found2 = true;
            } else {
                prevq = q;
                q     = q->nextEdge;
            }
        }
    }
    cout << "Edge " << nim1 << " -- " << nim2 << " dihapus.\n";
}

// =====================================================
// 8. DELETE VERTEX (hapus vertex + semua edge terkait)
// =====================================================
void deleteVertex(Graph &G, string nim) {
    Vertex* V    = G.firstVertex;
    Vertex* prev = NULL;

    while (V != NULL && V->nim != nim) {
        prev = V;
        V    = V->nextVertex;
    }

    if (V == NULL) {
        cout << "Vertex tidak ditemukan.\n";
        return;
    }

    // Hapus edge di vertex LAIN yang menunjuk ke V
    Vertex* W = G.firstVertex;
    while (W != NULL) {
        if (W != V) {
            Edge* e    = W->firstEdge;
            Edge* preve = NULL;
            while (e != NULL) {
                if (e->destNIM == nim) {
                    Edge* hapus = e;
                    if (preve == NULL) W->firstEdge = e->nextEdge;
                    else               preve->nextEdge = e->nextEdge;
                    e = e->nextEdge;
                    delete hapus;
                } else {
                    preve = e;
                    e     = e->nextEdge;
                }
            }
        }
        W = W->nextVertex;
    }

    // Hapus semua edge milik V
    Edge* e = V->firstEdge;
    while (e != NULL) {
        Edge* temp = e;
        e = e->nextEdge;
        delete temp;
    }

    // Hapus vertex V
    if (prev == NULL) G.firstVertex = V->nextVertex;
    else              prev->nextVertex = V->nextVertex;

    cout << "Vertex " << V->nama << " beserta seluruh edge-nya dihapus.\n";
    delete V;
}

// =====================================================
// 9. VIEW GRAPH
// =====================================================
void viewGraph(Graph G) {
    if (isEmptyGraph(G)) {
        cout << "Graph kosong.\n";
        return;
    }
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        cout << V->nim << " (" << V->nama << ") : ";
        Edge* E = V->firstEdge;
        if (E == NULL) {
            cout << "(tidak ada tetangga)";
        } else {
            while (E != NULL) {
                cout << E->destNIM;
                if (E->nextEdge != NULL) cout << ", ";
                E = E->nextEdge;
            }
        }
        cout << endl;
        V = V->nextVertex;
    }
}

// =====================================================
// 10. VIEW NEIGHBORS
// =====================================================
void viewNeighbors(Graph G, string nim) {
    Vertex* V = searchVertex(G, nim);
    if (V == NULL) {
        cout << "Vertex tidak ditemukan.\n";
        return;
    }

    cout << "Tetangga dari " << V->nama << " (" << V->nim << ") : ";
    if (V->firstEdge == NULL) {
        cout << "(belum memiliki hubungan pertemanan)\n";
        return;
    }
    Edge* E = V->firstEdge;
    while (E != NULL) {
        Vertex* T = searchVertex(G, E->destNIM);
        cout << E->destNIM;
        if (T != NULL) cout << " (" << T->nama << ")";
        if (E->nextEdge != NULL) cout << ", ";
        E = E->nextEdge;
    }
    cout << endl;
}

// =====================================================
// 11. DEGREE VERTEX (self-loop dihitung 2)
// =====================================================
int degreeVertex(Graph G, string nim) {
    Vertex* V = searchVertex(G, nim);
    if (V == NULL) return -1;

    int deg = 0;
    Edge* E = V->firstEdge;
    while (E != NULL) {
        if (E->destNIM == nim) deg += 2;   // self-loop = 2
        else                   deg += 1;
        E = E->nextEdge;
    }
    return deg;
}

// =====================================================
// 12. COUNT VERTEX
// =====================================================
int countVertex(Graph G) {
    int c = 0;
    Vertex* V = G.firstVertex;
    while (V != NULL) { c++; V = V->nextVertex; }
    return c;
}

// =====================================================
// 13. COUNT EDGES (edge logis, tidak double-count)
// =====================================================
int countEdges(Graph G) {
    int nonLoop = 0;
    int selfLoop = 0;
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        Edge* E = V->firstEdge;
        while (E != NULL) {
            if (E->destNIM == V->nim) selfLoop++;
            else                      nonLoop++;
            E = E->nextEdge;
        }
        V = V->nextVertex;
    }
    // non-loop dihitung 2x (di kedua vertex), bagi 2
    return (nonLoop / 2) + selfLoop;
}

// =====================================================
// 14. COUNT NEIGHBORS UNIK
// =====================================================
int countNeighbors(Graph G, string nim) {
    Vertex* V = searchVertex(G, nim);
    if (V == NULL) return -1;

    string seen[MAX_VISITED];
    int    nSeen = 0;

    Edge* E = V->firstEdge;
    while (E != NULL) {
        // Skip self-loop
        if (E->destNIM != nim) {
            bool already = false;
            for (int i = 0; i < nSeen; i++)
                if (seen[i] == E->destNIM) { already = true; break; }
            if (!already) seen[nSeen++] = E->destNIM;
        }
        E = E->nextEdge;
    }
    return nSeen;
}

// =====================================================
// 15. VIEW ISOLATED VERTICES
// =====================================================
void viewIsolatedVertices(Graph G) {
    cout << "Mahasiswa tanpa tetangga berbeda:\n";
    bool ada = false;
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        if (countNeighbors(G, V->nim) == 0) {
            cout << "  - " << V->nim << " (" << V->nama << ")\n";
            ada = true;
        }
        V = V->nextVertex;
    }
    if (!ada) cout << "  (tidak ada)\n";
}

// =====================================================
// 16. HAS LOOP
// =====================================================
bool hasLoop(Graph G) {
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        Edge* E = V->firstEdge;
        while (E != NULL) {
            if (E->destNIM == V->nim) return true;
            E = E->nextEdge;
        }
        V = V->nextVertex;
    }
    return false;
}

// =====================================================
// 17. HAS MULTIPLE EDGES
// =====================================================
bool hasMultipleEdges(Graph G) {
    Vertex* V = G.firstVertex;
    while (V != NULL) {
        Edge* E1 = V->firstEdge;
        while (E1 != NULL) {
            Edge* E2 = E1->nextEdge;
            while (E2 != NULL) {
                if (E1->destNIM == E2->destNIM) return true;
                E2 = E2->nextEdge;
            }
            E1 = E1->nextEdge;
        }
        V = V->nextVertex;
    }
    return false;
}

// =====================================================
// 18. IS SIMPLE GRAPH
// =====================================================
bool isSimpleGraph(Graph G) {
    return (!hasLoop(G) && !hasMultipleEdges(G));
}

// =====================================================
// 19. DFS (rekursif)
// =====================================================
static void DFSHelper(Graph G, string nim, string visited[], int &nVisited) {
    // sudah pernah dikunjungi?
    for (int i = 0; i < nVisited; i++)
        if (visited[i] == nim) return;

    visited[nVisited++] = nim;
    cout << nim;
    if (nVisited < MAX_VISITED) cout << " ";

    Vertex* V = searchVertex(G, nim);
    if (V == NULL) return;

    Edge* E = V->firstEdge;
    while (E != NULL) {
        DFSHelper(G, E->destNIM, visited, nVisited);
        E = E->nextEdge;
    }
}

void DFS(Graph G, string startNIM) {
    if (searchVertex(G, startNIM) == NULL) {
        cout << "Vertex awal tidak ditemukan!\n";
        return;
    }
    string visited[MAX_VISITED];
    int    nVisited = 0;
    cout << "DFS dari " << startNIM << " : ";
    DFSHelper(G, startNIM, visited, nVisited);
    cout << endl;
}

// =====================================================
// 20. BFS (pakai queue sederhana berbasis array)
// =====================================================
void BFS(Graph G, string startNIM) {
    if (searchVertex(G, startNIM) == NULL) {
        cout << "Vertex awal tidak ditemukan!\n";
        return;
    }

    string queue[MAX_VISITED];
    string visited[MAX_VISITED];
    int    head = 0, tail = 0;
    int    nVisited = 0;

    queue[tail++] = startNIM;
    visited[nVisited++] = startNIM;

    cout << "BFS dari " << startNIM << " : ";
    while (head < tail) {
        string curr = queue[head++];
        cout << curr << " ";

        Vertex* V = searchVertex(G, curr);
        if (V == NULL) continue;

        Edge* E = V->firstEdge;
        while (E != NULL) {
            bool sudah = false;
            for (int i = 0; i < nVisited; i++)
                if (visited[i] == E->destNIM) { sudah = true; break; }
            if (!sudah) {
                queue[tail++] = E->destNIM;
                visited[nVisited++] = E->destNIM;
            }
            E = E->nextEdge;
        }
    }
    cout << endl;
}

// =====================================================
// 21. IS CONNECTED
// =====================================================
bool isConnected(Graph G) {
    if (isEmptyGraph(G)) return false;          // graph kosong dianggap tidak terhubung
    if (countVertex(G) == 1) return true;

    string visited[MAX_VISITED];
    int    nVisited = 0;
    DFSHelper(G, G.firstVertex->nim, visited, nVisited);

    return (nVisited == countVertex(G));
}