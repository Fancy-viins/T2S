#include<stdio.h>
#include <stdlib.h> 
#include<float.h>
#include"TreeNode.h"
#include"Tree2HStar.h"
#include <iostream>
//#include<thread>
//#include<mutex>
//#include<future>
using namespace std;
void stateTree2HStar(Tree *Tree)
{
	printf("begin Hstar\n");
	float H;
	Node *PtrBackNode,*PtrFatherNode,*PtrNotDoneNode;
	PtrBackNode = Tree->PtrBackDoneHead;
	if (PtrBackNode == NULL)
	{
		printf("No GoalNode\n");
	
		return;
	}

	while (!(PtrBackNode == NULL && Tree->PtrBackNotDoneHead == NULL))
	{
		//printf("ID:%d\n", PtrBackNode->markingID);
		//future<void> GetEarning = async(CalcEarnings, PtrBackNode);
	//	CalcEarnings(PtrBackNode);//计算收益Q
		Tree->Back_num++;//反向次数计数
		if (PtrBackNode->markingID == 0)//根节点做特殊处理
		{
			TwinToBackDone(Tree, PtrBackNode);
		}
		else//非根结点
		{

			PtrFatherNode = PtrBackNode->PtrFathers[0];//选取father结点
			PtrFatherNode->NumSons_Back--;//计数
			if (PtrFatherNode->NumSons_Back >= 0)//为了避免重复计算子结点
			{
				H = PtrBackNode->hMin + PtrBackNode->g - PtrFatherNode->g;//计算h
				if (H < PtrFatherNode->hMin)//选取最小的h
				{
					PtrFatherNode->hMin = H;
				}
				TwinToBackDone(Tree, PtrBackNode);
				if (PtrFatherNode->NumSons_Back == 0)//已完成所有子结点的操作，可以把改结点放入backdone链表了
				{
					//CalcEarnings(PtrFatherNode);//计算收益Q
					if (!InDone(Tree, PtrFatherNode))//检查是否存在backdone链表里，避免重复
					{
						

						Tree->PtrBackDoneTail->PtrBackDoneNext = PtrFatherNode;
						Tree->PtrBackDoneTail = PtrFatherNode;
					}

					if (InNotDone(Tree, PtrFatherNode))//对notdone表中去除
					{
						DeleteNotDone(Tree, PtrFatherNode);
					}
				}
				else//notdone表放入
				{
					if (!InNotDone(Tree, PtrFatherNode))
					{
						NotDoneSort(Tree, PtrFatherNode);
					}
				}
			}
		}//上  计算h   放入链表
		
		PtrBackNode = PtrBackNode->PtrBackDoneNext;
		
		if(PtrBackNode == NULL)
		{
			if (Tree->PtrBackNotDoneHead != NULL)
			{
				PtrNotDoneNode = Tree->PtrBackNotDoneHead;
				while (PtrNotDoneNode != NULL && PtrNotDoneNode->NumTwinBack == 0)//选取h最小的结点进行Twin扩展
				{
					PtrNotDoneNode = PtrNotDoneNode->PtrBackNotDoneNext;
				} 
				if (PtrNotDoneNode == NULL)//所有twin都扩展完毕，需要选择结点放入BackDone表中
				{
					PtrNotDoneNode = Tree->PtrBackNotDoneHead;
					while (PtrNotDoneNode != NULL && InDone(Tree, PtrNotDoneNode))//从NotDone中选取不存在Done中的结点
					{
						PtrNotDoneNode = PtrNotDoneNode->PtrBackNotDoneNext;
						if (PtrNotDoneNode != NULL)
						{
							DeleteNotDone(Tree, PtrNotDoneNode->PtrBackNotDoneBefore);//删除twin扩展完毕并且已经存在与BackDone表中的结点
						}
					}
					if (PtrNotDoneNode == NULL)
					{
						break;
					}
					DeleteNotDone(Tree, PtrNotDoneNode);
					Tree->PtrBackDoneTail->PtrBackDoneNext = PtrNotDoneNode;
					Tree->PtrBackDoneTail = PtrNotDoneNode;
					PtrBackNode = PtrNotDoneNode;
				}
				else
				{
					PtrBackNode = TwinToBackDone(Tree, PtrNotDoneNode);
				}
			}
		}
	
		//GetEarning.wait();
	}

	if (Tree->PtrDeadlockHead != NULL)
	{
		CalcDeadLockH(Tree);
	}
	PtrBackNode = Tree->PtrBackDoneHead;
	while (PtrBackNode != nullptr)
	{
		if (PtrBackNode->Earnings == nullptr)
		{
			CalcEarnings(PtrBackNode);
			PtrBackNode = PtrBackNode->PtrBackDoneNext;
		}
		else
			PtrBackNode = PtrBackNode->PtrBackDoneNext;

	}
	printf("Back_num:%d\n", Tree->Back_num);
	printf("over Hstar\n");
}

