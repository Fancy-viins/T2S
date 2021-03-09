#include"TreeNode.h"
#include "Completecrosslinkedlist.h"
#include "IsEnabled.h"
#include<stdlib.h>

extern CrossMatrixHead C_pre;

/*
 判断在当前标识下，变迁Transition是否可以激发
 CrossList SMatrix_C_pre :  前置关联矩阵
 int current_m[] :  标识
 int Transition : 变迁
 Return ：int  0表示在标识current_m[]下变迁Transition不能激发，1则可以
*/
bool IsEnabled(short Transition,Node * NextNode)
{
	ptrMatrixElement PtrNextValue;
	PtrNextValue = C_pre.chead[Transition];
	while (PtrNextValue)
	{

		if (NextNode->PtrNetStateRow[PtrNextValue->row] == NULL)
		{
			return  0;
		}
		else
		{
			if (NextNode->PtrNetStateRow[PtrNextValue->row]->TokenNum >= PtrNextValue->element || NextNode->PtrNetStateRow[PtrNextValue->row]->TokenNum == PtrNextValue->element)
			{
				PtrNextValue = PtrNextValue->down;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;


}