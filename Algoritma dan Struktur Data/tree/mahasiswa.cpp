// =====================================================
// File : mahasiswa.cpp
// Berisi implementasi ADT Linked List dan BST
// =====================================================

#include <iostream>
#include <iomanip>
#include "mahasiswa.h"
using namespace std;

// =====================================================
//              IMPLEMENTASI LINKED LIST
// =====================================================
void createList(ListLL &L) {
    L.First = NULL;
}

bool isNull(ListLL L) {
    return (L.First == NULL);
}

NodeLL* createData(string nim, string nama, string prodi, double ipk) {
    NodeLL* P = new NodeLL;
    P->info.nim          = nim;
    P->info.nama         = nama;
    P->info.programStudi = prodi;
    P->info.ipk          = ipk;
    P->next              = NULL;
    return P;
}

NodeLL* searchNIM(ListLL L, string nimCari) {
    NodeLL* p = L.First;
    while (p != NULL) {
        if (p->info.nim == nimCari) return p;
        p = p->next;
    }
    return NULL;
}

bool isNIMExist(ListLL L, string nim) {
    return (searchNIM(L, nim) != NULL);
}

void insertFirst(ListLL &L, NodeLL* P) {
    if (isNIMExist(L, P->info.nim)) {
        cout << "NIM " << P->info.nim << " sudah terdaftar!\n";
        delete P;
        return;
    }
    P->next = L.First;
    L.First = P;
}

void insertLast(ListLL &L, NodeLL* P) {
    if (isNIMExist(L, P->info.nim)) {
        cout << "NIM " << P->info.nim << " sudah terdaftar!\n";
        delete P;
        return;
    }
    if (L.First == NULL) {
        L.First = P;
    } else {
        NodeLL* p = L.First;
        while (p->next != NULL) p = p->next;
        p->next = P;
    }
}

void insertAfter(ListLL &L, string nimAcuan, NodeLL* P) {
    if (isNIMExist(L, P->info.nim)) {
        cout << "NIM " << P->info.nim << " sudah terdaftar!\n";
        delete P;
        return;
    }
    NodeLL* acuan = searchNIM(L, nimAcuan);
    if (acuan == NULL) {
        cout << "NIM acuan " << nimAcuan << " tidak ditemukan!\n";
        delete P;
        return;
    }
    P->next     = acuan->next;
    acuan->next = P;
}

void updateMahasiswa(ListLL &L, string nim, string namaBaru,
                     string prodiBaru, double ipkBaru) {
    NodeLL* p = searchNIM(L, nim);
    if (p == NULL) {
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }
    p->info.nama         = namaBaru;
    p->info.programStudi = prodiBaru;
    p->info.ipk          = ipkBaru;
}

void deleteMahasiswa(ListLL &L, string nim) {
    if (isNull(L)) {
        cout << "List kosong.\n";
        return;
    }
    NodeLL* p    = L.First;
    NodeLL* prev = NULL;

    while (p != NULL && p->info.nim != nim) {
        prev = p;
        p    = p->next;
    }
    if (p == NULL) {
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }
    if (prev == NULL) L.First = p->next;
    else              prev->next = p->next;
    delete p;
}

void viewAll(ListLL L) {
    if (isNull(L)) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }
    cout << "=====================================================================\n";
    cout << left << setw(12) << "NIM"
         << setw(15) << "Nama"
         << setw(20) << "Program Studi"
         << setw(8)  << "IPK" << endl;
    cout << "=====================================================================\n";

    NodeLL* p = L.First;
    while (p != NULL) {
        cout << left << setw(12) << p->info.nim
             << setw(15) << p->info.nama
             << setw(20) << p->info.programStudi
             << fixed << setprecision(2) << setw(8) << p->info.ipk << endl;
        p = p->next;
    }
    cout << "=====================================================================\n";
}

void sortByNIM(ListLL L) {
    if (isNull(L)) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }
    int n = countNode(L);
    NodeLL** arr = new NodeLL*[n];

    NodeLL* p = L.First;
    int i = 0;
    while (p != NULL) {
        arr[i++] = p;
        p = p->next;
    }
    for (int a = 0; a < n - 1; a++)
        for (int b = 0; b < n - 1 - a; b++)
            if (arr[b]->info.nim > arr[b+1]->info.nim) {
                NodeLL* temp = arr[b];
                arr[b]       = arr[b+1];
                arr[b+1]     = temp;
            }

    cout << "Data diurutkan berdasarkan NIM (menaik):\n";
    for (int j = 0; j < n; j++)
        cout << left << setw(12) << arr[j]->info.nim
             << setw(15) << arr[j]->info.nama
             << setw(20) << arr[j]->info.programStudi
             << fixed << setprecision(2) << setw(8) << arr[j]->info.ipk << endl;
    delete[] arr;
}

