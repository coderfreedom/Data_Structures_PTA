#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535
typedef int WeightType;
typedef char DataType;
typedef int Vertex;
typedef struct GraphNode
{
    int iVertexNum;  //���������
    int iEdgeNum;  //�ߵ�����
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
    /*��ʼ��һ����vertexNum�����㵫û�бߵ�ͼ*/
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
    //�����<v, w>
    g->tGraph[e->v][e->w] = e->tWeight;
    
    //������ͼ����Ҫ����<w, v>
    g->tGraph[e->w][e->v] = e->tWeight;
}

Graph *BuildGraph(void)
{
    int vertexNum, i;
    Graph *g = NULL;
    Edge *e = NULL;
    
    scanf("%d", &vertexNum); //���붥��ĸ���
    g = (Graph*)CreateGraph(vertexNum);  //��ʼ��һ����vertexNum�����㵫û�бߵ�ͼ
    scanf("%d", g->iEdgeNum);  //�������
    if(g->iEdgeNum != 0) //����б�
    {
        e = (Edge*)malloc(sizeof(Edge)); //�����߽ڵ�
        
        for(i=0; i<g->iEdgeNum; i++)
        {
            scanf("%d %d %d", &e->v, &e->w, &e->tWeight);//���Ȩ�ز������ͣ�tWeight�Ķ����ʽҪ��
            InsertEdge(g, e);
        }
    }
    
    /*������������ݣ���������*/
    for(i=0; i<vertexNum; i++)
    {
        scanf("%c", &g->tData[i]);
    }
    
    return g;
}