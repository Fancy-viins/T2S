#pragma warning(disable:4996)
#include<stdio.h>
#include<float.h>
#include"TreeNode.h"
#include"OutPut.h"
#include<fstream>


void output(Tree *Tr)
{
	long int i;
	FILE *fp;
	struct Node *P;
	NetState *imf;
	P = (*Tr).PtrHead;
	fp = fopen("E:\\xh\\维余师兄程序\\Data\\outPut\\back\\1001.txt", "w+");
	printf("%s", "输出结果ID");
	printf("\n");

	do
	{
		fprintf(fp, "ID:");
		fprintf(fp, "%3d\t", P->markingID);

		fprintf(fp, "fathers:");
		for (i = 0; i < P->NumFathers; i++)
		{

			fprintf(fp, "%3d", P->PtrFathers[i]->markingID);
		}
		fprintf(fp, "\t");

		fprintf(fp, "T:");
		for (i = 0; i < P->NumFathers; i++)
		{
			fprintf(fp, "%3d", P->PtrFiredTransitions[i] + 1);
		}
		fprintf(fp, "\t");

		fprintf(fp, "sons:");
		for (i = 0; i < P->NumSons; i++)
		{
			fprintf(fp, "%d ", P->Ptrsons[i]->markingID);
		}
		fprintf(fp, "\t");

		fprintf(fp, "isGoal:");
		if (P->isGoal == 1)
		{
			fprintf(fp, "%2d\t", 1);
		}
		else
		{
			fprintf(fp, "%2d\t", 0);
		}

		fprintf(fp, "deadlock:");
		if (P->isDeadlock == 1)
		{
			fprintf(fp, "%2d\t", 1);
		}
		else
		{
			fprintf(fp, "%2d\t", 0);
		}
		fprintf(fp, "g:");
		fprintf(fp, "%.1f\t", P->g);
		fprintf(fp, "h:");
		fprintf(fp, "%.2f\t", P->hMin);

		fprintf(fp, "place:");
		imf = P->PtrNetStateHead;
		while (imf!=NULL)
		{
			fprintf(fp, "%d ", imf->row);
			imf = imf->PtrDown;
		}
		fprintf(fp, "\t");

		fprintf(fp, "m:");
		imf = P->PtrNetStateHead;
		while (imf != NULL)
		{
			fprintf(fp, "%3d", imf->TokenNum);
			imf = imf->PtrDown;
		}
		fprintf(fp, "\t");

		fprintf(fp, "x:");
		imf = P->PtrNetStateHead;
		while (imf != NULL)
		{
			fprintf(fp, "%.2f ", imf->residenceTime);
			imf = imf->PtrDown;
		}
		fprintf(fp, "\t");

		fprintf(fp, "NeedWaitingTime:");
		imf = P->PtrNetStateHead;
		while (imf != NULL)
		{
			fprintf(fp, "%.2f ", imf->NeedWaitingTime);
			imf = imf->PtrDown;
		}
		fprintf(fp, "\t");
		/*Earning* PtrEarning=P->PtrEanringHead;
		while (PtrEarning!=nullptr)
		{

			fprintf(fp, "t%d:%.2f\t", PtrEarning->action, PtrEarning->Q);;
			// printf("t%d:%.2f\t", PtrEarning->action, PtrEarning->Q);
			PtrEarning = PtrEarning->Ptrnext;
		}*/
		for (int i = 0; i < P->NumSons;i++)
		{
			if(P->Earnings!=nullptr)
			fprintf(fp, "t%d:%.2f\t", *P->Ptrsons[i]->PtrFiredTransitions, P->Earnings[i]);
			else
				fprintf(fp, "t%d:%.2f\t", *P->Ptrsons[i]->PtrFiredTransitions, 0);
		}


		fprintf(fp, "\n");
		P = P->PtrOpenNext;

	} while (P != NULL);
	fclose(fp);
	printf("Num:%d\n", Tr->node_num);
}

