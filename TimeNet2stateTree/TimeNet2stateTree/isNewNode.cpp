#include <stdlib.h> 
#include<stdio.h>
#include <string.h>
#include<float.h>
#include "TreeNode.h"
#include "Completecrosslinkedlist.h"
#include"isNewNode.h"
#include"CreateNextNode.h"

void JudgeFather(Node *NextNode, Tree *Tree) //判断
{
	struct Node *PtrFatherNode;
	NetState *PtrState;
	PtrFatherNode = NextNode->PtrFathers[0];
	while (PtrFatherNode != NULL)
	{
		PtrState = NextNode->PtrNetStateHead;;
		while (PtrState != NULL)
		{
			if (PtrFatherNode->PtrNetStateRow[PtrState->row] != NULL)
			{
				if (PtrState->TokenNum != PtrFatherNode->PtrNetStateRow[PtrState->row]->TokenNum)
				{
					NextNode->isNew = New;
					break;
				}
				else
				{
					NextNode->isNew = Old;
				}
			}
			else
			{
				NextNode->isNew = New;
				break;
			}
			PtrState = PtrState->PtrDown;
		}
		if (PtrState == NULL && NextNode->isNew == Old && NextNode->placeNum == PtrFatherNode->placeNum)
		{
			if (PtrFatherNode->NumTwin == 0)
			{
				PtrFatherNode->PtrSame = (PtrNodeType*)malloc(sizeof(PtrNodeType));
				PtrFatherNode->PtrSame[0] = NextNode;
			}
			else
			{
				PtrFatherNode->PtrSame = (PtrNodeType*)realloc(PtrFatherNode->PtrSame, sizeof(PtrNodeType) * (PtrFatherNode->NumTwin + 1));
				PtrFatherNode->PtrSame[PtrFatherNode->NumTwin] = NextNode;
			}
			PtrFatherNode->NumTwinBack++;
			PtrFatherNode->NumTwin++;
			NextNode->PtrTwin = PtrFatherNode;
			break;
		}
		if (PtrFatherNode->PtrFathers == NULL)
		{
			NextNode->isNew = New;
			break;
		}
		PtrFatherNode = PtrFatherNode->PtrFathers[0];
	}
}

