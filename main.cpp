#include "AVL.h"
#include "Matrix.h"
bool printNode(CAVL<int>::LPNODE lpNode)
{
	cout<<lpNode->element;
	return 1;
}
int main()
{
	CAVL<int> a;
	a.Insert(2);
	a.Insert(1);
	a.Insert(3);
	a.Insert(0);
	a.Insert(0);
	a.DeleteNode(a.search(0));
	a.InOrderTravel(printNode);
	getchar();
	return 0;
}
