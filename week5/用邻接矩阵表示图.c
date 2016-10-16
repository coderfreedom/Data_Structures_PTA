#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535
typedef int WeightType;
typedef char DataType;
typedef int Vertex;
typedef struct GraphNode
{
    int iVertexNum;  //顶点的数量
    int iEdgeNum;  //边的数量
    WeightType tGraph[MaxVertexNum][MaxVertexNum];
    DataType tData[MaxVertexNum];
}Graph;

typedef struct EdgeNode
{
    Vertex v, w;
    WeightType tWeight;
}Edge;

Graph *CreateGraph(int vertexNum);
void InsertEdge(Graph *g, Edge *e);
Graph *BuildGraph(void);

int main(void)
{
    
    return 0;
}

Graph *CreateGraph(int vertexNum)
{
    /*初始化一个有vertexNum个顶点但没有边的图*/
    Vertex v, w;
    Graph *g = NULL;
    
    g = (Graph*)malloc(sizeof(Graph));
    g->iVertexNum = vertexNum;
    g->iEdgeNum = 0;
    
    for(v=0; v<g->iVertexNum; v++)
    {
        for(w=0; w<g->iVertexNum; w++)
        {
            g->tGraph[v][w] = INFINITY;
        }
    }
    
    return g;
}

void InsertEdge(Graph *g, Edge *e)
{
    //插入边<v, w>
    g->tGraph[e->v][e->w] = e->tWeight;
    
    //对无向图，还要插入<w, v>
    g->tGraph[e->w][e->v] = e->tWeight;
}

Graph *BuildGraph(void)
{
    int vertexNum, i;
    Graph *g = NULL;
    Edge *e = NULL;
    
    scanf("%d", &vertexNum); //读入顶点的个数
    g = (Graph*)CreateGraph(vertexNum);  //初始化一个有vertexNum个顶点但没有边的图
    scanf("%d", g->iEdgeNum);  //读入边数
    if(g->iEdgeNum != 0) //如果有边
    {
        e = (Edge*)malloc(sizeof(Edge)); //建立边节点
        
        for(i=0; i<g->iEdgeNum; i++)
        {
            scanf("%d %d %d", &e->v, &e->w, &e->tWeight);//如果权重不是整型，tWeight的读入格式要改
            InsertEdge(g, e);
        }
    }
    
    /*如果顶点有数据，读入数据*/
    for(i=0; i<vertexNum; i++)
    {
        scanf("%c", &g->tData[i]);
    }
    
    return g;
}