//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include "Trie.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TImage *BingleImage;
	TEdit *SearchEdit;
	TButton *SearchButton;
	TButton *LuckyButton;
	TBitBtn *SearchBtn;
	TImage *BarImage;
	TMemo *Memo1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SearchEditChange(TObject *Sender);
	void __fastcall SearchBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	bool bMinimized;
	Trie *dictionary;
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
