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

class SetNode{
public:
    string data;
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

    Massive() {
        for (int i = 0; i < size; i++){
            elements[i] = "";
        }
    }

    string operator[] (int i){
        return elements[i];
    }

    bool is_empty(){
        return realsize == 0;
    }

    void MPrint(){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        int i = 0;
        cout << "Massive output:" << endl;
        while (i < realsize){
            cout << elements[i] << endl;
            i++;
        }
    }

    void MPushback(string element){
        realsize++;
        if (realsize >= size) {
            string* new_elements = new string[size*2];
            for (int i = 0; elements[i] != ""; i++){
                new_elements[i] = elements[i];
            }
            delete[] elements;
            elements = new_elements;
        }
        elements[realsize-1] = element;
        return;   
    }

    void MPushind(int ind, string element){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind > realsize-1){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        realsize++;
        if (realsize >= size){
            string* new_elements = new string[size*2];
            for (int i = 0; i < ind; i++){
                new_elements[i] = elements[i];
            }
            new_elements[ind] = element;
            for (int i = ind; i < size-1; i++){
                new_elements[i+1] = elements[i];
            }
            delete[] elements;
            elements = new_elements;
            return;
        }

        for (int i = realsize-1; i  > ind; --i){
            elements[i] = elements[i-1];
            
        }
        elements[ind] = element;
        return;        
    }

    void MPopind(int ind){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind > realsize){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        realsize--;
        for (ind; ind < realsize; ind++){
            elements[ind] = elements[ind+1];
            cout << elements[ind] << endl;
        }
    }

    void MChange(int ind, string element){
        string* new_elements = new string[size];
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind >= realsize){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        elements[ind] = element;
    }

    void MGet(int ind){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind >= realsize){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        //negative
        cout << "Element with index " << ind << ":" << endl;
        cout << elements[ind] << endl;
    }

    int Size(){
        return size;
    }
    
    void MWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Massive is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < realsize - 1){
            read.insert(ind_start+1, '\"' + elements[i] + '\"' + ';');
            ind_start += elements[i].size() + 3;
            i++;
        }
        read.insert(ind_start+1, '\"' + elements[realsize - 1] + '\"');
        in << read;
        in.close();
        return;
    }

    void MRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            MPushback(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }

};

class Hash{
public:
    int size = 7;
    HNode** tabs = new HNode*[size];

    Hash () {
        for (int i = 0; i < size; i++){
            tabs[i] = nullptr;
        }
    }
    bool is_empty(){
        for (int i = 0; i < size; i++){
            if (tabs[i] != nullptr){
                return false;
            }
        }
        return true;
    }
    void HPrint(){
        int ind = 0;
        if (is_empty()){
            cout << "Empty" << endl;
            return;
        }
        cout << "Output: " << endl;
        while (ind < size){
            cout << "num " << ind << endl;
            if (tabs[ind] == nullptr) cout << "Empty" << endl;
            if (tabs[ind] != nullptr){
                HNode* current = tabs[ind];
                cout << "[ ";
                while (current != nullptr){
                    cout << "<" << current->key << ", " << current->data << "> ";
                    current = current->next;
                }
                cout << "]" << endl;
            }
            ind++;
        }
    }

    int Htrans (string new_key){
        int sum = 0;
        for (int i = 0; i < new_key.size(); i++){
            sum += new_key[i];
        }
        return sum % size;
    }

    void HPush(string new_key_s, string new_data){
        int new_key = Htrans(new_key_s);
        HNode* new_node = new HNode{new_key_s, new_data, nullptr};
        if (tabs[new_key] != nullptr){
            if (tabs[new_key]->key == new_key_s){
                new_node->next = tabs[new_key]->next;
                delete tabs[new_key];
                tabs[new_key] = new_node;
                return;
            }
            HNode* current = tabs[new_key];
            while (current->next != nullptr){
                if (current->next->key == new_key_s){
                    new_node->next = current->next->next;
                    delete current->next;
                    current->next = new_node;
                    return;
                }
                current = current->next;
            }
        }      
        new_node->next = tabs[new_key];
        tabs[new_key] = new_node;
    }

    string HGet(string key_s){
        if (is_empty()){
            cout << "Hash is Empty" << endl;
            return "";
        }
        int new_key = Htrans(key_s);
        if (tabs[new_key] == nullptr){
            cout << "Don't have data with this key" << endl;
            return "";
        }
        HNode* current = tabs[new_key];
        while (current != nullptr){
            if (current->key == key_s){
                return current->data;
            }
            current = current->next;
        }
        if (current == nullptr){
            cout << "Don't have data with this key" << endl;
            return "";
        }
        return "";
    }

    void HPop(string key_s){
        if (is_empty()){
            cout << "Hash is Empty" << endl;
            return;
        }
        int new_key = Htrans(key_s);
        if (tabs[new_key] == nullptr){
            cout << "Don't have data with this key" << endl;
            return;
        }
        HNode* current = tabs[new_key];
        if (tabs[new_key]->key == key_s){
            current = tabs[new_key];
            delete current;
            tabs[new_key] = tabs[new_key]->next;
            return;
        }
        while (current->next != nullptr){
            if (current->next->key == key_s){
                HNode* kill_node = current->next;
                delete kill_node;
                current->next = current->next->next;
                return;
            }
            current = current->next;
        }
        if (current->next == nullptr){
            cout << "Don't have data with this key" << endl;
            return;
        }
    }

