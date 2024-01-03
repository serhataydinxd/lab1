#include <vector>
#include "AVLTree.h"
using namespace std;

void AVLTree::eraseTreeNodes(AVLTreeNode* node){
	if (node == NULL) { return; }
	eraseTreeNodes(node->left);
	eraseTreeNodes(node->right);
	delete node;
}

AVLTreeNode* AVLTree::min(){
	if (root == NULL) { throw exception("Tree is empty"); }
	AVLTreeNode* p = root;
	while (p->left != NULL) {
		p = p->left;
	}

	return p;
}

void AVLTree::add(string word){
	AVLTreeNode* parent = NULL;
	AVLTreeNode* current = root;
	while (current){
		parent = current;
		if (word == current->words.word){
			current->words.freq++;
			return;
		}
		else if (word < current->words.word) {
			current = current->left;
		}

		else {
			current = current->right;
		}
	}
	AVLTreeNode* node = new AVLTreeNode(word);
	counter++;
	if (root == NULL) {
		root = node;
	} else if (word < parent->words.word) {
		parent->left = node;
	} else {
		parent->right = node;
	}
}

void AVLTree::remove(AVLTreeNode* min){
	AVLTreeNode* parent = NULL;
	AVLTreeNode* current = root;
	while (current && current != min){
		parent = current;
		if (min->words.word < current->words.word) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (current == NULL) { return; };

	if (current->left && current->right){
		AVLTreeNode* qp = current;
		AVLTreeNode* q = current->left;

		while (q->right){
			qp = q;
			q = q->right;
		}

		current->words.word = q->words.word;
		parent = qp;
		current = q;
	}
	if (current == root){
		root = root->left ? root->left : root->right;
		delete current;
		return;
	}

	if (current == parent->left) {
		parent->left = current->left ? current->left : current->right;
	}
	else {
		parent->right = current->left ? current->left : current->right;
	}
	delete current;
}

void AVLTree::max(AVLTreeNode* node){
	if (!node) {
		return;
	}
	if (node->words.freq > maxFrequency) {
		maxFrequency = node->words.freq;
	}

	max(node->left);
	max(node->right);
}

int AVLTree::getMaxFrequency(){
	max(root);
	return maxFrequency;
}

void AVLTree::print(){
	printf("AVL Keys: ");
	printAux(root);
	printf("\n");
}

void AVLTree::printAux(AVLTreeNode* node){
	if (node == NULL) { return; }
	printAux(node->left);
	cout << node->words.word << " ";
	cout << node->words.freq << " ";
	printAux(node->right);
}
