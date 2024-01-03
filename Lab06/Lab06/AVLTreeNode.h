#pragma once
#include"WordFreq.h"
#include <iostream>

struct AVLTreeNode{
	WordFreq words;
	int height;
	AVLTreeNode* left, * right;
	AVLTreeNode(string word) : words(word) { words.freq++; left = right = NULL; height = 0; }
};