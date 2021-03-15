#pragma once


#include<iostream>
using namespace std;



struct Node
{
	int Numerator;       //����
	int Denominator;     //��ĸ
	Node *link;          //����

	Node()               //Ĭ�Ϲ���
	{
		link = NULL;
	}
	Node(int numerator,int denominator)       //���첢д������
	{
		Numerator = numerator;
		Denominator = denominator;
		link = NULL;
	}

};




class List
{
protected:
	Node *first;                    //��ʼ�ڵ�
public:
	List()
	{
		first = new Node(0,0);
	}

	bool Insert(int position, int numerator, int denominator)               //�ڵ�i��Ԫ�غ����
	{
		Node *current = first;                        //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣

		for (int i = 1; i<position; i++)                   //������ǰλ�á�ָ��Ҫ��λ��
		{
			if (current != NULL)
			{
				current = current->link;              //ָ����һ���ڵ�
			}
		}

		if (current == NULL)     //�������λ�ô��������ȣ�������Ϊ��
		{
			return false;
		}
		else                                          //����Ϊ�գ����߲���λ��С��������
		{
			Node *NewNode = new Node(numerator,denominator);           //�����µĽڵ� ,��������  
			NewNode->link = current->link;            //�������֮������������������
			current->link = NewNode;                  //�������֮ǰ�����������������
		}

		return true;
	}


	bool Insert(Node *node, int numerator, int denominator)               //��node�����
	{
		Node *NewNode = new Node(numerator, denominator);                 //�¼ӽڵ�
		Node *LastNode= node->link;

		//cout << LastNode->Denominator << endl;/////////////

		node->link = NewNode;
		NewNode->link = LastNode;
		return true;
	}





	bool Remove(int position) //ɾ����i��Ԫ��
	{
		Node *current = first;                        //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣

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
			current->link = current->link->link;        //��ɾ����֮���������֮ǰ�������������	               
		}
		return true;
	}
	
	Node *GetFirstNode()                            //�õ�ͷ���
	{
		return first;
	}

	
};