// =====================================================
// File : expression.cpp
// =====================================================

#include <iostream>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "expression.h"
using namespace std;

// =====================================================
// UTIL
// =====================================================
bool isOperator(string t) {
    return (t == "+" || t == "-" || t == "*" || t == "/" || t == "^");
}

bool isOperand(string t) {
    if (t.length() != 1) return false;
    return (isalpha(t[0]) || isdigit(t[0]));
}

bool isDigitToken(string t) {
    return (t.length() == 1 && isdigit(t[0]));
}

bool isValidToken(string t) {
    if (t.length() != 1) return false;
    char c = t[0];
    return (isalpha(c) || isdigit(c) || c == '+' || c == '-' ||
            c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
}

int priority(string op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// Tokenizer: setiap karakter non-spasi jadi 1 token
void tokenize(string expr, string tokens[], int &n) {
    n = 0;
    for (int i = 0; i < (int)expr.length(); i++) {
        char c = expr[i];
        if (c == ' ' || c == '\t') continue;
        tokens[n++] = string(1, c);
    }
}

// Operasi hitung dasar
bool hitung(double a, double b, string op, double &hasil, string &error) {
    if (op == "+") hasil = a + b;
    else if (op == "-") hasil = a - b;
    else if (op == "*") hasil = a * b;
    else if (op == "/") {
        if (b == 0) {
            error = "Pembagian dengan nol!";
            return false;
        }
        hasil = a / b;
    }
    else if (op == "^") hasil = pow(a, b);
    else {
        error = "Operator tidak dikenal: " + op;
        return false;
    }
    return true;
}

// Bantu: cek apakah stack berisi hasil operasi (angka hasil hitung)
// kita simpan hasil sebagai string desimal
static string doubleToString(double v) {
    char buf[64];
    sprintf(buf, "%.6f", v);
    return string(buf);
}

// =====================================================
// INFIX -> POSTFIX
// =====================================================
void infixToPostfix(string infix, string postfix[], int &n) {
    Stack S;
    createStack(S);
    Queue Q;
    createQueue(Q);

    for (int i = 0; i < (int)infix.length(); i++) {
        char c = infix[i];
        if (c == ' ' || c == '\t') continue;

        string token(1, c);

        if (isOperand(token)) {
            enqueue(Q, token);
        } else if (token == "(") {
            push(S, token);
        } else if (token == ")") {
            while (!isEmptyStack(S) && peek(S) != "(")
                enqueue(Q, pop(S));
            if (!isEmptyStack(S)) pop(S); // buang "("
        } else if (isOperator(token)) {
            // ^ bersifat right-associative, lainnya left-associative
            while (!isEmptyStack(S) && peek(S) != "(" &&
                   (priority(peek(S)) > priority(token) ||
                   (priority(peek(S)) == priority(token) && token != "^"))) {
                enqueue(Q, pop(S));
            }
            push(S, token);
        }
    }
    while (!isEmptyStack(S))
        enqueue(Q, pop(S));

    n = 0;
    while (!isEmptyQueue(Q))
        postfix[n++] = dequeue(Q);
}

// =====================================================
// EVALUASI POSTFIX (ITERATIF)
// =====================================================
bool processPostfix(string tokens[], int n, double &hasil, string &pesanError) {
    Stack S;
    createStack(S);

    for (int i = 0; i < n; i++) {
        string token = tokens[i];

        if (!isValidToken(token)) {
            pesanError = "Token tidak valid: " + token;
            return false;
        }

        if (isOperand(token)) {
            if (!isDigitToken(token)) {
                pesanError = "Operand huruf butuh nilai variabel.";
                return false;
            }
            push(S, token);
        } else if (isOperator(token)) {
            if (S.top < 1) {
                pesanError = "Operand tidak mencukupi untuk operator " + token;
                return false;
            }
            double b = atof(pop(S).c_str());
            double a = atof(pop(S).c_str());
            double r;
            if (!hitung(a, b, token, r, pesanError)) return false;
            push(S, doubleToString(r));
        }
    }

    if (S.top != 0) {
        pesanError = "Ekspresi tidak menghasilkan satu nilai akhir.";
        return false;
    }

    hasil = atof(pop(S).c_str());
    return true;
}

// =====================================================
// EVALUASI POSTFIX DENGAN VARIABEL (ITERATIF)
// =====================================================
bool processPostfixWithVars(string tokens[], int n,
                            VarValue vars[], int nVar,
                            double &hasil, string &pesanError) {
    Stack S;
    createStack(S);

    for (int i = 0; i < n; i++) {
        string token = tokens[i];

        if (isOperand(token)) {
            if (isDigitToken(token)) {
                push(S, token);
            } else {
                // cari nilai variabel
                bool found = false;
                for (int j = 0; j < nVar; j++) {
                    if (vars[j].name == token[0]) {
                        push(S, doubleToString(vars[j].value));
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    pesanError = "Nilai variabel " + token + " belum tersedia.";
                    return false;
                }
            }
        } else if (isOperator(token)) {
            if (S.top < 1) {
                pesanError = "Operand tidak mencukupi.";
                return false;
            }
            double b = atof(pop(S).c_str());
            double a = atof(pop(S).c_str());
            double r;
            if (!hitung(a, b, token, r, pesanError)) return false;
            push(S, doubleToString(r));
        } else {
            pesanError = "Token tidak valid: " + token;
            return false;
        }
    }

    if (S.top != 0) {
        pesanError = "Ekspresi tidak menghasilkan satu nilai akhir.";
        return false;
    }
    hasil = atof(pop(S).c_str());
    return true;
}

// =====================================================
// EVALUASI POSTFIX (REKURSIF)
// =====================================================
bool evaluatePostfixRecursive(string tokens[], int n, int idx,
                              Stack &S, double &hasil, string &err) {
    if (idx == n) {
        if (S.top != 0) {
            err = "Ekspresi tidak menghasilkan satu nilai akhir.";
            return false;
        }
        hasil = atof(pop(S).c_str());
        return true;
    }

    string token = tokens[idx];

    if (isOperand(token)) {
        if (!isDigitToken(token)) {
            err = "Operand huruf butuh nilai variabel.";
            return false;
        }
        push(S, token);
        return evaluatePostfixRecursive(tokens, n, idx + 1, S, hasil, err);
    } else if (isOperator(token)) {
        if (S.top < 1) {
            err = "Operand tidak mencukupi untuk operator " + token;
            return false;
        }
        double b = atof(pop(S).c_str());
        double a = atof(pop(S).c_str());
        double r;
        if (!hitung(a, b, token, r, err)) return false;
        push(S, doubleToString(r));
        return evaluatePostfixRecursive(tokens, n, idx + 1, S, hasil, err);
    }

    err = "Token tidak valid: " + token;
    return false;
}

// =====================================================
// EVALUASI POSTFIX REKURSIF DENGAN VARIABEL
// =====================================================
bool evaluatePostfixRecursiveWithVars(string tokens[], int n, int idx,
                                      Stack &S, VarValue vars[], int nVar,
                                      double &hasil, string &err) {
    if (idx == n) {
        if (S.top != 0) {
            err = "Ekspresi tidak menghasilkan satu nilai akhir.";
            return false;
        }
        hasil = atof(pop(S).c_str());
        return true;
    }

    string token = tokens[idx];

    if (isOperand(token)) {
        if (isDigitToken(token)) {
            push(S, token);
        } else {
            bool found = false;
            for (int j = 0; j < nVar; j++) {
                if (vars[j].name == token[0]) {
                    push(S, doubleToString(vars[j].value));
                    found = true;
                    break;
                }
            }
            if (!found) {
                err = "Nilai variabel " + token + " belum tersedia.";
                return false;
            }
        }
        return evaluatePostfixRecursiveWithVars(tokens, n, idx + 1,
                                                S, vars, nVar, hasil, err);
    } else if (isOperator(token)) {
        if (S.top < 1) {
            err = "Operand tidak mencukupi untuk operator " + token;
            return false;
        }
        double b = atof(pop(S).c_str());
        double a = atof(pop(S).c_str());
        double r;
        if (!hitung(a, b, token, r, err)) return false;
        push(S, doubleToString(r));
        return evaluatePostfixRecursiveWithVars(tokens, n, idx + 1,
                                                S, vars, nVar, hasil, err);
    }

    err = "Token tidak valid: " + token;
    return false;
}

// =====================================================
// POHON EKSPRESI
// =====================================================
ExpressionNode* buildExpressionTree(string tokens[], int n, bool &sukses) {
    ExpressionNode* stack[MAX_STACK];
    int top = -1;
    sukses = true;

    for (int i = 0; i < n; i++) {
        string token = tokens[i];

        if (isOperand(token)) {
            ExpressionNode* node = new ExpressionNode;
            node->token = token;
            node->left  = NULL;
            node->right = NULL;
            stack[++top] = node;
        } else if (isOperator(token)) {
            if (top < 1) {
                sukses = false;
                for (int j = 0; j <= top; j++) delete stack[j];
                return NULL;
            }
            ExpressionNode* right = stack[top--];
            ExpressionNode* left  = stack[top--];
            ExpressionNode* node  = new ExpressionNode;
            node->token = token;
            node->left  = left;
            node->right = right;
            stack[++top] = node;
        } else {
            sukses = false;
            for (int j = 0; j <= top; j++) delete stack[j];
            return NULL;
        }
    }

    if (top != 0) {
        sukses = false;
        for (int j = 0; j <= top; j++) delete stack[j];
        return NULL;
    }
    return stack[0];
}

// Traversal inorder: infix dengan tanda kurung
void inorder(ExpressionNode* root) {
    if (root == NULL) return;
    if (isOperator(root->token)) {
        cout << "(";
        inorder(root->left);
        cout << " " << root->token << " ";
        inorder(root->right);
        cout << ")";
    } else {
        cout << root->token;
    }
}

void preorder(ExpressionNode* root) {
    if (root == NULL) return;
    cout << root->token;
    if (root->left != NULL) { cout << " "; preorder(root->left); }
    if (root->right != NULL) { cout << " "; preorder(root->right); }
}

void postorder(ExpressionNode* root) {
    if (root == NULL) return;
    if (root->left != NULL) { postorder(root->left); cout << " "; }
    if (root->right != NULL) { postorder(root->right); cout << " "; }
    cout << root->token;
}

void deleteTree(ExpressionNode* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// =====================================================
// POSTFIX -> INFIX (tanpa tree, alternatif)
// =====================================================
bool postfixToInfix(string tokens[], int n, string &infix) {
    string stack[MAX_STACK];
    int top = -1;

    for (int i = 0; i < n; i++) {
        string token = tokens[i];
        if (isOperand(token)) {
            stack[++top] = token;
        } else if (isOperator(token)) {
            if (top < 1) return false;
            string right = stack[top--];
            string left  = stack[top--];
            stack[++top] = "(" + left + " " + token + " " + right + ")";
        } else {
            return false;
        }
    }
    if (top != 0) return false;
    infix = stack[0];
    return true;
}