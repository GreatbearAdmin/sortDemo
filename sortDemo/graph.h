#pragma once
#define MAXVEX 100
#define INFINITY_NEW 65535 //表示无穷大

//顶点类型
typedef char VertexType;
//边类型
typedef int EdgeType;

typedef enum
{
	ERROR = 0,
	OK,
}Status;

//邻接矩阵表示法
typedef struct
{
	//顶点列表
	VertexType vexs[MAXVEX];
	//邻接矩阵表示的边
	EdgeType arc[MAXVEX][MAXVEX];
	int numNodes, numEdges; //顶点数和边数
}MGraph;

//构建一个无向图的邻接矩阵表示
void createGraph(MGraph* g);

//深度优先遍历
void _dfs(MGraph* g, int i, bool* isVisited);
void dfsTraverse(MGraph* g);

//广度优先遍历
void bfsTraverse(MGraph* g);

//普利姆算法
void minSpanTreeFrPrim(MGraph* g);

//邻接表表示法
typedef struct EdgeNode
{
	int adjvex; //邻接点的下标
	EdgeType weight; //用于存储权值
	struct EdgeNode* next; //指向下一个邻接点
}EdgeNode;

typedef struct VertexNode
{
	int in; //顶点入度
	int out; //顶点出度
	VertexType data;
	EdgeNode* firstEdge; //边的头指针
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

//拓扑排序
Status topologicalSort(GraphAdjList* g);

//有向图校验是否存在环
bool checkCycleFrDGraph(GraphAdjList* g, int* topo);

//关键路径
bool criticalPath(GraphAdjList* g);


//十字链表法

//邻接多重表