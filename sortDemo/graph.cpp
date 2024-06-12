#include "stdafx.h"
#include "graph.h"
#include <stdio.h>
#include <iostream>
#include <queue>
//#include <list>

void createGraph(MGraph* g)
{
	if (nullptr == g)
	{
		return;
	}
	int i, j, k, w;
	printf("输入顶点数和边数：\n");
	scanf_s("%d, %d", &g->numNodes, &g->numEdges);
	for (i=0; i<g->numNodes; i++)
	{
		scanf_s(&g->vexs[i]);
	}
	for (i = 0; i < g->numNodes; i++)
	{
		for (j = 0; j < g->numNodes; j++)
		{
			g->arc[i][j] = INFINITY_NEW; //邻接矩阵初始化
		}
	}
	for (k = 0; k < g->numEdges; k++)
	{
		printf("输入边(vi, vj)上的下标i、j和权w：\n");
		scanf_s("%d, %d, %d", &i, &j, &w);
		g->arc[i][j] = w;
		//无向图
		g->arc[j][i] = g->arc[i][j];
	}
}

void _dfs(MGraph* g, int i, bool* isVisited)
{
	if (nullptr == g || nullptr == isVisited)
	{
		return;
	}
	isVisited[i] = true;
	int j;
	printf("%c ", g->vexs[i]);
	for (j = 0; j < g->numNodes; j++)
	{
		if (1 == g->arc[i][j] && !isVisited[j])
		{
			_dfs(g, j, isVisited);
		}
	}
}

void dfsTraverse(MGraph* g)
{
	if (nullptr == g)
	{
		return;
	}
	int i;
	bool isVisited[MAXVEX];
	for (i = 0; i < g->numNodes; i++)
	{
		isVisited[i] = false;
	}
	for (i = 0; i < g->numNodes; i++)
	{
		if (!isVisited[i])
		{
			_dfs(g, i, isVisited);
		}
	}
}

void bfsTraverse(MGraph* g)
{
	if (nullptr == g)
	{
		return;
	}
	int i, j;
	std::queue<int> q;
	bool isVisited[MAXVEX];
	for (i = 0; i < g->numNodes; i++)
	{
		isVisited[i] = false;
	}
	for (i = 0; i < g->numNodes; i++)
	{
		if (!isVisited[i])
		{
			isVisited[i] = true;
			printf("%c ", g->vexs[i]);
			q.push(i);
			while (!q.empty())
			{
				int index = q.front();
				q.pop();
				for (j = 0; j < g->numNodes; j++)
				{
					if (1 == g->arc[index][j] && !isVisited[j])
					{
						isVisited[j] = true;
						printf("%c ", g->vexs[j]);
						q.push(j);
					}
				}
			}
		}
	}

}


