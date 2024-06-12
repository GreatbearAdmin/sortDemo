#include "stdafx.h"
#include "cycle.h"
#include <queue>

bool checkCycleForDfs(VGraph g, int root, NodeColor* color)
{
	static bool hasCycle = false;
	static int last = -1;
	color[root] = Gray;
	for (auto child : g[root])
	{
		if (Gray == color[child] && child != last)
		{
			hasCycle = true;
			break;
		} else if (White == color[child])
		{
			last = root;
			checkCycleForDfs(g, child, color);
		}
	}
	color[root] = Black;
	return hasCycle;
}

bool checkCycleFrTopoSort(VGraph g)
{
	if (g.empty())
	{
		return false;
	}
	int size = g.size();
	vector<int> degree(size, 0);
	queue<int> q;
	for (int i = 0; i < size; i++)
	{
		degree[i] = g[i].size();
		if (degree[i] <= 1)
		{
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty())
	{
		cnt++;
		int root = q.front();
		q.pop();
		for (auto child : g[root])
		{
			degree[child]--;
			if (1 == degree[child])
			{
				q.push(child);
			}
		}
	}
	return (cnt != size);
}

bool checkCycleFrDfs(MGraph* g)
{
	if (nullptr == g || g->numNodes <= 0)
	{
		return false;
	}
	bool hasCycle = false;
	NodeColor* color = new NodeColor[g->numNodes];
	for (int i = 0; i < g->numNodes; i++)
	{
		dfs(g, i, color, hasCycle);
		if (hasCycle)
		{
			break;
		}
	}
	return hasCycle;
}

void dfs(MGraph* g, int index, NodeColor* color, bool& hasCycle)
{
	if (nullptr == g || nullptr == color)
	{
		return;
	}
	int i = index;
	color[i] = Gray;
	for (int j = 0; j < g->numNodes; j++)
	{
		if (0 == g->arc[i][j])
		{
			continue;
		}
		if (Gray == color[j])
		{
			hasCycle = true;
			break;
		}
		else if (Black == color[j])
		{
			continue;
		}
		else
		{
			dfs(g, j, color, hasCycle);
		}
	}
	color[i] = Black;
}

void createGraphNew(MGraph& g, bool isDirected /*= true*/)
{
	printf("请输入图的顶点数和边数：\n");
	scanf_s("%d, %d", &g.numNodes, &g.numEdges);
	//初始化邻接矩阵
	for (int i = 0; i < g.numNodes; i++)
	{
		for (int j = 0; j < g.numNodes; j++)
		{
			g.arc[i][j] = 0;
		}
	}
	for (int i = 0; i < g.numNodes; i++)
	{
		g.vexs[i] = i + 1;
	}
	printf("请输入边的头和尾：\n");
	for (int k = 0; k < g.numEdges; k++)
	{
		int i, j;
		scanf_s("%d, %d", &i, &j);
		g.arc[i-1][j-1] = 1;
		//是否无向图
		if (!isDirected)
		{
			g.arc[j - 1][i - 1] = g.arc[i - 1][j - 1];
		}
	}
	return;
}

bool checkCycleFrTopo(MGraph* g)
{
	if (nullptr == g || g->numNodes <= 0 || g->numEdges <= 0)
	{
		return false;
	}
	int* degree = new int[g->numNodes];
	memset(degree, 0, sizeof(int)*g->numNodes);
	//求所有节点的度数
	for (int i = 0; i < g->numNodes; i++)
	{
		for (int j = 0; j < g->numNodes; j++)
		{
			if (0 != g->arc[i][j])
			{
				degree[i]++;
			}
		}
	}
	queue<int> q;
	for (int i = 0; i < g->numNodes; i++)
	{
		if (degree[i] <= 1)
		{
			//将度数<=1的节点序号入队列
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		cnt++;
		for (int i = 0; i < g->numNodes; i++)
		{
			if (0 != g->arc[cur][i])
			{
				//其他关联的节点度数减1
				degree[i]--;
				if (degree[i] == 1)
				{
					//度数<=1的节点进入队列
					q.push(i);
				}
			}
			
		}
	}
	return (cnt != g->numNodes);
}

