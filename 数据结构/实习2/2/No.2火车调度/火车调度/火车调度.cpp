// �𳵵���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"�����������.h"
#include"�������.h"
#include <iostream>
#include<string>
#include<sstream>

#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;

class TrainDispatching
{
private:
	Queue Train;;          //������
	Queue *AllRailway;     //���
	int TrainNumber;       //�𳵸���
	int RailwayNumber;     //�������
	int length;            //����
	
public:
	TrainDispatching()
	{
		TrainNumber = 0;
		RailwayNumber = 0;
		length = 0;
	}
	TrainDispatching(int N)
	{
		TrainNumber = N;
		AllRailway = new Queue[TrainNumber];
	}
	void LeadingIn(int *TRAIN)
	{
		for (int i = 0; i <TrainNumber; i++)
		{
			Train.Insert(TRAIN[i]);
		}
		
	}
	void LeadingIn(char *TRAIN)
	{			
		int Number=0;
		for (int i = 0;; i++)
		{
			if (TRAIN[i] != ',' &&TRAIN[i] != '\0')
			{
				Number *= 10;
				Number += TRAIN[i] -48;
			}
			else if (TRAIN[i] == ',')
			{
				Train.Insert(Number);
				length++;
				Number = 0;
			}	
			else if (TRAIN[i] == '\0')
			{
				Train.Insert(Number);
				length++;
				Number = 0;
				break;
			}
		}	
	}
	void Calculate()
	{
		Node *current = Train.GetFirst()->link;                             //ָ��ǰ�����ָ��	                              
		int CurrentTrain;                                                   //��ǰ������
                               
		while(current != NULL)
		{

			CurrentTrain = current->Data;                                   //�õ����
			//cout << CurrentTrain << endl;
			for (int i = 0;; i++)                                           //������
			{
				if (AllRailway[i].GetFirst() != NULL)
				{
					if (AllRailway[i].GetLastData() < CurrentTrain)
					{
						AllRailway[i].Insert(CurrentTrain);                //����С�Ĳ�ֵ�Ĺ��֮�����
						//cout << i << "," << CurrentTrain << endl;
						break;
					}				
				}
				else
				{
					AllRailway[i+1].Insert(CurrentTrain);                  //����С�Ĳ�ֵ�Ĺ��֮�����
					break;
				}			
			}	

			current = current->link;                                        //ָ����һ������
		}
		
	}

	void OutPut()
	{

		fstream File("Train.txt", ios_base::out);

		File << "ͼʾ" << endl;
		Node *current;
		for (int i = 0; i < TrainNumber; i++)
		{
			if (AllRailway[i].GetFirst()->link != NULL)
			{
				current = AllRailway[i].GetFirst()->link;
				File << i + 1 << ": ";

				for (int j = 0;; j++)
				{
					if (current != NULL)
					{
						File << current->Data << " ";
						current = current->link;
					}
					else
					{
						File << endl;
						break;
					}
				}
			}
			else
			{
				break;
			}
		
		}
		File << endl;





		int OutputNumber = 1;
		while (OutputNumber != TrainNumber+1)
		{
			for (int i = 0;; i++)
			{
				if (AllRailway[i].GetFirst()->link != NULL)
				{
					if (AllRailway[i].GetTopData() == OutputNumber)
					{
						File << "���Ϊ�� " << OutputNumber <<" �ĳ���ӵ� "<<i+1<<" ��������!" << endl;
						OutputNumber++;
						AllRailway[i].Remove();
					}
				}
				else
				{
					break;
				}
			}
		}
	
		File.close();
		ShellExecute(NULL, L"open", L"Train.txt", NULL, NULL, SW_SHOWNORMAL);
	}


	char* StringToCHAR(string String)
	{
		char * CHAR = (char*)String.data();
		return CHAR;
	}
};



int main()
{
	cout << "����𳵳������" << endl;
	int N;
	cin >> N;

	TrainDispatching train(N);
	train.LeadingIn( RandomSequence(N) );
	//train.LeadingIn("3,4,6,1,11,13,5,7,19,8,12,2,9,16,10,14,17,18,20,15");

	train.Calculate();
	train.OutPut();
    return 0;
}







/*string STRING;
cout << "����" << endl;
cin >> STRING;
char* TrainQueue = train.StringToCHAR(STRING);*/
