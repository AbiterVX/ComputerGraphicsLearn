#pragma once


#include "����ջ.h"
#include<math.h>
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;




class Calculater            //����
{
protected:
	char *InfixExression = NULL;           //��׺���ʽ
	Stack<char> Symbols;                 //����ջ 
	Stack<double> OrderNumbers;          //ջ������ 
										 //Stack<char> OrderSymbols;            //����ջ 
										 //Stack<int> OrderList;                //����
	double Result = 0;                   //�����ֵ
	int Form[9][9] = { { 1,1,0,0,0,1,1,0,0 },
	                   { 1,1,0,0,0,1,1,0,0 },
	                   { 1,1,1,1,0,1,1,0,0 },
	                   { 1,1,1,1,0,1,1,0,0 },
	                   { 0,0,0,0,0,2,4,0,0 },
	                   { 1,1,1,1,4,1,1,1,0 },
	                   { 0,0,0,0,0,4,3,0,0 },
					   { 1,1,1,1,0,1,1,1,0 },
					   { 1,1,1,1,0,1,1,1,1 }
	                  };               //����ı��
public:
	Calculater()                      //Ĭ�Ϲ��� 
	{
		Symbols.InsertFirst('#');
	}
	void LeadingIn(char* infixExression)     //������׺���ʽ
	{
		InfixExression = infixExression;
	}
	bool IfSymbol(char CHAR)
	{
		if (CHAR == '(' || CHAR == ')' || CHAR == '#' || CHAR == '+' || CHAR == '-'
			|| CHAR == '*' || CHAR == '/' || CHAR == '^' || CHAR == '%')
		{
			return true;
		}
		else
		{
			return false;
		}
	}




	int TransformSymbol(char symbol)
	{
		int Level = 0;
		switch (symbol)
		{
		case '+':
			Level = 0;
			break;
		case '-':
			Level = 1;
			break;
		case '*':
			Level = 2;
			break;
		case '/':
			Level = 3;
			break;
		case '(':
			Level = 4;
			break;
		case ')':
			Level = 5;
			break;
		case '#':
			Level = 6;
			break;
		case '^':
			Level = 7;
			break;
		case '%':
			Level = 8;
			break;

		}
		

		return Level;
	}



	int IfPrior(char symbol1, char symbol2)   //�жϷ������ȼ�
	{
		int level = Form[TransformSymbol(symbol1)][TransformSymbol(symbol2)];
		return level;
	}




	double Transform()                       //��׺ת��׺
	{

		double TransformNumber = 0;      //С��
		char PreviousSymbol = '#';       //��һ���������ʵ��С������
		int DecimalTimes = 0;            //С��λ��

		for (int i = 0;; i++)
		{			
			if (InfixExression[i] != '\0')                                                   //���û������
			{
				if (48 <= InfixExression[i] && InfixExression[i] <= 57)                      //����
				{
					double number = InfixExression[i] - 48;                                  //ascll��������

					if (PreviousSymbol != '.')                                               //�������С��
					{
						TransformNumber *= 10;                                               //�����������
						TransformNumber += number;                                           //��ɶ�λ��
					}
					else                                                                     //�����С��
					{
						DecimalTimes++;                                                      //С��λ������
						TransformNumber = TransformNumber + number * pow(0.1, DecimalTimes); //����С��λ���
					}

					if (IfSymbol(InfixExression[i + 1]) == 1)                              //�����һλΪ���ţ���������������ϣ����������
					{
						OrderNumbers.InsertFirst(TransformNumber);                           //���뵽����ջ
																							 //OrderList.InsertLast(0);                                             //������λ�ü�Ϊ����0
						TransformNumber = 0;                                                 //���㣬����֮�����
						DecimalTimes = 0;
					}
				}

				else if (InfixExression[i] == '.')                                           //���ΪС���㣬��ǰ���Ÿ�ΪС����
				{
					PreviousSymbol = '.';
				}


				else if (IfSymbol(InfixExression[i]))                                        //���Ϊ�����
				{
					PreviousSymbol = InfixExression[i];                                      //��ǰ���Ÿ�Ϊ�����
					if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 0)                 //������ȼ�С����������ջ��
					{
						Symbols.InsertFirst(InfixExression[i]);                              //����
					}

					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 1)           //������ȼ�����
					{
						double Number2 = OrderNumbers.GetTopData();
						OrderNumbers.RemoveFirst();
						double Number1 = OrderNumbers.GetTopData();
						OrderNumbers.RemoveFirst();


						double result = CalculateNumber(Number1, Number2, Symbols.GetTopData());
						OrderNumbers.InsertFirst(result);

						Symbols.RemoveFirst();                                               //�Ƴ�����ջջ��Ԫ��

						i--;
					}



					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 2)         //���������������
					{
						Symbols.InsertFirst(InfixExression[i]);                             //�������������
						Symbols.RemoveFirst();
						Symbols.RemoveFirst();
					}
					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 3)         //�������#�����������
					{
						//cout << "������" << endl;
						break;
					}
					else                                                                    //��ʽ��ʽ����
					{
						cout << "����" << endl;
						break;
					}
				}

				if (InfixExression[i] == '#')
				{
					i--;
				}

			}

			else  //���������
			{
				break;
			}
		}

		Result = OrderNumbers.GetTopData();	
		return Result;
	}






	double CalculateNumber(double Number1, double Number2, char Symbol)
	{
		double result = 0;
		switch (Symbol)
		{
		case '+':
			result = Number1 + Number2;
			break;
		case '-':
			result = Number1 - Number2;
			break;
		case '*':
			result = Number1 * Number2;
			break;
		case '/':
			result = Number1 / Number2;
			break;
		case '^':
			result = pow(Number1,Number2);
			break;
		case '%':
			result = (int)Number1% (int)Number2;
			break;
		}

		return result;
	}

	



	char* CStringToCHAR(CString cstring) {          
		string STRING;
		stringstream ss;
		ss << cstring;
		ss >> STRING;
		char * CHAR = (char*)STRING.data();
		return CHAR;
	}

	CString DoubleToCString(double number)
	{
		CString CSTRING;
		CSTRING.Format(_T("%1f"), number);
		return CSTRING;
	}

	string CStringToString(CString cstring)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, cstring, -1, NULL, 0, NULL, NULL);   //CStringתchar*
		char *Formular = new char[len + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, cstring, -1, Formular, len, NULL, NULL);       //

		string STRING;
		STRING = Formular;
		return STRING;
	}

};


