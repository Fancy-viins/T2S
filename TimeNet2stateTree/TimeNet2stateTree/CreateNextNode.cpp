#include"TreeNode.h"
#include"CreateNode.h"
#include"CnectFather.h"
#include"CnectSon.h"
#include"FireInterval.h"
#include"isNewNode.h"
#include"IsDeadlock.h"
#include"IsGoal.h"
#include"CnectTwin.h"
#include"destory.h"
#include"CreateNextNode.h"
#include"UpdateM.h"
#include"updateResidenceTime.h"
#include<stdio.h>

void CreateNextNode(Node *CurntNode, float Delay[], Tree *Tree, short FireTransition,bool WhetherDelay)
{
	PtrNodeType PtrNextNode;//指针改ptr
	PtrNextNode = CreateNode(Tree->place_num);
	Tree->node_num++;
	PtrNextNode->markingID = Tree->node_num;
	UpdateM(PtrNextNode, FireTransition, Tree->place_num, CurntNode);
	updateResidenceTime(PtrNextNode, CurntNode, Delay, Tree->place_num, WhetherDelay, FireTransition);
	CnectFather(PtrNextNode, CurntNode, FireTransition);
	CnectSon(PtrNextNode, CurntNode);
	FireInterval(PtrNextNode, Delay,Tree->place_num,Tree->transit_num);
	IsGoal(PtrNextNode, Tree);
	isNewNode(Tree->PtrHead,PtrNextNode,Tree,Delay);
	IsDeadlock(PtrNextNode, Tree);//改顺序
	if (PtrNextNode->isNew == Old)
	{
		//CnectTwin(PtrNextNode, CurntNode);
		//destory(PtrNextNode, Tree->place_num);
	}
	else
	{
		Tree->PtrOpenTail->PtrOpenNext = PtrNextNode;
		Tree->PtrOpenTail = PtrNextNode;
	}
}
void CreateNextNode_v2(Node *CurntNode, float Delay[], Tree *Tree, short FireTransition, bool WhetherDelay)
{
	PtrNodeType PtrNextNode;//指针改ptr
	PtrNextNode = CreateNode(Tree->place_num);
	Tree->node_num++;
	PtrNextNode->markingID = Tree->node_num;
	//if (PtrNextNode->markingID == 420)
	//{
	//	printf("1");
	//}
	UpdateM(PtrNextNode, FireTransition, Tree->place_num, CurntNode);
	updateResidenceTime(PtrNextNode, CurntNode, Delay, Tree->place_num, WhetherDelay, FireTransition);
	CnectFather(PtrNextNode, CurntNode, FireTransition);
	CnectSon(PtrNextNode, CurntNode);
	FireInterval(PtrNextNode, Delay, Tree->place_num, Tree->transit_num);
	IsGoal_v2(PtrNextNode, Tree);
	isNewNode(Tree->PtrHead, PtrNextNode, Tree, Delay);
	if (PtrNextNode->isNew == Old)
	{
		//CnectTwin(NextNode, CurntNode);
		//destory(NextNode, Tree->place_num);
	}
	else
	{
		IsDeadlock(PtrNextNode, Tree);
		Tree->PtrOpenTail->PtrOpenNext = PtrNextNode;
		Tree->PtrOpenTail = PtrNextNode;
	}
}
//bool CreateNextNode2(Node *CurntNode, float Delay[], Tree *Tree, short FireTransition, bool WhetherDelay)
//{
//	NodeLink NextNode;//指针改ptr
//	bool isNew;
//	NextNode = CreateNode(Tree->place_num);
//	UpdateM(NextNode, FireTransition, Tree->place_num, CurntNode);
//	updateResidenceTime(NextNode, CurntNode, Delay, Tree->place_num,WhetherDelay);
//	isNewNode2(Tree->Head, NextNode, Tree);
//	isNew = NextNode->isNew;
//	destory(NextNode, Tree->place_num);
//	return isNew;
//	//if (NextNode->isNew == New && (NextNode->isGoal == 1 || CurntNode->isGoal == 1))
//	//{
//	//	return NextNode->isNew;
//	//}
//	//else
//	//{
//	//	
//	//	/*CnectFather(NextNode, CurntNode, FireTransition);
//	//	CnectSon(NextNode, CurntNode);
//	//	FireInterval(NextNode, Delay, Tree->place_num, Tree->transit_num);*/
//	//	//isNewNode2(Tree->Head, NextNode,Delay,Tree);
//
//	//	if (NextNode->isNew != Old)
//	//	{
//	//		CnectFather(NextNode, CurntNode, FireTransition);
//	//		CnectSon(NextNode, CurntNode);
//	//		FireInterval(NextNode, Delay, Tree->place_num, Tree->transit_num);
//	//		IsDeadlock(NextNode, Tree);
//	//		IsGoal(NextNode, Tree);
//	//		Tree->OpenTail->OpenNext = NextNode;
//	//		Tree->OpenTail = NextNode;
//	//	}
//	//	return NextNode->isNew;
//	//}
//	
//}


