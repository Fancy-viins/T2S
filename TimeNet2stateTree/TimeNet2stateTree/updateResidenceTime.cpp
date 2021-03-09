#include"TreeNode.h"
#include"updateResidenceTime.h"
#include<stdio.h>
#include<float.h>

void updateResidenceTime(Node *NextNode, Node *CurntNode, float Delay[], short place_num, bool WhetherDelay, short Transition)
{
	float Interval;
	NetState * PtrImf;
	PtrImf = NextNode->PtrNetStateHead;
	if (WhetherDelay != 0)
	{
		short Tans;
		for (int i = 0; i < CurntNode->NumEnTransWithDelay; i++)
		{
			if (CurntNode->EnTransWithDelay[i] == Transition)
			{
				Tans = i;
			}
		}
		Interval = CurntNode->DelaysOfEnTran[Tans];
	}
	else
	{
		Interval = 0;
	}
	if (CurntNode->NumEnTransWithDelay>1)
	{
		printf("Interval:%d\n", Interval);
	}

	NextNode->g = CurntNode->g + Interval;

	while (PtrImf !=NULL)
	{
		if (Delay[PtrImf->row] != 0 && CurntNode->PtrNetStateRow[PtrImf->row] != NULL)
		{
			PtrImf->residenceTime = CurntNode->PtrNetStateRow[PtrImf->row]->residenceTime + Interval;
			if (PtrImf->residenceTime > Delay[PtrImf->row])
			{
				PtrImf->residenceTime = Delay[PtrImf->row];
			}
		}
		if (PtrImf->residenceTime != 0)
		{
			if (PtrImf->residenceTime < Delay[PtrImf->row])
			{
				PtrImf->NeedWaitingTime = Delay[PtrImf->row] - PtrImf->residenceTime;
			}
			else
			{
				PtrImf->NeedWaitingTime = 0;
			}
		}
		PtrImf = PtrImf->PtrDown;
	}








	//printf("NextNode->residenceTime:");
	/*for (int NumInterval=0; NumInterval < place_num; NumInterval++)
	{
		if (Delay[NumInterval] == 0)
		{
			NextNode->residenceTime[NumInterval] = 0;
		}
		else
		{
			if (CurntNode->marking[NumInterval] == 0)
			{
				NextNode->residenceTime[NumInterval] = 0;
			}
			else
			{
				if (NextNode->marking[NumInterval] == 0 )
				{
					NextNode->residenceTime[NumInterval] = 0;
				}
				else
				{
					NextNode->residenceTime[NumInterval] = CurntNode->residenceTime[NumInterval] + Interval;
				}
			}
		}
		if (NextNode->residenceTime[NumInterval] > Delay[NumInterval])
		{
			NextNode->NeedWaitingTime[NumInterval] = 0;
		}
		else if(NextNode->residenceTime[NumInterval] != 0)
		{
			NextNode->NeedWaitingTime[NumInterval] = Delay[NumInterval] - NextNode->residenceTime[NumInterval];
		}
		else
		{
			NextNode->NeedWaitingTime[NumInterval] = FLT_MAX;
		}
	}*/
	
}