void outputpy(Tree* Tr)
{
	long int i;
	FILE* fp;
	struct Node* P;
	P = (*Tr).PtrHead;
	fp = fopen("E:\\xh\\维余师兄程序\\Data\\outPut\\py\\211.txt", "w+");
	printf("%s", "输出结果PY");
	printf("\n");
	do
	{
		//if (P->EqualG == 1)
		//{
		for (i = 0; i < P->NumFathers; i++)
		{
			if (i == 0)
			{
				fprintf(fp, "%2d\t", -1);
			}
			else
			{
				fprintf(fp, "%2d\t", 1);
			}
			fprintf(fp, "%d\t", P->markingID);
			//fprintf(fp, " g");
			//fprintf(fp, "%.1f\t", P->g);
			//fprintf(fp, " h");
			//fprintf(fp, "%.1f\t", P->hMin);
			//fprintf(fp, " g+h");
			//fprintf(fp, "%.1f\t", P->hMin + P->g);
			fprintf(fp, "%d\t", P->PtrFathers[i]->markingID);
			//fprintf(fp, " g");
			//fprintf(fp, "%.1f\t", P->PtrFathers[i]->g);
			//fprintf(fp, " h");
			//fprintf(fp, "%.1f\t", P->PtrFathers[i]->hMin);
			//fprintf(fp, " g+h");
			//fprintf(fp, "%.1f\t", P->PtrFathers[i]->hMin + P->PtrFathers[i]->g);
			fprintf(fp, "%d\t", P->PtrFiredTransitions[i]);
			for (int j = 0; j < P->PtrFathers[i]->NumSons; j++)
			{
				if (P->PtrFathers[i]->Earnings != nullptr && P->PtrFathers[i]->Ptrsons[j]->markingID == P->markingID) {
					fprintf(fp, "%.2f\t", P->PtrFathers[i]->Earnings[j]);
					break;
				}
			}
			if (P->isGoal == 1)
			{
				fprintf(fp, "%2d\t", 1);
			}
			else
			{
				fprintf(fp, "%2d\t", 0);
			}
			if (P->isDeadlock == 1)
			{
				fprintf(fp, "%2d\t", 1);
			}
			else
			{
				fprintf(fp, "%2d\t", 0);
			}
			if (P->EqualG == 1)
			{
				fprintf(fp, "%2d\n", 1);
			}
			else
			{
				fprintf(fp, "%2d\n", 0);
			}
		}
		if (P->NumTwin != 0)
		{
			for (i = 0; i < P->NumTwin; i++)
			{
				fprintf(fp, "%2d\t", 0);
				fprintf(fp, "%d\t", P->markingID);
				//fprintf(fp, " g");
				//fprintf(fp, "%.1f\t", P->g);
				//fprintf(fp, " h");
				//fprintf(fp, "%.1f\t", P->hMin);
/*				fprintf(fp, " g+h");
				fprintf(fp, "%.1f\t", P->hMin + P->g);*/
				fprintf(fp, "%d\t", P->PtrSame[i]->markingID);
				//fprintf(fp, " g");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->g);
				//fprintf(fp, " h");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->hMin);
				//fprintf(fp, " g+h");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->hMin + P->PtrSame[i]->g);
				fprintf(fp, "%d\t", P->PtrSame[i]->PtrFathers[0]->markingID);
				//fprintf(fp, " g");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->PtrFathers[0]->g);
				//fprintf(fp, " h");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->PtrFathers[0]->hMin);
				//fprintf(fp, " g+h");
				//fprintf(fp, "%.1f\t", P->PtrSame[i]->PtrFathers[0]->hMin + P->PtrSame[i]->PtrFathers[0]->g);
				fprintf(fp, "%2d\t", P->PtrSame[i]->PtrFiredTransitions[0]);
				for (int j = 0; j < P->PtrSame[i]->PtrFathers[0]->NumSons; j++)//未考虑多个相同节点多个父节点的问题***************************************************
				{
					//cout << P->PtrSame[i]->PtrFathers[0]->Ptrsons[j]->markingID << P->PtrSame[i]->markingID << endl;
					if (P->PtrSame[i]->PtrFathers[0]->Ptrsons[j]->markingID == P->PtrSame[i]->markingID && P->PtrSame[i]->PtrFathers[0]->Earnings != nullptr) {
						fprintf(fp, "%.2f\t", P->PtrSame[i]->PtrFathers[0]->Earnings[j]);
						break;
					}
				}
				fprintf(fp, "%2d\t", i);
				if (P->PtrSame[i]->EqualG == 1)
				{
					fprintf(fp, "%2d\n", 1);
				}
				else
				{
					fprintf(fp, "%2d\n", 0);
				}

			}

		}
		//}
		P = P->PtrOpenNext;
	} while (P != NULL);
	fclose(fp);
}

