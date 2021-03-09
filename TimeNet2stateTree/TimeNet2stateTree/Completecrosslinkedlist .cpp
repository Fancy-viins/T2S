#pragma warning(disable:4996)
#include "Completecrosslinkedlist.h"
#include <stdlib.h> 
#include<stdio.h>
#include <string.h>


/*
��ʼ��M(Crosslist�������ͱ���������г�ʼ��)
���򴴽������ƾ����д�)
*/
short InitSMatrix(CrossMatrixHead *ptrC)
{
	(*ptrC).rhead = (*ptrC).chead = NULL;
	(*ptrC).RowNum = (*ptrC).ColunmNum = (*ptrC).ElementNum = 0;
	return 1;
}


/*����ϡ�����
  Crosslist *M:�ṹ��ָ��;
  ����ָ��ṹ������ı�����Ա��mu/nu/tu/rhead/chead
  (*)M.mu = = M->mu
  �ͷ�����ͷָ��ĵ�ַ�ڴ�ռ䣬ʹ������ڴ��ػ�����
  �ͷ��ڴ�󣬽���ͷ��ָ���Լ�������������Ԫ�����ĵĳ�ʼ��
*/
short DestroySMatrix(CrossMatrixHead *M)
{
	short i;
	MatrixElement *p, *q;//ָ�����ã�ָ����(Ԫ��)��ַ

	for (i = 1; i <= (*M).RowNum; i++) // �����ͷŽ�� 
	{
		p = *((*M).rhead + i);//�����i��ͷָ���ַ
		while (p)
		{
			q = p;
			p = p->right;
			free(q);
		}
	}
	free((*M).rhead);
	free((*M).chead);
	(*M).rhead = (*M).chead = NULL;
	(*M).RowNum = (*M).ColunmNum = (*M).ElementNum = 0;
	return 1;
}



/*
����CreateSMatrix����������ϡ�����ʹ��ʮ������ķ�ʽ�洢����
  ��Ҫ�û���������,������ȷֵ֮����Ҫ����ͷָ�������(*M).rhead
  (*M).chead
*/

