//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

const double eps=1e-5, tt=1e-11;
double ts,tnach,d,l,a,*t,*t_prev,alpha,hx,ht,x,tay,tay_analit,tay_n;
double **t2, **t2_prev;

double yars2(int,TLineSeries *,bool);
double nrs2(int,TLineSeries *,bool);

double analit(double t)
{
 double bio,fur,teta;
 bio=alpha*d/l;
 teta=(tnach-ts)*0.01/(t-ts);
 fur=-log(teta)/bio;
 return fur*d*d/a;

}


double yars(int n, TLineSeries *S,bool vis)
{
   double tmp;
   int ii=0, count;

   t=new double [n+1];
 t_prev=new double [n+1];
 for (int i = 0; i < n+1; i++) {
   t[i]=tnach;
   t_prev[i]=t[i];
 }

   hx=(double)d/n;
   ht=0.9*hx*hx/(2*a);

   if (!vis)
   {
	Form1->Memo1->Lines->Add("N="+FloatToStrF(n,ffFixed,3,0));
   Form1->Memo1->Lines->Add("ht="+FloatToStrF(ht,ffFixed,10,7)+" с");
	  Form1->Memo1->Lines->Add("hx="+FloatToStrF(hx,ffFixed,10,7)+" м");
   }
   else {count=(int)tay_n/ht;}

  tay=0.;
  do {

	tay+=ht;
	ii++;
	   tmp=0.;

	   // запоминаем массив температур в предыдущий момент времени
	for (int i = 0; i < n+1; i++) {
   t_prev[i]=t[i];
 }
	 // рассчитываем температуру во внутренних точках
	for (int i = 1; i < n; i++) {
	  t[i]=t_prev[i]*(1-2*a*ht/(hx*hx))+a*ht/(hx*hx)*(t_prev[i+1]+t_prev[i-1]);
	}

	// рассчитываем температуру в граничных точках
 t[n]=(t[n-1]+alpha*hx/l*ts)/(1+alpha*hx/l);
	 t[0]=t[1];

	 // рассчитываем текущую погрешность
		for (int i = 0; i < n+1; i++)
		{
		if (fabs(t[i]-t_prev[i])>tmp) {
		 tmp=fabs(t[i]-t_prev[i]);
		}
		}

 if (!vis)
 S->AddXY(tay,t[0],"");
  else
  {
	x=0;
	for (int i = 0; i < n+1; i++) {
	if (ii==1){
  Form1->Series1->AddXY(x,t[i],"");
  Form2->Series1->AddXY(x,t[i],"");
  }
   else	 if (ii==count/3){
	 Form1->Series2->AddXY(x,t[i],"");
	Form2->Series2->AddXY(x,t[i],"");
	}
  else if (ii==count/2){
	 Form1->Series11->AddXY(x,t[i],"");
	 Form2->Series11->AddXY(x,t[i],"");
   }
   else	if (ii==2*count/3){
	 Form1->Series12->AddXY(x,t[i],"");
	 Form2->Series12->AddXY(x,t[i],"");
	}
  else if (ii==count){
	 Form1->Series13->AddXY(x,t[i],"");
	 Form2->Series13->AddXY(x,t[i],"");
	}

	 x+=hx;
	}
	}


	}while(tmp>eps);


  return tay;
}



