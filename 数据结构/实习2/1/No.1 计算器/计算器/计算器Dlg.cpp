
// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include"��׺ת��׺������.h"
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C������Dlg �Ի���



C������Dlg::C������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, ReallResult(0),CurrentSymbol1(" ")
	, ResultFormular(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Result);
	DDX_Text(pDX, IDC_EDIT2, ResultFormular);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C������Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C������Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C������Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &C������Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C������Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &C������Dlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON18, &C������Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTONPLUS, &C������Dlg::OnBnClickedButtonplus)
	ON_BN_CLICKED(IDC_BUTTONminus, &C������Dlg::OnBnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONmultipled, &C������Dlg::OnBnClickedButtonmultipled)
	ON_BN_CLICKED(IDC_BUTTONdivided, &C������Dlg::OnBnClickedButtondivided)
	ON_BN_CLICKED(IDC_BUTTONequal, &C������Dlg::OnBnClickedButtonequal)
	ON_BN_CLICKED(IDC_BUTTON15, &C������Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &C������Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTONwithdraw, &C������Dlg::OnBnClickedButtonwithdraw)
	ON_BN_CLICKED(IDC_BUTTONdelete, &C������Dlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTONsin, &C������Dlg::OnBnClickedButtonsin)
	ON_BN_CLICKED(IDC_BUTTONcos, &C������Dlg::OnBnClickedButtoncos)
	ON_BN_CLICKED(IDC_BUTTON10, &C������Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &C������Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &C������Dlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// C������Dlg ��Ϣ�������

BOOL C������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




 /*------------------------------������С����------------------------------------------------*/
void C������Dlg::OnBnClickedButton1()
{
	CurrentSymbol1 = "1";
	if (Symbol(CurrentSymbol1))
	{
		Result += "1";
	}	
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton2()
{
	CurrentSymbol1 = "2";
	if (Symbol(CurrentSymbol1))
	{
		Result += "2";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton3()
{
	CurrentSymbol1 = "3";
	if (Symbol(CurrentSymbol1))
	{
		Result += "3";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton4()
{
	CurrentSymbol1 = "4";
	if (Symbol(CurrentSymbol1))
	{
		Result += "4";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton5()
{
	CurrentSymbol1 = "5";
	if (Symbol(CurrentSymbol1))
	{
		Result += "5";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton6()
{
	CurrentSymbol1 = "6";
	if (Symbol(CurrentSymbol1))
	{
		Result += "6";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton7()
{
	CurrentSymbol1 = "7";
	if (Symbol(CurrentSymbol1))
	{
		Result += "7";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton8()
{
	CurrentSymbol1 = "8";
	if (Symbol(CurrentSymbol1))
	{
		Result += "8";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton9()
{
	CurrentSymbol1 = "9";
	if (Symbol(CurrentSymbol1))
	{
		
		Result += "9";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton0()
{
	CurrentSymbol1 = "0";
	if (Symbol(CurrentSymbol1))
	{
		if (Result.GetLength() != 0)
		{
			CString CurrentNumber;
			CurrentNumber = Result.Right(1);

			CString zero;
			zero = "0";

			if (CurrentNumber != zero)
			{
				Result += "0";
			}
		}
		else
		{
			Result += "0";
		}

	}

	
	UpdateData(false);
}



void C������Dlg::OnBnClickedButton18()  //С����
{
	CurrentSymbol1 = ".";



	if (Symbol(CurrentSymbol1))
	{
		if (CurrentPoint != CurrentSymbol1)   // ���С���㲻���ڣ�����ӣ�
		{
			Result += ".";
		}
		
	}
	CurrentPoint = ".";
	UpdateData(false);
}


/*------------------------------�����--------------------------------------------*/
void C������Dlg::OnBnClickedButtonplus()
{
	CurrentPoint = "";
	CurrentSymbol1 = "+";
	if (Symbol(CurrentSymbol1))
	{
		Result += "+";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButtonminus()
{	
	CurrentPoint = "";
	CurrentSymbol1 = "-";
	if (Symbol(CurrentSymbol1))
	{
		Result += "-";
	}
	
	UpdateData(false);
}
void C������Dlg::OnBnClickedButtonmultipled()
{
	CurrentPoint = "";
	CurrentSymbol1 = "*";
	if (Symbol(CurrentSymbol1))
	{
		Result += "*";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButtondivided()
{
	CurrentPoint = "";
	CurrentSymbol1 = "/";
	if (Symbol(CurrentSymbol1))
	{
		Result += "/";
	}	
	UpdateData(false);
}
void C������Dlg::OnBnClickedButtonsin() //sin
{
	CurrentPoint = "";
	CurrentSymbol1 = "sin";
	if (Symbol(CurrentSymbol1))
	{
		Result += "sin(";
		Brackets++;
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButtoncos()  //cos
{
	CurrentPoint = "";
	CurrentSymbol1 = "cos";
	if (Symbol(CurrentSymbol1))
	{
		Result += "cos(";
		Brackets++;
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton10()    //����
{
	CurrentPoint = "";
	CurrentSymbol1 = "sin";
	if (Symbol(CurrentSymbol1))
	{
		Result += "(-";
		Brackets++;
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton11()    //pow
{
	CurrentPoint = "";
	CurrentSymbol1 = "pow";
	if (Symbol(CurrentSymbol1))
	{
		Result += "^";
	}
	UpdateData(false);
}
void C������Dlg::OnBnClickedButton12()     //ȡ��
{
	CurrentPoint = "";
	CurrentSymbol1 = "%";
	if (Symbol(CurrentSymbol1))
	{
		Result += "%";
	}
	UpdateData(false);
}


///////////////////////////////////////////////////

void C������Dlg::OnBnClickedButton15()        //ǰ����
{
	CurrentPoint = "";
	CurrentSymbol1 = "(";
	if (Symbol(CurrentSymbol1))
	{
		Brackets++; 

		Result += "(";
		CurrentSymbol1 = "(";
		UpdateData(false);
	}
	
}
void C������Dlg::OnBnClickedButton16()       //������
{
	CurrentPoint = "";
	CurrentSymbol1 = ")";
	if (Symbol(CurrentSymbol1))
	{
		if (Brackets != 0)
		{
			Brackets--;

			Result += ")";
			CurrentSymbol1 = ")";
		}
	}
	
	
	UpdateData(false);
}




/*-----------------------------���ڣ�����------------------------------------*/
void C������Dlg::OnBnClickedButtonequal()
{
	UpdateData(true);
	ResultFormular = Result;         //�༭����빫ʽ


	CString Negative;
	Negative = "(-";
	int negative=Result.Find(Negative);

	CString zero;
	zero = "0";
	while (negative != -1)
	{
		Result.Insert(negative+1, zero);
		negative = Result.Find(Negative);
	}






	///////////////////////////////////////////////////////////////////////
	CString SIN;
	CString COS;
	CString LeftBrackets;
	CString RightBrackets;
	SIN = "sin(";
	COS = "cos(";
	LeftBrackets = "(";
	RightBrackets = ")";

	int EndPosition;
	int SinPosition=Result.Find(SIN);
	
	int Sinbrackets;
	int Cosbrackets;

	while (SinPosition != -1)
	{
		Sinbrackets = 1;
		for (int i = SinPosition + 4;; i++)
		{
			if (Result[i] == LeftBrackets)
			{
				Sinbrackets++;
			}
			else if (Result[i] == RightBrackets)
			{
				Sinbrackets--;
			}

			if (Sinbrackets == 0)
			{
				EndPosition = i;
				break;
			}
		}

		CString SinResult;
		int length= EndPosition- SinPosition - 4;
		SinResult = Result.Mid(SinPosition + 4, length);


		Calculater Sincalculater;            //����
		CString SinFormula = SinResult + '#';    //ת����ʽ
		double FormulaResult = 0;         //���

		int sinlen = WideCharToMultiByte(CP_ACP, 0, SinFormula, -1, NULL, 0, NULL, NULL);   //CStringת
		char *SinFormular = new char[sinlen + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, SinFormula, -1, SinFormular, sinlen, NULL, NULL);       //char*

		Sincalculater.LeadingIn(SinFormular);                                               //���롣	
		FormulaResult = Sincalculater.Transform();                                       //���㣬�ó����
		FormulaResult = sin(FormulaResult*acos(-1.0) /180);

		CString SINresult;
		SINresult=Sincalculater.DoubleToCString(FormulaResult);

		CString SIN;
		SIN = "sin(";
		SinResult = SIN + SinResult+ ')';
		Result.Replace(SinResult, SINresult);

		SinPosition = Result.Find(SIN);
	}
	

	int CosPosition = Result.Find(COS);
	while (CosPosition != -1)
	{
		Cosbrackets = 1;
		for (int i = CosPosition + 4;; i++)
		{
			if (Result[i] == LeftBrackets)
			{
				Cosbrackets++;
			}
			else if (Result[i] == RightBrackets)
			{
				Cosbrackets--;
			}

			if (Cosbrackets == 0)
			{
				EndPosition = i;
				break;
			}
		}

		CString CosResult;
		CosResult = Result.Mid(CosPosition + 4, EndPosition - CosPosition -4 );


		Calculater Coscalculater;            //����
		CString CosFormula = CosResult + '#';    //ת����ʽ
		double FormulaResult = 0;         //���

		int sinlen = WideCharToMultiByte(CP_ACP, 0, CosFormula, -1, NULL, 0, NULL, NULL);   //CStringת
		char *CosFormular = new char[sinlen + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, CosFormula, -1, CosFormular, sinlen, NULL, NULL);       //char*

		Coscalculater.LeadingIn(CosFormular);                                               //���롣	
		FormulaResult = Coscalculater.Transform();                                       //���㣬�ó����
		FormulaResult = cos(FormulaResult*acos(-1.0) / 180);

		CString COSresult;
		COSresult = Coscalculater.DoubleToCString(FormulaResult);
		CString COS;
		COS = "cos(";
		CosResult = COS + CosResult + ')';
		Result.Replace(CosResult, COSresult);

		CosPosition = Result.Find(COS);	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////






	Calculater calculater;            //����
	CString Formula= Result + '#';    //ת����ʽ
	double FormulaResult = 0;         //���

	int len = WideCharToMultiByte(CP_ACP, 0, Formula, -1, NULL, 0, NULL, NULL);   //CStringת
	char *Formular = new char[len + 1];                                           //
	WideCharToMultiByte(CP_ACP, 0, Formula, -1, Formular, len, NULL, NULL);       //char*


	calculater.LeadingIn(Formular);                                               //���롣	
	FormulaResult = calculater.Transform();                                       //���㣬�ó����
	
	Result =calculater.DoubleToCString(FormulaResult);                            //�༭����ʾ��

	UpdateData(false);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
void C������Dlg::OnBnClickedButtonwithdraw()           //����һλ
{
	CString point;
	CString bracketsform;
	CString bracketslatter;
	point = ".";
	bracketsform = "(";
	bracketslatter = ")";


	CString DeleteSymbol;
	DeleteSymbol=Result.Right(1);

	CString DeleteSymbolSinCos;


	DeleteSymbolSinCos = Result.Right(4);
	CString sinbracket;
	CString cosbracket;
	sinbracket = "sin(";
	cosbracket = "cos(";




	if (DeleteSymbolSinCos == sinbracket)
	{
		Result.Delete(Result.GetLength() - 4, 4);
	}

	else if (DeleteSymbolSinCos == cosbracket)
	{
		Result.Delete(Result.GetLength() - 4, 4);
	}

	else
	{
		if (DeleteSymbol == bracketslatter)
		{
			Brackets++;
		}
		else if (DeleteSymbol == bracketsform)
		{
			Brackets--;
		}
		else if (DeleteSymbol == point)
		{
			CurrentPoint = " ";
		}
		Result.Delete(Result.GetLength() - 1, 1);
	}
	
		





	UpdateData(false);
}

void C������Dlg::OnBnClickedButtondelete()   //���
{
	Result = "";
	ResultFormular = "";
	Brackets = 0;
	CurrentPoint = "";
	CurrentSymbol1 = "";

	UpdateData(false);

}