PtrNodeType TwinToBackDone(Tree *Tree, PtrNodeType PtrBackNode)
{
	short num = 0;
	PtrNodeType PtrNode = NULL;
	if (PtrBackNode->TwinIsDone == 0)
	{
		PtrBackNode->TwinIsDone = 1;//避免把重复tiwn指针指向的结点放入
		while (PtrBackNode->NumTwinBack)
		{
			PtrBackNode->NumTwinBack--;//计数
			PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]->hMin = PtrBackNode->hMin;//把相同的h赋给twin指针指向的old结点
			if (InDone(Tree, PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]) == 0)
			{
				num++;
				Tree->PtrBackDoneTail->PtrBackDoneNext = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
				Tree->PtrBackDoneTail = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
				if (num == 1)
				{
					PtrNode = Tree->PtrBackDoneTail;
				}
			}
		}
	}
	return PtrNode;
}

void DeleteNotDone(Tree *Tree, PtrNodeType BackNode)//从NotDone中删除结点
{
	if (BackNode->PtrBackNotDoneBefore != NULL)
	{
		BackNode->PtrBackNotDoneBefore->PtrBackNotDoneNext = BackNode->PtrBackNotDoneNext;
	}
	else
	{
		Tree->PtrBackNotDoneHead = BackNode->PtrBackNotDoneNext;
	}
	if (BackNode->PtrBackNotDoneNext != NULL)
	{
		BackNode->PtrBackNotDoneNext->PtrBackNotDoneBefore = BackNode->PtrBackNotDoneBefore;
	}
	else
	{
		Tree->PtrBackNotDoneTail = BackNode->PtrBackNotDoneBefore;
	}
	BackNode->PtrBackNotDoneBefore = NULL;
	BackNode->PtrBackNotDoneNext = NULL;


}

void NotDoneSort(Tree *Tree, PtrNodeType BackNode)//NotDone排序
{
	PtrNodeType PtrPreBack;
	PtrPreBack = Tree->PtrBackNotDoneHead;
	float hMIN;
	if (PtrPreBack == NULL)
	{
		Tree->PtrBackNotDoneHead = BackNode;
		Tree->PtrBackNotDoneTail = BackNode;
	}
	else
	{
		hMIN = PtrPreBack->hMin;
		while (PtrPreBack->PtrBackNotDoneNext != NULL && PtrPreBack->PtrBackNotDoneNext->hMin < BackNode->hMin)
		{
			PtrPreBack = PtrPreBack->PtrBackNotDoneNext;
		}
		if (PtrPreBack == NULL)
		{
			Tree->PtrBackNotDoneTail->PtrBackNotDoneNext = BackNode;
			BackNode->PtrBackNotDoneBefore = Tree->PtrBackNotDoneTail;
			Tree->PtrBackNotDoneTail = BackNode;
		}
		else
		{
			if (PtrPreBack->PtrBackNotDoneNext == NULL)
			{
				PtrPreBack->PtrBackNotDoneNext = BackNode;
				BackNode->PtrBackNotDoneBefore = PtrPreBack;
				Tree->PtrBackNotDoneTail = BackNode;
			}
			else
			{
				PtrPreBack->PtrBackNotDoneNext->PtrBackNotDoneBefore = BackNode;
				BackNode->PtrBackNotDoneNext = PtrPreBack->PtrBackNotDoneNext;
				PtrPreBack->PtrBackNotDoneNext = BackNode;
				BackNode->PtrBackNotDoneBefore = PtrPreBack;
			}
		}
	}
}

