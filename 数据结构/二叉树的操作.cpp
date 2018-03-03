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
//初始化栈  
Status InitStack(Sqstack &s);
//元素入栈  
Status Push(Sqstack &s, BiTree e);
//获得栈顶元素  
Status GetTop(Sqstack s, BiTree &e);
//弹出栈顶元素  
Status Pop(Sqstack &s, BiTree &e);
//判断栈是否为空，为空返回1，否则返回0  
int StackEmpty(Sqstack s);

//创建树,以先序序列建立树  
Status CreateBiTree(BiTree &t);
//非递归先序遍历  
Status PreOrder(BiTree t);
//非递归中序遍历  
Status InOrder(BiTree t);
//非递归后序遍历  
Status PostOrder(BiTree t);
//求树的深度
Status TreeDepth(BiTree t);
//求双节点个数
Status DoubleNode_Num(BiTree t);
//求结点数
Status NodeNum(BiTree t);
//求叶子节点数
Status LeafNum(BiTree t);


int main()
{
	BiTree T;
	int d, n,N,L;
	printf("按先序序列输入结点序列，'#'代表空:\n");
	CreateBiTree(T);
	printf("非递归先序遍历的结果：");
	PreOrder(T);
	printf("\n非递归中序遍历的结果：");
	InOrder(T);
	printf("\n非递归后序遍历的结果：");
	PostOrder(T);
	printf("\n");
	printf("树的深度为:");
	printf("%d\n", d = TreeDepth(T));
	printf("双节点个数为:");
	printf("%d\n", n = DoubleNode_Num(T));
	printf("节点数为:");
	printf("%d\n", N = NodeNum(T));
	printf("叶节点数为:");
	printf("%d\n", L = LeafNum(T));
	system("pause");
	return 0;
}

//初始化栈  
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

//元素入栈  
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

//获得栈顶元素  
Status GetTop(Sqstack s, BiTree &e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	e = *(s.top - 1);
	return OK;
}

//弹出栈顶元素  
Status Pop(Sqstack &s, BiTree &e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	e = *(--s.top);
	return OK;
}

//判断栈是否为空，为空返回1，否则返回0  
int StackEmpty(Sqstack s)
{
	if (s.top == s.base)
		return 1;
	return 0;
}

//创建树,以先序序列建立树  
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

//非递归先序遍历  
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

//非递归中序遍历  
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

//非递归后序遍历  
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
			{//左右子树都已输出，则该节点也输出          
				Pop(s, p);
				printf("%c", p->data);
				if (!StackEmpty(s))
					GetTop(s, p); //得到弹出节点元素的父节点  
				else
					p = NULL;
			}
			else
			{
				if ((p->lchild) && (p->lchild->isOut == 1))
				{//如果存在左子树,并且左子树已经遍历完，则说明该节点已经入栈，不用再次Push,直接走向右子树            
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
						p->isOut = 1; //右子树已输出，将父节点isOut置1  
				}
				else
					p = NULL;
			}

		}
	}
	return OK;
}
//求树的深度
Status TreeDepth(BiTree t)
{
	int N1, N2;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		N1 = TreeDepth(t->rchild);/*遍历左子树*/
		N2 = TreeDepth(t->lchild);/*遍历右子树*/
	}
	if (N1>N2)
		return N1 + 1;
	else
		return N2 + 1;
}
//求双节点个数
Status DoubleNode_Num(BiTree t)
{
	int num1, num2;
	if (t == NULL)
		return 0;
	num1 = DoubleNode_Num(t->rchild);/*遍历左子树*/
	num2 = DoubleNode_Num(t->lchild);/*遍历右子树*/
	if (t->rchild != NULL&t->lchild != NULL)
		return (num1 + num2 + 1);
	else
		return (num1 + num2);
}
//求结点数
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
//求叶子节点数
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