int countNode(ListLL L) {
    int c = 0;
    NodeLL* p = L.First;
    while (p != NULL) { c++; p = p->next; }
    return c;
}

double averageIPK(ListLL L) {
    if (isNull(L)) return 0;
    double total = 0;
    NodeLL* p = L.First;
    while (p != NULL) {
        total += p->info.ipk;
        p = p->next;
    }
    return total / countNode(L);
}

void deleteAllList(ListLL &L) {
    NodeLL* p = L.First;
    while (p != NULL) {
        NodeLL* temp = p;
        p = p->next;
        delete temp;
    }
    L.First = NULL;
}

// =====================================================
//              IMPLEMENTASI BST
// =====================================================
void createBST(BST &T) {
    T.root = NULL;
}

bool isEmptyBST(BST T) {
    return (T.root == NULL);
}

NodeTree* createNodeBST(string nim, string nama, string prodi, double ipk) {
    NodeTree* P = new NodeTree;
    P->info.nim          = nim;
    P->info.nama         = nama;
    P->info.programStudi = prodi;
    P->info.ipk          = ipk;
    P->left              = NULL;
    P->right             = NULL;
    return P;
}

NodeTree* insertBST(NodeTree* root, NodeTree* P) {
    if (root == NULL) return P;
    if (P->info.nim < root->info.nim)
        root->left  = insertBST(root->left, P);
    else if (P->info.nim > root->info.nim)
        root->right = insertBST(root->right, P);
    else {
        cout << "NIM " << P->info.nim << " sudah ada di BST!\n";
        delete P;
    }
    return root;
}

NodeTree* searchBST(NodeTree* root, string nimCari) {
    if (root == NULL) return NULL;
    if (root->info.nim == nimCari) return root;
    if (nimCari < root->info.nim) return searchBST(root->left, nimCari);
    return searchBST(root->right, nimCari);
}

void inOrder(NodeTree* root) {
    if (root == NULL) return;
    inOrder(root->left);
    cout << left << setw(12) << root->info.nim
         << setw(15) << root->info.nama
         << setw(20) << root->info.programStudi
         << fixed << setprecision(2) << setw(8) << root->info.ipk << endl;
    inOrder(root->right);
}

void preOrder(NodeTree* root) {
    if (root == NULL) return;
    cout << left << setw(12) << root->info.nim
         << setw(15) << root->info.nama
         << setw(20) << root->info.programStudi
         << fixed << setprecision(2) << setw(8) << root->info.ipk << endl;
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(NodeTree* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << left << setw(12) << root->info.nim
         << setw(15) << root->info.nama
         << setw(20) << root->info.programStudi
         << fixed << setprecision(2) << setw(8) << root->info.ipk << endl;
}

NodeTree* findMin(NodeTree* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

NodeTree* findMax(NodeTree* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) root = root->right;
    return root;
}

NodeTree* deleteBST(NodeTree* root, string nim) {
    if (root == NULL) return NULL;
    if (nim < root->info.nim)
        root->left  = deleteBST(root->left, nim);
    else if (nim > root->info.nim)
        root->right = deleteBST(root->right, nim);
    else {
        if (root->left == NULL) {
            NodeTree* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            NodeTree* temp = root->left;
            delete root;
            return temp;
        }
        NodeTree* succ = findMin(root->right);
        root->info     = succ->info;
        root->right    = deleteBST(root->right, succ->info.nim);
    }
    return root;
}

int countNodeBST(NodeTree* root) {
    if (root == NULL) return 0;
    return 1 + countNodeBST(root->left) + countNodeBST(root->right);
}

int countLeaf(NodeTree* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int countInternal(NodeTree* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 0;
    return 1 + countInternal(root->left) + countInternal(root->right);
}

int heightBST(NodeTree* root) {
    if (root == NULL) return -1;
    int lh = heightBST(root->left);
    int rh = heightBST(root->right);
    return 1 + (lh > rh ? lh : rh);
}

double totalIPK(NodeTree* root) {
    if (root == NULL) return 0;
    return root->info.ipk + totalIPK(root->left) + totalIPK(root->right);
}

double averageIPK_BST(BST T) {
    int n = countNodeBST(T.root);
    if (n == 0) return 0;
    return totalIPK(T.root) / n;
}

void deleteAllBST(NodeTree* &root) {
    if (root == NULL) return;
    deleteAllBST(root->left);
    deleteAllBST(root->right);
    delete root;
    root = NULL;
}