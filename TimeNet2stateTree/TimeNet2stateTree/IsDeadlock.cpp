#include"TreeNode.h"
#include"IsDeadlock.h"
#include <stdio.h>

void IsDeadlock(Node *NextNode,Tree *Tree)
{
	if (NextNode->EnTransZeroInterval == NULL && NextNode->EnTransWithDelay == NULL)
	{
		NextNode->isDeadlock = 1;
		if (Tree->PtrDeadlockHead == NULL)
		{
			Tree->PtrDeadlockHead = NextNode;
		}
		else
		{
			Tree->PtrDeadlockTail->DeadlockNext = NextNode;
		}
		Tree->PtrDeadlockTail = NextNode;
	}
}