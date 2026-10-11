// =====================================================
// File : expression.h
// =====================================================

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "stack.h"
#include "queue.h"
using namespace std;

// Struktur untuk menyimpan nilai variabel (huruf)
struct VarValue {
    char   name;
    double value;
};

// Node pohon ekspresi
struct ExpressionNode {
    string          token;
    ExpressionNode* left;
    ExpressionNode* right;
};

// ---------- UTIL ----------
bool isOperator(string token);
bool isOperand(string token);
bool isDigitToken(string token);
bool isValidToken(string token);
int  priority(string op);
void tokenize(string expr, string tokens[], int &n);
bool hitung(double a, double b, string op, double &hasil, string &error);

// ---------- INFIX -> POSTFIX ----------
void infixToPostfix(string infix, string postfix[], int &n);

// ---------- EVALUASI POSTFIX ----------
bool processPostfix(string tokens[], int n, double &hasil, string &pesanError);
bool processPostfixWithVars(string tokens[], int n,
                            VarValue vars[], int nVar,
                            double &hasil, string &pesanError);

// ---------- REKURSIF ----------
bool evaluatePostfixRecursive(string tokens[], int n, int idx,
                              Stack &S, double &hasil, string &err);
bool evaluatePostfixRecursiveWithVars(string tokens[], int n, int idx,
                                      Stack &S, VarValue vars[], int nVar,
                                      double &hasil, string &err);

// ---------- POHON EKSPRESI ----------
ExpressionNode* buildExpressionTree(string tokens[], int n, bool &sukses);
void inorder(ExpressionNode* root);
void preorder(ExpressionNode* root);
void postorder(ExpressionNode* root);
void deleteTree(ExpressionNode* root);

// ---------- POSTFIX -> INFIX ----------
bool postfixToInfix(string tokens[], int n, string &infix);

#endif