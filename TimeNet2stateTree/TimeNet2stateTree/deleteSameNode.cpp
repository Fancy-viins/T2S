#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include"TreeNode.h"
#include"deleteSameNode.h"
using namespace std;

//bool operator==(const vector<float>&v1,const vector<float>&v2)
//{
//	for (int i = 0; i < v1.size()-1; i++)
//	{
//		if (v1[i] != v2[i])
//		{
//			return false;
//		}
//	}
//	return true;
//}

void deleteSameNode()
{
	//读取文件
	ifstream ifs;
	string feature;
	float feat_onePoint;
	vector<vector<float>> *v = new vector<vector<float>>;
	ifs.open("E:\\TimeNet2stateTree\\OutputData\\backm\\mergem_v2.txt");
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	while (!ifs.eof())
	{
		getline(ifs, feature, '\n');
		stringstream stringin(feature);
		vector<float> *line = new vector<float>;
		while (stringin >> feat_onePoint)
		{
			line->push_back(feat_onePoint);
		}
		if (!line->empty())
		{
			for (int i = 0; i < v->size(); i++)
			{
				if (v->at(i) == *line)
				{
					if (v->at(i)[v->at(i).size() - 1] > line->at(line->size() - 1))//删除相同节点
					{
						v->at(i)[v->at(i).size() - 1] = line->at(line->size() - 1);
					}
					delete line;
					feature.clear();
					break;
				}
			}
			if (!feature.empty())
			{
				v->push_back(*line);
			}
		}
	}
	ifs.close();

	//生成新文件
	ofstream fout;
	fout.open("E:\\TimeNet2stateTree\\OutputData\\merge_single_v2.txt");
	for (int i = 0; i < v->size(); i++)
	{
		for (int j = 0; j < v->at(i).size(); j++)
		{
			fout << v->at(i)[j] << "	";
		}
		fout << endl;
	}
}


//void deleteSameNode()
//{
//	//读取文件
//	ifstream ifs;
//	string feature;
//	float feat_onePoint;
//	map<vector<float>, float> *m = new map<vector<float>, float>;
//	ifs.open("E:\\TimeNet2stateTree\\OutputData\\broBackH\\222mxth.txt");
//	if (!ifs.is_open())
//	{
//		cout << "文件打开失败" << endl;
//		return;
//	}
//	while (!ifs.eof())
//	{
//		getline(ifs, feature, '\n');
//		stringstream stringin(feature);
//		vector<float> *line = new vector<float>;
//		while (stringin >> feat_onePoint)
//		{
//			line->push_back(feat_onePoint);
//		}
//		if (!line->empty())
//		{
//			map<vector<float>, float>::iterator it = m->find(*line);
//			if (it != m->end())
//			{
//				it->second = it->second < line[line->size - 1] ? it->second : line[line->size - 1];
//				delete line;
//			}
//			else
//			{
//				m->insert(make_pair(*line, line[line->size - 1]));
//			}
//		}
//	}
//	ifs.close();
//
//	//生成新文件
//	ofstream fout;
//	fout.open("E:\\TimeNet2stateTree\\OutputData\\broBackH\\222mxth-noSame.txt");
//	for (map<vector<float>, float>::iterator it = m->begin(); it != m->end(); it++)
//	{
//		for (int i = 0; i < it->first.size - 1; i++)
//		{
//			fout << it->first[i] << "	";
//		}
//		fout << it->second << endl;
//	}
//	fout.close();
//}
//
//