double nrs(int n, TLineSeries *S,bool vis)
{
   double tmp,a1,b1,c1,*alfa,*beta;
	int ii=0, count;

   t=new double [n+1];
 t_prev=new double [n+1];
  alfa=new double [n+1];
 beta=new double [n+1];
 for (int i = 0; i < n+1; i++) {
   t[i]=tnach;
   t_prev[i]=t[i];
 }

   hx=(double)d/n;
   ht=0.9*hx*hx/(2*a);

if (!vis)
   {
	Form1->Memo1->Lines->Add("N="+FloatToStrF(n,ffFixed,3,0));
   Form1->Memo1->Lines->Add("ht="+FloatToStrF(ht,ffFixed,10,7)+" с");
	  Form1->Memo1->Lines->Add("hx="+FloatToStrF(hx,ffFixed,10,7)+" м");
   }
   else {count=(int)tay_n/ht;}

	  a1=-a*ht/hx/hx;
	  c1=a1;
	  b1=1+2*a*ht/hx/hx;

  tay=0.;

  do {
	tay+=ht;
	ii++;
	   tmp=0.;

	for (int i = 0; i < n+1; i++) {
   t_prev[i]=t[i];
 }

 // рассчитываем коэффициенты прогонки  - прямой ход прогонки
 alfa[0]=0.;
 beta[0]=t[1];

	for (int i = 1; i < n+1; i++) {
		alfa[i]=-a1/(b1+c1*alfa[i-1]);
		beta[i]=(t[i]-c1*beta[i-1])/(b1+c1*alfa[i-1]);
	}

	// рассчитываем температуру в граничной правой точке
t[n]=(beta[n-1]+alpha*hx/l*ts)/(1+alpha*hx/l-alfa[n-1]);


	  // рассчитываем температуру в остальных точках - обратный ход прогонки
		for (int j = n-1; j > -1; j--) {
	  t[j]=alfa[j]*t[j+1]+beta[j];
	}

	 // рассчитываем текущую погрешность
		for (int i = 0; i < n+1; i++)
		{
		if (fabs(t[i]-t_prev[i])>tmp) {
		 tmp=fabs(t[i]-t_prev[i]);
		}
		}

 if (!vis)
 S->AddXY(tay,t[0],"");
  else
  {
	x=0;
	for (int i = 0; i < n+1; i++) {
	if (ii==1){
  Form1->LineSeries1->AddXY(x,t[i],"");
  Form3->LineSeries1->AddXY(x,t[i],"");
  }
   else	 if (ii==count/3){
	 Form1->LineSeries2->AddXY(x,t[i],"");
	 Form3->LineSeries2->AddXY(x,t[i],"");
	 }
  else if (ii==count/2){
	 Form1->LineSeries3->AddXY(x,t[i],"");
	 Form3->LineSeries3->AddXY(x,t[i],"");
	 }
   else	if (ii==2*count/3){
	 Form1->LineSeries4->AddXY(x,t[i],"");
	 Form3->LineSeries4->AddXY(x,t[i],"");
	 }
  else if (ii==count){
	 Form1->LineSeries5->AddXY(x,t[i],"");
	 Form3->LineSeries5->AddXY(x,t[i],"");
	 }

	 x+=hx;
	}
	}


  }while(tmp>eps);

  return tay;
}


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form1->Memo1->Lines->Add("Явная схема");
Form1->Memo1->Lines->Add("");

int n;

d=Edit1->Text.ToDouble();
ts=Edit2->Text.ToDouble();
tnach=Edit3->Text.ToDouble();
l=Edit4->Text.ToDouble();
alpha=Edit5->Text.ToDouble();
a=Edit6->Text.ToDouble();

tay_analit=analit(tnach);

Form1->Memo1->Lines->Add("tay_analit="+FloatToStrF(tay_analit,ffFixed,10,0)+" c");

double tanalit=tnach, tmp_tay;
do {

 Form1->Series3->AddXY(tay_analit-analit(tanalit),tanalit,"");
   tanalit-=5.;
}while(tanalit>(tnach-ts)*0.01-tt);




