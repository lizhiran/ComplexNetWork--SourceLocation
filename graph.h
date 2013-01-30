
//#define MAX_NAME 10
#define MAX_VERTEX_NUM 200      //������
#define MAX_EDGE_NUM 300		//����

//#define DIFF_EDGE_NUM 20000          //diffuionʹ�õ���ʱ�����С
typedef int InfoType;				// �������Ȩֵ 
//typedef char VertexType[MAX_NAME];	// �ַ������� 
//typedef enum{DG,AG}GraphKind; // {����ͼ,����ͼ} 



typedef struct Arc
{
	int arcId;
	int arcsourceId;
	int arctargerId;
	InfoType Weight;
	InfoType tmpWeight;
}ArcList[MAX_EDGE_NUM];

typedef struct ArcNode
{
	int arcId;
	int arcsourceId; //һ�˵�arcsourceIDӦ�õ���VNode��nodeid
	int arctargerId;
	int adjvex;					// �û���ָ��Ķ����λ�� 
	struct ArcNode *nextarc;	// ָ����һ������ָ�� 			 
	//InfoType Weight;			// ͼ��Ȩֵ
	//InfoType tmpWeight;
}ArcNode;	// ���� 

typedef struct VNode
{
	//VertexType label;			// ������Ϣ
	int degree;					//�ڵ�Ķ�
	int nodeid;
	int time;			//��¼����ʱ��
	bool isActive;
	int direction;	 
	int parent;
	int plength;
	ArcNode *firstarc;			// ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ�� 
}VNode,AdjList[MAX_VERTEX_NUM];// ͷ��� 

typedef struct
{	
	ArcList arctices;
	AdjList vertices;
	int vexnum,arcnum;	// ͼ�ĵ�ǰ�������ͻ��� 
	//int kind;			// ͼ�������־ 
}ALGraph;

//ALGraph graph;