void isNewNode(Node *HeadNode, Node *NextNode, Tree *Tree,float Delay[])
{
	struct Node *PtrCrntOpenNode;
	NetState *Ptrimf;
	PtrCrntOpenNode = HeadNode;
	//int same, isold = 0;

	JudgeFather(NextNode, Tree);

	if (NextNode->isNew == New)
	{
		do
		{
			if (NextNode->g > PtrCrntOpenNode->g || NextNode->g == PtrCrntOpenNode->g)
			{
				Ptrimf = NextNode->PtrNetStateHead;
				while (Ptrimf != NULL)
				{
					if (PtrCrntOpenNode->PtrNetStateRow[Ptrimf->row] != NULL)
					{
						if (Ptrimf->TokenNum != PtrCrntOpenNode->PtrNetStateRow[Ptrimf->row]->TokenNum)
						{
							NextNode->isNew = New;
							break;
						}
						else if (Ptrimf->residenceTime > PtrCrntOpenNode->PtrNetStateRow[Ptrimf->row]->residenceTime)
						{
							NextNode->isNew = New;
							break;
						}
						else
						{
							NextNode->isNew = Old;
						}
					}
					else
					{
						NextNode->isNew = New;
						break;
					}
					Ptrimf = Ptrimf->PtrDown;
				}
				if (NextNode->isNew == Old && NextNode->placeNum == PtrCrntOpenNode->placeNum)
				{
					if (PtrCrntOpenNode->NumTwinBack == 0)
					{
						PtrCrntOpenNode->PtrSame = (PtrNodeType*)malloc(sizeof(PtrNodeType));
						PtrCrntOpenNode->PtrSame[0] = NextNode;
					}
					else
					{
						PtrCrntOpenNode->PtrSame = (PtrNodeType*)realloc(PtrCrntOpenNode->PtrSame, sizeof(PtrNodeType) * (PtrCrntOpenNode->NumTwinBack + 1));
						PtrCrntOpenNode->PtrSame[PtrCrntOpenNode->NumTwinBack] = NextNode;
					}
					PtrCrntOpenNode->NumTwinBack++;
					PtrCrntOpenNode->NumTwin++;
					NextNode->PtrTwin = PtrCrntOpenNode;
					break;
				}
				else
				{
					NextNode->isNew = New;
				}
			}
			else
			{
				NextNode->isNew = New;
			}
			PtrCrntOpenNode = PtrCrntOpenNode->PtrOpenNext;
		} while (PtrCrntOpenNode != NULL);
	}
}



	



	//do//先判断g，再判断m，再判断需要等待时间
	//{
	//	for (short i = 0; i < Tree->place_num; i++)
	//	{
	//		if (NextNode->marking[i] == CrntOpenNode->marking[i])//生成的新标识与链表的第一个结点的标识每一位判断是否相同（相同为真） 
	//		{
	//			same = 1;
	//		}
	//		else
	//		{
	//			same = 0;
	//			break;//标识与第i行不同则退出循环判断下一行 
	//		}
	//	}
	//	if (same == 1)
	//	{
	//		if (NextNode->g > CrntOpenNode->g || NextNode->g == CrntOpenNode->g)
	//		{
	//			for (short i = 0; i < Tree->place_num; i++)
	//			{
	//				if (NextNode->marking[i] != 0 )
	//				{
	//					if (NextNode->NeedWaitingTime[i] < CrntOpenNode->NeedWaitingTime[i])
	//					{
	//						NextNode->isNew = New;
	//						break;
	//					}
	//					else
	//					{
	//						/*isold = isOld(NextNode, Tree, Delay);
	//						if (isold == 0)
	//						{*/
	//						/*NextNode->twin = CrntOpenNode;
	//						if (CrntOpenNode->NumTwinBack == 0)
	//						{
	//							CrntOpenNode->same = (NodeLink*)malloc(sizeof(NodeLink));
	//							CrntOpenNode->same[0] = NextNode;
	//						}
	//						else
	//						{
	//							CrntOpenNode->same = (NodeLink*)realloc(CrntOpenNode->same, sizeof(NodeLink) * (CrntOpenNode->NumTwinBack + 1));
	//							CrntOpenNode->same[CrntOpenNode->NumTwinBack] = NextNode;
	//						}
	//						CrntOpenNode->NumTwinBack++;
	//						CrntOpenNode->NumTwin++;*/
	//						NextNode->isNew = Old;
	//						//break;
	//						//}
	//					}
	//				}
	//			}
	//			if (NextNode->isNew == Old)
	//			{
	//				if (CrntOpenNode->NumTwinBack == 0)
	//				{
	//					CrntOpenNode->same = (NodeLink*)malloc(sizeof(NodeLink));
	//					CrntOpenNode->same[0] = NextNode;
	//				}
	//				else
	//				{
	//					CrntOpenNode->same = (NodeLink*)realloc(CrntOpenNode->same, sizeof(NodeLink) * (CrntOpenNode->NumTwinBack + 1));
	//					CrntOpenNode->same[CrntOpenNode->NumTwinBack] = NextNode;
	//				}
	//				CrntOpenNode->NumTwinBack++;
	//				CrntOpenNode->NumTwin++;
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			NextNode->isNew = New;
	//		}
	//	}
	//	else
	//	{
	//		NextNode->isNew = New;
	//	}
	//	CrntOpenNode = CrntOpenNode->OpenNext;
	//} while (CrntOpenNode != NULL);


