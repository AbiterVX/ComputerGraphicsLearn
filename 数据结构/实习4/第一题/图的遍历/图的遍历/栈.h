#pragma once

using namespace std;
template <class T>
struct StackNode
{
	T Data;                 //����
	StackNode<T> *link;          //����
	StackNode()                  //Ĭ�Ϲ���
	{
		link = NULL;
	}
	StackNode(T data)            //���첢д������
	{
		Data = data;
		link = NULL;
	}

};
template <class T>
class stack
{
protected:
	StackNode<T> *first;                //ͷ�ڵ�
	StackNode<T> *last;                 //β�ڵ�
public:
	stack()
	{
		first = new StackNode<T>();
		last = new StackNode <T>();

		first->link = last;
		last->link = NULL;
	}
	void Empty()                   //���
	{
		StackNode<T> *current = NULL;

		if (first->link == NULL)
		{
			return;
		}
		while (first->link != NULL)
		{
			current = first->link;
			first->link = current->link;
			delete current;
		}
	}
	~stack()                         //����
	{
		Empty();
		delete first;
		//delete last;
	}
	bool InsertFirst(T data)                    //ͷ����
	{
		StackNode<T> *NewNode = new StackNode<T>(data);   //�����µĽڵ� ,��������  
		NewNode->link = first->link;            //�������֮������������������
		first->link = NewNode;                  //�������֮ǰ�����������������

		if (first->link->link == NULL)
		{
			last->link = NewNode;
		}
		return true;
	}
	bool InsertLast(T data)                     //ĩβ����
	{
		StackNode<T> *NewNode = new StackNode<T>(data);   //�����µĽڵ� ,�������� 
		if (last->link != NULL)
		{
			last->link->link = NewNode;
			last->link = NewNode;
		}
		else
		{
			first->link = NewNode;
			last->link = NewNode;
		}
		return true;
	}
	bool RemoveFirst()                         //ɾ��
	{
		if (first->link != last)
		{
			StackNode<T>*DeleteNode;
			DeleteNode = first->link;
			first->link = first->link->link;  //��ɾ����֮���������֮ǰ�������������	  
			delete DeleteNode;
		}
		else
		{
			return false;
		}
		return true;
	}
	T GetTopData()
	{
		if (first->link != last)
		{
			return first->link->Data;
		}
		
	}
	bool IfEmpty()                   //�ж��Ƿ�Ϊ��
	{
		if (first->link == last)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	StackNode<T>* GetFirst()
	{
		return first;
	}

	StackNode<T>* GetLast()
	{
		return last;
	}
};