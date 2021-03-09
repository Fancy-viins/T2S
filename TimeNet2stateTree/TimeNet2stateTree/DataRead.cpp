#pragma warning(disable:4996)
#include<stdio.h>
#include <stdlib.h> 
#include<vector>
#include<sstream>
#include<fstream>
#include<iostream>
#include <string.h>
#include"TreeNode.h"
#include "DataRead.h"
using namespace std;


/*
读取初始标识M0
int place_num :  库所数量
int M0[] :  初始标识
Return：void
*/
void DataRead(short place_num, short M0[], float Delay[] ,Tree *Tree)
{
	short i;
	FILE *fp;
	char line[100];
	fp = fopen(M0_path, "r"); //读取初始标识 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%d", &M0[i]);
	}
	fclose(fp);

	printf("初始标识：\n");
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", M0[i]);
	}
	printf("\n");

	fp = fopen(GoalPlace_path, "r"); //读取目标库所
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	while (1)
	{
		if (fgets(line, 300, fp) == NULL)
			break;

		/*分割每行*/
		char *pch = strtok(line, "	");//如果不是空，则使用strtok函数按照空格符划分，放在一个字符型指针
		while (pch != NULL)
		{
			short val = atoi(pch);
			Tree->NumGoal++;
			if (Tree->GoalPlace == NULL)
			{
				Tree->GoalPlace = (short *)malloc(sizeof(short));
				Tree->GoalPlace[0] = val;

			}
			else
			{
				Tree->GoalPlace = (short *)realloc(Tree->GoalPlace, sizeof(short)* Tree->NumGoal);
				Tree->GoalPlace[Tree->NumGoal -1] = val;
			}
			pch = strtok(NULL, "	");
		}
	}
	fclose(fp);

	printf("GoalPlace：\n");// 输出目标库所
	for (i = 0; i < Tree->NumGoal; i++)
	{
		printf("%3d", Tree->GoalPlace[i]);
	}
	printf("\n");



	fp = fopen(GoalMarking_path, "r"); //读取目标标识
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	Tree->GoalMarking = (short *)malloc(sizeof(short)* Tree->NumGoal);
	for (i = 0; i < Tree->NumGoal; i++)
	{
		fscanf(fp, "%d", &Tree->GoalMarking[i]);
	}
	fclose(fp);

	printf("GoalMarking：\n"); //输出目标标识
	for (i = 0; i < Tree->NumGoal; i++)
	{
		printf("%3d", Tree->GoalMarking[i]);
	}
	printf("\n");




	fp = fopen(Delay_path, "r"); //读取库所上赋时时间 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%f", &Delay[i]);
	}
	fclose(fp);

	printf("库所赋时时间：\n"); //输出赋时时间 
	for (i = 0; i < place_num; i++)
	{
		printf("%f  ", Delay[i]);
	}
	printf("\n");

}


void DataRead_v2(short place_num, short M0[], float Delay[], Tree *Tree)
{
	short i;
	FILE *fp;
	char line[100];
	fp = fopen(M0_path, "r"); //读取初始标识 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%d", &M0[i]);
	}
	fclose(fp);

	printf("初始标识：\n");
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", M0[i]);
	}
	printf("\n");

	

	fp = fopen(Delay_path, "r"); //读取库所上赋时时间 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%f", &Delay[i]);
	}
	fclose(fp);

	printf("库所赋时时间：\n"); //输出赋时时间 
	for (i = 0; i < place_num; i++)
	{
		printf("%f  ", Delay[i]);
	}
	printf("\n");

	ifstream ifs;
	string feature;
	float feat_onePoint;
	ifs.open("E:\\TimeNet2stateTree\\OutPutData\\333m.txt");
	while (!ifs.eof())
	{
		getline(ifs, feature, '\n');
		stringstream stringin(feature);
		vector<float> line ;
		while (stringin >> feat_onePoint)
		{
			line.push_back(feat_onePoint);
		}
		if (!line.empty())
		{
			Tree->LastGoal.push_back(line);
		}
	}
	ifs.close();

}