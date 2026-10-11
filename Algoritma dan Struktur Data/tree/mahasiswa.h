// =====================================================
// TUGAS 7      : Sistem Data Mahasiswa
//                (Linked List + Binary Search Tree)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : mahasiswa.h
// =====================================================

#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
using namespace std;

// =====================================================
//            ADT DATA MAHASISWA
// =====================================================
struct Mahasiswa {
    string nim;
    string nama;
    string programStudi;
    double ipk;
};

// =====================================================
//            ADT LINKED LIST
// =====================================================
struct NodeLL {
    Mahasiswa info;
    NodeLL*   next;
};

struct ListLL {
    NodeLL* First;
};

// ---------- PROSEDUR LINKED LIST ----------
void createList(ListLL &L);
void insertFirst(ListLL &L, NodeLL* P);
void insertLast(ListLL &L, NodeLL* P);
void insertAfter(ListLL &L, string nimAcuan, NodeLL* P);
void updateMahasiswa(ListLL &L, string nim, string namaBaru,
                     string prodiBaru, double ipkBaru);
void deleteMahasiswa(ListLL &L, string nim);
void viewAll(ListLL L);
void sortByNIM(ListLL L);
void deleteAllList(ListLL &L);

// ---------- FUNGSI LINKED LIST ----------
bool     isNull(ListLL L);
bool     isNIMExist(ListLL L, string nim);
NodeLL*  createData(string nim, string nama, string prodi, double ipk);
NodeLL*  searchNIM(ListLL L, string nimCari);
int      countNode(ListLL L);
double   averageIPK(ListLL L);

// =====================================================
//            ADT BINARY SEARCH TREE
// =====================================================
struct NodeTree {
    Mahasiswa info;
    NodeTree* left;
    NodeTree* right;
};

struct BST {
    NodeTree* root;
};

// ---------- PROSEDUR BST ----------
void createBST(BST &T);
void inOrder(NodeTree* root);
void preOrder(NodeTree* root);
void postOrder(NodeTree* root);
void deleteAllBST(NodeTree* &root);

// ---------- FUNGSI BST ----------
bool       isEmptyBST(BST T);
NodeTree*  createNodeBST(string nim, string nama, string prodi, double ipk);
NodeTree*  insertBST(NodeTree* root, NodeTree* P);
NodeTree*  searchBST(NodeTree* root, string nimCari);
NodeTree*  findMin(NodeTree* root);
NodeTree*  findMax(NodeTree* root);
NodeTree*  deleteBST(NodeTree* root, string nim);
int        countNodeBST(NodeTree* root);
int        countLeaf(NodeTree* root);
int        countInternal(NodeTree* root);
int        heightBST(NodeTree* root);
double     totalIPK(NodeTree* root);
double     averageIPK_BST(BST T);

#endif