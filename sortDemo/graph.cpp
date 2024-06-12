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
	printf("���붥�����ͱ�����\n");
	scanf_s("%d, %d", &g->numNodes, &g->numEdges);
	for (i=0; i<g->numNodes; i++)
	{
		scanf_s(&g->vexs[i]);
	}
	for (i = 0; i < g->numNodes; i++)
	{
		for (j = 0; j < g->numNodes; j++)
		{
			g->arc[i][j] = INFINITY_NEW; //�ڽӾ����ʼ��
		}
	}
	for (k = 0; k < g->numEdges; k++)
	{
		printf("�����(vi, vj)�ϵ��±�i��j��Ȩw��\n");
		scanf_s("%d, %d, %d", &i, &j, &w);
		g->arc[i][j] = w;
		//����ͼ
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
	printf("���붥�����ͱ�����\n");
	scanf_s("%d, %d", &g->numNodes, &g->numEdges);
	for (int i = 0; i < g->numNodes; i++)
	{
		//��ʼ��ÿ�����㣬����ֵ
		//scanf_s("%d", &g->adjList[i].data);
		g->adjList[i].data = i + 1;
		printf("�Զ����ɽڵ�ֵ:%d\n", g->adjList[i].data);
		g->adjList[i].firstEdge = nullptr;
		g->adjList[i].in = 0;
		g->adjList[i].out = 0;
	}
	for (int k = 0; k < g->numEdges; k++)
	{
		int i, j, weight;
		printf("�����%d����vi vj�ϵĶ�����ż�Ȩֵֵ��\n", k+1);
		scanf_s("%d %d %d", &i, &j, &weight);

		//����i->j�ı�
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		memset(e, NULL, sizeof(EdgeNode));
		e->adjvex = j;
		e->weight = weight;
		e->next = g->adjList[i].firstEdge;
		g->adjList[i].firstEdge = e;
		g->adjList[i].out++; //�ڵ���ȼ�1

		//j�ڵ�
		if (!isDirected) 
		{
			//������ͼ�У�����j->i�ı�
			e = (EdgeNode*)malloc(sizeof(EdgeNode));
			memset(e, NULL, sizeof(EdgeNode));
			e->adjvex = i;
			e->weight = weight;
			e->next = g->adjList[j].firstEdge;
			g->adjList[j].firstEdge = e;
			g->adjList[j].in++; //�ڵ���ȼ�1
		}
		else
		{
			g->adjList[j].in++; //�ڵ���ȼ�1
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
		//�����������Ϊ0�Ľڵ㣬�����
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
	//����һ������
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
		printf("��ǰ���������%d���ڵ㣺%d\n", cur, g->adjList[cur].data);
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
	//����������
	int* topo = new int[g->numNodes];
	memset(topo, 0, sizeof(int)*g->numNodes);
	
	//��¼�¼����緢��ʱ��
	int* ve = new int[g->numNodes];
	memset(ve, 0, sizeof(int)*g->numNodes);

	//��¼�¼�������ʱ��
	int* vl = new int[g->numNodes];
	memset(vl, 0, sizeof(int)*g->numNodes);

	//У���Ƿ��л����������������Ľ��
	if (checkCycleFrDGraph(g, topo))
	{
		printf("��������ݽڵ㼰�ߴ��ڻ����޷�����ؼ�·��");
		return false;
	}
	//�������˴�����ÿ��ʱ������緢��ʱ��
	for (int i = 0; i < g->numNodes; i++)
	{
		int cur = topo[i];
		EdgeNode* p = g->adjList[cur].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			if (ve[j] < ve[cur]+p->weight)
			{
				//�ӿ�ʼ�¼��ڵ㵽�ýڵ���·��
				ve[j] = ve[cur] + p->weight;
			}
			p = p->next;
		}
	}
	//��ʼ��vl
	for (int i = 0; i < g->numNodes; i++)
	{
		vl[i] = ve[g->numNodes - 1];
	}

	//�������˴�����ÿ���¼���������ʱ��
	for (int i = g->numNodes-1; i >= 0; i--)
	{
		int cur = topo[i];
		EdgeNode* p = g->adjList[cur].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			if (vl[cur] > vl[j] - p->weight)
			{
				//��Ҫ����ֹ�ڵ��ʱ�� - ����ֹ�¼��ڵ㵽�ýڵ���·��
				vl[cur] = vl[j] - p->weight;
			}
			p = p->next;
		}
	}

	//��ȡ�ؼ��
	for (int i = 0; i < g->numNodes; i++)
	{
		EdgeNode* p = g->adjList[i].firstEdge;
		while (nullptr != p)
		{
			int j = p->adjvex;
			int e = ve[i]; //�<i, j>���翪ʼʱ��
			int l = vl[j] - p->weight; //�<i, j>����ʼʱ��
			//���Ϊ�ؼ�������翪ʼʱ��������ʼʱ��Ӧ��һ��
			if (e == l)
			{
				printf("�ؼ��<i, j>Ϊ��<%d, %d>\n", g->adjList[i].data, g->adjList[j].data);
			}
			p = p->next;
		}
	}
	return true;
}
