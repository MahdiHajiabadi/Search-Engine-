#include <cstdio>
//#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include "Trie.h"

using namespace std;

ofstream fout("log.txt");

enum State{
	ST_START,
	ST_TAG_START,
	ST_TAG_FINISH_CANDID, // between '<' and '/'
	ST_TAG_FINISH,
	ST_DATA
};

#define BUF_SIZE (2 * 1024 * 1024)
#define HASH_SIZE 1000000007

//bool hashTable[HASH_SIZE];
char buf[BUF_SIZE + 1];
char tag[1000];
bool bFinishTag;
char word[1000];
int wordSize;
int totalWords = 0;
int distinctWords = 0;
int docId = 0;
int position = 0;

//FIXME : ofstream fout("doc0.txt");

inline int f(char *word)
{
	unsigned int k = 0, i = 0;
	while (word[i] != '\0')
	{
		k = (k * 247 + (int)(unsigned char)(word[i])) % HASH_SIZE;
		i++;
	}
	return k % HASH_SIZE;
}

void parse(char buf[], int n, State &state, int &tagCount, Trie &dictionary)
{
	int m;
	for (int i = 0; i < n; i++)
	{
		switch (state){
			case (ST_START):
				if (buf[i] == '<')
				{
					if (wordSize > 0)
					{
						if (word[wordSize - 1] == ',' || word[wordSize - 1] == '.')
							wordSize--;
						if (wordSize > 0)
						{
							word[wordSize] = '\0';
							//m = f(word);
							//if (!hashTable[m])
							//{
							//	distinctWords++;
							//	hashTable[m] = true;
							//}
							//FIXME : fout << word << "\n";

							if (dictionary.insert(word, docId, position))
							{
								distinctWords++;
							}

							position++;
							wordSize = 0;
							totalWords++;
						}
					}

					state = ST_TAG_START;
					bFinishTag = false;
				}
				else
				{
					if (tag[0] == 'B' && tag[1] == 'O' && tag[2] == 'D' && tag[3] == 'Y')
					{
						//fout << buf[i];
						if ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= '0' && buf[i] <= '9') 
							|| buf[i] == '.' || buf[i] == ',' || buf[i] == '\'' || buf[i] == '`')
						{
							word[wordSize++] = buf[i];
						}
						else
						{
							if (wordSize > 0)
							{
								if (word[wordSize - 1] == ',' || word[wordSize - 1] == '.')
									wordSize--;
								if (wordSize > 0)
								{
									word[wordSize] = '\0';
									//m = f(word);
									//if (!hashTable[m])
									//{
									//	distinctWords++;
									//	hashTable[m] = true;
									//}
									//FIXME : fout << word << "\n";
		
									if (dictionary.insert(word, docId, position))
									{
										distinctWords++;
									}
	
									position++;

									wordSize = 0;
									totalWords++;
								}
							}
						}
					}
				}
				break;
			case (ST_TAG_START):
				if (buf[i] == '/')
				{
					bFinishTag = true;
				}
				else if (buf[i] == '>')
				{
					state = ST_START;
					tag[tagCount] = '\0';
					if (bFinishTag)
					{
						//fout << "End: " << tag << "\n";
						if (tag[0] == 'B' && tag[1] == 'O' && tag[2] == 'D' && tag[3] == 'Y')
						{
							docId++;
							position = 0;
							char s[100];
							sprintf(s, "doc%d.txt", docId);
							//FIXME : fout.close();
							//FIXME : fout.open(s);
						}
					}
					else
					{
						//fout << "Start: " << tag << "\n";
					}

					tagCount = 0;
				}
				else
					tag[tagCount++] = buf[i];
				break;
			case (ST_TAG_FINISH_CANDID):
				if (buf[i] == '/')
					state = ST_TAG_FINISH;
				else
					state = ST_DATA;
				break;
			case (ST_TAG_FINISH):
				if (buf[i] == '>')
				{
					state = ST_START;
					tag[tagCount] = '\0';
					//fout << "End: " << tag << "\n";
					tagCount = 0;
				}
				else
					tag[tagCount++] = buf[i];
				break;
			case (ST_DATA):
				if (buf[i] == '<')
					state = ST_TAG_FINISH_CANDID;
				break;
		}
	}
}

Trie *initTrie()
{
	Trie *dictionary = new Trie();
	//dictionary.insert("Salam");
	//Node *node = dictionary.find("abc");
	//if (node != 0)
	//	fout << node->count << endl;
	//else
	//	fout << "Not found!" << endl;
	//return 0;


	int startTime = clock();//time(0);
	for (int ii = 0; ii <= 21; ii++)
	{
		FILE* dataFile;
		int tagCount = 0;
		char fileName[100];
		if (ii < 10)
			sprintf(fileName, "reuters21578\\reut2-00%d.sgm", ii);
		else
			sprintf(fileName, "reuters21578\\reut2-0%d.sgm", ii);
		dataFile = fopen(fileName, "rb");
		int n = fread(buf, 1, BUF_SIZE, dataFile);
		int i = 0;
		while (i < n && buf[i] != '\n')
			buf[i++] = ' ';
		State state = ST_START;
		wordSize = 0;
		while (n != 0)
		{
			parse(buf, n, state, tagCount, *dictionary);
			n = fread(buf, 1, BUF_SIZE, dataFile);
			fout << n << endl;
		}
	}
	int endTime = clock();// time(0);
	fout << "Total words: " << totalWords << endl;
	fout << "Distinct words: " << distinctWords << endl;
	fout << "Total time : " << (int)((endTime - startTime) / 1000.0) << "." << (int)((endTime - startTime) % 1000) << " sec" <<  endl;
	//FIXME : fout.close();
	return dictionary;

	char word[200];
	cin >> word;
	getchar();
	while (word[0] != 0)
	{
		Node *node = dictionary->find(word);
		if (node == 0 || node->count == 0)
			fout << word << " not found in documents!" << endl;
		else
		{
			fout << "The word \"" << word << "\" " << node->count << " times occures in documents:" << endl;
			for (int i = 0; i < node->documents.size(); i++)
			{
				if (i % 10 == 0)
				{
					getchar();
					fout << "-------------------------------- Page " << i / 10 + 1 << " ---------------------------------" << endl;
				}
				fout << "* In Doc(" << node->documents[i].id + 1 << "): ";
				char s[100];
				sprintf(s, "doc%d.txt", node->documents[i].id);
				ifstream fin(s);
				vector<string> str;
				string ss;
				while (fin >> ss)
				{
					str.push_back(ss);
				}
				int start = node->documents[i].pos - 5;
				if (start < 0)
					start = 0;
				int end = node->documents[i].pos + 6;
				if (end > str.size())
					end = str.size();
				for (int j = start; j < end; j++)
					fout << str[j] << " ";
				fout << endl;
			}
			fout << endl;
		}
		cin >> word;
	}
	return 0;
}