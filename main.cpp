#include "trie.h"
#include <fstream>

void pressKey() {
	system("pause");
}

bool fromVariety(string word, string variety) {
	for (int i = 0; i < word.length(); ++i) {
		bool in = false;
		for (int j = 0; j < variety.length(); ++j)
			if (word[i] == variety[j]) {
				in = true;
				break;
			}
		if (!in) return false;
	}
	return true;
}

int main() {
	TrieTree tree;
	string word;
	int solution=-1;
	while (solution) {
		cout<< "\tChoose an action:\n"
			<< "1 - Add words to the tree\n"
			<< "2 - Delete the word from the tree\n"
			<< "3 - Show all words\n"
			<< "4 - Select and show all words which consist of members of the set\n"
			<< "5 - Clear the tree\n"
			<< "\n0 - Stop the program\n\n"
		;
		cin >> solution;
		cin.get();
		cout << endl;
		switch (solution) {
		case 0://Stop the program
			break;
		case 1://Add words to the tree
			cout<< "1 - To type\n"
				<< "2 - To read from the file\n\n";
			cin >> solution;
			cin.get();
			cout << endl;
			if (solution == 1) {
				cout << "Input the word you wish to add:\n";
				getline(cin, word);
				tree.addWord(word);
				cout << word + " is added to the tree.\n";
				tree.sort();
			}
			else if (solution == 2) {
				cout << "Input the path of the file:\n";
				getline(cin, word);
				ifstream file(word);
				if (file)
				{
					while (file >> word) {
						for (int i = 0; i < 2; ++i){
							if (word[0] == '"'|| word[0] == '(') word.erase(0, 1);
							if (word[word.length() - 1] == '.' ||
								word[word.length() - 1] == ',' ||
								word[word.length() - 1] == ';' ||
								word[word.length() - 1] == '?' ||
								word[word.length() - 1] == '"' ||
								word[word.length() - 1] == ')' ||
								word[word.length() - 1] == '!') word.erase(word.length() - 1, 1);
						}
						if (word[word.length() - 1] == ')') word.erase(word.length() - 1, 1);
						tree.addWord(word);
						cout << word + " is added to the tree.\n";
					}
					file.close();
					tree.sort();
				}
				else cout << "File doesn't exist.\n";
			}
			else {
				cout << "Incorrect action. ";
			}
			break;
		case 2://Delete the word from the tree
			cout << "Which word do you want to delete?\n";
			getline(cin, word);
			tree.deleteWord(word);
			cout << word + " is deleted from the tree.\n";
			break;
		case 3://3 - Show all words
			tree.show();
			break;
		case 4://Select and show all words which consist of members of the set
			cout << "Input the set:\n";
			getline(cin, word);
			tree.showSelected(fromVariety, word);
			break;
		case 5://5 - Clear the tree
			tree.clearTree();
			cout << "Tree is clear.\n";
			break;
		default:
			cout << "Incorrect action. ";

		}
		pressKey();
		system("CLS");
	}
	return 0;
}