#include "Header.h"

Massive::Massive() {
    for (int i = 0; i < size; i++){
        elements[i] = "";
    }
}

string Massive::operator[] (int i){
    return elements[i];
}

bool Massive::is_empty(){
    return realsize == 0;
}

void Massive::MPrint(){
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

void Massive::MPushback(string element){
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

void Massive::MPushind(int ind, string element){
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

void Massive::MPopind(int ind){
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

void Massive::MChange(int ind, string element){
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

void Massive::MGet(int ind){
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

int Massive::Size(){
    return size;
}

void Massive::MWrite(string& read, string filename, int ind_start, int end){
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

void Massive::MRead(string& read, int& ind_start, int& ind){
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