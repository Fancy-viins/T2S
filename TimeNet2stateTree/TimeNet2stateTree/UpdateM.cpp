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

	while (PtrNextImf != NULL)  //把父结点的标识复制到当前结点
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
	while (PtrNextPlace !=NULL)  //新标识的更新
	{
		PtrPrior = NULL;
		PtrNew = NULL;
		if (NextNode->PtrNetStateRow[PtrNextPlace->row] != NULL) //判断是否有还无token的库所要新增token
		{
			NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum = NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum + PtrNextPlace->element;
			if (NextNode->PtrNetStateRow[PtrNextPlace->row]->TokenNum == 0) //当前库所token为0，删除结构体
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
				if (PtrPrior->row > PtrNew->row && PtrPrior == NextNode->PtrNetStateHead)  //  无next有
				{
					NextNode->PtrNetStateHead = PtrNew;
					PtrNew->PtrDown = PtrPrior;
					break;
				}
				else if (PtrPrior->PtrDown == NULL)  //有 next 无
				{
					PtrPrior->PtrDown = PtrNew;
					break;
				}
				else if (PtrPrior->row < PtrNew->row && PtrPrior->PtrDown->row > PtrNew->row)  // 有 next 有
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

