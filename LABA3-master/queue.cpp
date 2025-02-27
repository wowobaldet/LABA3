#include "Header.h"

bool Queue::is_empty(){
    return Qhead == nullptr;
}

bool Queue::QPrint(){
    if (is_empty()){
        cout << "Queue is empty" << endl;
        return 0;
    }
    cout << "Queue output:" << endl;
    QNode* current = Qhead;

    while (current != nullptr){
        cout << current->data << endl;
        current = current->next;
    }
    return 1;
}
void Queue::QPush(string new_data){
    QNode* new_node = new QNode{new_data, nullptr, nullptr};
    if (is_empty()){
        Qhead = new_node;
        Qtail = new_node;
    } else {
        new_node->prev = Qtail;
        Qtail->next = new_node;
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


