#include <stdlib.h> 
#include<stdio.h>
#include "TreeNode.h"
#include "Completecrosslinkedlist.h"
#include"FireInterval.h"
#include"IsEnabled.h"

extern CrossMatrixHead C_pre;

void FireInterval(Node *NextNode, float Delay[], short place_num, short transit_num)
{
	ptrMatrixElement PtrNextValue;
	short Transition, is_enalbe;
	float ans, Interval, step = 0;
	//float *x = (float *)malloc(sizeof(float) * place_num);
	//for (short i = 0; i < place_num; i++)
	//{
	//	x[i] = NextNode->residenceTime[i];
	//}
	for (Transition = 0; Transition < transit_num; Transition++)
	{
		step = 0;
		PtrNextValue = C_pre.chead[Transition];
		is_enalbe = IsEnabled(Transition,NextNode);
		if (is_enalbe == 1)
		{
			while (PtrNextValue != NULL) //更新step 
			{
				if (NextNode->PtrNetStateRow[PtrNextValue->row] != NULL)
				{
					ans = Delay[PtrNextValue->row] * (PtrNextValue->element) - NextNode->PtrNetStateRow[PtrNextValue->row]->residenceTime;                //损耗时间=赋时时间*前置值-已等待时间      
				}
				else
				{
					ans = Delay[PtrNextValue->row] * (PtrNextValue->element);
				}
				//ans = Delay[NextValue->row] * (NextValue->element) - x[NextValue->row];                //损耗时间=赋时时间*前置值-已等待时间      
				if (ans > step)                //与0做比较
					step = ans;
				PtrNextValue = PtrNextValue->down;
			}
			Interval = step;
			if (Interval == 0)
			{
				if (NextNode->NumEnTransZeroInterval == 0)
				{
					NextNode->EnTransZeroInterval = (short*)malloc(sizeof(short));
					NextNode->EnTransZeroInterval[0] = Transition;
				}
				else
				{
					NextNode->EnTransZeroInterval = (short*)realloc(NextNode->EnTransZeroInterval, (NextNode->NumEnTransZeroInterval + 1) * sizeof(short));
					NextNode->EnTransZeroInterval[NextNode->NumEnTransZeroInterval] = Transition;

				}
				NextNode->NumEnTransZeroInterval++;
			}
			else
			{
				if (NextNode->NumEnTransWithDelay == 0)
				{
					NextNode->EnTransWithDelay = (short*)malloc(sizeof(short));
					NextNode->DelaysOfEnTran = (float*)malloc(sizeof(float));
					NextNode->DelaysOfEnTran[0] = Interval;
					NextNode->EnTransWithDelay[0] = Transition;
				}
				else
				{
					NextNode->EnTransWithDelay = (short*)realloc(NextNode->EnTransWithDelay, (NextNode->NumEnTransWithDelay + 1) * sizeof(short));
					NextNode->EnTransWithDelay[NextNode->NumEnTransWithDelay] = Transition;
					NextNode->DelaysOfEnTran = (float*)realloc(NextNode->DelaysOfEnTran, (NextNode->NumEnTransWithDelay + 1) * sizeof(float));
					NextNode->DelaysOfEnTran[NextNode->NumEnTransWithDelay] = Interval;
				}

				NextNode->NumEnTransWithDelay++;
			}
		}

	}
}