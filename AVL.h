#include "BST.h"
template <class T>
class CAVL:public CBST<T>
{
public:
	void leftRotate(LPNODE root)
	{
		LPNODE rootR=root->r;
		if(rootR==NULL) return;
		LPNODE rootP=root->p;
		LPNODE rootRL=rootR->l;
		if(rootP)
		{
			if(rootP->l==root)
			{
				rootP->l=rootR;
			}
			if(rootP->r==root)
			{
				rootP->r=rootR;
			}
			rootR->p=rootP;
		}else
		{
			pRoot=rootR;
			rootR->p=NULL;
		}
		rootR->l=root;
		root->p=rootR;
		root->r=rootRL;
		if(rootRL) rootRL->p=root;
	}
	void rightRotate(LPNODE root)
	{
		LPNODE rootL=root->l;
		if(rootL==NULL) return;
		LPNODE rootP=root->p;
		LPNODE rootLR=rootL->r;
		if(rootP)
		{
			if(rootP->l==root)
			{
				rootP->l=rootL;
			}
			if(rootP->r==root)
			{
				rootP->r=rootL;
			}
			rootL->p=rootP;
		}else
		{
			pRoot=rootL;
			rootL->p=NULL;
		}
		rootL->r=root;
		root->p=rootL;
		root->l=rootLR;
		if(rootLR) rootLR->p=root;
	}
	bool Insert(const T& element)
	{
		LPNODE lpNewNode=NULL;
		if(!CBST::Insert(element,&lpNewNode)) return 1;
		if(lpNewNode->p&&lpNewNode->p->p)
		{
			int l=GetHeightR(lpNewNode->p->p->l);
			int r=GetHeightR(lpNewNode->p->p->r);
			if(abs(r-l)>1)//如果平衡因子的绝对值超过1
			{
				if(r>l)//如果right>left
				{
					if(lpNewNode==lpNewNode->p->l)//新增的节点是left节点
					{
						/*
						原始。
							\
							 \
							 /
						*/
						rightRotate(lpNewNode->p);
						/*
						一次right旋转之后。
							\
							 \
							  \
						*/
						leftRotate(lpNewNode->p);
						/*
						再次left旋转之后。
							\
							/\
							  
						*/
					}else
					{
						/*
						原始。
							\
							 \
							  \
						*/
						leftRotate(lpNewNode->p->p);
						/*
						一次right旋转之后。
							\
							/\
						*/
					}
				}else//如果是left>right
				{
					if(lpNewNode->p->l==lpNewNode)
					{
						/*
						原始
								/
							   /
							  /
						*/
						rightRotate(lpNewNode->p->p);
					}else
					{
						/*
							原始
								/
							   /
							   \
						*/
						leftRotate(lpNewNode->p);
						/*
							执行完毕
								/
							   /
							  /
						*/
						rightRotate(lpNewNode->p);
					}
				}
			}
		}
		return false;
	}
};
