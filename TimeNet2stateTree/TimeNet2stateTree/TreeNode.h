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
	struct Node **PtrFathers;//父节点数组
	short NumFathers;//父节点数目
	struct Node **Ptrsons;//子节点数组
	short NumSons;//子节点数目
	short NumSons_Back;//子节点数目
	short *PtrFiredTransitions;	//新标识的变迁来源
	short *EnTransZeroInterval;	//存在0延时情况下的变迁
	short *EnTransWithDelay;//存储有延时变迁
	short NumEnTransWithDelay;//有延时变迁的数目
	short NumEnTransZeroInterval;	//存在0延时情况下变迁的数量
	float *DelaysOfEnTran;//存储延时时间
	short isNew;//新旧标志
	long int markingID;//新标识的下标
	//short *marking;//新具体标识
	//float *residenceTime; // 此时刻库所中托肯已经等待时间
	//float *NeedWaitingTime;  // 此时刻库所中token需要等待的时间
	float g; //已耗费的时间代价
	float hMin; // 估计值最小值
	bool isDeadlock;//死锁标志
	struct Node *PtrOpenNext;//下一个要扩展的标识
	struct Node **PtrSame; //相同的标识 
	struct Node *PtrTwin;
	short NumTwinBack;
	short NumTwin;
	bool isGoal;  //目标节点标志
	struct Node *PtrGoalNext; // 链接目标节点下个地址
	struct Node *PtrBackDoneNext; //链接下个待扩展节点下个地址
	struct Node *PtrBackNotDoneNext;//链接下个未扩展节点下个地址
	struct Node *PtrBackNotDoneBefore;//链接上个未扩展节点下个地址
	bool TwinIsDone;//重复计算判断
	struct Node *AClosedNext;
	struct Node *AStarOpenNext;
	struct Node *AStarOpenBefore;
	struct Node *DeadlockNext;   //链接死锁节点下个地址
	struct NetState **PtrNetStateRow;//结点信息的行
	struct NetState *PtrNetStateHead;//结点信息的列
	int placeNum;//
	bool EqualG;
	float* Earnings;//shouyishuzu
	Earning* PtrEarning;
	Earning* PtrEanringHead;
	//map<short, float> Earnings;
	float *DelaysOfTranH;//存储延时时间
} *PtrNodeType;
//typedef Node *NodeLink;

typedef struct Tree
{
	Node *PtrHead; //指向树的第一个结点
	Node *PtrGoalHead; //树的终止结点
	Node *PtrGoalTail; // 末尾连接终止结点
	Node *PtrBackDoneHead;//已完成反向头结点
	Node *PtrBackDoneTail;//已完成反向尾结点
	Node *PtrDeadlockHead;//死锁头结点
	Node *PtrDeadlockTail;//死锁尾结点
	Node *PtrOpenTail;  //扩展的尾结点  
	Node *PtrBackNotDoneHead;//未完成反向头结点
	Node *PtrBackNotDoneTail;//未完成反向尾结点
	short *GoalMarking;//目标token
	short *GoalPlace;//目标库所
	short NumGoal;//目标库所数目
	short  place_num;  //库所数量
	short  transit_num; //变迁数量
	long int  node_num; // 树的结点个数
	long int Back_num;//返回次数
	vector<vector<float>> LastGoal;
};   //Tree结构体
