#include <iostream>

struct Node{
    float val;
    Node* left;
    Node* right;
};
class BST{
    Node* root;
    Node* get_parent(Node*);

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
    Node* search_data(float val);
    void delete_data(float val);
};

// risky: the provided node must exist
// returns the parent of the given node (not the root of the tree)
Node* BST::get_parent(Node* node) {
    if (node == root){
        return nullptr;
    }
    auto temp = root;
    Node* parent = nullptr;
    while (temp != nullptr){
        parent = temp;
        if (temp->right->val == node->val || temp->left->val == node->val){
            return parent;
        }
        else if(node->val < temp->val){
            temp = temp->left;
        } else if (node->val > temp->val){
            temp = temp->right;
        }
    }
}

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

Node* BST::search_data(float val) {
    auto temp = root;
    while (temp != nullptr){
        if (temp->val == val){
            std::cout << "The value" << val << " is found\n";
            return temp; // value found so return early
        }
        else if(val < temp->val){
            temp = temp->left;
        } else if (val > temp->val){
            temp = temp->right;
        }
    }
    // if you complete the loop no such value is present.
    std::cout << val << " not found\n";
    return temp;
}

void BST::delete_data(float val) {
    // check if the value exist
    auto delete_node = search_data(val);
    if(delete_node != nullptr){
        auto parent = get_parent(delete_node);
        std::cout << "Parent value: " << parent->val << "\n";
        // if the value exists
        // There are 3 cases
        //1. if the node with the value has no children, just remove the node
        if(delete_node->right == nullptr &&  delete_node->left == nullptr){
            if(delete_node->val > parent->val)
              parent->right = nullptr;
            else
                parent->left = nullptr;

            delete delete_node; // risky: clean up thing
        }
        // 2. if the node has only one child, set the child as parent
        else if(delete_node->right == nullptr || delete_node->left == nullptr) {
            if (delete_node->right != nullptr){
                // set delete_node -> right as a parent
                if(delete_node->right->val > parent->val)
                  parent->right = delete_node->right;
                else
                    parent->left = delete_node->right;

            } else if (delete_node-> left != nullptr){
                // set delete_node -> left as a parent.
                if(delete_node->left->val > parent->val)
                   parent->right = delete_node->left;
                else
                    parent->left = delete_node->left;
            }

            delete delete_node;
        }
        // 3. if the node has both children,
        else{

        }
    } else {
        std::cout << "Couldn't delete, " << val << " :no such value exists";
    }
}


int main() {

    auto my_btree = new BST();
    my_btree->insert_data(5.0f);
    my_btree->insert_data(6.0f);
    my_btree->insert_data(9.0f);
    my_btree->insert_data(3.0f);
    my_btree->insert_data(4.0f);
    my_btree->insert_data(2.0f);

    std::cout << "Before Deletion\n";
    my_btree->inorder_traverse(my_btree->get_root());

    my_btree->delete_data(4.0f);
    std::cout << "After Deletion\n";
    my_btree->inorder_traverse(my_btree->get_root());

    return 0; // happy compiler :)
}
