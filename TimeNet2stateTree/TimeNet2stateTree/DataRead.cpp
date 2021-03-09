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
��ȡ��ʼ��ʶM0
int place_num :  ��������
int M0[] :  ��ʼ��ʶ
Return��void
*/
void DataRead(short place_num, short M0[], float Delay[] ,Tree *Tree)
{
	short i;
	FILE *fp;
	char line[100];
	fp = fopen(M0_path, "r"); //��ȡ��ʼ��ʶ 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%d", &M0[i]);
	}
	fclose(fp);

	printf("��ʼ��ʶ��\n");
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", M0[i]);
	}
	printf("\n");

	fp = fopen(GoalPlace_path, "r"); //��ȡĿ�����
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	while (1)
	{
		if (fgets(line, 300, fp) == NULL)
			break;

		/*�ָ�ÿ��*/
		char *pch = strtok(line, "	");//������ǿգ���ʹ��strtok�������տո�����֣�����һ���ַ���ָ��
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

	printf("GoalPlace��\n");// ���Ŀ�����
	for (i = 0; i < Tree->NumGoal; i++)
	{
		printf("%3d", Tree->GoalPlace[i]);
	}
	printf("\n");



	fp = fopen(GoalMarking_path, "r"); //��ȡĿ���ʶ
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

	printf("GoalMarking��\n"); //���Ŀ���ʶ
	for (i = 0; i < Tree->NumGoal; i++)
	{
		printf("%3d", Tree->GoalMarking[i]);
	}
	printf("\n");




	fp = fopen(Delay_path, "r"); //��ȡ�����ϸ�ʱʱ�� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%f", &Delay[i]);
	}
	fclose(fp);

	printf("������ʱʱ�䣺\n"); //�����ʱʱ�� 
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
	fp = fopen(M0_path, "r"); //��ȡ��ʼ��ʶ 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%d", &M0[i]);
	}
	fclose(fp);

	printf("��ʼ��ʶ��\n");
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", M0[i]);
	}
	printf("\n");

	

	fp = fopen(Delay_path, "r"); //��ȡ�����ϸ�ʱʱ�� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%f", &Delay[i]);
	}
	fclose(fp);

	printf("������ʱʱ�䣺\n"); //�����ʱʱ�� 
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