if (Form1->RadioGroup1->ItemIndex==0) {

Series1->Clear();
Series2->Clear();
Series4->Clear();
Series5->Clear();
Series6->Clear();
Series7->Clear();
Series8->Clear();
Series9->Clear();
Series10->Clear();
Series11->Clear();
Series12->Clear();
Series13->Clear();
Form2->Series1->Clear();
Form2->Series2->Clear();
Form2->Series11->Clear();
Form2->Series12->Clear();
Form2->Series13->Clear();


 Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(5,Series4,0),ffFixed,10,0)+" c");
 Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  n=5;  tmp_tay=fabs(tay-tay_analit);   tay_n=tay;
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(10,Series5,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=10; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(25,Series6,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=25; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(50,Series7,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=50;  tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(100,Series8,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=100; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(130,Series9,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=130;  tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(200,Series10,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=200; tay_n=tay;
	  }

	  Form1->Memo1->Lines->Add("N оптимальное="+FloatToStrF(n,ffFixed,10,0));

	  yars(n,Series10,1);

}

else
{

Series1->Clear();
Series2->Clear();
Series4->Clear();
Series5->Clear();
Series6->Clear();
Series7->Clear();
Series8->Clear();
Series9->Clear();
Series10->Clear();
Series11->Clear();
Series12->Clear();
Series13->Clear();
Form2->Series1->Clear();
Form2->Series2->Clear();
Form2->Series11->Clear();
Form2->Series12->Clear();
Form2->Series13->Clear();


 Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars2(5,Series4,0),ffFixed,10,0)+" c");
 Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  n=5;  tmp_tay=fabs(tay-tay_analit);   tay_n=tay;
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars2(10,Series5,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=10; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars2(25,Series6,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=25; tay_n=tay;
	  }

	  Form1->Memo1->Lines->Add("N оптимальное="+FloatToStrF(n,ffFixed,10,0));

	  yars2(n,Series10,1);
	  }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 Form1->Memo1->Lines->Add("Неявная схема");
Form1->Memo1->Lines->Add("");

int n;

d=Edit1->Text.ToDouble();
ts=Edit2->Text.ToDouble();
tnach=Edit3->Text.ToDouble();
l=Edit4->Text.ToDouble();
alpha=Edit5->Text.ToDouble();
a=Edit6->Text.ToDouble();

tay_analit=analit(tnach);

Form1->Memo1->Lines->Add("tay_analit="+FloatToStrF(tay_analit,ffFixed,10,0)+" c");

double tanalit=tnach, tmp_tay;
do {

 Form1->LineSeries6->AddXY(tay_analit-analit(tanalit),tanalit,"");
   tanalit-=5.;
}while(tanalit>(tnach-ts)*0.01-tt);




if (Form1->RadioGroup1->ItemIndex==0) {

LineSeries1->Clear();
LineSeries2->Clear();
LineSeries3->Clear();
LineSeries4->Clear();
LineSeries5->Clear();
LineSeries7->Clear();
LineSeries8->Clear();
LineSeries9->Clear();
LineSeries10->Clear();
LineSeries11->Clear();
LineSeries12->Clear();
LineSeries13->Clear();
Form3->LineSeries1->Clear();
Form3->LineSeries2->Clear();
Form3->LineSeries3->Clear();
Form3->LineSeries4->Clear();
Form3->LineSeries5->Clear();

 Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(5,LineSeries7,0),ffFixed,10,0)+" c");
 Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  n=5;  tmp_tay=fabs(tay-tay_analit);   tay_n=tay;
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(10,LineSeries8,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=10; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(25,LineSeries9,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=25; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(50,LineSeries10,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=50;  tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(yars(100,LineSeries11,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=100; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(130,LineSeries12,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=130;  tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs(200,LineSeries13,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=200; tay_n=tay;
	  }

	  Form1->Memo1->Lines->Add("N оптимальное="+FloatToStrF(n,ffFixed,10,0));

	nrs(n,LineSeries10,1);

}

else

{

LineSeries1->Clear();
LineSeries2->Clear();
LineSeries3->Clear();
LineSeries4->Clear();
LineSeries5->Clear();
LineSeries7->Clear();
LineSeries8->Clear();
LineSeries9->Clear();
LineSeries10->Clear();
LineSeries11->Clear();
LineSeries12->Clear();
LineSeries13->Clear();

Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs2(5,LineSeries7,0),ffFixed,10,0)+" c");
 Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  n=5;  tmp_tay=fabs(tay-tay_analit);   tay_n=tay;
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs2(10,LineSeries8,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=10; tay_n=tay;
	  }
	  Form1->Memo1->Lines->Add("tay="+FloatToStrF(nrs2(25,LineSeries9,0),ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("tay-tay_analit="+FloatToStrF(tay-tay_analit,ffFixed,10,1)+" c");
	  Form1->Memo1->Lines->Add("");
	  if (fabs(tay-tay_analit)<tmp_tay-tt) {
		  tmp_tay=fabs(tay-tay_analit); n=25; tay_n=tay;
	  }

	  Form1->Memo1->Lines->Add("N оптимальное="+FloatToStrF(n,ffFixed,10,0));

	  nrs2(n,Series10,1);
	  }

}

//---------------------------------------------------------------------------


double yars2(int n,TLineSeries *S,bool vis)
{
   double tmp, hy;
	  int ii=0, count;

    t2=new double* [n+1];
 t2_prev=new double* [n+1];

 for (int i = 0; i < n+1; i++) {
 t2[i]=new double[n+1];
 t2_prev[i]=new double[n+1];
 for (int j = 0; j < n+1; j++) {
   t2[i][j]=tnach;
   t2_prev[i][j]=t2[i][j];
 }
 }

   hx=(double)d/n;
   hy=(double)d/n;
   ht=0.9*hx*hx/(4*a);

   if (!vis)
   {
	Form1->Memo1->Lines->Add("N="+FloatToStrF(n,ffFixed,3,0));
   Form1->Memo1->Lines->Add("ht="+FloatToStrF(ht,ffFixed,10,7)+" с");
	  Form1->Memo1->Lines->Add("hx="+FloatToStrF(hx,ffFixed,10,7)+" м");
	  Form1->Memo1->Lines->Add("hy="+FloatToStrF(hy,ffFixed,10,7)+" м");
   }
   else {count=(int)tay_n/ht;}

  tay=0.;
  do {

	tay+=ht;
	ii++;
	   tmp=0.;
	for (int i = 0; i < n+1; i++) {
	for (int j = 0; j < n+1; j++) {
   t2_prev[i][j]=t2[i][j];
	}
 }

	for (int i = 1; i < n; i++) {
	for (int j = 1; j < n; j++) {
	  t2[i][j]=t2_prev[i][j]*(1-2*a*ht/(hx*hx)-2*a*ht/(hy*hy))+a*ht/(hx*hx)*(t2_prev[i+1][j]+t2_prev[i-1][j])+a*ht/(hy*hy)*(t2_prev[i][j+1]+t2_prev[i][j-1]);
	}
	}

	for (int i = 0; i < n+1; i++) {
 t2[n][i]=(t2[n-1][i]+alpha*hx/l*ts)/(1+alpha*hx/l);
 t2[i][n]=(t2[i][n-1]+alpha*hy/l*ts)/(1+alpha*hy/l);
	 t2[0][i]=t2[1][i];
	 t2[i][0]=t2[i][1];
	}

		for (int i = 0; i < n+1; i++)
		{
		for (int j = 0; j < n+1; j++)
		{
		if (fabs(t2[i][j]-t2_prev[i][j])>tmp) {
		 tmp=fabs(t2[i][j]-t2_prev[i][j]);
		}
		}
		}

   if (!vis)
 S->AddXY(tay,t2[0][0],"");
  else
  {
	x=0;
	for (int i = 0; i < n+1; i++) {
	if (ii==1)
  Form1->Series1->AddXY(x,t2[0][i],"");
   else	 if (ii==count/3)
	 Form1->Series2->AddXY(x,t2[0][i],"");
  else if (ii==count/2)
	 Form1->Series11->AddXY(x,t2[0][i],"");
   else	if (ii==2*count/3)
	 Form1->Series12->AddXY(x,t2[0][i],"");
  else if (ii==count)
	 Form1->Series13->AddXY(x,t2[0][i],"");

	 x+=hx;
	}
	}

	}while(tmp>eps);

  return tay;
}



double nrs2(int n,TLineSeries *S,bool vis)
{
   double tmp,a1,b1,c1,*alfa,*beta,hy;
	int ii=0, count;

   t2=new double* [n+1];
 t2_prev=new double* [n+1];
  alfa=new double [n+1];
 beta=new double [n+1];
 for (int i = 0; i < n+1; i++) {
 t2[i]=new double[n+1];
 t2_prev[i]=new double[n+1];
 for (int j = 0; j < n+1; j++) {
   t2[i][j]=tnach;
   t2_prev[i][j]=t2[i][j];
 }
 }

   hx=(double)d/n;
   hy=(double)d/n;
   ht=0.9*hx*hx/(4*a);

  if (!vis)
   {
	Form1->Memo1->Lines->Add("N="+FloatToStrF(n,ffFixed,3,0));
   Form1->Memo1->Lines->Add("ht="+FloatToStrF(ht,ffFixed,10,7)+" с");
	  Form1->Memo1->Lines->Add("hx="+FloatToStrF(hx,ffFixed,10,7)+" м");
	  Form1->Memo1->Lines->Add("hy="+FloatToStrF(hy,ffFixed,10,7)+" м");
   }
   else {count=(int)tay_n/ht;}


  tay=0.;

  do {

	tay+=ht;
	ii++;
	   tmp=0.;

		for (int i = 0; i < n+1; i++) {
	for (int j = 0; j < n+1; j++) {
   t2_prev[i][j]=t2[i][j];
	}
 }


	for (int j = 0; j < n+1; j++) {

	  a1=-a*ht/hx/hx;
	  c1=a1;
	  b1=1+2*a*ht/hx/hx;


	alfa[0]=0.;
 beta[0]=t2[1][j];

	for (int i = 1; i < n+1; i++) {
		alfa[i]=-a1/(b1+c1*alfa[i-1]);
		beta[i]=(t2[i][j]-c1*beta[i-1])/(b1+c1*alfa[i-1]);
		}

	t2[n][j]=(t2[n-1][j]+alpha*hx/l*ts)/(1+alpha*hx/l);

	for (int i = n-1; i > -1; i--) {
	  t2[i][j]=alfa[i]*t2[i+1][j]+beta[i];
	}

	 }


		for (int i = 0; i < n+1; i++) {

		a1=-a*ht/hy/hy;
	  c1=a1;
	  b1=1+2*a*ht/hy/hy;

	alfa[0]=0.;
 beta[0]=t2[i][1];

	for (int j = 1; j < n+1; j++) {
		alfa[j]=-a1/(b1+c1*alfa[j-1]);
		beta[j]=(t2[i][j]-c1*beta[j-1])/(b1+c1*alfa[j-1]);
		}

	t2[i][n]=(t2[i][n-1]+alpha*hy/l*ts)/(1+alpha*hy/l);

		for (int j = n-1; j > -1; j--) {
	  t2[i][j]=alfa[j]*t2[i][j+1]+beta[j];
	}

	 }

	for (int i = 0; i < n+1; i++)
		{
		for (int j = 0; j < n+1; j++)
		{
		if (fabs(t2[i][j]-t2_prev[i][j])>tmp) {
		 tmp=fabs(t2[i][j]-t2_prev[i][j]);
		}
		}
		}

		if (!vis)
 S->AddXY(tay,t2[0][0],"");
  else
  {
	x=0;
	for (int i = 0; i < n+1; i++) {
	if (ii==1)
  Form1->LineSeries1->AddXY(x,t2[n/2][i],"");
   else	 if (ii==count/3)
	 Form1->LineSeries2->AddXY(x,t2[n/2][i],"");
  else if (ii==count/2)
	 Form1->LineSeries3->AddXY(x,t2[n/2][i],"");
   else	if (ii==2*count/3)
	 Form1->LineSeries4->AddXY(x,t2[n/2][i],"");
  else if (ii==count)
	 Form1->LineSeries5->AddXY(x,t2[n/2][i],"");

	 x+=hx;
	}
	}

  }while(tmp>eps);

return tay;

}

void __fastcall TForm1::Chart3DblClick(TObject *Sender)
{
Form3->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Chart1DblClick(TObject *Sender)
{
Form2->Show();
}
//---------------------------------------------------------------------------

