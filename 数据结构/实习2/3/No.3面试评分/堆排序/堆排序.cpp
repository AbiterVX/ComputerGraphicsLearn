// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�����.h"

#include<iostream>
#include<time.h>
#include"�����������.h"
#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;



int main()
{
	cout << "����������и����Լ�ǰM�������ĸ���" << endl;
	int N, M;
	cin >>N>>M ;

	Heap heap(RandomSequence(N), N+1);
	heap.HeapSort();
	heap.OutPut(M);
    return 0;
}




/*
clock_t start, end;
start = clock();


end = clock();
double t = double(end - start) / 1000;
cout << t << endl;

*/