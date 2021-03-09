#include<stdio.h>
#include <stdlib.h> 
#include"InitialRootNode.h"
#include"TreeNode.h"
#include "Completecrosslinkedlist.h"
#include"CreateNode.h"
#include"FireInterval.h"
#include"IsDeadlock.h"
#include"IsGoal.h"
#include<float.h>


PtrNodeType InitialRootNode(short palce_num, short transit_num, float Delay[], short M0[], Tree *Tree)
{
	PtrNodeType PtrRootNode;
	NetState * PtrNext , *PtrLast = NULL;
	PtrRootNode = CreateNode(palce_num);
	for (short i=0; i < palce_num; i++)
	{
		if (M0[i] != 0)
		{
			PtrNext = (NetState *)malloc(sizeof(NetState));
			PtrNext->TokenNum = M0[i];
			PtrNext->NeedWaitingTime = 0;
			PtrNext->residenceTime = 0;
			PtrNext->row = i;
			PtrNext->PtrDown = NULL;
			PtrRootNode->PtrNetStateRow[i] = PtrNext;
			if (PtrRootNode->PtrNetStateHead == NULL)
			{
				PtrRootNode->PtrNetStateHead = PtrNext;
			}
			else
			{
				PtrLast->PtrDown = PtrNext;
			}
			PtrLast = PtrNext;
			PtrRootNode->placeNum++;
		}
	}

	PtrRootNode->markingID = 0;
	PtrRootNode->isNew = New;
	FireInterval(PtrRootNode, Delay, palce_num, transit_num);
	IsDeadlock(PtrRootNode, Tree);
	IsGoal(PtrRootNode,Tree);
	return PtrRootNode;

}

PtrNodeType InitialRootNode_v2(short palce_num, short transit_num, float Delay[], short M0[], Tree *Tree)
{
	PtrNodeType PtrRootNode;
	NetState * PtrNext, *PtrLast = NULL;
	PtrRootNode = CreateNode(palce_num);
	for (short i = 0; i < palce_num; i++)
	{
		if (M0[i] != 0)
		{
			PtrNext = (NetState *)malloc(sizeof(NetState));
			PtrNext->TokenNum = M0[i];
			PtrNext->NeedWaitingTime = 0;
			PtrNext->residenceTime = 0;
			PtrNext->row = i;
			PtrNext->PtrDown = NULL;
			PtrRootNode->PtrNetStateRow[i] = PtrNext;
			if (PtrRootNode->PtrNetStateHead == NULL)
			{
				PtrRootNode->PtrNetStateHead = PtrNext;
			}
			else
			{
				PtrLast->PtrDown = PtrNext;
			}
			PtrLast = PtrNext;
			PtrRootNode->placeNum++;
		}
	}

	PtrRootNode->markingID = 0;
	PtrRootNode->isNew = New;
	FireInterval(PtrRootNode, Delay, palce_num, transit_num);
	IsDeadlock(PtrRootNode, Tree);
	IsGoal_v2(PtrRootNode, Tree);
	return PtrRootNode;

}