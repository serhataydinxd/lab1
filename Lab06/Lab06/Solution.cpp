#include "WordFreq.h"
#include "AVLTree.h"
#include <vector>
#include <fstream>
#include <iostream>

///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
	vector<WordFreq> result;
	fstream file;
	string temp, word;
	AVLTree AVL;
	int count = 0;
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Couldn't open file" << endl;
		exit(0);
	}
	while (getline(file, temp)){
		for (int i = 0; i < temp.size(); i++){
			if (int(temp[i]) > 64 && int(temp[i]) < 91 || int(temp[i]) > 96 && int(temp[i]) < 123){
				if (int(temp[i]) > 64 && int(temp[i]) < 91){
					word += temp[i] + 32;
					continue;
				}
				word += temp[i];
			}
			else{
				if (word.size() >= 3) {
					AVL.add(word);
				}
				word = "\0";
			}
		}
		if (word.size() >= 3) {
			AVL.add(word);
		}
		word = "\0";
	}
	int t = AVL.getMaxFrequency();
	vector<vector<string>> words(t + 1);
	for (int i = 0; i < AVL.getCounter(); i++){
		for (int j = 0;; j++){
			if (AVL.min()->words.freq == j && AVL.min()){
				AVLTreeNode* minimum = AVL.min();
				words[j].push_back(minimum->words.word);
				AVL.remove(minimum);
				break;
			}
		}
	}
	for (int i = t; i >= 0; i--){
		for (int j = 0; j < words[i].size(); j++){
			WordFreq frequentWord("");
			frequentWord.word = words[i][j];
			frequentWord.freq = i;
			result.push_back(frequentWord);
			count++;
			if (count == k)
				break;
		}
		if (count == k)
			break;
	}
	file.close();
	return result;
} //end-GetMostFrequentKWords