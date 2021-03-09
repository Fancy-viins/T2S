#pragma once

typedef int ElemType;
typedef struct MatrixElement //MatrixElement
{
	short row, colunm;    // �÷���Ԫ���к����±� i-row   j-colunm
	ElemType element;    // ����Ԫ��ֵ e-element
	struct MatrixElement *right, *down; // �÷���Ԫ�����б���б�ĺ������ 
}MatrixElement, *ptrMatrixElement;//ptrMatrixElement


typedef struct// �к�������ͷָ��������ַ,��CreatSMatrix_OL()����
{
	ptrMatrixElement *rhead, *chead;
	short RowNum, ColunmNum, ElementNum;        // ϡ�����������������ͷ���Ԫ���� RowNum  ColunmNum  ElementNum
}CrossMatrixHead;//CrossMatrixHead


short InitSMatrix(CrossMatrixHead *M);    // ��ʼ��M(CrossList���͵ı��������ʼ��,���򴴽������ƾ��󽫳���) 
short DestroySMatrix(CrossMatrixHead *M);    // ����ϡ�����M
void CreateSMatrix(CrossMatrixHead *M, const char *path);     // ����ʮ������洢��ʾ
short OutputSMatrix(CrossMatrixHead M);  // ���л������ϡ�����M
short CompuSMatrix(CrossMatrixHead M, CrossMatrixHead N, CrossMatrixHead *Q); //  ��ϡ�����Ĳ�Q=M-N 