    void HWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Hash is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size){
            if (tabs[i] != nullptr){
                HNode* current = tabs[i];
                while(current != nullptr){
                    read.insert(ind_start+1, '(' + current->key + ',' + current->data + ')');
                    ind_start += current->key.size() + current->data.size() + 3;
                    current = current->next;
                }
            }
            i++;
        }
        in << read;
        in.close();
        return;
    }

    void HRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        string key = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '(' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != ',' && read[ind] != ')' && ind < read.size(); ind++){
                key += read[ind];
            }
            ind++;
            for (ind; read[ind] != ')' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            HPush(key, datas);
            datas = "";
            key = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
};

class Tree{
public:
    TNode* root;

    bool is_empty(){
        return root == nullptr;
    }

    void TPush(TNode* current, string new_data){
        if (is_empty()){
            root = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->left == nullptr){
            current->left = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->right == nullptr){
            current->right = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (new_data >= current->data){
            TPush(current->right, new_data);
            return;
        } else {
            TPush(current->left, new_data);
            return;
        }
    }

    bool TFind(TNode* current, string find_data){
        if (is_empty()){
            cout << "Tree is empty" << endl;
            return false;
        }
        if (current->data == find_data){
            return true;
        }
        bool is_here = false;
        while ((current != nullptr) && (current->right != nullptr && current->left != nullptr)){
            if (current->left->data == find_data || current->right->data == find_data){
                is_here = true;
                break;
            }
            if (find_data > current->data){
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return is_here;
    }
    
    bool is_full(TNode* current){
        if (is_empty()){
            cout << "List is empty" << endl;
            return false;
        }
        if (current == nullptr){
            return true;
        }
        if (current->left == nullptr && current->right == nullptr){
            return true;
        }

        if (current->right != nullptr && current->left != nullptr){
            return is_full(current->left) && is_full(current->right);
        }

        return false;

    }
    void print_Tree(TNode* root, int level)
    {
        if (root != NULL)
        {
            print_Tree(root->right, level + 1);
            for (int i = 0; i < level * 4; i++) cout << "   ";
            cout << root->data << endl;
            print_Tree(root->left, level + 1);
        }
    }

    void TWrite(string& read, string filename, int ind_start, int ind, string data){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        if (read[ind_start+1] == '}') read.insert(ind_start + 1, '\"' + data + '\"');
        else {
            read.insert(ind, '\"' + data + '\"');
        }
        in << read;
        in.close();
        return;
    }   

    int TRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return 0;
        }
        int count = 1;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            count++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++) count++;
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++){
                datas += read[ind];
                count++;
            }
            TPush(root, datas);
            datas = "";
        }
        return count;
    }
};

class Set{
public:
    int size;
    SetNode** setik;

    Set(int num) : size(num){
        setik = new SetNode*[size];
        for (int i = 0; i < size; i++){
            setik[i] = nullptr;
        }
    }

    bool is_empty(){
        for (int i = 0; i < size; i++){
            if (setik[i] != nullptr){
                return 0;
            }
        }
        return 1;
    }

    bool is_full(){
        int count = 0;
        for (int i = 0; i < size; i++){
            if (setik[i] != nullptr) count++;
        }
        if (count == size) return 1;
        return 0;
    }

    int HSet (string data){
        int sum = 0;
        for (int i = 0; i < data.size(); i++){
            sum += data[i];
        }
        return sum % size;
    }

    bool FindInd(string value, int& ind){
        if (is_empty()){
            return 0;
        }
        for (ind = 0; ind < size; ind++){
            if (setik[ind] == nullptr) continue;
            if (setik[ind]->data == value) return 1;
        }
        return 0;
    }

    bool Set_At(string data){
        int key = HSet(data);
        if (setik[key] != nullptr && setik[key]->data == data){
            return 1;
        }
        bool is_here = FindInd(data, key);
        if (is_here){
            return 1;
        }
        return 0;
    }

    void SetPush(string new_data){
        if(is_full()) return;
        if (Set_At(new_data)) return;       
        int new_key = HSet(new_data);
        SetNode* new_node = new SetNode{new_data};
        if (setik[new_key] != nullptr){
            for (int i = 0; i < size; i++){
                if (setik[i] == nullptr){
                    setik[i] = new_node;
                    return;
                }
            }
        }
        else {
            setik[new_key] = new_node;
            return;
        }   
    }

    void SetPop(string data){
        if(is_empty()) return;
        int key = HSet(data);
        if (setik[key] != nullptr && setik[key]->data == data){
            delete setik[key];
            setik[key] = nullptr;
            return;
        }
        if (FindInd(data, key)){
            delete setik[key];
            setik[key] = nullptr;
            return;
        }
        cout << "Don't have" << endl;
        return;
    }

    void SPrint(){
        if (is_empty()) return;
        for (int i = 0; i < size; i++){
            if (setik[i] == nullptr) continue;
            cout << setik[i]->data << endl;
        }
    }

    void SetWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Set is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size){
            if (setik[i] != nullptr){
                read.insert(ind_start+1, '\"' + setik[i]->data + '\"' + ';');
                ind_start += setik[i]->data.size() + 3;
            }
            i++;
        }
        end = ind_start + 1;
        read.erase(ind_start, end - ind_start);
        in << read;
        in.close();
        return;
    }

    void SetRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            SetPush(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }

    

};
