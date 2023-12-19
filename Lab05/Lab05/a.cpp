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
    BSTNode* newNode = new BSTNode(key);

    if (root == nullptr) {
        root = newNode;
    } else {
        BSTNode* current = root;
        while (true) {
            if (key < current->key) {
                if (current->leftLinkType == CHILD) {
                    current = current->left;
                } else {
                    newNode->right = current;
                    newNode->left = current->left;
                    current->left = newNode;
                    current->leftLinkType = CHILD;
                    break;
                }
            } else if (key > current->key) {
                if (current->rightLinkType == CHILD) {
                    current = current->right;
                } else {
                    newNode->left = current;
                    newNode->right = current->right;
                    current->right = newNode;
                    current->rightLinkType = CHILD;
                    break;
                }
            } else {
                delete newNode;
                return;
            }
        }
    }
}


///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	BSTNode* current = root;
	BSTNode* parent = nullptr;
	bool found = false;

	// Find the node to be removed
	while (current != nullptr) {
		if (key == current->key) {
			found = true;
			break;
		} else if (key < current->key) {
			if (current->leftLinkType == THREAD) {
				break;
			}
			parent = current;
			current = current->left;
		} else {
			if (current->rightLinkType == THREAD) {
				break;
			}
			parent = current;
			current = current->right;
		}
	}

	if (!found) {
		return;
	}

	// If node has no children
	if (current->leftLinkType == THREAD && current->rightLinkType == THREAD) {
		if (parent == nullptr) {
			root = nullptr;
		} else if (current == parent->left) {
			parent->leftLinkType = THREAD;
			parent->left = current->left;
		} else {
			parent->rightLinkType = THREAD;
			parent->right = current->right;
		}
		delete current;
	}
	// If node has only left child
	else if (current->leftLinkType == THREAD) {
		BSTNode* successor = current->right;
		while (successor->leftLinkType == CHILD) {
			successor = successor->left;
		}
		successor->left = current->left;
		if (parent == nullptr) {
			root = successor;
		} else if (current == parent->left) {
			parent->left = successor;
		} else {
			parent->right = successor;
		}
		delete current;
	}
	// If node has only right child
	else if (current->rightLinkType == THREAD) {
		BSTNode* predecessor = current->left;
		while (predecessor->rightLinkType == CHILD) {
			predecessor = predecessor->right;
		}
		predecessor->right = current->right;
		if (parent == nullptr) {
			root = predecessor;
		} else if (current == parent->left) {
			parent->left = predecessor;
		} else {
			parent->right = predecessor;
		}
		delete current;
	}
	// If node has both left and right children
	else {
		BSTNode* predecessor = current->left;
		while (predecessor->rightLinkType == CHILD) {
			predecessor = predecessor->right;
		}
		predecessor->right = current->right;
		BSTNode* successor = current->right;
		while (successor->leftLinkType == CHILD) {
			successor = successor->left;
		}
		successor->left = predecessor;
		if (parent == nullptr) {
			root = successor;
		} else if (current == parent->left) {
			parent->left = successor;
		} else {
			parent->right = successor;
		}
		delete current;
	}
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {
	BSTNode* current = root;

	while (current != nullptr) {
		if (key == current->key) {
			return current;
		} else if (key < current->key) {
			if (current->leftLinkType == THREAD) {
				break;
			}
			current = current->left;
		} else {
			if (current->rightLinkType == THREAD) {
				break;
			}
			current = current->right;
		}
	}


	return nullptr;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	if (root == nullptr) {
		return nullptr;
	}

	BSTNode* current = root;
	while (current->leftLinkType == CHILD) {
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
	if (root == nullptr) {
		return nullptr;
	}

	BSTNode* current = root;
	while (current->rightLinkType == CHILD) {
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
    if (node == nullptr) {
        return nullptr;
    }

    if (node->leftLinkType == THREAD) {
        return node->left;
    }

    BSTNode* predecessor = node->left;
    while (predecessor->rightLinkType == CHILD) {
        predecessor = predecessor->right;
    }

    return predecessor;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->rightLinkType == CHILD) {
		// If the right child is not a thread, find the leftmost node in the right subtree
		BSTNode* current = node->right;
		while (current->leftLinkType == CHILD) {
			current = current->left;
		}
		return current;
	} else {
		// If the right child is a thread, the inorder successor is the right child itself
		return node->right;
	}
} // end-next