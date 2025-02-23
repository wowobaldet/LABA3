#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class SNode{
public:
    string data;
    SNode* next;
};

class LSNode{
public:
    string data;
    LSNode* next;
};

class LDNode{
public:
    string data;
    LDNode* next;
    LDNode* prev;
};

class QNode{
public:
    string data;
    QNode* next;
    QNode* prev;
};

class HNode{
public:
    string key;
    string data;
    HNode* next;
};

class TNode{
public:
    string data;
    TNode* left;
    TNode* right;
};


class Stk{
public:
    SNode* head;

    Stk() : head(nullptr) {}

    bool is_empty();

    void SPUSH(string data);

    void SPOP();
    
    void printStack();
    
    void SWrite(string& read, string filename, int ind_start, int end);

    void SRead(string& read, int& ind_start, int& ind);
};

class LIST_S {
public:
    LSNode* Lhead;


    bool is_empty();

    void LsPRINT();

    void LsPUSH_end(string new_data);

    void LsPUSH_front(string new_data);

    void LsPOP_head();

    void LsPOP_end();

    void LsPOP_data(string kill_data);
    
    void LsGET(string get_data);

    void LsWrite(string& read, string filename, int ind_start, int end);

    void LsRead(string& read, int& ind_start, int& ind);
};

class LIST_d{
public:
    LDNode* Lhead;
    LDNode* Ltail;

    bool is_empty();

    void LdPRINT();

    void LdPUSH_end(string new_data);

    void LdPUSH_front(string new_data);

    void LdPOP_head();

    void LdPOP_end();

    void LdPOP_data(string kill_data);

    void LdGET(string get_data);

    void LdWrite(string& read, string filename, int ind_start, int end);

    void LdRead(string& read, int& ind_start, int& ind);

};

class Queue{
public:
    QNode* Qhead;
    QNode* Qtail;

    bool is_empty();

    void QPrint();
    
    void QPush(string new_data);

    void QPop();

    void QWrite(string& read, string filename, int ind_start, int end);

    void QRead(string& read, int& ind_start, int& ind);
};

class Massive{
public:
    int size = 10;
    int realsize = 0;
    string* elements = new string[size];

    Massive();

    string operator[] (int i);

    bool is_empty();

    void MPrint();

    void MPushback(string element);

    void MPushind(int ind, string element);

    void MPopind(int ind);

    void MChange(int ind, string element);

    void MGet(int ind);

    int Size();
    
    void MWrite(string& read, string filename, int ind_start, int end);

    void MRead(string& read, int& ind_start, int& ind);

};

class Hash{
public:
    int size = 7;
    HNode** tabs = new HNode*[size];

    Hash ();
    bool is_empty();
    void HPrint();

    int Htrans (string new_key);

    void HPush(string new_key_s, string new_data);

    string HGet(string key_s);

    void HPop(string key_s);

    void HWrite(string& read, string filename, int ind_start, int end);

    void HRead(string& read, int& ind_start, int& ind);
};

class Tree{
public:
    TNode* root;

    bool is_empty();

    void TPush(TNode* current, string new_data);

    bool TFind(TNode* current, string find_data);
    
    bool is_full(TNode* current);
    void print_Tree(TNode* root, int level);

    void TWrite(string& read, string filename, int ind_start, int ind, string data);   

    int TRead(string& read, int& ind_start, int& ind);
};