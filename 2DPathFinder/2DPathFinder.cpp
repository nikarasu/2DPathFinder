#include "pch.h"
#include "PathFinder.h"

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
	PathFinder pf;
	Nick::Vector2 start{ nStartX,  nStartY };
	Nick::Vector2 target{ nTargetX, nTargetY };

	return 	pf.FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
}

int main()
{
	return 0;
}