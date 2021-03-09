#include"TreeNode.h"
#include "Completecrosslinkedlist.h"
#include "IsEnabled.h"
#include<stdlib.h>

extern CrossMatrixHead C_pre;

/*
 �ж��ڵ�ǰ��ʶ�£���ǨTransition�Ƿ���Լ���
 CrossList SMatrix_C_pre :  ǰ�ù�������
 int current_m[] :  ��ʶ
 int Transition : ��Ǩ
 Return ��int  0��ʾ�ڱ�ʶcurrent_m[]�±�ǨTransition���ܼ�����1�����
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