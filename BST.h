#include <iostream>
using namespace std;

template <class T>
class CBST
{
public:
	typedef struct _Node
	{
		_Node(const T& element,_Node* l,_Node* r,_Node* p)
		{
			this->element=element;
			this->r=r;
			this->l=l;
			this->p=p;
		}
		_Node* p;
		_Node* l;
		_Node* r;
		T element;
	}Node,*LPNODE;
	int GetHeight()
	{
		return GetHeightR(pRoot);
	}
protected:
	LPNODE pRoot;
	int GetHeightR(LPNODE root)
	{
		if(root==NULL) return 0;
		int lHeight=GetHeightR(root->l);
		int rHeight=GetHeightR(root->r);
		return (rHeight>lHeight?rHeight:lHeight)+1;
	}
	LPNODE GetSuccessor(LPNODE lpNode)
	{
		if(lpNode->r==NULL) return NULL;
		LPNODE p=NULL;
		for(p=lpNode->r;p->l!=NULL;p=p->l);
		return p;
	}
	void DestroyTreeR(LPNODE pRoot)
	{
		if(pRoot!=NULL)
		{
			DestroyTreeR(pRoot->r);
			DestroyTreeR(pRoot->l);
			delete pRoot;
		}
	}
	void InOrderTravelR(LPNODE pRoot,bool(*pf)(LPNODE lpNode))
	{
		if(pRoot==NULL) return;
		InOrderTravelR(pRoot->l,pf);
		if(!pf(pRoot)) return;
		InOrderTravelR(pRoot->r,pf);
	}
public:
	CBST():pRoot(NULL)
	{

	}
	LPNODE search(const T& element)
	{
		LPNODE p=pRoot;
		while(p!=NULL)
		{
			if(element>(p->element))
			{
				p=p->r;
			}else if(element<(p->element))
			{
				p=p->l;
			}else
			{
				return p;
			}
		}
		return p;
	}
	void Remove(const T& element)
	{
		DeleteNode(search(element));
	}
	void InOrderTravel(bool(*pf)(LPNODE lpNode))
	{
		InOrderTravelR(pRoot,pf);
	}
	bool Insert(const T& element,LPNODE* ppNode)
	{
		LPNODE lpNewNode=new Node(element,0,0,0);
		*ppNode=lpNewNode;
		if(!lpNewNode) return false;
		if(!pRoot)
		{
			pRoot=lpNewNode;
			return true; 
		}
		LPNODE p=pRoot;
		while(1)
		{
			if(element<(p->element))
			{
				if(p->l)
				{
					p=p->l;
				}else
				{
					p->l=lpNewNode;
					lpNewNode->p=p;
					break;
				}
			}else
			{
				if(p->r)
				{
					p=p->r;
				}else
				{
					p->r=lpNewNode;
					lpNewNode->p=p;
					break;
				}
			}
		}
		return true;
	}
	void DestroyTree()
	{
		DestroyTreeR(pRoot);
		pRoot=NULL;
	}
	void DeleteNode(LPNODE lpNode)
	{
		if(!lpNode) return;
		if(!(lpNode->r&&lpNode->l))//如果有一颗子树不存在
		{
			if(lpNode->p)//如果不是根节点
			{
				if(lpNode->p->r==lpNode)
				{
					lpNode->p->r=(LPNODE)(((int)lpNode->r)|((int)lpNode->l));
				}else
				{
					lpNode->p->l=(LPNODE)(((int)lpNode->r)|((int)lpNode->l));
				}
				delete lpNode;
			}else
			{
				pRoot=(LPNODE)(((int)lpNode->r)|((int)lpNode->l));
				delete lpNode;
			}
		}else//都存在
		{
			LPNODE lpSuc=GetSuccessor(lpNode);
			lpNode->element=lpSuc->element;
			DeleteNode(lpSuc);
		}
	}
	virtual ~CBST()
	{
		DestroyTree();
	}
};
