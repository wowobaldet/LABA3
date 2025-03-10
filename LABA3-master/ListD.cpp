#include "Header.h"

bool LIST_d::is_empty(){
    return Lhead == nullptr;
}

bool LIST_d::LdPRINT(){
    LDNode* current = Lhead;
    if (is_empty()){
        cout << "List is empty!" << endl;
        return 0;
    }
    cout << "List output" << endl;
    while (current != nullptr) {
        cout << current->data << endl;
        current = current->next;
    }
    return 1;
}

void LIST_d::LdPUSH_end(string new_data){
    LDNode* new_node = new LDNode{new_data, nullptr, nullptr};
    if (is_empty()){
        Lhead = new_node;
        Ltail = new_node;
        return;
    }
    else {
        new_node->prev = Ltail;
        Ltail->next = new_node;
        Ltail = new_node;
    }
}

void LIST_d::LdPUSH_front(string new_data){
    LDNode* new_node = new LDNode{new_data, nullptr, nullptr};
    if (!is_empty()){
        new_node->next = Lhead;
        Lhead->prev = new_node;
        Lhead = new_node;
    }
    else{
        Lhead = new_node;
        Ltail = new_node;
    }
}

void LIST_d::LdPOP_head(){
    if (is_empty()){
        cout << "List is empty!" << endl;
        return;
    }
    if (Lhead == Ltail){
        Ltail = Ltail->next;
        Lhead = Ltail;
        return;
    }
    LDNode* kill_node = Lhead;
    Lhead->next->prev = nullptr;
    Lhead = Lhead->next;
    delete kill_node;
}

void LIST_d::LdPOP_end(){
    if (is_empty()){
        cout << "List is empty!" << endl;
        return;
    }
    LDNode* kill_node = Ltail;
    if (Ltail == Lhead){
        LdPOP_head();
        return;
    }
    Ltail = Ltail->prev;
    Ltail->next = nullptr;
    delete kill_node;
}

void LIST_d::LdPOP_data(string kill_data){
    bool is_having;
    LDNode* current = Lhead;
    LDNode* kill_node = new LDNode();
    if (is_empty()){
        cout << "LIST IS EMPTY!!!" << endl;
        return;
    }
    if (Lhead->data == kill_data){
        while (Lhead->data == kill_data){
            LdPOP_head();
            if(is_empty()){
                return;
            }
        }
        current = Lhead;
        is_having = 1;
    }
    while (current->next != nullptr) {             
        if (current->data == kill_data){
            kill_node = current;
            current->next->prev = current->prev;
            current->prev->next = current->next; 
            delete kill_node;
            is_having = 1;
        }
        current = current->next;            
    }
    if (Ltail->data == kill_data){
        LdPOP_end();
        is_having = 1;         
    }
    if (is_having == 0){
        cout << "List don't have that data" << endl;
        return;
    }            

}

bool LIST_d::LdGET(string get_data){
    LDNode* current = Lhead;
    bool is_having = 0;
    int ind = 0;
    if (is_empty()){
        cout << "List is empty!" << endl;
        return 0;
    }
    cout << "Elements with data " << get_data << ":" << endl;
    while (current->next != nullptr){
        if (current->data == get_data){
            cout << ind << endl;
            is_having = 1;
        }
        current = current->next;
        ind++;
    }
    if (Ltail->data == get_data){
        cout << ind << endl;
        is_having = 1;
    }
    if (is_having == 0){
        cout << "List don't have that" << endl;
        return 0;
    }
    return 1;
}
