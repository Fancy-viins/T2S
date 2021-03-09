#pragma once

typedef int ElemType;
typedef struct MatrixElement //MatrixElement
{
	short row, colunm;    // 该非零元的行和列下标 i-row   j-colunm
	ElemType element;    // 非零元素值 e-element
	struct MatrixElement *right, *down; // 该非零元所在行表和列表的后继链域 
}MatrixElement, *ptrMatrixElement;//ptrMatrixElement


typedef struct// 行和列链表头指针向量基址,由CreatSMatrix_OL()分配
{
	ptrMatrixElement *rhead, *chead;
	short RowNum, ColunmNum, ElementNum;        // 稀疏矩阵的行数、列数和非零元个数 RowNum  ColunmNum  ElementNum
}CrossMatrixHead;//CrossMatrixHead


short InitSMatrix(CrossMatrixHead *M);    // 初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) 
short DestroySMatrix(CrossMatrixHead *M);    // 销毁稀疏矩阵M
void CreateSMatrix(CrossMatrixHead *M, const char *path);     // 采用十字链表存储表示
short OutputSMatrix(CrossMatrixHead M);  // 按行或按列输出稀疏矩阵M
short CompuSMatrix(CrossMatrixHead M, CrossMatrixHead N, CrossMatrixHead *Q); //  求稀疏矩阵的差Q=M-N 
