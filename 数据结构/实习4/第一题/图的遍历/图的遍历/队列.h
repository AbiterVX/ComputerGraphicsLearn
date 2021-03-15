#pragma once
using namespace std;

template<typename Type>
struct QueueNode
{
	Type Data;                 //����
	QueueNode<Type> *link;          //����

	QueueNode()                  //Ĭ�Ϲ���
	{
		link = NULL;
	}
	QueueNode(Type data)            //���첢д������
	{
		Data = data;
		link = NULL;
	}

};


template<typename Type>
class Queue
{
protected:
	QueueNode<Type> *first;                //��ʼ�ڵ�
	QueueNode<Type> *last;                 //β�ڵ�
	int Length;
public:
	Queue()
	{
		Length = 0;
		first = new QueueNode<Type>();
		last = new QueueNode<Type>();
		first->link = NULL;
		last->link = NULL;
	}
	void Empty()                   //���
	{
		QueueNode<Type> *current = NULL;

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
	/*~Queue()                         //����
	{
	Empty();
	delete first;
	//delete last;
	}*/
	bool Insert(Type data)                 //����
	{
		Length++;
		QueueNode<Type> *NewNode = new QueueNode<Type>(data);   //�����µĽڵ� ,�������� 
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
	bool Remove()                         //ɾ��
	{
		Length--;
		if (first->link != NULL)
		{
			QueueNode<Type>*DeleteNode;
			DeleteNode = first->link;
			first->link = first->link->link;  //��ɾ����֮���������֮ǰ�������������	
			if (first->link == NULL)
			{
				last->link = NULL;
			}
			delete DeleteNode;
		}
		else
		{
			return false;
		}
		return true;
	}
	Type GetTopData()
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
	

	Type GetLastData()
	{
		if (last->link != NULL)
		{
			return last->link->Data;
		}
		else
		{
			return 0;
		}
	}
	bool IfEmpty()                   //�ж��Ƿ�Ϊ��
	{
		if (first->link == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	QueueNode<Type>* GetFirst()
	{
		return first;
	}

	QueueNode<Type>* GetLast()
	{
		return last;
	}
};
