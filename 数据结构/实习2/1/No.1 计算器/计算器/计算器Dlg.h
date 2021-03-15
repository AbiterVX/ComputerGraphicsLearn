
// ������Dlg.h : ͷ�ļ�
//

#pragma once

#include"����ջ.h"
#include<string>
#include<sstream>
#include<cstring>
#include"��׺ת��׺������.h"
#include<math.h>
#include<cmath>



// C������Dlg �Ի���
class C������Dlg : public CDialogEx
{
// ����
public:
	C������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString Result;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButtonplus();
	afx_msg void OnBnClickedButtonminus();
	afx_msg void OnBnClickedButtonmultipled();
	afx_msg void OnBnClickedButtondivided();
	afx_msg void OnBnClickedButtonequal();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	double ReallResult;
	afx_msg void OnBnClickedButtonwithdraw();
	afx_msg void OnBnClickedButtondelete();

	afx_msg void OnBnClickedButtonsin();
	afx_msg void OnBnClickedButtoncos();
	CString ResultFormular;


	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();





	int Brackets=0;                        //��������
	CString CurrentSymbol1;                //��ǰ�ַ�
	CString CurrentPoint;                  //С����


	bool Symbol(CString CurrentSymbol)
	{
		
		CString PreviousSymbol = Result.Right(1);

		CString plus;
		CString minus;
		CString multipled;
		CString divided;
		CString point;
		CString bracketsform;
		CString bracketslatter;
		CString sin;
		CString cos;
		CString tan;
		CString pow;
		CString remainder;
		plus = "+";
		minus = "-";
		multipled = "*";
		divided = "/";
		point = ".";
		bracketsform = "(";
		bracketslatter = ")";
		sin = "sin";
		cos = "cos";
		tan = "tan";
		pow = "pow";
		remainder = "%";


		int PreviousOperator = 0;
		if (PreviousSymbol == plus || PreviousSymbol == minus || PreviousSymbol == multipled 
			|| PreviousSymbol == divided || PreviousSymbol == pow || PreviousSymbol == remainder)
		{
			PreviousOperator = 2;
		}
		else if (PreviousSymbol == sin || PreviousSymbol == cos || PreviousSymbol == tan)
		{
			PreviousOperator = 1;
		}
		else if (PreviousSymbol == point)
		{
			PreviousOperator = 5;
		}
		else if (PreviousSymbol == bracketsform)
		{
			PreviousOperator = 3;
		}
		else if (PreviousSymbol == bracketslatter)
		{
			PreviousOperator = 4;
		}
		else if (PreviousSymbol == "")
		{
			PreviousOperator = 6;
		}


		int CurrentOperator = 0;
		if (CurrentSymbol == plus || CurrentSymbol == minus || CurrentSymbol == multipled 
			|| CurrentSymbol == divided || CurrentSymbol == pow || CurrentSymbol == remainder)
		{
			CurrentOperator = 2;
		}
		else if (CurrentSymbol == sin || CurrentSymbol == cos || CurrentSymbol == tan)
		{
			CurrentOperator = 1;
		}
		else if (CurrentSymbol == point)
		{
			CurrentOperator = 5;
		}
		else if (CurrentSymbol == bracketsform)
		{
			CurrentOperator = 3;
		}
		else if (CurrentSymbol == bracketslatter)
		{
			CurrentOperator = 4;
		}










		if (PreviousOperator == 2)                             // ֮ǰ���ַ�Ϊ��Ԫ������
		{
			if (CurrentOperator == 2)                          //��ǰҲΪ��Ԫ�������򸲸�
			{
				Result = Result.Left(Result.GetLength() - 1);
			}
			else if (CurrentOperator == 5)                    //��ǰΪС���㣬����Ч
			{
				return false;
			}
			else if (CurrentOperator == 4)                     //��ǰΪ�����ţ�����Ч
			{
				return false;
			}
		}
		else if (PreviousOperator == 5)                          //֮ǰ���ַ�ΪС����,�����ǰ��Ϊ��������Ч
		{
			if (CurrentOperator !=0)
			{
				return false;
			}
		}

		else if (PreviousOperator == 3)                          //֮ǰ���ַ�Ϊǰ����,�����ǰΪ ��Ԫ�������С���� ����Ч
		{
			if (CurrentOperator == 4)
			{
				Result += "0";
				return true;
			}
			if (CurrentOperator == 2 || CurrentOperator == 5)
			{
				return false;
			}
		}

		else if (PreviousOperator == 4)                          //֮ǰ���ַ�Ϊ������,�����ǰ��Ϊ˫Ŀ���������Ч
		{
			if (CurrentOperator == 4)
			{
				return true;
			}
			if (CurrentOperator != 2 )
			{
				return false;
			}
		}

		else if (PreviousOperator == 1)                          //֮ǰ���ַ�ΪһԪ�����,�����ǰ��Ϊ ���ֻ������� ����Ч
		{                                                        //
			if (CurrentOperator == 0 || CurrentOperator == 3)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (PreviousOperator == 0)                          //֮ǰ���ַ�Ϊ����,�����ǰ��Ϊ ��Ԫ�������С��������� ����Ч
		{      
			if (CurrentOperator == 0|| CurrentOperator == 2  || CurrentOperator == 5)
			{
				return true;
			}
			else if (CurrentOperator==4 && Brackets !=0)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
		else if (PreviousOperator == 6)
		{
			if (CurrentOperator == 0 || CurrentOperator == 1)
			{
				return true;
			}
			
		}


		return true;
	}



	/*void UnaryOperator()
	{
		CString sin1;           
		CString cos1;
		CString negative1;
		CString bracketsform1;
		CString bracketslatter1;
		sin1 = "sin";
		cos1 = "cos";
		negative1 = "negative";
		bracketsform1 = "(";
		bracketslatter1 = ")";

		CString UnaryOperator;
		int SIN;
		int COS;
		int NEGATIVE;
		SIN = UnaryOperator.Find(sin1);
		COS = UnaryOperator.Find(cos1);
		NEGATIVE = UnaryOperator.Find(negative1);



		while (SIN != -1)
		{
			CString SinFormular;
			
			int BracketsNumber = 1;
			for (int i = SIN+4; ; i++)
			{
				if (Result[i] == bracketslatter1)
				{
					BracketsNumber--;
				}
				else if (Result[i] == bracketsform1)
				{
					BracketsNumber++;
				}


				if (BracketsNumber == 0) 
				{
					SinFormular=SinFormular.Mid(SIN + 3, i - SIN - 3);
					break;
				}
			}

			Calculater calculater;

			int len = WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, NULL, 0, NULL, NULL);   //CStringת
			char *sinFormular = new char[len + 1];                                           //
			WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, sinFormular, len, NULL, NULL);       //char*
			calculater.LeadingIn(sinFormular);
			double sinresult= sin( calculater.Transform() );

			
			SinFormular = sin1 + SinFormular;
			Result.Trim(SinFormular);

			Result.Insert(SIN, );

		}
		while (COS != -1)
		{
			CString SinFormular;

			int BracketsNumber = 1;
			for (int i = COS + 4; ; i++)
			{
				if (Result[i] == bracketslatter1)
				{
					BracketsNumber--;
				}
				else if (Result[i] == bracketsform1)
				{
					BracketsNumber++;
				}


				if (BracketsNumber == 0)
				{
					SinFormular = SinFormular.Mid(COS + 3, i - COS - 3);
					break;
				}
			}

			Calculater calculater;

			int len = WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, NULL, 0, NULL, NULL);   //CStringת
			char *sinFormular = new char[len + 1];                                           //
			WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, sinFormular, len, NULL, NULL);       //char*
			calculater.LeadingIn(sinFormular);
			double sinresult = sin(calculater.Transform());


			SinFormular = sin1 + SinFormular;
			Result.Trim(SinFormular);

			Result.Insert(SIN, );

		}
		while (NEGATIVE != -1)
		{
			CString SinFormular;

			int BracketsNumber = 1;
			for (int i = COS + 4; ; i++)
			{
				if (Result[i] == bracketslatter1)
				{
					BracketsNumber--;
				}
				else if (Result[i] == bracketsform1)
				{
					BracketsNumber++;
				}


				if (BracketsNumber == 0)
				{
					SinFormular = SinFormular.Mid(SIN + 3, i - SIN - 3);
					break;
				}
			}

			Calculater calculater;

			int len = WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, NULL, 0, NULL, NULL);   //CStringת
			char *sinFormular = new char[len + 1];                                           //
			WideCharToMultiByte(CP_ACP, 0, SinFormular, -1, sinFormular, len, NULL, NULL);       //char*
			calculater.LeadingIn(sinFormular);
			double sinresult = sin(calculater.Transform());


			SinFormular = sin1 + SinFormular;
			Result.Trim(SinFormular);

			Result.Insert(SIN, );

		}
	}
	*/
	
};
