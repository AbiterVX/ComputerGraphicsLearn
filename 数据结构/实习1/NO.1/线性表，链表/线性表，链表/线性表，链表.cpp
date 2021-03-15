// ���Ա�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include<Windows.h>
using namespace std;

template <class T>
struct Node
{
	T Data;            //����
	Node<T> *link;          //����

	Node()               //Ĭ�Ϲ���
	{		
		link = NULL;
	}
	Node(T data)       //���첢д������
	{
		Data = data;
		link = NULL;
	}

};


template <class T>
class List
{
protected:
	Node<T> *first;                //��ʼ�ڵ�
public:
	List()   
	{
		first = new Node<T>(0);
		first->link = NULL;
	}
	List(T data)
	{		
		first = new Node(data);
	}

	void Empty()                   //���
	{
		Node<int> *current=NULL;

		if (first->link ==NULL)
		{
			
			return;
		}
		while (first->link !=NULL)
		{	
            
			current = first->link;
			//cout << current->Data << endl;
			first->link = current->link;
			
			delete current;
				
		}
		
	}

	~List()                         //����
	{
		Empty();
		delete first;
	}


	int Length()                     //������
	{
		int length = 0;              //��ʼ����
		Node *current;               //��ǰ�ڵ�
		current = first->link;       //��ʼ�ڵ��뵱ǰ����λ��һ��
		while (current != NULL)      //�жϳ����Ƿ����
		{
			current = current->link; //ָ����һ���ڵ�
			length++;                //�Լ�
		}
		return length;
	} 

	bool Insert(int position, T data)                 //�ڵ�i��Ԫ�غ����
	{
		Node<T> *current = first;                     //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣

		for(int i=1;i<position;i++)                   //������ǰλ�á�ָ��Ҫ��λ��
		{
			if (current != NULL)
			{
				current = current->link;              //ָ����һ���ڵ�
			}
		}

		if (current == NULL)                          //�������λ�ô��������ȣ�������Ϊ��
		{
			return false;
		}
		else                                          //����Ϊ�գ����߲���λ��С��������
		{
			Node<T> *NewNode = new Node<T>(data);     //�����µĽڵ� ,��������  
			NewNode->link = current->link;            //�������֮������������������
			current->link = NewNode;                  //�������֮ǰ�����������������
		}
		
		return true;
	}

	bool Remove(int position)                         //ɾ����i��Ԫ��
	{
		Node<T> *current = first;                     //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣
		Node<T> *DeleteNode;
		for (int i = 1; i<position; i++)              //������ǰλ�á�ָ��Ҫ��λ��
		{
			if (current != NULL)
			{
				current = current->link;              //ָ����һ���ڵ�
			}
		}

		if (current == NULL)                          //���ɾ��λ�ô���������
		{
			return false;
		}
		else                                          //ɾ��λ��С��������
		{
			DeleteNode = current->link;
			current->link=current->link->link;        //��ɾ����֮���������֮ǰ�������������	  
			delete DeleteNode;
		}
		return true;
	} 

	T GetData(int position)                           //�õ�ĳ�������
	{
		Node<T> *current = first;                     //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣

		for (int i = 1; i<=position; i++)             //������ǰλ�á�ָ��Ҫ��λ��
		{
			if (current != NULL)
			{
				current = current->link;              //ָ����һ���ڵ�
			}
		}

		return current->Data;
	}


	bool Combine(List &AnotherList)                    //����˳������ϲ�
	{
		Node<T> *current1 = first;                         //��һ������ĵ�ǰλ��
		Node<T> *current2 = AnotherList.first->link;       //�ڶ�������ĵ�ǰλ��
		Node<T> *LastCurrent1 = current1->link;            //��һ�������ʣ��
		Node<T> *LastCurrent2 = current2->link;            //�ڶ��������ʣ��

		while (current2 != NULL)
		{
			LastCurrent1 = current1->link;
			LastCurrent2 = current2->link;

			if (current1->link != NULL )
			{			
				if (current1->Data < current2->Data &&current2->Data <= current1->link->Data)
				{
					current1->link = current2;
					current2->link = LastCurrent1;

					current1 = current2;
					current2 = LastCurrent2;

					
				}
				else
				{
					current1 = current1->link;			
				}				
			}
			else
			{		
				current1->link = current2;
				break;
			}
		}
		
		current1 = current1->link;
		if (current1->link != NULL &&current2 !=NULL)
		{
			if (current2->Data <= current1->link->Data)
			{
				LastCurrent1 = current1->link;
				current1->link = current2;
				current2->link = LastCurrent1;
			}
		}
		
		AnotherList.GetFirstNode()->link = NULL;
		

		return true;
	}
	bool Inverse(Node<T> *node)                   //����
	{
		Node<T> *current=first->link;
		Node<T> *LinkNode1;
		Node<T> *LinkNode2 = NULL;
		
		while (current!= NULL)
		{
			LinkNode1 = current->link;		
			current->link = LinkNode2;			
			LinkNode2 = current;                  /////////////
						
			current = LinkNode1;
		}
		first->link = LinkNode2;

		return true;
	}
	bool OutPutOrder(Node<T> *node)                    //˳��ݹ����,  list.GetFirstNode()->link
	{	
		if (node != NULL)
		{
			cout << node->Data << " ";
			OutPutOrder(node->link);	
		}
		return true;
	}

