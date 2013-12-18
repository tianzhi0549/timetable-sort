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
	a.Insert(4);
	a.Insert(5);
	a.InOrderTravel(printNode);
	getchar();
	return 0;
}
