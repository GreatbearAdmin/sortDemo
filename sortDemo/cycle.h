#pragma once
#include "graph.h"
#include <vector>
using namespace std;
typedef enum
{
	White = 0, //未访问的节点：白色
	Gray, //访问后的节点：灰色
	Black, //该节点的所有邻接点都访问完：黑色
}NodeColor;

typedef vector<vector<int>> VGraph;
typedef vector<int> NodeList;

bool checkCycleForDfs(VGraph g, int root, NodeColor* color);

bool checkCycleFrTopoSort(VGraph g);

void dfs(MGraph* g, int index, NodeColor* color, bool& hasCycle);
bool checkCycleFrDfs(MGraph* g);

bool checkCycleFrTopo(MGraph* g);

void createGraphNew(MGraph& g, bool isDirected = true);