void CreateSMatrix(CrossMatrixHead *ptrC, const char *path)//   M-ptrCpreHead//ptrCpostHead
{
	short k, i;
	short NotZeroNum = 0;
	MatrixElement *p, *q;//ָ��OLNode���͵�ָ��p��q
	if ((*ptrC).rhead)//�ж�ϡ����������ͷָ���Ƿ�Ϊ��
		DestroySMatrix(ptrC);
	/*
	�����С���ͷָ�������
	OLink*:ָ�����ͣ���������MaxRow����ÿһ����ָ��OLink���͵ı���
	�������ŵ���һ��ָ��OLNode���͵�ָ���ַ
	*/
	(*ptrC).rhead = (ptrMatrixElement*)malloc(sizeof(ptrMatrixElement));
	if (!(*ptrC).rhead)
		exit(0);
	(*ptrC).chead = (ptrMatrixElement*)malloc(sizeof(ptrMatrixElement));
	if (!(*ptrC).chead)
		exit(0);
	/*������������������ͷ�����ʼ����
	����Ĳ�����̵�����һ���ж������������ǵ�ֵΪNULL�������л��Ǹ���û�н��
	*/

	(*ptrC).rhead[0] = NULL;
	(*ptrC).chead[0] = NULL;

	/*��ʼ���󣬽���һ������������������(�洢��������Ԫ��ֵ��������Ԫ��)�������г�ʼ��*/
	short **buf = NULL;
	char line[100];
	FILE * pFile;
	short irow = 0;
	short icol = 0;
	short colNum = 0;

	buf = (short **)malloc(sizeof(short*));
	buf[0] = (short *)malloc(sizeof(short));
	//buf[0] = NULL;




	/*��ν��ж�ȡ����*/
	pFile = fopen(path, "r");
	if (pFile != NULL)
	{
		while (1)
		{
			if (fgets(line, 300, pFile) == NULL)
				break;

			/*�ָ�ÿ��*/
			char *pch = strtok(line, "	");//������ǿգ���ʹ��strtok�������տո�����֣�����һ���ַ���ָ��

			while (pch != NULL)
			{
				short val = atoi(pch);

				/*�洢����,������Ԫ�ض����ڻ��������*/
				buf[irow][icol] = val;
				if (val != 0)
				{
					p = (MatrixElement*)malloc(sizeof(MatrixElement));
					if (!p)
						exit(0);
					/* ���ɽ��*/
					p->row = irow;
					p->colunm = icol;
					p->element = val;
					/*printf("i:%d", p->i);
					printf("j:%d", p->j);
					printf("e:%d", p->e);
					printf("\n");*/

					/*���ɽ���Ҫ����һ����ͷָ��������һ����Ϊ0��Ԫ����������
					 �ж���ͷָ�롢��ͷָ��ѡ�����������
					 ���һ�������һ����û�н�㣬ѡ��ֱ�Ӳ���
					 ������������һ�����н�㣬ѡ����뵽��ȷ��λ��
					 ����ж����޽�㣺֮ǰ�ԣ�*M��.rhead/(*M).chead���г�ʼ��������Ԫ��ֵ��ΪNULL��
					 �ж�������(*M).rhead[i] == NULL;
					*/

					if ((*ptrC).rhead[irow] == NULL)
					{
						//p���ڸ��еĵ�һ����㴦
						p->right = (*ptrC).rhead[irow];  //������ָ��Ŀո�����һ������right
						(*ptrC).rhead[irow] = p;         //��p�ĵ�ַ������ͷָ�룬ָ���ұߵĵ�һ�����

					}
					else // Ѱ�����б��еĲ���λ�� 
					{
						//�Ӹ��е�������ͷ��ʼ��ֱ���ҵ�
						q = (*ptrC).rhead[irow];
						while (q->right != NULL)
						{
							q = q->right;
						}
						q->right = p;
						p->right = NULL;
						//p->right = q->right; // ����в��� 
						//q->right = p
					}

					if ((*ptrC).chead[icol] == NULL)
					{
						// p���ڸ��еĵ�һ����㴦
						p->down = (*ptrC).chead[icol];
						(*ptrC).chead[icol] = p;
					}
					else // Ѱ�����б��еĲ���λ�� 
					{
						q = (*ptrC).chead[icol];
						while (q->down != NULL)
						{
							q = q->down;
						}
						q->down = p;
						p->down = NULL;
						//p->down = q->down; // ����в��� 
						//q->down = p;
					}

					NotZeroNum++;
				}

				icol++;
				buf[irow] = (short *)realloc(buf[irow], sizeof(short) * (icol + 1));
				if (irow == 0)
				{
					(*ptrC).chead = (ptrMatrixElement*)realloc((*ptrC).chead, (icol + 1) * sizeof(ptrMatrixElement));
					(*ptrC).chead[icol] = NULL;

				}

				// �����ָ�
				pch = strtok(NULL, "	");
			}

			irow++;

			(*ptrC).rhead = (ptrMatrixElement*)realloc((*ptrC).rhead, (irow + 1) * sizeof(ptrMatrixElement));
			(*ptrC).rhead[irow] = NULL;
			buf = (short **)realloc(buf, sizeof(short*) * (irow + 1));
			buf[irow] = (short *)malloc(sizeof(short));


			colNum = icol;
			icol = 0;
		}
		fclose(pFile);
	}

	(*ptrC).RowNum = irow;
	(*ptrC).ColunmNum = colNum;
	(*ptrC).ElementNum = NotZeroNum;
	printf("\n");
	/* ������� irow��¼ʵ��������colNum��¼ʵ������*/
	for (short i = 0; i < irow; i++)
	{
		for (short j = 0; j < colNum; j++)
		{
			printf("%3d ", buf[i][j]);
		}
		printf("\n");
	}
}


