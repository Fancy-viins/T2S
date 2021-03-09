#include"TreeNode.h"
#include"CreateNode.h"
#include <stdlib.h> 
#include<float.h>
#include<map>
using namespace std;
PtrNodeType CreateNode(short place_num)
{
	PtrNodeType PtrNextNode;
	PtrNextNode = (PtrNodeType)malloc(sizeof(struct Node));
	//NextNode->marking = (short *)malloc(sizeof(short) * place_num);
	//NextNode->residenceTime = (float *)malloc(sizeof(float) * place_num);
	//NextNode->NeedWaitingTime = (float *)malloc(sizeof(float) * place_num);
	PtrNextNode->PtrNetStateHead = NULL;
	PtrNextNode->PtrNetStateRow = (NetState **)malloc(sizeof(NetState *) * place_num);
	for (short i = 0; i < place_num; ++i)
	{
		PtrNextNode->PtrNetStateRow[i] = NULL;
	}
	PtrNextNode->PtrFiredTransitions = NULL;
	PtrNextNode->DeadlockNext = NULL;
	PtrNextNode->g = 0;
	PtrNextNode->hMin = FLT_MAX;
	PtrNextNode->PtrBackDoneNext = NULL;
	PtrNextNode->PtrBackNotDoneNext = NULL;
	PtrNextNode->PtrBackNotDoneBefore = NULL;
	PtrNextNode->TwinIsDone = 0;
	PtrNextNode->PtrSame = NULL;
	PtrNextNode->PtrTwin = NULL;
	PtrNextNode->NumTwinBack = 0;
	PtrNextNode->PtrOpenNext = NULL;
	PtrNextNode->EnTransWithDelay = NULL;
	PtrNextNode->EnTransZeroInterval = NULL;
	PtrNextNode->DelaysOfEnTran = NULL;
	PtrNextNode->NumEnTransZeroInterval = 0;
	PtrNextNode->NumEnTransWithDelay = 0;
	PtrNextNode->PtrFathers = NULL;
	PtrNextNode->Ptrsons = NULL;
	PtrNextNode->NumFathers = 0;
	PtrNextNode->NumSons = 0;
	PtrNextNode->NumSons_Back = 0;
	PtrNextNode->PtrGoalNext = NULL;
	PtrNextNode->isGoal = 0;
	PtrNextNode->isDeadlock = 0;
	PtrNextNode->AClosedNext = NULL;
	PtrNextNode->AStarOpenNext = NULL;
	PtrNextNode->AStarOpenBefore = NULL;
	PtrNextNode->EqualG = 0;
	PtrNextNode->NumTwin = 0;
	PtrNextNode->placeNum = 0;
	PtrNextNode->DelaysOfTranH = NULL;
	PtrNextNode->Earnings = nullptr;
	PtrNextNode->PtrEarning =nullptr;
	PtrNextNode->PtrEanringHead = nullptr;
	//PtrNextNode->PtrEarning->Ptrnext = nullptr;
	//PtrNextNode->Earnings->size();
	//printf("%f",PtrNextNode->Earnings->size());
	//PtrNextNode->Earnings.clear();
	return PtrNextNode;

}