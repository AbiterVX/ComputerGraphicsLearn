#pragma once


#include "stdafx.h"
#include<iostream>
#include<vector>
#include<stack>
#include<math.h>
using namespace std;


class TreeNode
{
public:
	int val;
	TreeNode *left, *right;
	TreeNode(int val)
	{
		this->val = val;
		this->left = this->right = NULL;
	}
};


class Solution {
public:
	/*
	* @param root: A Tree
	* @return: A list of lists of integer include the zigzag level order traversal of its nodes' values.
	*/

	int maxPathSum(TreeNode * root)
	{
		int MaxPathSum = pow(2, 31) - 1;
		MaxPathSum = 0 - MaxPathSum;
		EachPath(root, MaxPathSum);
		return MaxPathSum;
	}

	int EachPath(TreeNode * root, int &MaxPathSum)
	{
		if (root == NULL)    //Ϊ�գ��ݹ�
		{
			return 0;
		}
		int LeftPath = EachPath(root->left, MaxPathSum);
		int RightPath = EachPath(root->right, MaxPathSum);

		int Left = 0;                //�Ƿ�ѡ����child �� ��child
		int Right = 0;
		if (Left < LeftPath)
		{
			Left = LeftPath;
		}
		if (Right<RightPath)
		{
			Right = RightPath;
		}
		if (MaxPathSum < Left + Right + root->val) //�ж��󣬵���ǰ���ٵ��ң�����·���Ƿ�Ϊ���
		{
			MaxPathSum = Left + Right + root->val;
		}
		int OneSide = Left;                         //���ص�����̣�  1.ֻ�е�ǰ�ڵ� 
		if (Left < Right)                          //                2.��ǰ�ڵ� +��child
		{                                          //                3.��ǰ�ڵ� +��child
			OneSide = Right;
		}
		return OneSide + root->val;
	}
};
