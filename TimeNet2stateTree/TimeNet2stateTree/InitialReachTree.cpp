#include<stdio.h>
#include"InitialReachTree.h"
#include"TreeNode.h"


Tree* InitialReachTree(short place_num, short transit_num)
{
	Tree Tree;
	Tree.node_num = 0;
	Tree.PtrHead = NULL;
	Tree.PtrOpenTail = NULL;
	Tree.PtrGoalHead = NULL;
	Tree.PtrGoalTail = NULL;
	Tree.PtrDeadlockHead = NULL;
	Tree.PtrDeadlockTail = NULL;
	Tree.PtrBackDoneHead = NULL;
	Tree.PtrBackDoneTail = NULL;
	Tree.GoalMarking = NULL;
	Tree.GoalPlace = NULL;
	Tree.PtrBackNotDoneHead = NULL;
	Tree.PtrBackNotDoneTail = NULL;
	Tree.Back_num = 0;
	Tree.NumGoal = 0;
	Tree.place_num = place_num;
	Tree.transit_num = transit_num;
	return &Tree;
}