	bool OutPutReverse(Node<T> *node)                  //����ݹ����,  list.GetFirstNode()->link
	{
		if (node != NULL)
		{
			OutPutReverse(node->link);
			cout << node->Data << " ";
		}
		return true;
	}
	Node<T> *GetFirstNode()
	{
		return first;
	}

	bool FactorialOutPutReverse(Node<T> *node)                    //�����׳ˣ�˳��ݹ����,  list.GetFirstNode()->link
	{
		
		if (node != NULL)
		{
			FactorialOutPutReverse(node->link);

			if (node->link != NULL)
			{
				if (node->Data >= 100)
				{
					cout << node->Data << " ";
				}
				else if (10 <= node->Data && node->Data < 100)
				{
					cout << 0 << node->Data << " ";
				}
				else if (0 <= node->Data && node->Data < 10)
				{
					cout << 0 << 0 << node->Data << " ";
				}
			}
			else
			{
				cout << node->Data << " ";
			}
			
		}
		return true;
	}
};



void Factorial(int number) //�����׳�
{	
	List<int> Result;                                                 //���
	Result.Insert(0, 1);                                         //��ʼ�ڵ�
	Node<int> *current = Result.GetFirstNode()->link;                 //���õ�ǰ�ڵ����һ���ڵ�λ��һ��
	int add = 0;                                                 //��λ	

	for (int i = 1; i <= number; i++)                            //�׳�
	{
		while (current != NULL)                                  //���ڵ����� ���г˷�
		{			
			(current->Data) *= i;			
			current = current->link;
		}
		current= Result.GetFirstNode()->link;                    //���õ�ǰ�ڵ����һ���ڵ�λ��һ��

		while (current != NULL)                                  //ÿһ��������˺����ݽ��й淶����ÿ���ڵ�����Ϊ3λ
		{
			if (current->link == NULL && current->Data >= 1000)  //������λ����3λ������ǰ����һλ
			{
				Node<int> *NewNode = new Node<int>(0);
				current->link = NewNode;
			}

			add=(current->Data) /1000;                           //��λ
			current->Data %= 1000;			
			current = current->link;
			if (current != NULL)                                 //���λ��λ
			{			
				(current->Data) += add;
			}
			
		}	
		current=Result.GetFirstNode()->link;                     //���õ�ǰ�ڵ����һ���ڵ�λ��һ��
	}


	if (current->Data >= 1000)                                   //���λ��λ��
	{
		Node<int> *NewNode = new Node<int>;
		current->link = NewNode;
		add = (current->Data) % 1000;
		current->Data % 1000;
		current = current->link;
		current += add;
	}

	Result.Inverse(Result.GetFirstNode());
	Node<int> *node = Result.GetFirstNode()->link;
	int i = 0;



	fstream File("Factorial.txt", ios_base::out );

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
	File.close();

	ShellExecute(NULL, L"open", L"Factorial.txt", NULL, NULL, SW_SHOWNORMAL); //���ļ�
	//Result.FactorialOutPutReverse(Result.GetFirstNode()->link);  //����ݹ����
}




int main()
{
	
	List<int> list;
	list.Insert(0, 10);
	list.Insert(0, 8);
	list.Insert(0, 6);
	list.Insert(0, 4);
	list.Insert(0, 2);

	list.OutPutOrder(list.GetFirstNode()->link);
	cout << endl;

	List<int> list1;
	list1.Insert(0, 9);
	list1.Insert(0, 7);
	list1.Insert(0, 5);
	list1.Insert(0, 3);
	list1.Insert(0, 1);

	list1.OutPutOrder(list1.GetFirstNode()->link);
	cout << endl;


	list1.Combine(list);
	list1.OutPutOrder(list1.GetFirstNode()->link);

    return 0;
}












/*
int number;
cin >> number;
Factorial(number);
*/





/*
List<int> list;
list.Insert(0, 10);
list.Insert(0, 8);
list.Insert(0, 6);
list.Insert(0, 4);
list.Insert(0, 2);

List<int> list1;
list1.Insert(0, 9);
list1.Insert(0, 7);
list1.Insert(0, 5);
list1.Insert(0, 3);
list1.Insert(0, 1);

list1.Combine(list);
list1.OutPutOrder(list1.GetFirstNode()->link);
*/