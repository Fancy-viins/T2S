#include <stdlib.h> 
#include <stdio.h>
#include "TreeNode.h"
#include"destory.h"

void destory(Node *NextNode, short place_num)
{
	//for (short i = 0; i < place_num; i++)
	//{
	//	NextNode->marking[i] = 0;
	//	NextNode->residenceTime[i] = 0;
	//	NextNode->NeedWaitingTime[i] = 0;
	//}
	NextNode->g = 0;
	NextNode->hMin = 0;
	NextNode->markingID = 0;

	//free(NextNode->marking);
	//NextNode->marking = NULL;

	//free(NextNode->residenceTime);
	//NextNode->residenceTime = NULL;

	//free(NextNode->NeedWaitingTime);
	//NextNode->residenceTime = NULL;

	free(NextNode);
	NextNode = NULL;
}


void DesImf(Node *NextNode,NetState * imf)
{
	short i;
	i = imf->row;
	imf->row = 0;
	imf->PtrDown = NULL;
	free(NextNode->PtrNetStateRow[i]);
	NextNode->PtrNetStateRow[i] = NULL;
}