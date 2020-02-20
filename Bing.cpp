
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <Tchar.h>
#include <ctime>
#include <conio.h>
#include "Reader.h"
#include "Trie.h"

using namespace std;

#define COLS 80
#define LINES 40

void *myConsole;    // Handle to write to the console.

unsigned char consoleBuffer[COLS * LINES * 4];

string getQuery();

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h, c);
}

void refresh()
{
    COORD charBufSize = {COLS, LINES};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0, 0, COLS - 1, LINES - 1}; 
	WriteConsoleOutputA(myConsole, (_CHAR_INFO *)consoleBuffer, charBufSize, characterPos, &writeArea);
}

int getcolor(int x, int y)
{
	return ((int)consoleBuffer[y * COLS * 4 + x * 4 + 2]) / 16;
}

void block(int x, int y, int tc, int bc, unsigned char ch)
{
	consoleBuffer[y * COLS * 4 + x * 4] = ch;
	consoleBuffer[y * COLS * 4 + x * 4 + 2] = tc + 16 * bc;
}

void clearScreen(int x1, int y1, int x2, int y2, int tc, int bc, unsigned char ch)
{
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			block(i, j, tc, bc, ch);
}

void block(int x, int y, int tc, int bc, const char *s)
{
	while (*s != 0)
	{
		block(x, y, tc, bc, *s);
		x++;
		s++;
	}
}

int main(int argc, _TCHAR* argv[])
{
	Trie *dictionary = initTrie();
	string s = getQuery();
	char word[200];
	strcpy(word, s.c_str());
	//cin >> word;
//	getchar();
	while (word[0] != 0)
	{
		Node *node = dictionary->find(word);
		if (node == 0 || node->count == 0)
			cout << word << " not found in documents!" << endl;
		else
		{
			//cout << "The word \"" << word << "\" " << node->count << " times occures in documents:" << endl;
			for (int i = 0; i < node->documents.size(); i++)
			{
				if (i % 10 == 0)
				{
					//getchar();
					//cout << "-------------------------------- Page " << i / 10 + 1 << " ---------------------------------" << endl;
					refresh();
					clearScreen(0, 5, 80, 35, 15, 1, ' ');
					char tmpS[200];
					sprintf(tmpS, "%d Results found in 0 sec!", node->documents.size());
					block(1, 5, 12, 9, tmpS);
					sprintf(tmpS, "Page %d : ", i / 10 + 1);
					block(1, 6, 12, 9, tmpS);
				}
				//cout << "* In Doc(" << node->documents[i].id + 1 << "): ";
				char tmpS[200];
				sprintf(tmpS, "Document Number %d : ", node->documents[i].id + 1);
				block(1, 8 + i % 10 * 3, 10, 9, tmpS);
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
				int t = 1;
				string tmpStr;
				for (int j = start; j < end; j++)
				{
					tmpStr += str[j] + " ";
					//cout << str[j] << " ";

				}
				block(1, 8 + i % 10 * 3 + 1, 10, 9, tmpStr.c_str());
				//cout << endl;
			}
			//cout << endl;
		}
		getch();
		s = getQuery();
		strcpy(word, s.c_str());
	}
	return 0;
}


string getQuery()
{
	srand(time(0));
    // Set up the handles for reading/writing:
    myConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change the window title:
    SetConsoleTitle(TEXT("Bing"));

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, COLS - 1, LINES - 1};
    
    // Change the console window size:
    SetConsoleWindowInfo(myConsole, TRUE, &windowSize);
    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {COLS, LINES};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(myConsole, bufferSize);

    // Set up the positions:
    COORD charBufSize = {COLS, LINES};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0, 0, COLS - 1, LINES - 1}; 

	ReadConsoleOutputA(myConsole, (_CHAR_INFO *)consoleBuffer, charBufSize, characterPos, &writeArea);

	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			block(j, i, 15, 1, ' ');
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 4; j < COLS - 4; j++)
		{
			if (i == 0 || i == 2 || j == 4 || j == COLS - 5)
				block(j, i, 15, 14, ' ');
			else
				block(j, i, 15, 9, ' ');
		}
	}

	for (int j = 5; j < COLS - 5; j++)
	{
		block(j, 1, 15, 9, ' ');
	}
	block(22, 3, 15, 1, "Goooooooooooooooooooooooooooooooogle");

	string query;

	WriteConsoleOutputA(myConsole, (_CHAR_INFO *)consoleBuffer, charBufSize, characterPos, &writeArea);
	gotoxy(6 + query.length(), 1);

	while (true)
	{
		char ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ' || ch == '.' || ch == '+' || ch == '-')
			query += ch;
		if (ch == 8 && query.size() > 0)
			query = query.substr(0, query.length() - 1);
		if (ch == 13)
		{
			return query;
		}
		for (int j = 5; j < COLS - 5; j++)
		{
			block(j, 1, 15, 9, ' ');
		}
		block(6, 1, 15, 9, query.c_str());
		WriteConsoleOutputA(myConsole, (_CHAR_INFO *)consoleBuffer, charBufSize, characterPos, &writeArea);
		gotoxy(6 + query.length(), 1);
	}

}