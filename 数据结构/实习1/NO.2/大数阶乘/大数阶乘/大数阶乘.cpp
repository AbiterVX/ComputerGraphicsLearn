// �����׳�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include"����.h"

#include<Windows.h>

using namespace std;




void Factorial(int number) //�����׳�
{
	List Result;                                                 //���
	Result.Insert(0, 1);                                         //��ʼ�ڵ�
	Node *current = Result.GetFirstNode()->link;                 //���õ�ǰ�ڵ����һ���ڵ�λ��һ��
	int add = 0;                                                 //��λ	

	for (int i = 1; i <= number; i++)                            //�׳�
	{
		while (current != Result.GetLastNode())                                  //���ڵ����� ���г˷�
		{
			(current->Data) *= i;
			current = current->link;
		}
		current = Result.GetFirstNode()->link;                    //���õ�ǰ�ڵ����һ���ڵ�λ��һ��

		while (current != Result.GetLastNode())                                  //ÿһ��������˺����ݽ��й淶����ÿ���ڵ�����Ϊ3λ
		{
			if (current->link == Result.GetLastNode() && current->Data >= 1000)  //������λ����3λ������ǰ����һλ
			{
				Node *NewNode = new Node(0);
				current->link = NewNode;
				NewNode->link = Result.GetLastNode();
				Result.GetLastNode()->BackLink = NewNode;
				NewNode->BackLink = current;
				
			}

			add = (current->Data) / 1000;                           //��λ
			current->Data %= 1000;
			current = current->link;
			if (current != Result.GetLastNode())                                 //���λ��λ
			{
				(current->Data) += add;
			}

		}
		current = Result.GetFirstNode()->link;                     //���õ�ǰ�ڵ����һ���ڵ�λ��һ��
	}


	if (current->Data >= 1000)                                   //���λ��λ��
	{
		Node *NewNode = new Node;
		current->link = NewNode;
		add = (current->Data) % 1000;
		current->Data % 1000;
		current = current->link;
		current += add;
	}

	//Result.Inverse(Result.GetFirstNode());

	Node *node = Result.GetLastNode()->BackLink;
	int i = 0;



	fstream File("Factorial.txt", ios_base::out);

	while (node != Result.GetFirstNode() )
	{
		if (i>0)
		{
			if (node->Data >= 100)
			{
				File << node->Data << " ";
			}
			else if (10 <= node->Data && node->Data < 100)
			{
				File << 0 << node->Data << " ";
			}
			else if (0 <= node->Data && node->Data < 10)
			{
				File << 0 << 0 << node->Data << " ";
			}
		}
		else
		{
			File << node->Data << " ";
			i = 1;
		}

		node = node->BackLink;
	}


	File.close();

	ShellExecute(NULL, L"open", L"Factorial.txt", NULL, NULL, SW_SHOWNORMAL); //���ļ�
																			  //Result.FactorialOutPutReverse(Result.GetFirstNode()->link);  //����ݹ����
}





int main()
{
	int number;
	cin >> number;
	Factorial(number);

    return 0;
}

/*
Result.Inverse(Result.GetFirstNode());
Node *node = Result.GetFirstNode()->link;
int i = 0;




while (node != NULL)
{
if (i>0)
{
if (node->Data >= 100)
{
File << node->Data << " ";
}
else if (10 <= node->Data && node->Data < 100)
{
File << 0 << node->Data << " ";
}
else if (0 <= node->Data && node->Data < 10)
{
File << 0 << 0 << node->Data << " ";
}
}
else
{
File << node->Data << " ";
i = 1;
}

node = node->link;
}
*/