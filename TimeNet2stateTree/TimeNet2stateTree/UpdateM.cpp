#include"Completecrosslinkedlist.h"
#include"TreeNode.h"
#include"UpdateM.h"
#include"destory.h"
#include <stdlib.h> 
#include<stdio.h>

extern CrossMatrixHead C;

void  UpdateM(Node *NextNode, short Transition, short place_num, Node *CurntNode)
{
	ptrMatrixElement PtrNextPlace;
	NetState * PtrNextImf,*PtrNew,*PtrPrior = NULL;
	PtrNextPlace = C.chead[Transition];//C
	PtrNextImf = CurntNode->PtrNetStateHead;//m

	while (PtrNextImf != NULL)  //�Ѹ����ı�ʶ���Ƶ���ǰ���
	{
		NextNode->placeNum++;
		PtrNew = (NetState *)malloc(sizeof(NetState));
		PtrNew->TokenNum = PtrNextImf->TokenNum;
		PtrNew->NeedWaitingTime = 0;
		PtrNew->residenceTime = 0;
		PtrNew->row = PtrNextImf->row;
		PtrNew->PtrDown = NULL;
		NextNode->PtrNetStateRow[PtrNew->row] = PtrNew;
		if (NextNode->PtrNetStateHead == NULL)
		{
			NextNode->PtrNetStateHead = PtrNew;
		}
		else
		{
			PtrPrior->PtrDown = PtrNew;
		}
		PtrPrior = PtrNew;
		PtrNextImf = PtrNextImf->PtrDown;
	}
	while (PtrNextPlace !=NULL)  //�±�ʶ�ĸ���
	{
		PtrPrior = NULL;
		PtrNew = NULL;
		if (NextNode->PtrNetStateRow[PtrNextPlace->row] != NULL) //�ж��Ƿ��л���token�Ŀ���Ҫ����token
		{
			NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum = NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum + PtrNextPlace->element;
			if (NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum == 0) //��ǰ����tokenΪ0��ɾ���ṹ��
			{
				NextNode->placeNum--;
				if (NextNode->PtrNetStateHead == NextNode->PtrNetStateRow[PtrNextPlace->row])
				{
					NextNode->PtrNetStateHead = NextNode->PtrNetStateHead->PtrDown;
					DesImf(NextNode, NextNode->PtrNetStateRow[PtrNextPlace->row]);
				}
				else
				{
					PtrPrior = NextNode->PtrNetStateHead;
					PtrNew = PtrPrior->PtrDown;
					do
					{
						if (PtrNew == NextNode->PtrNetStateRow[PtrNextPlace->row])
						{
							PtrPrior->PtrDown = PtrNew->PtrDown;
							DesImf(NextNode, NextNode->PtrNetStateRow[PtrNextPlace->row]);
							break;
						}
						PtrPrior = PtrPrior->PtrDown;
						PtrNew = PtrNew->PtrDown;
					} while (PtrNew != NULL);
				}
			}
		}
		else
		{
			NextNode->placeNum++;
			PtrNew = (NetState *)malloc(sizeof(NetState));
			PtrNew->TokenNum = PtrNextPlace->element;
			PtrNew->NeedWaitingTime = 0;
			PtrNew->residenceTime = 0;
			PtrNew->row = PtrNextPlace->row;
			PtrNew->PtrDown = NULL;
			NextNode->PtrNetStateRow[PtrNew->row] = PtrNew;

			PtrPrior = NextNode->PtrNetStateHead;
			do
			{
				if (PtrPrior->row > PtrNew->row && PtrPrior == NextNode->PtrNetStateHead)  //  ��next��
				{
					NextNode->PtrNetStateHead = PtrNew;
					PtrNew->PtrDown = PtrPrior;
					break;
				}
				else if (PtrPrior->PtrDown == NULL)  //�� next ��
				{
					PtrPrior->PtrDown = PtrNew;
					break;
				}
				else if (PtrPrior->row < PtrNew->row && PtrPrior->PtrDown->row > PtrNew->row)  // �� next ��
				{
					PtrNew->PtrDown = PtrPrior->PtrDown;
					PtrPrior->PtrDown = PtrNew;
					break;
				}
				PtrPrior = PtrPrior->PtrDown;
			} while (PtrPrior != NULL);
		}
		PtrNextPlace = PtrNextPlace->down;
	}
}