void outback(Tree *Tr)
{
	short i;
	FILE *fp;
	struct Node *P;
	P = (*Tr).PtrHead;
	fp = fopen("E:\\xh\\维余师兄程序\\Data\\outPut\\out\\433m.txt", "w+");
	if (fp == NULL)
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	do
	{
		for(int j=0;j<P->NumSons;j++)
		{
			for (i = 0; i < (*Tr).place_num; i++)
			{
				if (i != 8 && i != 17 && i != 26)
				{
					if (P->PtrNetStateRow[i] != NULL)
					{
						fprintf(fp, "%d\t", P->PtrNetStateRow[i]->TokenNum);
					}
					else
					{
						fprintf(fp, "%d\t", 0);
					}

				}
			}
		
		fprintf(fp, "%d\t", P->Ptrsons[j]->PtrFiredTransitions[0]);//暂时只有一个父节点
			fprintf(fp, "%.2f\n", P->Earnings[j]);
		}
		P = P->PtrOpenNext;
	} while (P != NULL);
	fclose(fp);

	/*P = (*Tr).PtrHead;
	fp = fopen("E:\\TimeNet2stateTree\\OutPutData\\m\\111mx.txt", "w+");
	do
	{
		for (i = 0; i < (*Tr).place_num; i++)
		{
			if (i != 8 && i != 17 && i != 26)
			{
				if (P->PtrNetStateRow[i] != NULL)
				{
					fprintf(fp, "%d\t", P->PtrNetStateRow[i]->TokenNum);
				}
				else
				{
					fprintf(fp, "%d\t", 0);
				}
			}
		}
		for (i = 0; i < (*Tr).place_num; i++)
		{
			if (i == 2 || i == 4 || i == 6 || i == 11 || i == 13 || i == 15 || i == 20 || i == 22 || i == 24)
			{
				if (P->PtrNetStateRow[i] != NULL)
				{
					fprintf(fp, "%.2f\t", P->PtrNetStateRow[i]->residenceTime);
				}
				else
				{
					fprintf(fp, "%.2f\t", 0.00);
				}
			}
		}
		fprintf(fp, "%.2f\n", P->hMin);
		P = P->PtrOpenNext;
	} while (P != NULL);
	fclose(fp);*/
}

void OutputBackHTrans(Tree *Tr)
{
	short i;
	FILE *fp;
	struct Node *P;
	P = (*Tr).PtrHead;
	fp = fopen("E:\\xh\\维余师兄程序\\Data\\outPut\\backh\\222mxth-change.txt", "w+");
	do
	{
		for (i = 0; i < (*Tr).place_num; i++)
		{
			if (i != 8 && i != 17 && i != 26)
			{
				if (P->PtrNetStateRow[i] != NULL)
				{
					fprintf(fp, "%d\t", P->PtrNetStateRow[i]->TokenNum);
				}
				else
				{
					fprintf(fp, "%d\t", 0);
				}
			}
		}
		for (i = 0; i < (*Tr).place_num; i++)
		{
			if (i == 2 || i == 4 || i == 6 || i == 11 || i == 13 || i == 15 || i == 20 || i == 22 || i == 24)
			{
				if (P->PtrNetStateRow[i] != NULL)
				{
					fprintf(fp, "%.2f\t", P->PtrNetStateRow[i]->residenceTime);
				}
				else
				{
					fprintf(fp, "%.2f\t", 0.00);
				}
			}
		}
		for (i = 0; i < Tr->transit_num; i++)
		{
			fprintf(fp, "%.2f\t", P->DelaysOfTranH[i]);
		}
		fprintf(fp, "%.2f\n", P->hMin);
		P = P->PtrOpenNext;
	} while (P != NULL);
	fclose(fp);
}