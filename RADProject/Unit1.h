//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TMemo *Memo1;
	TChart *Chart1;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TButton *Button2;
	TChart *Chart2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TRadioGroup *RadioGroup1;
	TLineSeries *Series5;
	TLineSeries *Series6;
	TLineSeries *Series7;
	TLineSeries *Series8;
	TLineSeries *Series9;
	TLineSeries *Series10;
	TLineSeries *Series11;
	TLineSeries *Series12;
	TLineSeries *Series13;
	TChart *Chart3;
	TLineSeries *LineSeries1;
	TLineSeries *LineSeries2;
	TLineSeries *LineSeries3;
	TLineSeries *LineSeries4;
	TLineSeries *LineSeries5;
	TChart *Chart4;
	TLineSeries *LineSeries6;
	TLineSeries *LineSeries7;
	TLineSeries *LineSeries8;
	TLineSeries *LineSeries9;
	TLineSeries *LineSeries10;
	TLineSeries *LineSeries11;
	TLineSeries *LineSeries12;
	TLineSeries *LineSeries13;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Chart3DblClick(TObject *Sender);
	void __fastcall Chart1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
