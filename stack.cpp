#include "Header.h"

    Stk::Stk() : head(nullptr) {};

    bool Stk::is_empty(){
        return head == nullptr;
    }

    void Stk::SPUSH(string data){
    SNode* new_node = new SNode();
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    }

    void Stk::SPOP(){
        SNode* new_head = head;
        head = head->next;
        delete new_head;
    }
    
    void Stk::printStack() const {
        SNode* current = head;
        cout << "Stack output:" << endl;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }
    
    void Stk::SWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Stack is empty" << endl;
            in << read;
            in.close();
            return;
        }
        SNode* current = head;
        while (current->next != nullptr){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';' + '\n');
            ind_start += current->data.size() + 4;
            current = current->next;
        }
        read.insert(ind_start+1, '\"' + current->data + '\"');
        in << read;
        in.close();
        return;
    }

    void Stk::SRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        Stk flip;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            flip.SPUSH(datas);
            datas = "";
        }
        while(flip.head != nullptr){
            SPUSH(flip.head->data);
            flip.head = flip.head->next;
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }