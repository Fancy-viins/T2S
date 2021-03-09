#include<stdio.h>
#include"TreeNode.h"
#include"optimal.h"
#include"FindGMin.h"

void optimal(Tree *Tree)
{
	PtrNodeType PtrGoal,PtrNode;
	PtrGoal = FindGmimGoal(Tree);
	PtrNode = Tree->PtrHead;
	do
	{
		if ((PtrNode->g + PtrNode->hMin) == PtrGoal->g)
		{
			PtrNode->EqualG = 1;
		}
		PtrNode = PtrNode->PtrOpenNext;
	} while (PtrNode !=NULL);
}