#include "Header.h"

Hash::Hash () {
    for (int i = 0; i < size; i++){
        tabs[i] = nullptr;
    }
}
bool Hash::is_empty(){
    for (int i = 0; i < size; i++){
        if (tabs[i] != nullptr){
            return false;
        }
    }
    return true;
}
void Hash::HPrint(){
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

int Hash::Htrans (string new_key){
    int sum = 0;
    for (int i = 0; i < new_key.size(); i++){
        sum += new_key[i];
    }
    return sum % size;
}

void Hash::HPush(string new_key_s, string new_data){
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

string Hash::HGet(string key_s){
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

void Hash::HPop(string key_s){
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

void Hash::HWrite(string& read, string filename, int ind_start, int end){
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

void Hash::HRead(string& read, int& ind_start, int& ind){
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
