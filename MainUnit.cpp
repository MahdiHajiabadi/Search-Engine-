//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "Trie.h"
#include "Reader.h"
#include <string>
#include <fstream>

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	dictionary = initTrie();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SearchEditChange(TObject *Sender)
{
	if (!bMinimized)
	{
		bMinimized = true;
		BingleImage->Left = 20;
		BingleImage->Top = 20;
		BingleImage->Width = 170;
		BingleImage->Height = 100;
		SearchEdit->Left = BingleImage->Left + BingleImage->Width + 20;
		SearchEdit->Top = BingleImage->Top;
		SearchBtn->Left = SearchEdit->Left + SearchEdit->Width;
		SearchBtn->Top = SearchEdit->Top;
		SearchBtn->Show();
		BarImage->Show();
		SearchButton->Hide();
		LuckyButton->Hide();
		Memo1->Show();
	}
	SearchBtnClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SearchBtnClick(TObject *Sender)
{
	AnsiString s = SearchEdit->Text;
	char word[200];
	strcpy(word, s.c_str());
	//cin >> word;
//	getchar();
//	while (word[0] != 0)
	{
		Node *node = dictionary->find(word);
		if (node == 0 || node->count == 0)
		{
			AnsiString s = word;
//			ShowMessage(s + " not found in documents!");
			Memo1->Lines->Clear();
//			cout << word << " not found in documents!" << endl;
		}
		else
		{
			//cout << "The word \"" << word << "\" " << node->count << " times occures in documents:" << endl;
			for (int i = 0; i < node->documents.size(); i++)
			{
				if (i % 14 == 0)
				{
					//getchar();
					//cout << "-------------------------------- Page " << i / 10 + 1 << " ---------------------------------" << endl;
//					refresh();
//					clearScreen(0, 5, 80, 35, 15, 1, ' ');
					Memo1->Lines->Clear();
					char tmpS[200];
					sprintf(tmpS, "%d Results found in 0 sec!", node->documents.size());
					Memo1->Lines->Add(UnicodeString(tmpS));
//					block(1, 5, 12, 9, tmpS);
					sprintf(tmpS, "Page %d : ", i / 10 + 1);
					Memo1->Lines->Add(UnicodeString(tmpS));
//					block(1, 6, 12, 9, tmpS);
				}
				if (i >= 13)
					break;
				//cout << "* In Doc(" << node->documents[i].id + 1 << "): ";
				char tmpS[200];
				sprintf(tmpS, "Document Number %d : ", node->documents[i].id + 1);
//				block(1, 8 + i % 10 * 3, 10, 9, tmpS);
				Memo1->Lines->Add(UnicodeString(tmpS));
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
				Memo1->Lines->Add(UnicodeString(tmpStr.c_str()));
//				block(1, 8 + i % 10 * 3 + 1, 10, 9, tmpStr.c_str());
				//cout << endl;
				Memo1->Lines->Add("");
			}
			//cout << endl;
		}
//		getch();
//		s = getQuery();
		strcpy(word, s.c_str());
	}

}
//---------------------------------------------------------------------------
