#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/*�ߵĶ���*/
typedef struct EdgeNode
{
	Vertex v, w;  //�����<v,w>
	WeightType tWeight; //Ȩ��
}Edge;

/*�ڽӵ�Ķ���*/
typedef struct AdjNode
{
	Vertex adjvex;  //�ڽӵ��±�
	WeightType tWeight; // ��Ȩ��
	struct AdjNode *next; //ָ����һ���ڽӵ�
}AdjNode;

/*�����ͷ���Ķ���*/
typedef struct VertexNode
{
	DataType tData;  //�洢ͷ��������
	AdjNode *tFirstEdge;  //�߱�ͷָ��
}VertexNode;

/*ͼ���Ķ���*/
typedef struct GraphNode
{
	int iVertexNum; //������
	int iEdgeNum;	//����
	VertexNode G[MaxVertexNum]; //�ڽӱ�
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
	/*��ʼ��һ����iVertexNum�����㵫û�бߵ�ͼ*/
	Vertex v;
	Graph *g = NULL;

	g = (Graph*)malloc(sizeof(Graph)); //����ͼ
	g->iVertexNum = iVertexNum;
	g->iEdgeNum = 0;

	/*��ʼ���ڽӱ�ͷָ��*/
	for (v = 0; v < g->iVertexNum; v++)
	{
		g->G[v].tFirstEdge = NULL;
	}

	return g;
}

void InsertEdge(Graph *g, Edge *e)
{
	AdjNode *adj = NULL;

	/* �����<v, w> */
	//Ϊw�����µ��ڽӵ�
	adj = (AdjNode*)malloc(sizeof(AdjNode));
	adj->adjvex = e->w;
	adj->tWeight = e->tWeight;
	//���ڽӵ����v�ı�ͷ
	adj->next = g->G[e->v].tFirstEdge;
	g->G[e->v].tFirstEdge = adj;

	/*���������ͼ����Ҫ����<w, v>*/
	//Ϊv�����µ��ڽӵ�
	adj = (AdjNode*)malloc(sizeof(AdjNode));
	adj->adjvex = e->v;
	adj->tWeight = e->tWeight;
	//���ڽӵ����w�ı�ͷ
	adj->next = g->G[e->w].tFirstEdge;
	g->G[e->w].tFirstEdge = adj;
}

Graph *BuildGraph(void)
{
	int iVertexNum, i;
	Graph *g = NULL;
	Edge *e = NULL;

	scanf("%d", &iVertexNum); //���붥��ĸ���
	g = CreateGraph(iVertexNum); //��ʼ����iVertexNum�����㵫û�бߵ�ͼ

	scanf("%d", g->iEdgeNum); //�������
	if (g->iEdgeNum != 0) //����б�
	{
		e = (Edge*)malloc(sizeof(Edge)); //�����߽��
		
		/*����ߣ�����ߣ����ݸ�ʽ����� �յ� Ȩ��*/
		for (i = 0; i < g->iEdgeNum; i++)
		{
			scanf("%d %d %d", &e->v, &e->w, &e->tWeight);//���Ȩ�ز������ͣ�Ȩ�صĶ��뷽ʽҪ��
			InsertEdge(g, e);
		}
	}

	/* ������������ݣ��������� */
	for (i = 0; i < g->iVertexNum; i++)
	{
		scanf("%c", &g->G[i].tData);
	}

	return g;
}