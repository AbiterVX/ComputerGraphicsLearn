#pragma once


using namespace std;





struct Node
{
	int Data;                 //����
	Node *link;          //����

	Node()                  //Ĭ�Ϲ���
	{
		link = NULL;
	}
	Node(int data)            //���첢д������
	{
		Data = data;
		link = NULL;
	}

};




class Queue
{
protected:
	Node *first;                //��ʼ�ڵ�
	Node *last;                 //β�ڵ�
	int Length;
public:
	Queue()
	{
		Length = 0;
		first = new Node(0);
		last = new Node(0);

		first->link = NULL;
		last->link = NULL;
	}
	

	void Empty()                   //���
	{
		Node *current = NULL;

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


	bool Insert(int data)                 //����
	{
		Length++;
		Node *NewNode = new Node(data);   //�����µĽڵ� ,�������� 
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
		if (first->link != last)
		{
			Node*DeleteNode;
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


	int GetTopData()
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

	int GetLastData()
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
		if (first->link == last)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	Node* GetFirst()
	{
		return first;
	}

	Node* GetLast()
	{
		return last;
	}
};
