// =====================================================
// TUGAS 8      : ADT Graph - Sistem Pertemanan Mahasiswa
//                (Adjacency List berbasis Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : graph.h
// =====================================================

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
using namespace std;

const int MAX_VISITED = 100;

// =====================================================
//            DEFINISI ADT GRAPH
// =====================================================

// Node Edge: menyimpan tujuan (NIM tetangga)
struct Edge {
    string destNIM;
    Edge*  nextEdge;
};

// Node Vertex: menyimpan data mahasiswa + adjacency list
struct Vertex {
    string  nim;
    string  nama;
    Edge*   firstEdge;
    Vertex* nextVertex;
};

// Graph: pointer ke vertex pertama
struct Graph {
    Vertex* firstVertex;
};

// =====================================================
//            OPERASI DASAR GRAPH
// =====================================================
void    createGraph(Graph &G);
bool    isEmptyGraph(Graph G);
Vertex* createVertex(string nim, string nama);
void    insertVertex(Graph &G, Vertex* V);
Vertex* searchVertex(Graph G, string nimCari);
Edge*   createEdge(string destNIM);
void    insertEdge(Graph &G, string nim1, string nim2);
void    deleteEdge(Graph &G, string nim1, string nim2);
void    deleteVertex(Graph &G, string nim);
void    viewGraph(Graph G);
void    viewNeighbors(Graph G, string nim);
int     degreeVertex(Graph G, string nim);
int     countVertex(Graph G);
int     countEdges(Graph G);
int     countNeighbors(Graph G, string nim);
void    viewIsolatedVertices(Graph G);

// =====================================================
//            FUNGSI PEMERIKSAAN
// =====================================================
bool hasLoop(Graph G);
bool hasMultipleEdges(Graph G);
bool isSimpleGraph(Graph G);

// =====================================================
//            TRAVERSAL GRAPH
// =====================================================
void DFS(Graph G, string startNIM);
void BFS(Graph G, string startNIM);
bool isConnected(Graph G);

#endif