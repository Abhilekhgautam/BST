#include <iostream>

struct Node{
    float val;
    Node* left;
    Node* right;
};
class BST{
    Node* root;

public:
    BST(){
        root = nullptr;
    }
    BST(float val){
        root = new Node();
        root->val = val;
        root->right = nullptr;
        root->left = nullptr;
    }

    Node* get_root(){
        return root;
    }
    void insert_data(float val);
    void inorder_traverse(Node* root);
    void search_data(float val);
    void delete_data(float val);
};

void BST::insert_data(float val) {

    if (root == nullptr){
        root = new Node();
        root->val = val;
        root->left = nullptr;
        root->right = nullptr;
        return; // early exit
    }
    Node* temp_root = root;
    Node* temp_prev = nullptr;

    while (temp_root != nullptr){
        temp_prev = temp_root;
        if (val < temp_root->val){
            temp_root = temp_root->left;
        } else {
            temp_root = temp_root->right;
        }
    }

    Node* add_node = new Node();
    add_node->left = nullptr;
    add_node->right = nullptr;
    add_node->val = val;

    if(temp_prev->val < val){
        temp_prev->right = add_node;
    } else{
        temp_prev->left = add_node;
    }

}

void BST::inorder_traverse(Node* root) {
    if(root != nullptr){
        std::cout << root->val << '\n';
        inorder_traverse(root->left);
        inorder_traverse(root->right);
    }
}

void BST::search_data(float val) {
    auto temp = root;
    while (temp != nullptr){
        if (temp->val == val){
            std::cout << "The value" << val << " is found\n";
            return; // value found so return early
        }
        else if(val < temp->val){
            temp = temp->left;
        } else if (val > temp->val){
            temp = temp->right;
        }
    }
    // if you complete the loop no such value is present.
    std::cout << val << " not found\n";
}

int main() {

    auto my_btree = new BST();
    my_btree->insert_data(5.0f);
    my_btree->insert_data(6.0f);
    my_btree->insert_data(9.0f);
    my_btree->insert_data(3.0f);
    my_btree->insert_data(4.0f);
    my_btree->insert_data(2.0f);

    my_btree->inorder_traverse(my_btree->get_root());

    my_btree->search_data(55.0f);

    my_btree->search_data(3.0f);
    return 0; // happy compiler :)
}
