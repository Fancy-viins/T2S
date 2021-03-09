#include"TreeNode.h"
#include"JudgeGoal.h"
#include<stdlib.h>
const int NumWork1 = 3;
const int NumWork2 = 3;
const int NumWork3 = 3;

short JudgeGoal(Node *NextNode, short NumGoal, short *GoalMarking, short *GoalPlace)
{
	if (NumGoal != 0)
	{
		short Goal = 1, place;

		for (int i = 0; i < NumGoal; i++)
		{
			place = GoalPlace[i];
			if (NextNode->PtrNetStateRow[place] != NULL)
			{
				if (NextNode->PtrNetStateRow[place]->TokenNum != GoalMarking[i])
				{
					Goal = 0;
					break;
				}
			}
			else
			{
				Goal = 0;
				break;
			}
			/*if (NextNode->marking[place] != GoalMarking[i])
			{
				Goal = 0;
				break;
			}*/
		}
		if (Goal == 1)
		{
			NextNode->isGoal = 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

bool JudgeGoal_v2(Node *NextNode)
{
	NetState *imfo = NextNode->PtrNetStateHead;
	int workpiece1 = 0, workpiece2 = 0, workpiece3 = 0;
	while (imfo !=NULL)
	{
		if (imfo->row < 8)
		{
			workpiece1+= imfo->TokenNum;
		}
		else if (imfo->row < 17 && imfo->row > 8)
		{
			workpiece2+= imfo->TokenNum;
		}
		else if (imfo->row < 26 && imfo->row > 17)
		{
			workpiece3+= imfo->TokenNum;
		}
		imfo = imfo->PtrDown;
	}
	return workpiece1 <= NumWork1 && workpiece2 <= NumWork2 && workpiece3 <= NumWork3;
}
