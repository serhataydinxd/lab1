#pragma once
#include <iostream>
#include <string>
#include "AVLTreeNode.h"
class AVLTree{
private:
	AVLTreeNode* root;
	int counter;
	int maxFrequency;
	void printAux(AVLTreeNode* node);
	void eraseTreeNodes(AVLTreeNode* node);
	void max(AVLTreeNode*);
public:
	AVLTree() { root = NULL; counter = 0, maxFrequency = 0; }
	~AVLTree() { eraseTreeNodes(root); root = NULL; }
	AVLTreeNode* min();
	void add(string word);
	void remove(AVLTreeNode*);
	int getCounter() { return counter; }
	void print();
	int getMaxFrequency();
};

