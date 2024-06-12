#pragma once
#include "graph.h"
#include <vector>
using namespace std;
typedef enum
{
	White = 0, //δ���ʵĽڵ㣺��ɫ
	Gray, //���ʺ�Ľڵ㣺��ɫ
	Black, //�ýڵ�������ڽӵ㶼�����꣺��ɫ
}NodeColor;

typedef vector<vector<int>> VGraph;
typedef vector<int> NodeList;

bool checkCycleForDfs(VGraph g, int root, NodeColor* color);

bool checkCycleFrTopoSort(VGraph g);

void dfs(MGraph* g, int index, NodeColor* color, bool& hasCycle);
bool checkCycleFrDfs(MGraph* g);

bool checkCycleFrTopo(MGraph* g);

void createGraphNew(MGraph& g, bool isDirected = true);
