#include "Header.h"

bool Tree::is_empty(){
    return root == nullptr;
}

void Tree::TPush(TNode* current, string new_data){
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

bool Tree::TFind(TNode* current, string find_data){
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

bool Tree::is_full(TNode* current){
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
void Tree::print_Tree(TNode* root, int level)
{
    if (root != NULL)
    {
        print_Tree(root->right, level + 1);
        for (int i = 0; i < level * 4; i++) cout << "   ";
        cout << root->data << endl;
        print_Tree(root->left, level + 1);
    }
}

void Tree::TWrite(string& read, string filename, int ind_start, int ind, string data){
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

int Tree::TRead(string& read, int& ind_start, int& ind){
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