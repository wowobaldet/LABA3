#include "Header.h"

bool LIST_S::is_empty(){
    return Lhead == nullptr;
}

bool LIST_S::LsPRINT(){
    LSNode* current = Lhead;
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

void LIST_S::LsPUSH_end(string new_data){
    LSNode* new_node = new LSNode{new_data, nullptr};
    LSNode* current = Lhead;
    if (is_empty()){
        Lhead = new_node;
        return;
    }
    else {
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = new_node;
    }
}

void LIST_S::LsPUSH_front(string new_data){
    LSNode* new_node = new LSNode{new_data, nullptr};
    if (!is_empty()){
        new_node->next = Lhead;
        Lhead = new_node;
    }
    else{
        Lhead = new_node;
    }
}

void LIST_S::LsPOP_head(){
    if (is_empty()){
        cout << "List is empty!";
        return;
    }
    LSNode* kill_node = Lhead;
    Lhead = Lhead->next;
    delete kill_node;
}

void LIST_S::LsPOP_end(){
    LSNode* kill_node;
    LSNode* current = Lhead;
    if (is_empty()){
        cout << "List is empty!";
        return;
    }
    if (current->next == nullptr){
        LsPOP_head();
        return;
    }
    while (current->next->next != nullptr){
        current = current->next;
    }
    kill_node = current->next->next;
    delete current->next;
    current->next = kill_node;
}

void LIST_S::LsPOP_data(string kill_data){
    LSNode* current = Lhead;
    bool is_having = 0;
    if (is_empty()){
        cout << "LIST IS EMPTY!!!" << endl;
        return;
    }
    if (current->data == kill_data){
        while(current->data == kill_data){
            LsPOP_head();
            if (is_empty()){
                return;
            }
            current = current->next;
        }
    }
    if (is_empty() || current->next == nullptr){
        return;
    }
    while (current->next->next != nullptr){
        if (current->next->data == kill_data){
            LSNode* kill_node = current->next;
            current->next = current->next->next;
            delete kill_node;
            is_having = 1;
        }
        current = current->next; 
        if (current->next == nullptr){
            break;
        }             
    }
    if (is_empty()){
        return;
    }
    if (current->next == nullptr){
        if (current->data == kill_data){
            LsPOP_end();
            is_having = 1;
        }
    }
    else if (current->next->data == kill_data){
        LsPOP_end();
        is_having = 1;
    }            
    if (is_having == 0){
        cout << "List don't have that position" << endl;
        return;
    }
}


bool LIST_S::LsGET(string get_data){
    LSNode* current = Lhead;
    int ind = 0;
    bool is_having = 0;
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
    if (current->data == get_data){
        cout << ind << endl;
        is_having = 1;
    }
    if (is_having == 0){
        cout << "List don't has them" << endl;
        return 0;
    }
    return 1;
}

