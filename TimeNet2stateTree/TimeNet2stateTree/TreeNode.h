#pragma once
#include<vector>
#include<map>
#include<iostream>
using namespace std;
#define Len_node         sizeof(struct Node)
#define New 1
#define Old 0
#define ZeroInterval 2
const bool WithDelay = 1;
const bool ZeroDelay = 0;
class Earning
{
public:
	short action;
	float Q;
	Earning* Ptrnext;
	Earning(short a, float q) :action(a), Q(q) { Ptrnext = nullptr; };
	Earning() { action = 0; Q = 0; Ptrnext = nullptr;}
	void insert(short a, float q) {
		Earning* PtrNewNext;
		PtrNewNext = new Earning(a, q);
		if (Ptrnext == nullptr)
			Ptrnext = PtrNewNext;
		else
		{
			while (Ptrnext != nullptr)
			{
				Ptrnext = Ptrnext->Ptrnext;
			}
			Ptrnext = PtrNewNext;
		}
	}
};

typedef struct NetState
{
	short TokenNum;
	float residenceTime;
	float NeedWaitingTime;
	short row;
	struct NetState * PtrDown;
};


typedef struct Node 
{
	struct Node **PtrFathers;//���ڵ�����
	short NumFathers;//���ڵ���Ŀ
	struct Node **Ptrsons;//�ӽڵ�����
	short NumSons;//�ӽڵ���Ŀ
	short NumSons_Back;//�ӽڵ���Ŀ
	short *PtrFiredTransitions;	//�±�ʶ�ı�Ǩ��Դ
	short *EnTransZeroInterval;	//����0��ʱ����µı�Ǩ
	short *EnTransWithDelay;//�洢����ʱ��Ǩ
	short NumEnTransWithDelay;//����ʱ��Ǩ����Ŀ
	short NumEnTransZeroInterval;	//����0��ʱ����±�Ǩ������
	float *DelaysOfEnTran;//�洢��ʱʱ��
	short isNew;//�¾ɱ�־
	long int markingID;//�±�ʶ���±�
	//short *marking;//�¾����ʶ
	//float *residenceTime; // ��ʱ�̿������п��Ѿ��ȴ�ʱ��
	//float *NeedWaitingTime;  // ��ʱ�̿�����token��Ҫ�ȴ���ʱ��
	float g; //�Ѻķѵ�ʱ�����
	float hMin; // ����ֵ��Сֵ
	bool isDeadlock;//������־
	struct Node *PtrOpenNext;//��һ��Ҫ��չ�ı�ʶ
	struct Node **PtrSame; //��ͬ�ı�ʶ 
	struct Node *PtrTwin;
	short NumTwinBack;
	short NumTwin;
	bool isGoal;  //Ŀ��ڵ��־
	struct Node *PtrGoalNext; // ����Ŀ��ڵ��¸���ַ
	struct Node *PtrBackDoneNext; //�����¸�����չ�ڵ��¸���ַ
	struct Node *PtrBackNotDoneNext;//�����¸�δ��չ�ڵ��¸���ַ
	struct Node *PtrBackNotDoneBefore;//�����ϸ�δ��չ�ڵ��¸���ַ
	bool TwinIsDone;//�ظ������ж�
	struct Node *AClosedNext;
	struct Node *AStarOpenNext;
	struct Node *AStarOpenBefore;
	struct Node *DeadlockNext;   //���������ڵ��¸���ַ
	struct NetState **PtrNetStateRow;//�����Ϣ����
	struct NetState *PtrNetStateHead;//�����Ϣ����
	int placeNum;//
	bool EqualG;
	float* Earnings;//shouyishuzu
	Earning* PtrEarning;
	Earning* PtrEanringHead;
	//map<short, float> Earnings;
	float *DelaysOfTranH;//�洢��ʱʱ��
} *PtrNodeType;
//typedef Node *NodeLink;

typedef struct Tree
{
	Node *PtrHead; //ָ�����ĵ�һ�����
	Node *PtrGoalHead; //������ֹ���
	Node *PtrGoalTail; // ĩβ������ֹ���
	Node *PtrBackDoneHead;//����ɷ���ͷ���
	Node *PtrBackDoneTail;//����ɷ���β���
	Node *PtrDeadlockHead;//����ͷ���
	Node *PtrDeadlockTail;//����β���
	Node *PtrOpenTail;  //��չ��β���  
	Node *PtrBackNotDoneHead;//δ��ɷ���ͷ���
	Node *PtrBackNotDoneTail;//δ��ɷ���β���
	short *GoalMarking;//Ŀ��token
	short *GoalPlace;//Ŀ�����
	short NumGoal;//Ŀ�������Ŀ
	short  place_num;  //��������
	short  transit_num; //��Ǩ����
	long int  node_num; // ���Ľ�����
	long int Back_num;//���ش���
	vector<vector<float>> LastGoal;
};   //Tree�ṹ��
