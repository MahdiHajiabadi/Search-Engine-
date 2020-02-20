
#include "Trie.h"
#include "Utility.h"
using namespace std;

Position::Position(int id_, int pos_)
{
	id = id_;
	pos = pos_;
}

Node::Node()
{
	next = 0;
	count = 0;
}

Trie::Trie()
{
	root = 0;
}

Trie::~Trie()
{
}

Node *Trie::find(char *word)
{
	if (*word == 0)
		return 0;

	if (root == 0)
	{
		return 0;
	}

	Node *node = root;
	Node *preNode = 0;
	int ind;
	while (*word != 0)
	{
		ind = index(*word);
		if (node == 0)
		{
			return 0;
		}
		node += ind;
		preNode = node;
		node = node->next;
		word++;
	}
	return preNode;
}

bool Trie::insert(char *word, int docId, int pos)
{
	if (*word == 0)
		return true;

	if (root == 0)
	{
		root = new Node[NUM_OF_VALID_CHARS];
	}

	Node *node = root;
	Node *preNode = 0;
	
	int ind;
	while (*word != 0)
	{
		ind = index(*word);
		if (node == 0)
		{
			node = new Node[NUM_OF_VALID_CHARS];
			preNode->next = node;
		}
		node += ind;
		preNode = node;
		node = node->next;
		word++;
	}
	preNode->count++;
	preNode->documents.push_back(Position(docId, pos));
	return preNode->count == 1;
}
