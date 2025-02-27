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
    
    bool printStack();
    
};

class LIST_S {
public:
    LSNode* Lhead;


    bool is_empty();

    bool LsPRINT();

    void LsPUSH_end(string new_data);

    void LsPUSH_front(string new_data);

    void LsPOP_head();

    void LsPOP_end();

    void LsPOP_data(string kill_data);
    
    bool LsGET(string get_data);

};

class LIST_d{
public:
    LDNode* Lhead;
    LDNode* Ltail;

    bool is_empty();

    bool LdPRINT();

    void LdPUSH_end(string new_data);

    void LdPUSH_front(string new_data);

    void LdPOP_head();

    void LdPOP_end();

    void LdPOP_data(string kill_data);

    bool LdGET(string get_data);

};

class Queue{
public:
    QNode* Qhead;
    QNode* Qtail;

    bool is_empty();

    bool QPrint();
    
    void QPush(string new_data);

    void QPop();
};

class Massive{
public:
    int size = 10;
    int realsize = 0;
    string* elements = new string[size];

    Massive();

    string operator[] (int i);

    bool is_empty();

    bool MPrint();

    void MPushback(string element);

    void MPushind(int ind, string element);

    void MPopind(int ind);

    void MChange(int ind, string element);

    string MGet(int ind);

    int Size();


};

class Hash{
public:
    int size = 7;
    HNode** tabs = new HNode*[size];

    Hash ();
    bool is_empty();
    bool HPrint();

    int Htrans (string new_key);

    void HPush(string new_key_s, string new_data);

    string HGet(string key_s);

    void HPop(string key_s);

};

class Tree{
public:
    TNode* root;

    bool is_empty();

    void TPush(TNode* current, string new_data);

    bool TFind(TNode* current, string find_data);
    
    bool is_full(TNode* current);
    void print_Tree(TNode* root, int level);

};