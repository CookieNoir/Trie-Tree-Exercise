#include <iostream>
#include <string>
using namespace std;

class TrieTree {
	struct TrieNode {
		char letter;
		bool end;
		TrieNode* right;
		TrieNode* down;
	};
	TrieNode* tree;
	TrieNode* addLetter(string word, int level);
	void addWordRec(TrieNode*& node, string word, TrieNode* connector, int level);
	void showRec(TrieNode* node, string str);
	template <class T> void showSelectedRec(TrieNode* node, string str, bool (*condition)(string, T),T data);
	void deleteWordRec(TrieNode*& node, string word, int level);
	void sortRec(TrieNode*& node);
	void clearTreeRec(TrieNode*& node);
public:
	TrieTree();
	void addWord(string word);
	void deleteWord(string word);
	void show();
	template <class T> void showSelected(bool (*condition)(string,T),T data);
	void sort();
	void clearTree();
	~TrieTree();
};

template <class T> void TrieTree::showSelectedRec(TrieNode* node, string str, bool(*condition)(string, T), T data) {
	TrieNode* p = node;
	while (p) {
		if (p->end) if (condition(str + p->letter, data)) cout << "  " + str + p->letter << endl;
		showSelectedRec(p->down, str + p->letter, condition, data);
		p = p->right;
	}
}
template <class T> void TrieTree::showSelected(bool(*condition)(string, T), T data) {
	TrieNode* p = tree;
	cout << "Selected:\n";
	while (p) {
		if (condition(string(1, p->letter), data)) cout << " " << p->letter << endl;
		if (p->end) if (condition(string(1, p->letter), data)) cout <<"  " << p->letter << endl;
		showSelectedRec(p->down, string(1, p->letter), condition, data);
		p = p->right;
	}
	cout << "---------\n";
}