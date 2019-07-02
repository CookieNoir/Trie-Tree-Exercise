#include "trie.h"

TrieTree::TrieTree() {
	tree = new TrieNode();
	tree = nullptr;
}

//Add Word
TrieTree::TrieNode* TrieTree::addLetter(string word, int level) {
	TrieNode* p = new TrieNode;
	p->letter = word[level];
	p->right = 0;
	p->end = false;
	if (level + 1 < word.length()) p->down = addLetter(word, level + 1);
	else {
		p->end = true;
		p->down = 0;
	}
	return p;
}
void TrieTree::addWordRec(TrieNode*& node, string word, TrieNode* connector, int level) {
	TrieNode* p = node;
	if (!p) connector->down = addLetter(word, level);
	else
		if (p->letter == word[level])
			if (level + 1 < word.length()) {
				addWordRec(p->down, word, p, level + 1);
				return;
			}
			else {
				p->end = true;
				return;
			}
		else {
			while (p->right) {
				if (p->right->letter == word[level])
					if (level + 1 < word.length()) {
						addWordRec(p->right->down, word, p->right, level + 1);
						return;
					}
					else {
						p->right->end = true;
						return;
					}
				p = p->right;
			}
			if (!p->right) p->right = addLetter(word, level);
		}
}
void TrieTree::addWord(string word) {
	TrieNode* p = tree;
	if (!p) tree = addLetter(word, 0);
	else
		if (p->letter == word[0])
			if (1 < word.length()) {
				addWordRec(p->down, word, p, 1);
				return;
			}
			else {
				p->end = true;
				return;
			}
		else {
			while (p->right) {
				if (p->right->letter == word[0])
					if (1 < word.length()) {
						addWordRec(p->right->down, word, p->right, 1);
						return;
					}
					else {
						p->right->end = true;
						return;
					}
				p = p->right;
			}
			if (!p->right) p->right = addLetter(word, 0);
		}
}

//Show
void TrieTree::showRec(TrieNode* node, string str) {
	TrieNode* p = node;
	while (p) {
		if (p->end) cout << "  " + str + p->letter << endl;
		showRec(p->down, str + p->letter);
		p = p->right;
	}
}
void TrieTree::show() {
	TrieNode* p = tree;
	cout << "Dictionary:\n";
	while (p) {
		cout << " " << p->letter << endl;
		if (p->end) cout << "  " << p->letter << endl;
		showRec(p->down, string(1, p->letter));
		p = p->right;
	}
	cout << "-----------\n";
}

//Clear Tree
void TrieTree::clearTreeRec(TrieNode*& node) {
	if (node->down) clearTreeRec(node->down);
	if (node->right) clearTreeRec(node->right);
	delete node;
	node = nullptr;
}
void TrieTree::clearTree() {
	if (!tree) return;
	if (tree->down) clearTreeRec(tree->down);
	if (tree->right) clearTreeRec(tree->right);
	delete tree;
	tree = nullptr;
}

TrieTree::~TrieTree() {
	clearTree();
}

//Delete Word
void TrieTree::deleteWordRec(TrieNode*& node, string word, int level) {
	TrieNode* p = node;
	if (!p) {
		cout << "You didn't add this word to the dictionary.\n";
		return;
	}
	else {
		TrieNode* prev=nullptr;
		while (p&&p->letter != word[level]) { prev = p; p = p->right; }
		if (!p) {
			cout << "You didn't add this word to the dictionary.\n";
			return;
		}
		else {
			if (level + 1 < word.length()) {
				deleteWordRec(p->down, word, level + 1);
				if (!p->end) {
					if (!p->down) {
						if (!prev) node = p->right;
						else prev->right = p->right;
						delete p;
						p = nullptr;
					}
				}
				return;
			}
			else {
				p->end = false;
				if (!p->down) {
					if (!prev) node = p->right;
					else prev->right = p->right;
					delete p;
					p = nullptr;
				}
				return;
			}
		}
	}
}
void TrieTree::deleteWord(string word) {
	TrieNode* p = tree;
	if (!p) {
		cout << "You didn't add this word to the dictionary.\n";
		return;
	}
	else {
		TrieNode* prev=nullptr;
		while (p&&p->letter != word[0]) { prev = p; p = p->right; }
		if (!p) {
			cout << "You didn't add this word to the dictionary.\n";
			return;
		}
		else {
			if (1 < word.length()) {
				deleteWordRec(p->down, word, 1);
				if (!p->end) {
					if (!p->down) {
						if (!prev) tree = p->right;
						else prev->right = p->right;
						delete p;
						p = nullptr;
					}
				}
				return;
			}
			else {
				p->end = false;
				if (!p->down) {
					if (!prev) tree = p->right;
					else prev->right = p->right;
					delete p;
					p = nullptr;
				}
				return;
			}
		}
	}
}

void TrieTree::sortRec(TrieNode*& node) {
	TrieNode* p = node;
	TrieNode* min = p;
	TrieNode* minprev = nullptr;
	if (!p) return;
	else {
		while (p->right) {
			if (p->right->letter < min->letter) {
				min = p->right; minprev = p;
			}
			p = p->right;
		}
		if (minprev) {
			minprev->right = min->right;
			min->right = node;
			node = min;
		}
		sortRec(node->right);
	}
}
void TrieTree::sort() {
	TrieNode* p = tree;
	TrieNode* min = p;
	TrieNode* minprev = nullptr;
	if (!p) return;
	else {
		while (p->right) {
			if (p->right->letter < min->letter) {
				min = p->right; minprev = p;
			}
			p = p->right;
		}
		if (minprev) {
			minprev->right = min->right;
			min->right = tree;
			tree = min;
		}
		sortRec(tree->right);
	}
}