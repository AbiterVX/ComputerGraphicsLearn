// ͼ�ı���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"ͼ.h"
#include<fstream>
using namespace std;

int main()
{
	int type = 0;
	cout << "Ĭ�����밴1���ֶ����밴2" << endl;
	cin >> type;
	if (type == 1)
	{
		Graph graph(8);
		fstream GetData("��Ϣ.txt", ios_base::in | ios_base::binary);
		int vertexNumber = 8;
		char Vertex = ' ';
		char edge1 = ' ';
		char edge2 = ' ';
		int count = 0;
		while (!GetData.eof())
		{
			if (count < vertexNumber)
			{
				GetData.read((char*)&Vertex, sizeof(char) * 1);
				graph.InsertVertex(Vertex);
				count++;
			}
			else
			{
				GetData.read((char*)&edge1, sizeof(char) * 1);
				GetData.read((char*)&edge2, sizeof(char) * 1);
				graph.InsertEdge(edge1, edge2);
			}
		}
		cout << "�ڽӱ�" << endl;
		graph.OutPut();
		cout << endl << "��ʼ�㣺b" << endl;
		cout << endl << "BFS:" << endl;
		graph.BFS('b');
		cout << endl << "DFS:" << endl;
		graph.DFS('b');
	}
	else if (type == 2)
	{
		int VertexNumber=0;
		cout << "�����ĸ���" << endl;
		cin >> VertexNumber;
		Graph graph(VertexNumber);

		cout << "������������Ϣ" << endl;
		char *vertex=new char[VertexNumber+1];
		cin >> vertex;
		for (int i = 0; i < VertexNumber; i++)
		{	
			graph.InsertVertex(vertex[i]);
		}

		int EdgeNumber = 0;
		cout << "����ߵĸ���" << endl;
		cin >> EdgeNumber;
		cout << "�����,����������Ϣ" << endl;
		char* EdgeS = new char[EdgeNumber * 2 + 1];
		cin >> EdgeS;
		char edge1, edge2;
		for (int i = 0; i < EdgeNumber; i++)
		{
			edge1 = EdgeS[i * 2];
			edge2 = EdgeS[i * 2 + 1];
			graph.InsertEdge(edge1, edge2);
		}
		char StratVertex;
		cout << "������ʼ��" << endl;
		cin >> StratVertex;
		cout << endl<<endl;
		cout << "�ڽӱ�" << endl;
		graph.OutPut();
		cout << endl << "��ʼ�㣺"<< StratVertex << endl;
		cout << endl << "BFS:" << endl;
		graph.BFS(StratVertex);
		cout << endl << "DFS:" << endl;
		graph.DFS(StratVertex);
	}


	
    return 0;
}

//GetData.read((char*)&vertexNumber, sizeof(int) * 1);
/*ofstream Information("��Ϣ.txt", ios_base::out | ios_base::binary);
char VertexS[9] = "abcdefgh";
char EdgeS[19] = "abacbdbedfefcgchgh";
int VertexNumber=8;

//Information.write((char*)&VertexNumber, sizeof(int) * 1);
Information.write((char*)VertexS, sizeof(char) * 8);
Information.write((char*)EdgeS, sizeof(char) * 18);*/

