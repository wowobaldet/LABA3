#include "Header.h"

bool LIST_S::is_empty(){
    return Lhead == nullptr;
}

void LIST_S::LsPRINT(){
    LSNode* current = Lhead;
    if (is_empty()){
        cout << "List is empty!" << endl;
        return;
    }
    cout << "List output" << endl;
    while (current != nullptr) {
        cout << current->data << endl;
        current = current->next;
    }

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
    if (is_empty()){
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


void LIST_S::LsGET(string get_data){
    LSNode* current = Lhead;
    int ind = 0;
    bool is_having = 0;
    if (is_empty()){
        cout << "List is empty!" << endl;
        return;
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
    }
}

void LIST_S::LsWrite(string& read, string filename, int ind_start, int end){
    ofstream in;
    in.open(filename);
    if (is_empty()){
        cout << "List is empty" << endl;
        in << read;
        in.close();
        return;
    }
    LSNode* current = Lhead;
    while (current->next != nullptr){
        read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
        ind_start += current->data.size() + 3;
        current = current->next;
    }
    read.insert(ind_start+1, '\"' + current->data + '\"');
    in << read;
    in.close();
    return;
}

void LIST_S::LsRead(string& read, int& ind_start, int& ind){
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
        LsPUSH_end(datas);
        datas = "";
    }
    read.erase(ind_start + 1, ind - ind_start - 1);
    return;
}