// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "����.h"
#include<iostream>

#include <fstream>
#include <sstream>

#include<Windows.h>

using namespace std;


void FareySeries(int number)
{
	List Series;
	Series.Insert(1, 0, 1);
	Series.Insert(2, 1, 1);

	Node *Former = Series.GetFirstNode()->link;
	Node *Latter = Former->link;

	int NewNumerator = 0;
	int NewDenominator = 0;

	if(number>1)
	{

		while (Former->link != NULL)
		{
			NewNumerator = (Former->Numerator) + (Latter->Numerator);
			NewDenominator = (Former->Denominator) + (Latter->Denominator);

			if (NewDenominator <= number)
			{
				Series.Insert(Former, NewNumerator, NewDenominator);
				Former = Former;
				Latter = Former->link;
				//cout << Latter->Denominator << endl;
			}
			else
			{
				Former = Latter;
				Latter = Former->link;
			}
		}
		
		
	}
	
	fstream File("FareySeries.txt", ios_base::out);

	Node *current= Series.GetFirstNode()->link;
	while (current != NULL)
	{
		File << current->Numerator <<"/"<< current->Denominator <<" ";
		current = current->link;
	}
	
	File.close();

	ShellExecute(NULL, L"open", L"FareySeries.txt", NULL, NULL, SW_SHOWNORMAL); //���ļ�
}


int main()
{
	int number;
	cin >> number;

	if (number > 0)
	{
		FareySeries(number);
	}
	

    return 0;
}

