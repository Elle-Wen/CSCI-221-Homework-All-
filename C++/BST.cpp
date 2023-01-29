#include <bits/stdc++.h>
#include <memory>
#include <cstdlib>

using namespace std;
template <typename T>
class Node {
public:
    unique_ptr<T> value;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;
    shared_ptr<Node<T>> parent;
    Node(const T& val) : value(make_unique<T>(val)) {}
};
template <typename T>
class BinarySearchTree{
public:
    int count;
    shared_ptr<Node<T>> root;
	//default constructor 
    BinarySearchTree() : count(0), root(nullptr) {}
    //parameter constructor 
    auto BinarySearchTree_make_tree(const vector<T>& values) {
        shared_ptr<BinarySearchTree<T>> tree = make_shared<BinarySearchTree<T>>();
        for (const auto& value : values) {
            tree->insert(value);
        }
        return tree;
    }
	//destructor 
	~BinarySearchTree() {
        // Clear the tree by deleting all nodes
        root = nullptr;
        count = 0;
    }
    // Adds the given value to the binary search tree
    void insert(const T& value) {
        shared_ptr<Node<T>> new_node = make_shared<Node<T>>(value);
        if (root == nullptr) {
            root = new_node;
            count++;
            return;
        }
        shared_ptr<Node<T>> current_node = root;
        while (current_node != nullptr) {
            if (value < *(current_node->value)) {
                if (current_node->left == nullptr) {
                    current_node->left = new_node;
                    new_node->parent = current_node;
                    count++;
                    break;
                }
                else {
                    current_node = current_node->left;
                }
            }
            else {
                if (current_node->right == nullptr) {
                    current_node->right = new_node;
                    new_node->parent = current_node;
                    count++;
                    break;
                }
                else {
                    current_node = current_node->right;
                }
            }
        }
		return; 
    }
    int delete1(T value) {
        // Find the node with the given value in the tree
        auto node = find_node(value);
        if (node == nullptr) {
            return 0;
        }

        // Get the parent of the node
        auto parent = node->parent;

        // If the node has no children, simply remove it by
        // setting its parent's corresponding child pointer to nullptr
        if (node->left == nullptr && node->right == nullptr) {
            if (parent->left == node) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }

        // If the node has a left child but no right child,
        // replace the node with its left child
        else if (node->left != nullptr && node->right == nullptr) {
            if (parent->left == node) {
                parent->left = node->left;
            }
            else {
                parent->right = node->left;
            }

            // Update the parent pointer of the left child
            node->left->parent = parent;
        }

        // If the node has a right child but no left child,
        // replace the node with its right child
        else if (node->left == nullptr && node->right != nullptr) {
            if (parent->left == node) {
                parent->left = node->right;
            }
            else {
                parent->right = node->right;
            }

            // Update the parent pointer of the right child
            node->right->parent = parent;
        }

        // If the node has both left and right children,
        // find the largest value in the left subtree,
        // replace the node's value with the largest value,
        // and delete the node containing the largest value
        // in the left subtree
        else {
            auto largest_node = find_largest_node(node->left);
            node->value = largest_node->value;
            return delete1(largest_node->value);
        }

        // Decrement the count of nodes in the tree
        // and delete the node
        count--;
        node = nullptr;
        return 1;
    }
	shared_ptr<Node<T>> find_node(T value) {
        auto current_node = root;
        while (current_node != nullptr) {
            if (value == current_node->value) {
                return current_node;
            }
            else if (value < current_node->value) {
                current_node = current_node->left;
            }
            else {
                current_node = current_node->right;
            }
        }
        return nullptr;
    }
	shared_ptr<Node<T>> find_largest_node(std::shared_ptr<Node<T>> subtree_root) {
        auto current_node = subtree_root;
        while (current_node->right != nullptr) {
            current_node = current_node->right;
        }
        return current_node;
    }
};

int main(){
}