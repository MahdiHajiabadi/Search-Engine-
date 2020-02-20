
#ifndef _TRIE_H_
#define _TRIE_H_

#include <vector>

struct Position{
	int id;
	int pos;
	Position(int id_ = 0, int pos_ = 0);
};

struct Node{
	int count;
	std::vector<Position> documents;
	Node *next;
	Node();
};

//struct AlphaNode{
//	int count;
//	Node *next;
//	Node *alpha;
//	Node();
//};
//
//struct NextNode{
//	int count;
//	Node *next;
//	Node *alpha;
//	Node();
//};


struct Trie{
	Node *root;
	Node *find(char *word);
	bool insert(char *word, int docId, int pos);
	Trie();
	~Trie();
};
#endif