int  GetNodeIndex(ALGraph G,int nodeid)//���ݽڵ�ID�����������е�����ֵ
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(G.vertices[i].nodeid==nodeid)
			return i;
	return -1;

}
/************************************************************************/
/* ���ڵ����ڵıߵ�ID��������     */  
/************************************************************************/
int *getNodeEdges(ALGraph *graph,int nodeId)
{
	int nodeIndex = GetNodeIndex(*graph,nodeId);
	int nodeDegree = graph->vertices[nodeIndex].degree;
	int *edges;
	// 	if (edges != NULL)
	// 	{
	// 		free(edges);
	// 	}
	edges = (int *)malloc(nodeDegree * sizeof(int));
	ArcNode *p;
	p = graph->vertices[nodeIndex].firstarc;
	int i = 0;
	while(p)
	{
		edges[i] = p->arcId;
		p=p->nextarc;
		i++;
	}
	free(p);
	return edges;

}
int GetEdgeId(ALGraph graph,int sourceid,int targetid)
{
	int nodeIndex = GetNodeIndex(graph,sourceid);
//	int nodeDegree = graph.vertices[nodeIndex].degree;
	ArcNode *p;
	p = graph.vertices[nodeIndex].firstarc;
	int arcID;
	while(p)
	{
		if (p->arctargerId == targetid)
		{
			arcID = p->arcId;
			break;
			//return arcID;
		}
		p=p->nextarc;
	}
	return arcID;
}
int CreateGraph(ALGraph *graph)//��ͼ��ýṹ������Ϊnodeid//���ҿ��٣������ܲ��ǣ�����������
{// ֻ������ͼ�����

	FILE *fpNode;
	FILE *fpEdge;
	//char charEnd;

	if ((fpEdge=fopen("C:\\BA_5_Edges.csv","r"))==NULL)
	{
		printf("no file\n");
		exit(0);
	}
	if ((fpNode=fopen("C:\\BA_5_Nodes.csv","r"))==NULL)
	{
		printf("no file\n");
		exit(0);
	}
	int nodeNum = 0;
	while(!feof(fpNode))
	{			
		int tmpNodeId;
		fscanf(fpNode,"%d",&tmpNodeId);
		printf("%d\n",tmpNodeId);
		// **�����ˣ��ڴ��Եõ��Ľڵ�IDΪͼ�������ID��������洢�����⡶���ڵ㲻�����������м�ڵ�δ��ֵ�������л��ǰ�˳����

		graph->vertices[nodeNum].nodeid = tmpNodeId;
		graph->vertices[nodeNum].firstarc = 0;
		graph->vertices[nodeNum].degree = 0;
		graph->vertices[nodeNum].direction = -1;
		graph->vertices[nodeNum].isActive = false;
		graph->vertices[nodeNum].time = 1;
		graph->vertices[nodeNum].parent = -1;
		nodeNum++;
	}
	graph->vexnum = nodeNum-1;
	int edgeNum = 0;
	while(!feof(fpEdge))
	{	
		int sourceid;
		int targetid;
		fscanf(fpEdge,"%d %d",&sourceid,&targetid);
		printf("%d,%d\n",sourceid,targetid);
		graph->arctices[edgeNum].arcId = edgeNum;
		graph->arctices[edgeNum].arcsourceId = sourceid;
		graph->arctices[edgeNum].arctargerId = targetid;
		graph->arctices[edgeNum].Weight = 1;
		graph->arctices[edgeNum].tmpWeight =1;
		edgeNum++;
	}
	graph->arcnum = edgeNum-1;
	fclose(fpNode);
	fclose(fpEdge);

	int i,j,k;
	int nodeindex;
	//	int w;		// Ȩֵ 
	//VertexType va,vb;
	ArcNode *p;
	int degree;
	for(k = 0;k < graph->arcnum; ++k)	// ����������� 
	{
		i =	graph->arctices[k].arcsourceId;// ��ͷ 
		j =	graph->arctices[k].arctargerId;// ��β
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->arcId= graph->arctices[k].arcId;
		p->arcsourceId = i;
		p->arctargerId = j;
		//p->Weight =(*graph).arctices[k].Weight;
		p->adjvex =j;
		nodeindex = GetNodeIndex(*graph,i); 
		p->nextarc = graph->vertices[nodeindex].firstarc; // ���ڱ�ͷ 
		graph->vertices[nodeindex].firstarc = p;

		degree = graph->vertices[nodeindex].degree;//���ýڵ�Ķ�
		graph->vertices[nodeindex].degree = degree + 1;

		//����ͼ��������j�ϼ�һ����
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->arcId=graph->arctices[k].arcId;//Ҫ����һ�������ʹ����ͬ�ı�ID
		p->arcsourceId = j;
		p->arctargerId = i;
		p->adjvex = i;
		nodeindex = GetNodeIndex(*graph,j);
		p->nextarc = graph->vertices[nodeindex].firstarc; // ���ڱ�ͷ 
		graph->vertices[nodeindex].firstarc = p;
		degree = graph->vertices[nodeindex].degree;//���ýڵ�Ķ�
		graph->vertices[nodeindex].degree = degree + 1;
	}
	return 1;
}
//	���ͼ���ڽӱ�G��
void Display(ALGraph G)
{
	int i;
	ArcNode *p;
	printf("%d�����㣺\n",G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
		printf("%d ",G.vertices[i].nodeid);
	printf("\n%d����(��):\n", G.arcnum);
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			// 			if (p->arcsourceId<p->arctargerId)
			// 			{
			// 				printf("%d-%d ",p->arcsourceId,p->arctargerId);
			// 			}
			// 			p=p->nextarc;


			printf("%d-%d-%d ",p->arcId,p->arcsourceId,p->arctargerId);

			p=p->nextarc;
		}
		printf("\n");
		printf("��Ϊ%d\n", G.vertices[i].degree);
	}
}
