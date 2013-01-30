
typedef int QElemType;
// ���е�˳��洢�ṹ(ѭ������)
#define MAX_QSIZE 100 // �����г���+1�����Ϊ�ڵ�����С
struct SqQueue
{
	QElemType *base; // ��ʼ���Ķ�̬����洢�ռ�
	int front; // ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear; // βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
};


void InitQueue(SqQueue &Q)
{ // ����һ���ն���Q
	Q.base=(QElemType *)malloc(MAX_QSIZE*sizeof(QElemType));
	if(!Q.base) // �洢����ʧ��
		exit(OVERFLOW);
	Q.front=Q.rear=0;
}

void DestroyQueue(SqQueue &Q)
{ // ���ٶ���Q��Q���ٴ���
	if(Q.base)
		free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
}

void ClearQueue(SqQueue &Q)
{ // ��Q��Ϊ�ն���
	Q.front=Q.rear=0;
}

bool QueueEmpty(SqQueue Q)
{ // ������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	if(Q.front==Q.rear) // ���пյı�־
		return true;
	else
		return false;
}

int QueueLength(SqQueue Q)
{ // ����Q��Ԫ�ظ����������еĳ���
	return(Q.rear-Q.front+MAX_QSIZE)%MAX_QSIZE;
}

bool GetHead(SqQueue Q,QElemType &e)
{ // �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	if(Q.front==Q.rear) // ���п�
		return false;
	e=Q.base[Q.front];
	return true;
}

bool EnQueue(SqQueue &Q,QElemType e)
{ // ����Ԫ��eΪQ���µĶ�βԪ��
	if((Q.rear+1)%MAX_QSIZE==Q.front) // ������
		return false;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAX_QSIZE;
	return true;
}

bool DeQueue(SqQueue &Q,QElemType &e)
{ // �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	if(Q.front==Q.rear) // ���п�
		return false;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAX_QSIZE;
	return true;
}

