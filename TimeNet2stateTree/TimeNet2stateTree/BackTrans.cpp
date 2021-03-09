#include<stdio.h>
#include <stdlib.h> 
#include<float.h>
#include"TreeNode.h"
#include"BackTransH.h"


void BackTransH(Tree *Tree)
{
	Node *PtrNode = Tree->PtrHead;
	while (PtrNode !=NULL)
	{
		PtrNode->DelaysOfTranH = (float *)malloc(sizeof(float) * Tree->transit_num);
		for (int i = 0; i < Tree->transit_num; i++)
		{
			PtrNode->DelaysOfTranH[i] = PtrNode->hMin;
		}
		for (int i = 0; i < PtrNode->NumSons; i++)
		{
			PtrNode->DelaysOfTranH[PtrNode->Ptrsons[i]->PtrFiredTransitions[0]] = PtrNode->Ptrsons[i]->hMin;
		}
		PtrNode = PtrNode->PtrOpenNext;
	}
}