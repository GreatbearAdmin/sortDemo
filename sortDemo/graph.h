#pragma once
#define MAXVEX 100
#define INFINITY_NEW 65535 //��ʾ�����

//��������
typedef char VertexType;
//������
typedef int EdgeType;

typedef enum
{
	ERROR = 0,
	OK,
}Status;

//�ڽӾ����ʾ��
typedef struct
{
	//�����б�
	VertexType vexs[MAXVEX];
	//�ڽӾ����ʾ�ı�
	EdgeType arc[MAXVEX][MAXVEX];
	int numNodes, numEdges; //�������ͱ���
}MGraph;

//����һ������ͼ���ڽӾ����ʾ
void createGraph(MGraph* g);

//������ȱ���
void _dfs(MGraph* g, int i, bool* isVisited);
void dfsTraverse(MGraph* g);

//������ȱ���
void bfsTraverse(MGraph* g);

//����ķ�㷨
void minSpanTreeFrPrim(MGraph* g);

//�ڽӱ��ʾ��
typedef struct EdgeNode
{
	int adjvex; //�ڽӵ���±�
	EdgeType weight; //���ڴ洢Ȩֵ
	struct EdgeNode* next; //ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode
{
	int in; //�������
	int out; //�������
	VertexType data;
	EdgeNode* firstEdge; //�ߵ�ͷָ��
}VertexNode, AdjList[MAXVEX];
//typedef VertexNode[MAXVEX] AdjList;
typedef struct 
{
	AdjList adjList;
	int numNodes, numEdges;
}GraphAdjList;

void createALGraph(GraphAdjList *g, bool isDirected = false);

void _dfsForAl(GraphAdjList* g, int i, bool* isVisited);
void dfsTraverseForAl(GraphAdjList* g);

void bfsTraverseForAl(GraphAdjList* g);

//��������
Status topologicalSort(GraphAdjList* g);

//����ͼУ���Ƿ���ڻ�
bool checkCycleFrDGraph(GraphAdjList* g, int* topo);

//�ؼ�·��
bool criticalPath(GraphAdjList* g);


//ʮ������

//�ڽӶ��ر