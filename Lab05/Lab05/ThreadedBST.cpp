#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode *curr = this->min();

	while (curr != NULL){
		BSTNode *n = this->next(curr);
		delete curr;
		curr = n;
	} // end-while
	
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
    if (root == nullptr) {
        root = new BSTNode(key);
    }
    else {
        BSTNode* current = root;
        while (true) {
            if (key < current->key) {
                if (current->leftLinkType == THREAD) {
                    // Insert as left child
                    BSTNode* newNode = new BSTNode(key);
                    newNode->left = current->left;
                    newNode->right = current;
                    current->left = newNode;
                    current->leftLinkType = CHILD;
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else if (key > current->key) {
                if (current->rightLinkType == THREAD) {
                    // Insert as right child
                    BSTNode* newNode = new BSTNode(key);
                    newNode->left = current;
                    newNode->right = current->right;
                    current->right = newNode;
                    current->rightLinkType = CHILD;
                    break;
                }
                else {
                    current = current->right;
                }
            }
            else {
                // Key already exists
                break;
            }
        }
    }
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
    BSTNode* current = root;
    BSTNode* parent = nullptr;
    bool isLeftChild = false;

    while (current != nullptr) {
        if (key < current->key) {
            parent = current;
            current = (current->leftLinkType == THREAD) ? nullptr : current->left;
            isLeftChild = true;
        }
        else if (key > current->key) {
            parent = current;
            current = (current->rightLinkType == THREAD) ? nullptr : current->right;
            isLeftChild = false;
        }
        else {
            // Key found
            if (current->leftLinkType == CHILD && current->rightLinkType == CHILD) {
                // Node has two children
                // Find the inorder successor
                BSTNode* successor = current->right;
                BSTNode* successorParent = current;

                while (successor->leftLinkType == CHILD) {
                    successorParent = successor;
                    successor = successor->left;
                }

                // Copy the successor's key to the current node
                current->key = successor->key;

                // Remove the successor node
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                }
                else {
                    successorParent->right = successor->right;
                }

                delete successor;

                return; // Exit the function after removal
            }

            // Node has one child or no child
            BSTNode* child = (current->leftLinkType == CHILD) ? current->left : current->right;

            if (current == root) {
                root = child;
            }
            else if (isLeftChild) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            delete current;

            return; // Exit the function after removal
        }
    }
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {
    BSTNode* current = root;
    while (current != nullptr) {
        if (key < current->key) {
            current = (current->leftLinkType == THREAD) ? nullptr : current->left;
        }
        else if (key > current->key) {
            current = (current->rightLinkType == THREAD) ? nullptr : current->right;
        }
        else {
            // Key found
            return current;
        }
    }
    // Key not found
	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
    BSTNode* current = root;
    while (current != nullptr && current->leftLinkType == CHILD) {
        current = current->left;
    }
    return current;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
    BSTNode* current = root;
    while (current != nullptr && current->rightLinkType == CHILD) {
        current = current->right;
    }
    return current;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
    if (node->leftLinkType == THREAD) {
        return node->left;
    }
    else {
        BSTNode* predecessor = node->left;
        while (predecessor->rightLinkType == CHILD) {
            predecessor = predecessor->right;
        }
        return predecessor;
    }
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
    if (node->rightLinkType == THREAD) {
        return node->right;
    }
    else {
        BSTNode* successor = node->right;
        while (successor->leftLinkType == CHILD) {
            successor = successor->left;
        }
        return successor;
    }
} // end-next