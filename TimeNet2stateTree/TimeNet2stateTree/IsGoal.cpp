#include"TreeNode.h"
#include"IsGoal.h"
#include"JudgeGoal.h"
#include"GoalH.h"
#include <stdio.h>

void IsGoal(Node *NextNode, Tree *Tree) 
{
	if (JudgeGoal(NextNode, Tree->NumGoal, Tree->GoalMarking, Tree->GoalPlace) == 1)
	{
		NextNode->isGoal = 1;
		NextNode->hMin = 0;
		if (Tree->PtrGoalHead == NULL)
		{
			Tree->PtrGoalHead = NextNode;
			Tree->PtrBackDoneHead = NextNode;
			
		}
		else
		{
			Tree->PtrGoalTail->PtrGoalNext = NextNode;
			Tree->PtrBackDoneTail->PtrBackDoneNext = NextNode;
		}
		Tree->PtrGoalTail = NextNode;
		Tree->PtrBackDoneTail = NextNode;
	}

}
void IsGoal_v2(Node *NextNode, Tree *Tree)
{
	short isGoal;
	float h;
	isGoal = JudgeGoal_v2(NextNode);
	if (isGoal == 1)
	{
		h = NextNode->hMin;
		NextNode->hMin = GoalH(NextNode, Tree);
		if (NextNode->hMin != -1)
		{
			NextNode->isGoal = 1;
			if (Tree->PtrGoalHead == NULL)
			{
				Tree->PtrGoalHead = NextNode;
				Tree->PtrBackDoneHead = NextNode;

			}
			else
			{
				Tree->PtrGoalTail->PtrGoalNext = NextNode;
				Tree->PtrBackDoneTail->PtrBackDoneNext = NextNode;
			}
			Tree->PtrGoalTail = NextNode;
			Tree->PtrBackDoneTail = NextNode;
		}
		else
		{
			NextNode->hMin = h;
		}
	}
}


