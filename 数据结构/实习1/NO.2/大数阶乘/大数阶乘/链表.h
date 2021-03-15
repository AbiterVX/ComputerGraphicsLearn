#pragma once

using namespace std;


 


struct Node
{
	int Data;            //����
	Node *link;          //����
	Node *BackLink;

	Node()               //Ĭ�Ϲ���
	{
		link = NULL;
		BackLink = NULL;
	}
	Node(int data)       //���첢д������
	{
		Data = data;
		link = NULL;
		BackLink = NULL;
	}

};

class List
{
protected:
	Node *first;                    //��ʼ�ڵ�
	Node *last;
public:
	List()
	{
		first = new Node(0);
		last = new Node(0);

		first->link = last;
		last->BackLink = first;
		last->link = NULL;
		first->BackLink = NULL;
	}

	void Empty()                   //���
	{
		Node *current;

		if (first->link == last)
		{
			return;
		}
		while (first->link != last)
		{
			current = first->link;
			first->link = current->link;
			delete current;
		}

	}

	~List()                         //����
	{
		Empty();
		delete first;
		delete last;
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


	bool Insert(int position, int data)               //�ڵ�i��Ԫ�غ����
	{
		Node *current = first;                        //��ǰλ�ã���ʼλ��Ϊ��ʼ�ڵ㡣

		for (int i = 1; i<position; i++)                   //������ǰλ�á�ָ��Ҫ��λ��
		{
			if (current != last)
			{
				current = current->link;              //ָ����һ���ڵ�
			}
		}

		if (current == last )     //�������λ�ô��������ȣ�������Ϊ��
		{
			return false;
		}
		else                                          //����Ϊ�գ����߲���λ��С��������
		{
			Node *NewNode = new Node(data);           //�����µĽڵ� ,��������  
			NewNode->link = current->link;            //�������֮������������������
			current->link = NewNode;                  //�������֮ǰ�����������������

		    
			NewNode->BackLink = current;
			NewNode->link->BackLink = NewNode;

			//cout<< NewNode->Data << endl;
			//cout << NewNode->BackLink->Data << endl;
		}

		return true;
	}



	Node *GetFirstNode()
	{
		return first;
	}
	
	Node *GetLastNode()
	{
		return last;
	}


	bool Inverse(Node *node)                   //����
	{
		Node *current = first->link;
		Node *LinkNode1;
		Node *LinkNode2 = NULL;

		while (current != NULL)
		{
			LinkNode1 = current->link;
			current->link = LinkNode2;
			LinkNode2 = current;                  /////////////

			current = LinkNode1;
		}
		first->link = LinkNode2;

		return true;
	}
	
	

	/*bool FactorialOutPutReverse(Node *node)                    //�����׳ˣ�˳��ݹ����,  list.GetFirstNode()->link
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
	}*/
};
