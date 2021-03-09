#include <stdlib.h> 
#include <stdio.h>
#include "TreeNode.h"
#include"CnectTwin.h"


void CnectTwin(Node *NextNode, Node *CurntNode)
{
	//printf("NextNode->->twin->ID:%d\n", NextNode->twin->markingID);
	NextNode->PtrTwin->NumFathers++;
	NextNode->PtrTwin->PtrFathers = (PtrNodeType*)realloc(NextNode->PtrTwin->PtrFathers, NextNode->PtrTwin->NumFathers * sizeof(PtrNodeType));
	NextNode->PtrTwin->PtrFathers[NextNode->PtrTwin->NumFathers - 1] = CurntNode;
	NextNode->PtrTwin->PtrFiredTransitions = (short*)realloc(NextNode->PtrTwin->PtrFiredTransitions, NextNode->PtrTwin->NumFathers * sizeof(short));
	NextNode->PtrTwin->PtrFiredTransitions[NextNode->PtrTwin->NumFathers - 1] = NextNode->PtrFiredTransitions[0];
	CurntNode->Ptrsons[CurntNode->NumSons - 1] = NextNode->PtrTwin;
}


