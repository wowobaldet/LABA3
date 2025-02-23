#include "Header.h"

bool Queue::is_empty(){
    return Qhead == nullptr;
}

void Queue::QPrint(){
    if (is_empty()){
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue output:" << endl;
    QNode* current = Qhead;

    while (current != nullptr){
        cout << current->data << endl;
        current = current->next;
    }
}
void Queue::QPush(string new_data){
    QNode* new_node = new QNode{new_data, nullptr, nullptr};
    if (is_empty()){
        Qhead = new_node;
        Qtail = new_node;
    } else {
        new_node->prev = Qtail;
        Qtail->next = new_node;
        Qtail->prev = nullptr;
        Qtail = new_node;
    }
}

void Queue::QPop(){
    if (is_empty()){
        cout << "Queue is empty" << endl;
        return;
    }
    QNode* kill_node = Qhead;
    Qhead = Qhead->next;
    delete kill_node;
}

void Queue::QWrite(string& read, string filename, int ind_start, int end){
    ofstream in;
    in.open(filename);
    if (is_empty()){
        cout << "Queue is empty" << endl;
        in << read;
        in.close();
        return;
    }
    QNode* current = Qhead;
    while (current != Qtail){
        read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
        ind_start += current->data.size() + 3;
        current = current->next;
    }
    read.insert(ind_start+1, '\"' + Qtail->data + '\"');
    in << read;
    in.close();
    return;
}

void Queue::QRead(string& read, int& ind_start, int& ind){
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
        QPush(datas);
        datas = "";
    }
    read.erase(ind_start + 1, ind - ind_start - 1);
    return;
}