#include"TreeNode.h"
#include"CnectSon.h"
#include <stdlib.h> 

void CnectSon(Node *NextNode, Node *CurntNode)
{
	CurntNode->NumSons++;
	CurntNode->NumSons_Back++;
	if (CurntNode->NumSons > 1)
	{
		CurntNode->Ptrsons = (PtrNodeType*)realloc(CurntNode->Ptrsons, CurntNode->NumSons * sizeof(PtrNodeType));
	}
	else
	{
		CurntNode->Ptrsons = (PtrNodeType*)malloc(sizeof(PtrNodeType));
	}
	CurntNode->Ptrsons[CurntNode->NumSons - 1] = NextNode;
}