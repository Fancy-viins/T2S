#include"TreeNode.h"
#include"GoalH.h"
#include<iostream>
#include<assert.h>
using namespace std;

bool operator==(const vector<float>&v1, const vector<float>&v2)
{
	for (int i = 0; i < v1.size() - 1; i++)
	{
		if (v1[i] != v2[i])
		{
			return false;
		}
	}
	return true;
}

float GoalH(Node* NextNode,Tree * Tree)
{
	vector<float> v;
	for (int i = 0; i < Tree->place_num; i++)
	{
		if (i != 8 && i != 17 && i != 26)
		{
			if (NextNode->PtrNetStateRow[i] != NULL )
			{
				v.push_back(NextNode->PtrNetStateRow[i]->TokenNum);
			}
			else
			{
				v.push_back(0);
			}
		}
	}
	//for (int i = 0; i < Tree->place_num; i++)//x
	//{
	//	if (i == 2 || i == 4 || i == 6 || i == 11 || i == 13 || i == 15 || i == 20 || i == 22 || i == 24)
	//	{
	//		if (NextNode->PtrNetStateRow[i] != NULL)
	//		{
	//			v.push_back(NextNode->PtrNetStateRow[i]->residenceTime);
	//		}
	//		else
	//		{
	//			v.push_back(0);
	//		}
	//	}
	//}
	v.push_back(0);
	for (vector<vector<float>>::iterator it = Tree->LastGoal.begin(); it != Tree->LastGoal.end(); it++)
	{
		if (*it == v)
		{
			return it->at(it->size() - 1);
		}
	}
	//cout << "没有找到对应的目标节点" << endl;
	return -1;
	cout << "没有找到对应的目标节点" << endl;
	//assert(0);
}