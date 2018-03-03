#include<stdio.h>  
#include<stdlib.h>  
#define STACKINITSIZE 100  
#define STACKINCREASESIZE 20 
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef int Status;
typedef char ElemType;
typedef struct tree
{
	ElemType data;
	struct tree * lchild;
	struct tree * rchild;
	unsigned int isOut;
}BiTNode, *BiTree;
typedef struct stack
{
	BiTree * base;
	BiTree * top;
	int stacksize;
}Sqstack;
//��ʼ��ջ  
Status InitStack(Sqstack &s);
//Ԫ����ջ  
Status Push(Sqstack &s, BiTree e);
//���ջ��Ԫ��  
Status GetTop(Sqstack s, BiTree &e);
//����ջ��Ԫ��  
Status Pop(Sqstack &s, BiTree &e);
//�ж�ջ�Ƿ�Ϊ�գ�Ϊ�շ���1�����򷵻�0  
int StackEmpty(Sqstack s);

//������,���������н�����  
Status CreateBiTree(BiTree &t);
//�ǵݹ��������  
Status PreOrder(BiTree t);
//�ǵݹ��������  
Status InOrder(BiTree t);
//�ǵݹ�������  
Status PostOrder(BiTree t);
//���������
Status TreeDepth(BiTree t);
//��˫�ڵ����
Status DoubleNode_Num(BiTree t);
//������
Status NodeNum(BiTree t);
//��Ҷ�ӽڵ���
Status LeafNum(BiTree t);


int main()
{
	BiTree T;
	int d, n,N,L;
	printf("�������������������У�'#'�����:\n");
	CreateBiTree(T);
	printf("�ǵݹ���������Ľ����");
	PreOrder(T);
	printf("\n�ǵݹ���������Ľ����");
	InOrder(T);
	printf("\n�ǵݹ��������Ľ����");
	PostOrder(T);
	printf("\n");
	printf("�������Ϊ:");
	printf("%d\n", d = TreeDepth(T));
	printf("˫�ڵ����Ϊ:");
	printf("%d\n", n = DoubleNode_Num(T));
	printf("�ڵ���Ϊ:");
	printf("%d\n", N = NodeNum(T));
	printf("Ҷ�ڵ���Ϊ:");
	printf("%d\n", L = LeafNum(T));
	system("pause");
	return 0;
}

//��ʼ��ջ  
Status InitStack(Sqstack &s)
{
	s.base = (BiTree *)malloc(STACKINITSIZE * sizeof(BiTree));
	if (!s.base)
	{
		exit(OVERFLOW);
	}
	s.top = s.base;
	s.stacksize = STACKINITSIZE;
	return OK;
}

//Ԫ����ջ  
Status Push(Sqstack &s, BiTree e)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (BiTree *)realloc(s.base, (s.stacksize + STACKINCREASESIZE) * sizeof(BiTree));
		if (!s.base)
		{
			exit(OVERFLOW);
		}

		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREASESIZE;
	}
	e->isOut = 0;
	*s.top++ = e;
	return OK;
}

//���ջ��Ԫ��  
Status GetTop(Sqstack s, BiTree &e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	e = *(s.top - 1);
	return OK;
}

//����ջ��Ԫ��  
Status Pop(Sqstack &s, BiTree &e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	e = *(--s.top);
	return OK;
}

//�ж�ջ�Ƿ�Ϊ�գ�Ϊ�շ���1�����򷵻�0  
int StackEmpty(Sqstack s)
{
	if (s.top == s.base)
		return 1;
	return 0;
}

//������,���������н�����  
Status CreateBiTree(BiTree &t)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		t = NULL;
	else
	{
		if (!(t = (BiTNode *)malloc(sizeof(BiTNode))))
		{
			exit(OVERFLOW);
		}
		t->data = ch;
		CreateBiTree(t->lchild);
		CreateBiTree(t->rchild);
	}
}

//�ǵݹ��������  
Status PreOrder(BiTree t)
{
	BiTree p = t;
	Sqstack s;
	InitStack(s);

	while (p || !StackEmpty(s))
	{
		if (p)
		{
			printf("%c", p->data);
			Push(s, p);
			p = p->lchild;
		}
		else
		{
			Pop(s, p);
			p = p->rchild;
		}
	}
	return OK;
}

//�ǵݹ��������  
Status InOrder(BiTree t)
{
	BiTree p = t;
	Sqstack s;
	InitStack(s);
	while (p || !StackEmpty(s))
	{
		if (p)
		{
			Push(s, p);
			p = p->lchild;
		}
		else
		{
			Pop(s, p);
			printf("%c", p->data);
			p = p->rchild;
		}
	}
	return OK;
}

//�ǵݹ�������  
Status PostOrder(BiTree t)
{
	t->isOut = 0;
	BiTree p = t;
	Sqstack s;
	InitStack(s);
	while (p || !StackEmpty(s))
	{
		if (p)
		{
			if (p->isOut)
			{//�������������������ýڵ�Ҳ���          
				Pop(s, p);
				printf("%c", p->data);
				if (!StackEmpty(s))
					GetTop(s, p); //�õ������ڵ�Ԫ�صĸ��ڵ�  
				else
					p = NULL;
			}
			else
			{
				if ((p->lchild) && (p->lchild->isOut == 1))
				{//�������������,�����������Ѿ������꣬��˵���ýڵ��Ѿ���ջ�������ٴ�Push,ֱ������������            
					p->isOut = 1;
					p = p->rchild;
				}
				else
				{
					Push(s, p);
					p = p->lchild;
				}
			}
		}
		else
		{
			if (!StackEmpty(s))
				GetTop(s, p);
			else
				p = NULL;

			if (p->rchild)
			{
				p = p->rchild;
			}
			else
			{
				Pop(s, p);
				printf("%c", p->data);
				p->isOut = 1;
				if (!StackEmpty(s))
				{
					GetTop(s, p);
					if (p->lchild == NULL)
						p->isOut = 1; //������������������ڵ�isOut��1  
				}
				else
					p = NULL;
			}

		}
	}
	return OK;
}
//���������
Status TreeDepth(BiTree t)
{
	int N1, N2;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		N1 = TreeDepth(t->rchild);/*����������*/
		N2 = TreeDepth(t->lchild);/*����������*/
	}
	if (N1>N2)
		return N1 + 1;
	else
		return N2 + 1;
}
//��˫�ڵ����
Status DoubleNode_Num(BiTree t)
{
	int num1, num2;
	if (t == NULL)
		return 0;
	num1 = DoubleNode_Num(t->rchild);/*����������*/
	num2 = DoubleNode_Num(t->lchild);/*����������*/
	if (t->rchild != NULL&t->lchild != NULL)
		return (num1 + num2 + 1);
	else
		return (num1 + num2);
}
//������
Status NodeNum(BiTree t)
{

	if (t == NULL)
	{
		return ERROR;
	}
	else
	{
		return 1 + NodeNum(t->lchild) + NodeNum(t->rchild);
	}
}
//��Ҷ�ӽڵ���
Status LeafNum(BiTree t)
{
	if (t == NULL)
	{
		return ERROR;
	}
	if (t->lchild == NULL && t->rchild == NULL)
	{
		return OK;
	}
	else
	{
		return LeafNum(t->lchild) + LeafNum(t->rchild);
	}
}