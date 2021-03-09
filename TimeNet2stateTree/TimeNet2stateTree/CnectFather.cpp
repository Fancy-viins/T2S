#include"TreeNode.h"
#include"CnectFather.h"
#include <stdlib.h> 
#include<stdio.h>

void CnectFather(Node *NextNode, Node *CurntNode, short FireTransition)
{
	NextNode->NumFathers++;
	NextNode->PtrFathers = (PtrNodeType*)malloc(sizeof(PtrNodeType));
	NextNode->PtrFathers[0] = CurntNode;
	NextNode->PtrFiredTransitions = (short*)malloc(sizeof(short));
	NextNode->PtrFiredTransitions[0] = FireTransition;
	//printf("FireTransition:%d\n", NextNode->firedTransitions[0]);
}