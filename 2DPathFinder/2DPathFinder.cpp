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
	//Avoid classes for thread safety
	PathFinder pf;
	return 	pf.FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
}


int main()
{
	return 0;
}
