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
	return 	pf.FindPath({ nStartX, nStartY }, { nTargetX, nTargetY }, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
}


int main()
{
	unsigned char pMap30x4AllAccess[] =
	{
		1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,
		1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1
	};

	const int bufferSize = 42;
	int pOutBuffer[bufferSize];

	int result = FindPath(0, 0, 23, 1, pMap30x4AllAccess, 30, 4, pOutBuffer, bufferSize);
	
	std::cout << "Result: " << result << std::endl;
	if (result == bufferSize)
	{
		std::cout << "Found path" << std::endl;
	}
	else
	{
		std::cout << "No path" << std::endl;
	}
	system("pause");
}