bool InDone(Tree *Tree,PtrNodeType BackNode)
{
	PtrNodeType PtrBack;
	PtrBack = Tree->PtrBackDoneHead;
	while (PtrBack != NULL)
	{
		if (BackNode->markingID == PtrBack->markingID)
		{
			return 1;
		}
		PtrBack = PtrBack->PtrBackDoneNext;
	} 
	return 0;
}

bool InNotDone(Tree *Tree, PtrNodeType BackNotDoneNode)
{
	PtrNodeType PtrBack;
	PtrBack = Tree->PtrBackNotDoneHead;
	while (PtrBack != NULL)
	{
		if (BackNotDoneNode->markingID == PtrBack->markingID)
		{
			return 1;
		}
		PtrBack = PtrBack->PtrBackNotDoneNext;
	}
	return 0;
}

bool NotInDeadLock(Tree *Tree, PtrNodeType DeadLock)
{
	PtrNodeType PtrDeadNode;
	PtrDeadNode = Tree->PtrDeadlockHead;
	while (PtrDeadNode != NULL)
	{
		if (DeadLock->markingID == PtrDeadNode->markingID)
		{
			return 0;
		}
		PtrDeadNode = PtrDeadNode->DeadlockNext;
	}
	return 1;
}

void CalcDeadLockH(Tree *Tree)
{
	PtrNodeType PtrDeadLock;
	PtrDeadLock = Tree->PtrDeadlockHead;
	float h;
	while (PtrDeadLock != NULL)
	{
		h = FLT_MAX;
		for (short i = 0; i < PtrDeadLock->NumFathers; ++i)
		{
			if (PtrDeadLock->PtrFathers[i]->isDeadlock != 1)
			{
				if (PtrDeadLock->PtrFathers[i]->hMin == FLT_MAX)
				{
					Tree->PtrDeadlockTail->DeadlockNext = PtrDeadLock->PtrFathers[i];
					Tree->PtrDeadlockTail = PtrDeadLock->PtrFathers[i];
					PtrDeadLock->PtrFathers[i]->isDeadlock = 1;
				}
				else
				{

					for (short j = 0; j < PtrDeadLock->PtrFathers[i]->NumSons; j++)
					{
						if (PtrDeadLock->PtrFathers[i]->Ptrsons[j]->isDeadlock == 0 && PtrDeadLock->PtrFathers[i]->Ptrsons[j]->hMin < h)
						{
							h = PtrDeadLock->PtrFathers[i]->Ptrsons[j]->hMin;
						}
					}
				}
			}
		}
		Tree->Back_num++;
		PtrDeadLock->hMin = (h * 1.5);
		PtrDeadLock = PtrDeadLock->DeadlockNext;
	} 
}

void CalcEarnings(Node* PtrNode)
{
	if (PtrNode->hMin == 0)
		return;
	else
	{
		float Q;
		PtrNode->Earnings = new float[PtrNode->NumSons];
		for (int i = 0; i < PtrNode->NumSons; i++)
		{
			Q = -(PtrNode->Ptrsons[i]->g - PtrNode->g) - PtrNode->Ptrsons[i]->hMin;
			PtrNode->Earnings[i] = Q;
			//cout << PtrNode->Ptrsons[i]->hMin << "Q=" << Q << " " << "t" << *(PtrNode->Ptrsons[i]->PtrFiredTransitions) << "   " << endl;;
			//PtrNode->Earnings.insert(pair<short, float>(i, Q));
			/*if (PtrNode->PtrEarning == nullptr) 
			{
				PtrNode->PtrEarning = new Earning(*(PtrNode->Ptrsons[i]->PtrFiredTransitions), Q);
				PtrNode->PtrEanringHead = PtrNode->PtrEarning;
			}
			else 
				PtrNode->PtrEarning->insert(*(PtrNode->Ptrsons[i]->PtrFiredTransitions), Q);*/
		}
	}
	//cout << endl;
}