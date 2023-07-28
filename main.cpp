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

    [[maybe_unused]] BST(float val){
        root = new Node();
        root->val = val;
        root->right = nullptr;
        root->left = nullptr;
    }

    Node* get_root(){
        return root;
    }
    void insert_data(float);
    void inorder_traverse(Node*);
    Node* search_data(float);
    void delete_data(float);

    [[maybe_unused]] static Node* minimum(Node*);
    static Node* maximum(Node*);
    static Node* successor(Node*);
};
// returns the minimum value considering the argument as the root.
[[maybe_unused]] Node* BST::minimum(Node* node) {
    auto temp_node = node;
    if(node->left == nullptr) return nullptr;
    while(node != nullptr){
      temp_node = node;
      node = node->left;
    }
    return temp_node;
}
Node* BST::maximum(Node* node) {
    auto temp_node = node;
    if(node->right == nullptr) return nullptr;
    while(node != nullptr){
        temp_node = node;
        node = node->right;
    }
    return temp_node;
}
// successor of any node 'x' is a node with the smallest value greater than x.val
Node* BST::successor(Node* node){
    if(node->left != nullptr) {
        std::cout << "The successor of " << node->val << " is " << maximum(node->left) -> val;
        return maximum(node->left);
    }

}
// risky: the provided node must exist
// returns the parent node of the given node (not the root of the tree)
Node* BST::get_parent(Node* node) {
    if (node == root){
        std::cout << "nullptr encountered\n";
        return nullptr;
    }
    auto temp = root;
    Node* parent = new Node();
    while (temp != nullptr){
        parent = temp;
        if(temp->right != nullptr){
            if(temp->right->val == node->val){
                std::cout << "The parent of " << node->val << " is " << parent->val << '\n';
                return parent;
            }
            else if(node->val < temp->val){
                temp = temp->left;
            } else if (node->val > temp->val){
                temp = temp->right;
            }
        } else if (temp->left != nullptr){
            if(temp->left->val == node->val){
                std::cout << "The parent of " << node->val << " is " << parent->val << '\n';
                return parent;
            }
            else if(node->val < temp->val){
                temp = temp->left;
            } else if (node->val > temp->val){
                temp = temp->right;
            }
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
// recursively traverse through the tree nodes.
void BST::inorder_traverse(Node* node) {
    if(node != nullptr){
        inorder_traverse(node->left);
        std::cout << node->val << '\n';
        inorder_traverse(node->right);
    }
}
// search a node with the given value and return the node.
Node* BST::search_data(float val) {
    auto temp = root;
    while (temp != nullptr){
        if (temp->val == val){
            std::cout << "The value " << val << " is found\n";
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
// delete a node with the given value.
void BST::delete_data(float val) {
    // check if the value exist
    auto delete_node = search_data(val);
    auto parent = get_parent(delete_node);
    auto successor_node = successor(delete_node);

    // special case : deletion of the root node.
    if (delete_node == root){
        auto successor_parent = get_parent(successor_node);
        if(successor_parent->val > successor_node->val){
            successor_parent->left = successor_node->right;
        } else{
            successor_parent->right = successor_node->right;
        }
        // replace the node to be deleted by successor
        successor_node->left = delete_node->left;
        successor_node->right = delete_node->right;

        delete delete_node; // risky: free memory
        // set the root of the BST.
        root = successor_node;
        return;
    }

    if(delete_node != nullptr){
        std::cout << "Parent value: " << parent->val << "\n";
        // if the value exists
        // There are 3 cases
        //1. if the node with the value has no children, just remove the node
        if(delete_node->right == nullptr &&  delete_node->left == nullptr){
            if(delete_node->val > parent->val)
              parent->right = nullptr;
            else
                parent->left = nullptr;

            delete delete_node;
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
           // find the successor of the node to be deleted, the successor cannot have left child.
           // if the immediate rightmost node is the successor (one with no left child)
           if(delete_node->right->left == nullptr){
               auto replace_temp_node = delete_node->right;
               replace_temp_node->left = delete_node->left;
               if(parent->val > delete_node->val){
                   parent->left = replace_temp_node;
               } else{
                   parent->right = replace_temp_node;
               }
               std::cout << "Deleted value: " << delete_node->val << '\n';
              delete delete_node;
           }
           // if the immediate rightmost node is not the successor
           else{
               //replace the successor with its right child
               auto successor_parent = get_parent(successor_node);
               if(successor_parent->val > successor_node->val){
                   successor_parent->left = successor_node->right;
               } else{
                   successor_parent->right = successor_node->right;
               }
               // replace the node to be deleted by successor
               if(parent->val > delete_node->val){
                   parent->left = successor_node;
               } else{
                   parent->right = successor_node;
               }
               successor_node->left = delete_node->left;
               successor_node->right = delete_node->right;

               delete delete_node;
           }


        }
    } else {
        std::cout << "Couldn't delete, " << val << " :no such value exists";
    }
}

int main() {

    auto my_btree = new BST();
    // insert nodes to the tree.
    my_btree->insert_data(5.0f);
    my_btree->insert_data(6.0f);
    my_btree->insert_data(9.0f);
    my_btree->insert_data(3.0f);
    my_btree->insert_data(4.0f);
    my_btree->insert_data(2.0f);
    my_btree->insert_data(8.0f);
    my_btree->insert_data(7.0f);
    my_btree->insert_data(10.0f);
    my_btree->insert_data(14.0f);
    my_btree->insert_data(12.0f);
    my_btree->insert_data(13.0f);


    std::cout << "Before Deletion\n";
    my_btree->inorder_traverse(my_btree->get_root());

    my_btree->delete_data(5.0f);
    std::cout << "After Deletion\n";
    my_btree->inorder_traverse(my_btree->get_root());
    delete my_btree;
    return 0; // happy compiler :)
}
