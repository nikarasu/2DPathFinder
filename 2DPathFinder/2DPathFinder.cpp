#include "pch.h"
#include "PathFinder.h"
#include <iostream>

int FindPath(
	const int nStartX,
	const int nStartY,
	const int nTargetX,
	const int nTargetY,
	const unsigned char* pMap,
	const int nMapWidth,
	const int nMapHeight,
	int* pOutBuffer,
	const int nOutBufferSize
)
{
	//Undvik classes f?r tr?ds?kerhetens skull
	PathFinder pf;
	return 	pf.FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
}

class B
{
public:
	virtual ~B();
	int getA() const { return a; }

private:
	int a;
};

int main()
{


	std::cout << sizeof(B) << std::endl;
	return 0;
}
