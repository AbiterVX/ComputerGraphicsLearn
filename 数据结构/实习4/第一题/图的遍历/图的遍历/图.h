#pragma once

#include"����.h"
#include"ջ.h"
#include<iostream>
using namespace std;

struct Edge
{
	int AnotherAddress;  //�ߵ���һ������
	double Weight;             //Ȩ��
	Edge *link;                //��һ������ָ��
	Edge()
	{
		link = NULL;
	}
};
struct Vertex
{
	char Data;        //�����Ϣ
	int Address;      //��ַ
	Edge *LinkEdge;   //������
	Vertex()
	{
		LinkEdge = NULL;
	}
};



class Graph
{
private:
	Vertex *AllVertex;  //���ж�����Ϣ
	int MaxVertexNumber;//����ĸ���
	int VertexNumber;   //��ĸ���
	int EdgeNumber;     //�ߵĸ���
public:
	Graph(int MaxVertex)
	{
		AllVertex = new Vertex[MaxVertex];
		MaxVertexNumber = MaxVertex;
		VertexNumber = 0;
		EdgeNumber = 0;
	}
	~Graph() {}
	bool InsertEdge(char Vertex1, char Vertex2, double weight = 1)//�����
	{
		int Vertex1Address = -1;
		int Vertex2Address = -1;
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data== Vertex1)
			{
				Vertex1Address = i;
				break;
			}
		}
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == Vertex2)
			{
				Vertex2Address = i;
				break;
			}
		}
		if (Vertex1Address!=-1 && Vertex2Address!=-1)
		{
			Edge *CurrentEdge = AllVertex[Vertex1Address].LinkEdge;     //��ǰλ��
			while (CurrentEdge != NULL)                                 //�ҵ�ĩβλ��
			{
				if (CurrentEdge->AnotherAddress != Vertex2Address)//�����Ƿ��ظ�
				{
					CurrentEdge = CurrentEdge->link;
				}
				else
				{
					return false;  //�ظ�
				}
			}

			CurrentEdge = new Edge;
			CurrentEdge->AnotherAddress = Vertex2Address;
			CurrentEdge->Weight = weight;
			CurrentEdge->link = AllVertex[Vertex1Address].LinkEdge; //������ͷ����
			AllVertex[Vertex1Address].LinkEdge = CurrentEdge;       //

			Edge *CurrentEdge2=new Edge;                         //��һ����
			CurrentEdge2->AnotherAddress = Vertex1Address;
			CurrentEdge2->Weight = weight;
			CurrentEdge2->link = AllVertex[Vertex2Address].LinkEdge;//������ͷ����
			AllVertex[Vertex2Address].LinkEdge = CurrentEdge2;      //

			EdgeNumber++;
			return true;
		}
		return false;
	}	
	bool InsertVertex(char data)//���붥��
	{
		for (int i = 0; i < VertexNumber; i++)
		{
			if (data == AllVertex[i].Data)
			{
				return false;
			}
		}

		if (VertexNumber < MaxVertexNumber)
		{			
			VertexNumber++;
			AllVertex[VertexNumber - 1].Data = data;
			AllVertex[VertexNumber - 1].Address = VertexNumber - 1;
			return true;
		}
		return false;
	}

	bool DFS(char BeginData)
	{
		int CurrentVertex = -1;                  //�ҵ���ʼλ��
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == BeginData)
			{
				CurrentVertex = i;
				break;
			}
		}
		if (CurrentVertex == -1)
		{
			return false;
		}

		int *IfVisit = new int[VertexNumber];      //�ж��Ƿ񱻷��ʣ�����
		char *VisitQueue = new char[VertexNumber]; //���ʵĴ�������
		for (int i = 0; i < VertexNumber; i++)
		{
			IfVisit[i] = 0;                        //��ʼΪδ�����ʣ�Ϊ0
		}

		stack<Vertex> VertexStack;                 //����ջ
		int VisitedNumber = 0;                     //�ѱ����ʶ���ĸ���
		Edge *CurrentEdge;                         //�ڽӶ���
		do
		{
			if (IfVisit[CurrentVertex] != 1)                                  //��ǰ����δ������
			{
				IfVisit[CurrentVertex] = 1;                                   //����	
				VisitQueue[VisitedNumber] = AllVertex[CurrentVertex].Data;    //����
				VisitedNumber++;
				VertexStack.InsertFirst(AllVertex[CurrentVertex]);            //������ջ	
				CurrentEdge = AllVertex[CurrentVertex].LinkEdge;              //��ǰ���ڽӶ��� 
				while (CurrentEdge != NULL)                                   //�ҵ���һ��δ�����ʵ��ڽӶ���
				{
					if (IfVisit[CurrentEdge->AnotherAddress] == 1)
					{
						CurrentEdge = CurrentEdge->link;
					}
					else
					{
						break;
					}
				}
				if (CurrentEdge != NULL)                              //�����ǰ�������δ�����ʵ��ڽӶ���
				{
					CurrentVertex = CurrentEdge->AnotherAddress;      //��һ������
				}
			}
			else                                                      //��ǰ���㱻���ʹ�
			{
				VertexStack.RemoveFirst();		
				Edge *CurrentEdge= VertexStack.GetTopData().LinkEdge;
				while (CurrentEdge != NULL)
				{
					if (IfVisit[CurrentEdge->AnotherAddress] == 1)
					{
						CurrentEdge = CurrentEdge->link;
					}
					else
					{
						CurrentVertex = CurrentEdge->AnotherAddress;
						break;
					}			
				}
				if (CurrentEdge = NULL)
				{
					CurrentVertex = VertexStack.GetTopData().Address;
				}
			}
		} while (!VertexStack.IfEmpty());

		for (int i = 0; i < VertexNumber; i++)
		{
			cout << VisitQueue[i] << " ";
		}
		return true;
	}
	bool BFS(char BeginData)
	{
		int CurrentVertex = -1;                    //�ҵ���ʼλ��
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == BeginData)
			{
				CurrentVertex = i;
				break;
			}
		}
		if (CurrentVertex == -1)
		{
			return false;
		}

		int *IfVisit = new int[VertexNumber];      //�ж��Ƿ񱻷���
		char *VisitQueue = new char[VertexNumber]; //���ʵĴ���
		for (int i = 0; i < VertexNumber; i++)
		{
			IfVisit[i] = 0;                        //��ʼΪδ������
		}
		Queue<Edge *> VertexQueue;                 //�������
		int VisitedNumber = 0;                     //�ѱ����ʶ���ĸ���
		Edge*CurrentEdge;                         //�ڽӶ���
		do
		{
			IfVisit[CurrentVertex] = 1;                                   //����	
			VisitQueue[VisitedNumber] = AllVertex[CurrentVertex].Data;    //�����������
			VisitedNumber++;
			CurrentEdge = AllVertex[CurrentVertex].LinkEdge;
			while (CurrentEdge != NULL)
			{
				if (IfVisit[CurrentEdge->AnotherAddress] != 1)
				{				
					VertexQueue.Insert(CurrentEdge);
					IfVisit[CurrentEdge->AnotherAddress] = 1;
				}			
				CurrentEdge = CurrentEdge->link;
			}
			if (!VertexQueue.IfEmpty())
			{
				CurrentVertex = VertexQueue.GetTopData()->AnotherAddress;
				VertexQueue.Remove();
			}			
		} while (VisitedNumber != VertexNumber);

		for (int i = 0; i < VertexNumber; i++)
		{
			cout << VisitQueue[i] << " ";
		}
		return true;
	}

	void OutPut()
	{
		Edge *CurrentEdge;
		for (int i = 0; i < VertexNumber; i++)
		{
			cout <<AllVertex[i].Data<< ": ";
			CurrentEdge=AllVertex[i].LinkEdge;
			while (CurrentEdge != NULL)
			{
				cout << AllVertex[CurrentEdge->AnotherAddress].Data << " ";
				CurrentEdge = CurrentEdge->link;
			}
			cout << endl;
		}
	}
};