void minSpanTreeFrPrim(MGraph* g)
{
	if (nullptr == g)
	{
		return;
	}
	int min, i, j, k;
	int adjvex[MAXVEX];
	int lowcost[MAXVEX];
	adjvex[0] = 0;
	lowcost[0] = 0;
	for (i = 0; i < g->numNodes; i++)
	{
		lowcost[i] = g->arc[0][i];
		adjvex[i] = 0;
	}
	for (i = 0; i < g->numNodes; i++)
	{
		min = INFINITY_NEW;
		j = 1;
		k = 0;
		while (j < g->numNodes)
		{
			if (lowcost[j] != 0 && min < lowcost[j])
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		printf("(%d, %d)\n", adjvex[k], k);
		lowcost[k] = 0;
		for (j = 1; j < g->numNodes; j++)
		{
			if (lowcost[j] != 0 && g->arc[k][j] < lowcost[j])
			{
				lowcost[j] = g->arc[k][j];
				adjvex[j] = k;
			}
		}
	}
}







void createALGraph(GraphAdjList *g, bool isDirected /*= false*/)
{
	if (nullptr == g)
	{
		return;
	}
	EdgeNode* e;
	printf("输入顶点数和边数：\n");
	scanf_s("%d, %d", &g->numNodes, &g->numEdges);
	for (int i = 0; i < g->numNodes; i++)
	{
		//初始化每个顶点，并赋值
		//scanf_s("%d", &g->adjList[i].data);
		g->adjList[i].data = i + 1;
		printf("自动生成节点值:%d\n", g->adjList[i].data);
		g->adjList[i].firstEdge = nullptr;
		g->adjList[i].in = 0;
		g->adjList[i].out = 0;
	}
	for (int k = 0; k < g->numEdges; k++)
	{
		int i, j, weight;
		printf("输入第%d条边vi vj上的顶点序号及权值值：\n", k+1);
		scanf_s("%d %d %d", &i, &j, &weight);

		//创建i->j的边
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		memset(e, NULL, sizeof(EdgeNode));
		e->adjvex = j;
		e->weight = weight;
		e->next = g->adjList[i].firstEdge;
		g->adjList[i].firstEdge = e;
		g->adjList[i].out++; //节点出度加1

		//j节点
		if (!isDirected) 
		{
			//在无向图中，创建j->i的边
			e = (EdgeNode*)malloc(sizeof(EdgeNode));
			memset(e, NULL, sizeof(EdgeNode));
			e->adjvex = i;
			e->weight = weight;
			e->next = g->adjList[j].firstEdge;
			g->adjList[j].firstEdge = e;
			g->adjList[j].in++; //节点入度加1
		}
		else
		{
			g->adjList[j].in++; //节点入度加1
		}
		
	}

}

void _dfsForAl(GraphAdjList* g, int i, bool* isVisited)
{
	if (nullptr == g || nullptr == isVisited)
	{
		return;
	}
	isVisited[i] = true;
	printf("%c ", g->adjList[i].data);
	EdgeNode* p = g->adjList[i].firstEdge;
	while (nullptr != p)
	{
		if (!isVisited[p->adjvex])
		{
			_dfsForAl(g, p->adjvex, isVisited);
		}
		p = p->next;
	}
}

void dfsTraverseForAl(GraphAdjList* g)
{
	if (nullptr == g)
	{
		return;
	}
	int i;
	bool isVisited[MAXVEX];
	for (i = 0; i < g->numNodes; i++)
	{
		isVisited[i] = false;
	}
	for (i = 0; i < g->numNodes; i++)
	{
		if (!isVisited[i])
		{
			_dfsForAl(g, i, isVisited);
		}
	}
}

void bfsTraverseForAl(GraphAdjList* g)
{
	if (nullptr == g)
	{
		return;
	}
	int i;
	bool isVisited[MAXVEX];
	std::queue<int> q;
	for (i = 0; i < g->numNodes; i++)
	{
		isVisited[i] = false;
	}
	for (i = 0; i < g->numNodes; i++)
	{
		if (!isVisited[i])
		{
			isVisited[i] = true;
			printf("%c ", g->adjList[i].data);
			q.push(i);
			while (!q.empty())
			{
				int index = q.front();
				q.pop();
				EdgeNode* p = g->adjList[index].firstEdge;
				while (nullptr != p)
				{
					if (!isVisited[p->adjvex])
					{
						isVisited[p->adjvex] = true;
						printf("%c ", g->adjList[p->adjvex].data);
						q.push(p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}
}

Status topologicalSort(GraphAdjList* g)
{
	if (nullptr == g)
	{
		return ERROR;
	}
	EdgeNode* e = nullptr;
	int i, k, gettop;
	int top = 0;
	int count = 0;
	int* stack = (int*)malloc(sizeof(int) * g->numNodes);
	for (i = 0; i < g->numNodes; i++)
	{
		//查找所有入度为0的节点，入队列
		if (0 == g->adjList[i].in)
		{
			stack[++top] = i;
		}
	}
	while (top != 0)
	{
		gettop = stack[top--];
		printf("%d -> ", g->adjList[gettop].data);
		count++;
		for (e = g->adjList[gettop].firstEdge; nullptr != e; e = e->next)
		{
			k = e->adjvex;
			if (0 == (--g->adjList[e->adjvex].in))
			{
				stack[++top] = k;
			}
		}
	}
	if (count < g->numNodes)
	{
		return ERROR;
	}
	return OK;
}

bool checkCycleFrDGraph(GraphAdjList* g, int* topo)
{
	if (nullptr == g)
	{
		return false;
	}
	//构造一个队列
	std::queue<int> q;
	for (int i = 0; i < g->numNodes; i++)
	{
		if (0 == g->adjList[i].in)
		{
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		printf("当前输出索引：%d，节点：%d\n", cur, g->adjList[cur].data);
		if (nullptr != topo)
		{
			topo[cnt] = cur;
		}
		cnt++;
		for (EdgeNode* e = g->adjList[cur].firstEdge; nullptr != e; e = e->next)
		{
			if (0 < g->adjList[e->adjvex].in && 0 == (--g->adjList[e->adjvex].in))
			{
				q.push(e->adjvex);
			}
		}
	}
	return (cnt != g->numNodes);
}

bool criticalPath(GraphAdjList* g)
{
	if (nullptr == g || g->numNodes <= 0
		|| g->numNodes <= 0)
	{
		return false;
	}
	//拓扑排序结果
	int* topo = new int[g->numNodes];
	memset(topo, 0, sizeof(int)*g->numNodes);
	
	//记录事件最早发生时间
	int* ve = new int[g->numNodes];
	memset(ve, 0, sizeof(int)*g->numNodes);

	//记录事件最晚发生时间
	int* vl = new int[g->numNodes];
	memset(vl, 0, sizeof(int)*g->numNodes);

	//校验是否有环并返回拓扑排序后的结果
	if (checkCycleFrDGraph(g, topo))
	{
		printf("输入的数据节点及边存在环，无法计算关键路径");
		return false;
	}
	//按照拓扑次序求每个时间的最早发生时间
	for (int i = 0; i < g->numNodes; i++)
	{
		int cur = topo[i];
		EdgeNode* p = g->adjList[cur].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			if (ve[j] < ve[cur]+p->weight)
			{
				//从开始事件节点到该节点的最长路径
				ve[j] = ve[cur] + p->weight;
			}
			p = p->next;
		}
	}
	//初始化vl
	for (int i = 0; i < g->numNodes; i++)
	{
		vl[i] = ve[g->numNodes - 1];
	}

	//按逆拓扑次序求每个事件的最晚发生时间
	for (int i = g->numNodes-1; i >= 0; i--)
	{
		int cur = topo[i];
		EdgeNode* p = g->adjList[cur].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			if (vl[cur] > vl[j] - p->weight)
			{
				//需要用终止节点的时间 - 从终止事件节点到该节点的最长路径
				vl[cur] = vl[j] - p->weight;
			}
			p = p->next;
		}
	}

	//获取关键活动
	for (int i = 0; i < g->numNodes; i++)
	{
		EdgeNode* p = g->adjList[i].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			int e = ve[i]; //活动<i, j>最早开始时间
			int l = vl[j] - p->weight; //活动<i, j>最晚开始时间
			//如果为关键活动，最早开始时间与最晚开始时间应该一样
			if (e == l)
			{
				printf("关键活动<i, j>为：<%d, %d>\n", g->adjList[i].data, g->adjList[j].data);
			}
			p = p->next;
		}
	}
	return true;
}
