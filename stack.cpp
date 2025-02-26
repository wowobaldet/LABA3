#include "Header.h"


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
        if (is_empty()){
            cout << "Stack is empty" << endl;
            return;
        }
        SNode* new_head = head;
        head = head->next;
        delete new_head;
    }
    
    bool Stk::printStack() {
        if (is_empty()){
            cout << "Stack is empty" << endl;
            return 0;
        }
        SNode* current = head;
        cout << "Stack output:" << endl;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
        return 1;
    }
    