/*���л������ϡ�����M*/
short OutputSMatrix(CrossMatrixHead ptrC)
{
	int i, j;
	ptrMatrixElement p;
	printf("%d��%d��%d������Ԫ��\n", ptrC.RowNum, ptrC.ColunmNum, ptrC.ElementNum);
	printf("������ѡ��(1.������� 2.�������): ");
	scanf("%d", &i);
	switch (i)
	{
	case 1://ѡ�������
		for (j = 0; j < ptrC.RowNum; j++)
		{
			p = ptrC.rhead[j];
			while (p)
			{
				printf("%d��%d��ֵΪ%d\n", (p->row), (p->colunm), p->element);
				p = p->right;
			}
		}
		break;
	case 2://ѡ�������
		for (j = 0; j < ptrC.ColunmNum; j++)
		{
			p = ptrC.chead[j];
			while (p)
			{
				printf("%d��%d��ֵΪ%d\n", (p->row), (p->colunm), p->element);
				p = p->down;
			}
		}
	}
	return 1;
}


/*
��ʼ������ϡ�����M��N������������Ӧ���
�����������ϡ�����Ĳ�Q = M - N
*/
short CompuSMatrix(CrossMatrixHead M, CrossMatrixHead N, CrossMatrixHead *Q)
{
	short i, k;
	ptrMatrixElement p, pq=NULL, pm, pn; //��Ϊ�м���ָ��
	ptrMatrixElement *col;//ָ����ָ��

	if (M.RowNum != N.RowNum || M.ColunmNum != N.ColunmNum)
	{
		printf("����������ͬ���͵�,�������\n");
		exit(0);
	}
	(*Q).RowNum = M.RowNum; // ��ʼ��Q���� 
	(*Q).ColunmNum = M.ColunmNum;
	(*Q).ElementNum = 0;
	(*Q).rhead = (ptrMatrixElement*)malloc(((*Q).RowNum) * sizeof(ptrMatrixElement));//ΪQ��������ڴ�
	if (!(*Q).rhead)
		exit(0);
	(*Q).chead = (ptrMatrixElement*)malloc(((*Q).ColunmNum) * sizeof(ptrMatrixElement));
	if (!(*Q).chead)
		exit(0);
	for (k = 0; k < (*Q).RowNum; k++) // ��ʼ��Q����ͷָ������;��������Ϊ������ 
		(*Q).rhead[k] = NULL;
	for (k = 0; k < (*Q).ColunmNum; k++) // ��ʼ��Q����ͷָ������;��������Ϊ������ 
		(*Q).chead[k] = NULL;
	// ����ָ���е�����������
	col = (ptrMatrixElement*)malloc(((*Q).ColunmNum + 1) * sizeof(ptrMatrixElement));
	if (!col)
		exit(0);
	for (k = 0; k < (*Q).ColunmNum; k++) // ����ֵ 
		col[k] = NULL;
	for (i = 0; i < (*Q).RowNum; i++) // ���е�˳����� 
	{
		pm = M.rhead[i]; // pmָ�����M�ĵ�i�еĵ�1����� 
		pn = N.rhead[i]; // pnָ�����N�ĵ�i�еĵ�1����� 
		while (pm&&pn) // pm��pn������ 
		{
			if (pm->colunm < pn->colunm) // ����M��ǰ������С�ھ���N��ǰ������ 
			{
				p = (ptrMatrixElement)malloc(sizeof(MatrixElement)); // ���ɾ���Q�Ľ�� 
				if (!p)
					exit(0);
				(*Q).ElementNum++; // ����Ԫ������1 
				p->row = i; // ����㸳ֵ 
				p->colunm = pm->colunm;
				p->element = pm->element;
				p->right = NULL;
				pm = pm->right; // pmָ�������� 
			}
			// ����M��ǰ�����д��ھ���N��ǰ������ 
			else if (pm->colunm > pn->colunm)
			{
				p = (ptrMatrixElement)malloc(sizeof(MatrixElement)); // ���ɾ���Q�Ľ�� 
				if (!p)
					exit(0);
				(*Q).ElementNum++; // ����Ԫ������1 
				p->row = i; // ����㸳ֵ 
				p->colunm = pn->colunm;
				p->element = -pn->element;
				p->right = NULL;
				pn = pn->right; // pnָ�������� 
			}
			else if (pm->element - pn->element)
			{
				// ����M��N��ǰ�������������Ԫ��֮�Ϊ0 
				p = (ptrMatrixElement)malloc(sizeof(MatrixElement)); // ���ɾ���Q�Ľ�� 
				if (!p)
					exit(0);
				(*Q).ElementNum++; // ����Ԫ������1 
				p->row = i; // ����㸳ֵ 
				p->colunm = pn->colunm;
				p->element = pm->element - pn->element;
				p->right = NULL;
				pm = pm->right; // pmָ�������� 
				pn = pn->right; // pnָ�������� 
			}
			else // ����M��N��ǰ�������������Ԫ��֮��Ϊ0 
			{
				pm = pm->right; // pmָ�������� 
				pn = pn->right; // pnָ�������� 
				continue;
			}
			if ((*Q).rhead[i] == NULL) // pΪ���еĵ�1����� 
				// p���ڸ��еı�ͷ��pqָ��p(���е����һ�����)
				(*Q).rhead[i] = pq = p;
			else // ����pq��ָ���֮�� 
			{
				pq->right = p; // ����в��� 
				pq = pq->right; // pqָ����е����һ����� 
			}
			if ((*Q).chead[p->colunm] == NULL) // pΪ���еĵ�1����� 
				// p���ڸ��еı�ͷ��col[p->j]ָ��p
				(*Q).chead[p->colunm] = col[p->colunm] = p;
			else // ����col[p->]��ָ���֮�� 
			{
				col[p->colunm]->down = p; // ����в���
				// col[p->j]ָ����е����һ����� 
				col[p->colunm] = col[p->colunm]->down;
			}
		}
		while (pm) // ������M���е�ʣ��Ԫ�ز������Q 
		{
			p = (ptrMatrixElement)malloc(sizeof(MatrixElement)); // ���ɾ���Q�Ľ�� 
			if (!p)
				exit(0);
			(*Q).ElementNum++; // ����Ԫ������1 
			p->row = i; // ����㸳ֵ 
			p->colunm = pm->colunm;
			p->element = pm->element;
			p->right = NULL;
			pm = pm->right; // pmָ�������� 
			if ((*Q).rhead[i] == NULL) // pΪ���еĵ�1����� 
				// p���ڸ��еı�ͷ��pqָ��p(���е����һ�����)
				(*Q).rhead[i] = pq = p;
			else // ����pq��ָ���֮�� 
			{
				pq->right = p; // ����в��� 
				pq = pq->right; // pqָ����е����һ����� 
			}
			if ((*Q).chead[p->colunm] == NULL) // pΪ���еĵ�1�����
				// p���ڸ��еı�ͷ��col[p->j]ָ��p  
				(*Q).chead[p->colunm] = col[p->colunm] = p;
			else // ����col[p->j]��ָ���֮�� 
			{
				col[p->colunm]->down = p; // ����в���
				// col[p->j]ָ����е����һ����� 
				col[p->colunm] = col[p->colunm]->down;
			}
		}
		while (pn) // ������N���е�ʣ��Ԫ�ز������Q 
		{
			p = (ptrMatrixElement)malloc(sizeof(MatrixElement)); // ���ɾ���Q�Ľ�� 
			if (!p)
				exit(0);
			(*Q).ElementNum++; // ����Ԫ������1 
			p->row = i; // ����㸳ֵ 
			p->colunm = pn->colunm;
			p->element = -pn->element;
			p->right = NULL;
			pn = pn->right; // pmָ�������� 
			if ((*Q).rhead[i] == NULL) // pΪ���еĵ�1����� 
				// p���ڸ��еı�ͷ��pqָ��p(���е����һ�����)
				(*Q).rhead[i] = pq = p;
			else // ����pq��ָ���֮�� 
			{
				pq->right = p; // ����в��� 
				pq = pq->right; // pqָ����е����һ����� 
			}
			if ((*Q).chead[p->colunm] == NULL) // pΪ���еĵ�1�����
				// p���ڸ��еı�ͷ��col[p->j]ָ��p 
				(*Q).chead[p->colunm] = col[p->colunm] = p;
			else // ����col[p->j]��ָ���֮�� 
			{
				col[p->colunm]->down = p; // ����в���
				// col[p->j]ָ����е����һ�����  
				col[p->colunm] = col[p->colunm]->down;
			}
		}
	}
	for (k = 0; k < (*Q).ColunmNum; k++)
		if (col[k]) // k���н�� 
			col[k]->down = NULL; // ��������һ������downָ��Ϊ�� 
	free(col);
	return 1;
}