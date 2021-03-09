#include"TreeNode.h"
#include"FindGmin.h"

PtrNodeType FindGmimGoal(Tree *Tree)
{
	PtrNodeType Goal;
	float Gmin;
	Goal = Tree->PtrGoalHead;
	Gmin = Goal->g;
	do
	{
		if (Gmin > Goal->g)
		{
			Gmin = Goal->g;
		}
		Goal = Goal->PtrGoalNext;
	} while (Goal != NULL);
	Goal = Tree->PtrGoalHead;
	do
	{
		if (Goal->g == Gmin)
		{
			break;
		}
		Goal = Goal->PtrGoalNext;
	} while (Goal != NULL);
	printf("Gmin:%.1f\n", Gmin);
	return Goal;
}