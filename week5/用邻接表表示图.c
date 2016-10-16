#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/*边的定义*/
typedef struct EdgeNode
{
	Vertex v, w;  //有向边<v,w>
	WeightType tWeight; //权重
}Edge;

/*邻接点的定义*/
typedef struct AdjNode
{
	Vertex adjvex;  //邻接点下标
	WeightType tWeight; // 边权重
	struct AdjNode *next; //指向下一个邻接点
}AdjNode;

/*顶点表头结点的定义*/
typedef struct VertexNode
{
	DataType tData;  //存储头结点的数据
	AdjNode *tFirstEdge;  //边表头指针
}VertexNode;

/*图结点的定义*/
typedef struct GraphNode
{
	int iVertexNum; //顶点数
	int iEdgeNum;	//边数
	VertexNode G[MaxVertexNum]; //邻接表
}Graph;

Graph *CreateGraph(int iVertexNum);
void InsertEdge(Graph *g, Edge *e);
Graph *BuildGraph(void);

int main(void)
{



	return 0;
}

Graph *CreateGraph(int iVertexNum)
{
	/*初始化一个有iVertexNum个顶点但没有边的图*/
	Vertex v;
	Graph *g = NULL;

	g = (Graph*)malloc(sizeof(Graph)); //建立图
	g->iVertexNum = iVertexNum;
	g->iEdgeNum = 0;

	/*初始化邻接表头指针*/
	for (v = 0; v < g->iVertexNum; v++)
	{
		g->G[v].tFirstEdge = NULL;
	}

	return g;
}

void InsertEdge(Graph *g, Edge *e)
{
	AdjNode *adj = NULL;

	/* 插入边<v, w> */
	//为w建立新的邻接点
	adj = (AdjNode*)malloc(sizeof(AdjNode));
	adj->adjvex = e->w;
	adj->tWeight = e->tWeight;
	//将邻接点插入v的表头
	adj->next = g->G[e->v].tFirstEdge;
	g->G[e->v].tFirstEdge = adj;

	/*如果是无向图，还要插入<w, v>*/
	//为v建立新的邻接点
	adj = (AdjNode*)malloc(sizeof(AdjNode));
	adj->adjvex = e->v;
	adj->tWeight = e->tWeight;
	//将邻接点插入w的表头
	adj->next = g->G[e->w].tFirstEdge;
	g->G[e->w].tFirstEdge = adj;
}

Graph *BuildGraph(void)
{
	int iVertexNum, i;
	Graph *g = NULL;
	Edge *e = NULL;

	scanf("%d", &iVertexNum); //读入顶点的个数
	g = CreateGraph(iVertexNum); //初始化有iVertexNum个顶点但没有边的图

	scanf("%d", g->iEdgeNum); //读入边数
	if (g->iEdgeNum != 0) //如果有边
	{
		e = (Edge*)malloc(sizeof(Edge)); //建立边结点
		
		/*读入边，插入边，数据格式：起点 终点 权重*/
		for (i = 0; i < g->iEdgeNum; i++)
		{
			scanf("%d %d %d", &e->v, &e->w, &e->tWeight);//如果权重不是整型，权重的读入方式要改
			InsertEdge(g, e);
		}
	}

	/* 如果顶点有数据，读入数据 */
	for (i = 0; i < g->iVertexNum; i++)
	{
		scanf("%c", &g->G[i].tData);
	}

	return g;
}