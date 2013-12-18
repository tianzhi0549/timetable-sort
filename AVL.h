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
			if(abs(r-l)>1)//���ƽ�����ӵľ���ֵ����1
			{
				if(r>l)//���right>left
				{
					if(lpNewNode==lpNewNode->p->l)//�����Ľڵ���left�ڵ�
					{
						/*
						ԭʼ��
							\
							 \
							 /
						*/
						rightRotate(lpNewNode->p);
						/*
						һ��right��ת֮��
							\
							 \
							  \
						*/
						leftRotate(lpNewNode->p);
						/*
						�ٴ�left��ת֮��
							\
							/\
							  
						*/
					}else
					{
						/*
						ԭʼ��
							\
							 \
							  \
						*/
						leftRotate(lpNewNode->p->p);
						/*
						һ��right��ת֮��
							\
							/\
						*/
					}
				}else//�����left>right
				{
					if(lpNewNode->p->l==lpNewNode)
					{
						/*
						ԭʼ
								/
							   /
							  /
						*/
						rightRotate(lpNewNode->p->p);
					}else
					{
						/*
							ԭʼ
								/
							   /
							   \
						*/
						leftRotate(lpNewNode->p);
						/*
							ִ�����
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
