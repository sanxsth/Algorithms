#include <bits/stdc++.h>
using namespace std;


class Node {
	public:
	bool word_flag;

	Node* links[26];

	Node() {
		for (int pos = 0; pos < 26; pos++)
			links[pos] = nullptr;
		word_flag = false;
	}

	bool checkLink(char ch) {
		return links[ch - 'a'];
	}

	void createLink(char ch) {
		links[ch - 'a'] = new Node();
	}

	Node* getLink(char ch) {
		return links[ch - 'a'];
	}
};

class Trie {
	private:
	Node *root;

	void findAllWords(Node* node, string &cur_word) {
		if (node->word_flag)
			cout<<cur_word<<endl;

		for (int pos = 0; pos < 26; pos++) {
			if (node->links[pos]) {
				cur_word.push_back('a' + pos);
				findAllWords(node->links[pos], cur_word);
				cur_word.pop_back();
			}
		}
	}

	public:
	Trie() {
		root = new Node();
	}

	void insertWord(string &s) {
		auto node = root;

		for (auto ch : s) {
			if (!node->checkLink(ch))
				node->createLink(ch);
			node = node->getLink(ch);
		}

		node->word_flag = true;
	}

	void getAllWords() {
		string word = "";
		findAllWords(root, word);
	}
};

int main() {
	Trie *trie = new Trie();
	vector<string> words = {"sandeep", "satheesh"}; //trie supprts only lower case letters between a-z.
	for (auto word : words)
		trie->insertWord(word);
	trie->getAllWords();
	return 0;
}
