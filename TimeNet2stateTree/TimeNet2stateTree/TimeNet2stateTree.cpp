#include<stdio.h>
#include<stdlib.h>
#include "Completecrosslinkedlist.h"
#include"InitialReachTree.h"
#include"InitialRootNode.h"
#include"DataRead.h"
#include"TreeNode.h"
#include"CreateNextNode.h"
#include"OutPut.h"
#include"Tree2HStar.h"
#include"optimal.h"
#include "time.h"
#include"deleteSameNode.h"
#include"BackTransH.h"
#include<future>


CrossMatrixHead C_pre, C_post;
CrossMatrixHead C;


void TimeNet2stateTree()
{

	InitSMatrix(&C_pre);
	printf("����ǰ�ù�������C_pre: ");
	CreateSMatrix(&C_pre, "E:\\git\\learngit\\T2S\\TimeNet2stateTree\\������\\pre.txt");
	OutputSMatrix(C_pre);
	printf("\n");

	InitSMatrix(&C_post);
	printf("�������ù�������C_post: ");
	CreateSMatrix(&C_post, "E:\\git\\learngit\\T2S\\TimeNet2stateTree\\������\\post.txt");
	OutputSMatrix(C_post);
	printf("\n");

	CompuSMatrix(C_post, C_pre, &C);
	printf("��������SMatrix_C: ");
	OutputSMatrix(C);
	printf("\n");

	clock_t start_time, end_time;
	start_time = clock();   //��ȡ��ʼִ��ʱ��

	short place_num = C.RowNum;      //��������
	short transit_num = C.ColunmNum; //��Ǩ����
	short *M0 = (short *)malloc(sizeof(short) * place_num);           //��ʼ��ʶ     ��ʾ��ʮ������m,x,needtime
	float *Delay = (float *)malloc(sizeof(float) * place_num);           //��ʱʱ��  ��ʾ��ʮ������
	short DelayFireTrans, FireTransition, ImmediatelyFireTrans;
	
	Tree Tree;
	PtrNodeType PtrCurntNode;

	Tree = *(InitialReachTree(place_num, transit_num));
	DataRead(place_num, M0, Delay,&Tree);
	PtrCurntNode=InitialRootNode(place_num, transit_num, Delay, M0, &Tree);
	Tree.PtrHead=Tree.PtrOpenTail = PtrCurntNode;
	printf("begin state tree\n");

	do
	{
		if (PtrCurntNode->isGoal != 1)
		{
			if (PtrCurntNode->NumEnTransWithDelay > 0)
			{
				DelayFireTrans = PtrCurntNode->NumEnTransWithDelay;
				while (DelayFireTrans > 0)
				{
					FireTransition = PtrCurntNode->EnTransWithDelay[DelayFireTrans - 1];
					CreateNextNode(PtrCurntNode, Delay, &Tree, FireTransition, WithDelay);
					DelayFireTrans--;
					}
			}
			if (PtrCurntNode->NumEnTransZeroInterval > 0)
			{
				ImmediatelyFireTrans = PtrCurntNode->NumEnTransZeroInterval;
				while (ImmediatelyFireTrans > 0)
				{
					FireTransition = PtrCurntNode->EnTransZeroInterval[ImmediatelyFireTrans - 1];
					CreateNextNode(PtrCurntNode, Delay, &Tree, FireTransition, ZeroDelay);
					ImmediatelyFireTrans--;
				}
			}	
		}
		PtrCurntNode = PtrCurntNode->PtrOpenNext;
		//output(&Tree);
		//outputpy(&Tree);
	} while (PtrCurntNode != NULL);
	printf("over state tree\n");

	stateTree2HStar(&Tree);
	//BackTransH(&Tree);
	std::future<void> BackTransH_ = std::async(BackTransH, &Tree);
	OutputBackHTrans(&Tree);
	std::future<void> outback_ = std::async(outback, &Tree);
	//outback(&Tree);
	//optimal(&Tree);
	std::future<void> output_ = std::async(output, &Tree);
	//output(&Tree);
	std::future<void> outputpy_ = std::async(outputpy, &Tree);
	//outputpy(&Tree);
	outputpy_.wait();
	printf("Num:%d\n", Tree.node_num);

	end_time = clock();     //��ȡ����ʱ��
	double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("%f seconds\n", Times);
}


void TimeNet2stateTree_v2()
{
	InitSMatrix(&C_pre);
	printf("����ǰ�ù�������C_pre: ");
	CreateSMatrix(&C_pre, "E:\\TimeNet2stateTree\\Data\\pre.txt");
	OutputSMatrix(C_pre);
	printf("\n");

	InitSMatrix(&C_post);
	printf("�������ù�������C_post: ");
	CreateSMatrix(&C_post, "E:\\TimeNet2stateTree\\Data\\post.txt");
	OutputSMatrix(C_post);
	printf("\n");

	CompuSMatrix(C_post, C_pre, &C);
	printf("��������SMatrix_C: ");
	OutputSMatrix(C);
	printf("\n");

	clock_t start_time, end_time;
	start_time = clock();   //��ȡ��ʼִ��ʱ��

	short place_num = C.RowNum;      //��������
	short transit_num = C.ColunmNum; //��Ǩ����
	short *M0 = (short *)malloc(sizeof(short) * place_num);           //��ʼ��ʶ     
	float *Delay = (float *)malloc(sizeof(float) * place_num);           //��ʱʱ��  
	short DelayFireTrans, FireTransition, ImmediatelyFireTrans;


	Tree Tree;
	PtrNodeType PtrCurntNode;

	Tree = *(InitialReachTree(place_num, transit_num));
	DataRead_v2(place_num, M0, Delay, &Tree);
	PtrCurntNode = InitialRootNode_v2(place_num, transit_num, Delay, M0, &Tree);
	Tree.PtrHead = Tree.PtrOpenTail = PtrCurntNode;

	printf("begin state tree\n");

	if (PtrCurntNode->isDeadlock != 1)
	{
		do
		{
			if (PtrCurntNode->isGoal != 1)
			{
				if (PtrCurntNode->NumEnTransWithDelay > 0)
				{
					DelayFireTrans = PtrCurntNode->NumEnTransWithDelay;
					while (DelayFireTrans > 0)
					{
						FireTransition = PtrCurntNode->EnTransWithDelay[DelayFireTrans - 1];
						CreateNextNode_v2(PtrCurntNode, Delay, &Tree, FireTransition, WithDelay);
						DelayFireTrans--;
					}
				}
				if (PtrCurntNode->NumEnTransZeroInterval > 0)
				{
					ImmediatelyFireTrans = PtrCurntNode->NumEnTransZeroInterval;
					while (ImmediatelyFireTrans > 0)
					{
						FireTransition = PtrCurntNode->EnTransZeroInterval[ImmediatelyFireTrans - 1];
						CreateNextNode_v2(PtrCurntNode, Delay, &Tree, FireTransition, ZeroDelay);
						ImmediatelyFireTrans--;
					}
				}
			}
			PtrCurntNode = PtrCurntNode->PtrOpenNext;
			//outputpy(&Tree);
		} while (PtrCurntNode != NULL);
	}
	printf("over state tree\n");

	stateTree2HStar(&Tree);
	outback(&Tree);

	//output(&Tree);
	//outputpy(&Tree);
	printf("Num:%d\n", Tree.node_num);
	end_time = clock();     //��ȡ����ʱ��
	double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("%f seconds\n", Times);
}

int main()
{
	TimeNet2stateTree();
}


