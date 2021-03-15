#pragma once

#include<algorithm>
#include<iostream>
#include<time.h>

#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;



class Heap
{
private:
	int *Data;     //����
	int Length;    //����

public:
	Heap(int *data, int TotalNumber)      //����
	{
		Data = data;                      //��������
		Length = TotalNumber - 1;         //�����ڡ�0���������±��Ӧ��
	}

	void HeapAdjust(int CurrentNumber, int length)          //����һ�Σ��õ����ֵ��������
	{
		int CurrentMax = CurrentNumber;                     //��ǰ���
		int LeftChild = CurrentNumber * 2;                  //��child
		int RightChild = CurrentNumber * 2 + 1;             //��child


		if (CurrentNumber <= length / 2)                                    //�����ǰС���ܳ�
		{
			if (LeftChild <= length && Data[LeftChild] > Data[CurrentMax])  //�����child��ΪҶ�ڵ㣬
			{                                                               //�Ҵ��ڵ�ǰ����ֵ��
				CurrentMax = LeftChild;                                     //��ǰ����Ϊ��child
			}
			if (RightChild <= length && Data[RightChild] > Data[CurrentMax])//�����child��ΪҶ�ڵ㣬
			{                                                               //�Ҵ��ڵ�ǰ����ֵ��
				CurrentMax = RightChild;                                    //��ǰ����Ϊ��child
			}

			if (CurrentMax != CurrentNumber)                                //������ֵ  
			{
				swap(Data[CurrentMax], Data[CurrentNumber]);
				HeapAdjust(CurrentMax, length);
			}
		}
	}

	void HeapSort()
	{
		for (int i = Length / 2; i >= 1; i--)
		{
			HeapAdjust(i, Length);
		}

		for (int i = Length; i >= 1; i--)
		{
			swap(Data[1], Data[i]);
			HeapAdjust(1, i - 1);
		}
    }
	



	void OutPut()
	{
		
		for (int i = Length; i > 0; i--)
		{
			cout << Data[i] << " ";
		}
		cout << endl;
	}

	void OutPut(int OutputNumber)                           //���ǰM��
	{
		fstream File("Heap.txt", ios_base::out);
		int end = Length - OutputNumber;
		for (int i = Length; i >end; i--)
		{
			File << Data[i] << " ";
		}
		//cout << endl;
		File.close();
		ShellExecute(NULL, L"open", L"Heap.txt", NULL, NULL, SW_SHOWNORMAL);
	}

};


