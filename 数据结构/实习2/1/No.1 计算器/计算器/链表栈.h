#pragma once


using namespace std;


template <class T>
struct Node
{
	T Data;                 //����
	Node<T> *link;          //����

	Node()                  //Ĭ�Ϲ���
	{
		link = NULL;
	}
	Node(T data)            //���첢д������
	{
		Data = data;
		link = NULL;
	}

};


template <class T>
class Stack
{
protected:
	Node<T> *first;                //ͷ�ڵ�
	Node<T> *last;                 //β�ڵ�
public:
	Stack()
	{
		first = new Node<T>(0);
		last = new Node <T>(0);

		first->link = last;
		last->link = NULL;
	}

	void Empty()                   //���
	{

		Node<T> *current = NULL;

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
	~Stack()                         //����
	{

		Empty();
		delete first;
		//delete last;
	}

	bool InsertFirst(T data)                    //ͷ����
	{
		Node<T> *NewNode = new Node<T>(data);   //�����µĽڵ� ,��������  
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
		Node<T> *NewNode = new Node<T>(data);   //�����µĽڵ� ,�������� 
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
			Node<T>*DeleteNode;
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
		else
		{
			return false;
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



	Node<T>* GetFirst()
	{
		return first;
	}

	Node<T>* GetLast()
	{
		return last;
	}
};