//激发子节点判断新旧节点
//void isNewNode(Node *HeadNode, Node *NextNode,Tree *Tree,short Delay[])
//{
//	struct Node *CrntOpenNode;
//	CrntOpenNode = HeadNode;
//	int same,isold = 0,x = 0;
//
//	do
//	{
//		for (short i = 0; i < Tree->place_num; i++)
//		{
//			if (NextNode->marking[i] == CrntOpenNode->marking[i])//生成的新标识与链表的第一个结点的标识每一位判断是否相同（相同为真） 
//			{
//				same = 1;
//			}
//			else
//			{
//				same = 0;
//				break;//标识与第i行不同则退出循环判断下一行 
//			}
//		}
//		if (same == 1)
//		{
//			if (NextNode->g > CrntOpenNode->g || NextNode->g == CrntOpenNode->g)
//			{
//				x = 0;
//				for (short i = 0; i < Tree->place_num; i++)
//				{
//					if (NextNode->residenceTime[i] <= CrntOpenNode->residenceTime[i])
//					{
//						x++;
//					}
//					if ((x+1) == Tree->place_num)
//					{
//						NextNode->twin = CrntOpenNode;
//						/*if (CrntOpenNode->NumTwinBack == 0)
//						{
//							CrntOpenNode->same = (NodeLink*)malloc(sizeof(NodeLink));
//							CrntOpenNode->same[0] = NextNode;
//						}
//						else
//						{
//							CrntOpenNode->same = (NodeLink*)realloc(CrntOpenNode->same, sizeof(NodeLink) * (CrntOpenNode->NumTwinBack + 1));
//							CrntOpenNode->same[CrntOpenNode->NumTwinBack] = NextNode;
//						}
//						CrntOpenNode->NumTwinBack++;*/
//						CrntOpenNode->NumTwin++;
//						NextNode->isNew = Old;
//						break;
//					}
//
//				}
//					//isold = isOld(NextNode, Tree, Delay);
//					//if (isold == 0)
//					//{
//					//	NextNode->twin = CrntOpenNode;
//					//	if (CrntOpenNode->NumTwinBack == 0)
//					//	{
//					//		CrntOpenNode->same = (NodeLink*)malloc(sizeof(NodeLink));
//					//		CrntOpenNode->same[0] = NextNode;
//					//	}
//					//	else
//					//	{
//					//		CrntOpenNode->same = (NodeLink*)realloc(CrntOpenNode->same, sizeof(NodeLink) * (CrntOpenNode->NumTwinBack + 1));
//					//		CrntOpenNode->same[CrntOpenNode->NumTwinBack] = NextNode;
//					//	}
//					//	CrntOpenNode->NumTwinBack++;
//					//	CrntOpenNode->NumTwin++;
//					//	NextNode->isNew = Old;
//					//	break;
//					//}
//					/*if (isold!= 0 && CrntOpenNode->NumTwin != 0)
//					{
//						CrntOpenNode->NumTwin = 0;
//						CrntOpenNode->NumTwinBack = 0;
//						CrntOpenNode->same = NULL;
//						free(CrntOpenNode->same);
//					}*/
//				
//			}
//			else
//			{
//				NextNode->isNew = New;
//			}
//		}
//		else
//		{
//			NextNode->isNew = New;
//		}
//		if (NextNode->isNew == Old)
//		{
//			break;
//		}
//		CrntOpenNode = CrntOpenNode->OpenNext;
//	} while (CrntOpenNode !=NULL);
//}


//void isNewNode2(Node *HeadNode, Node *NextNode,Tree *Tree)
//{
//	struct Node *CrntOpenNode;
//	CrntOpenNode = HeadNode;
//	int same;
//	do
//	{
//		for (short i = 0; i < Tree->place_num; i++)
//		{
//			if (NextNode->marking[i] == CrntOpenNode->marking[i])//生成的新标识与链表的第一个结点的标识每一位判断是否相同（相同为真） 
//			{
//				same = 1;
//			}
//			else
//			{
//				same = 0;
//				break;//标识与第i行不同则退出循环判断下一行 
//			}
//		}
//		if (same == 1)
//		{
//			if (NextNode->g > CrntOpenNode->g || NextNode->g == CrntOpenNode->g)
//			{
//				NextNode->isNew = Old;
//				break;
//			}
//			else
//			{
//				NextNode->isNew = New;
//			}
//		}
//		else
//		{
//			NextNode->isNew = New;
//		}
//		CrntOpenNode = CrntOpenNode->OpenNext;
//	} while (CrntOpenNode != NULL);
//}




//bool isOld(Node *CurntNode, Tree *Tree, float Delay[])
//{
//	short isnew = 0, DelayFireTrans, FireTransition, ImmediatelyFireTrans;
//
//		/*DelayFireTrans = CurntNode->NumEnTransWithDelay;
//		while (DelayFireTrans > 0)
//		{
//			FireTransition = CurntNode->EnTransWithDelay[DelayFireTrans - 1];
//			isnew = isnew + CreateNextNode2(CurntNode, Delay,Tree, FireTransition, WithDelay);
//			DelayFireTrans--;
//		}*/
//	if (CurntNode->NumEnTransZeroInterval > 0)
//	{
//		ImmediatelyFireTrans = CurntNode->NumEnTransZeroInterval;
//		while (ImmediatelyFireTrans > 0)
//		{
//			FireTransition = CurntNode->EnTransZeroInterval[ImmediatelyFireTrans - 1];
//			isnew = isnew + CreateNextNode2(CurntNode, Delay, Tree, FireTransition, ZeroDelay);
//			ImmediatelyFireTrans--;
//		}
//	}
//	if (isnew != 0)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}