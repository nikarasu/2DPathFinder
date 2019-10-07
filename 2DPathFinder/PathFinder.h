#pragma once
#include "structs.h"
#include "CustomBitSet.h"

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	int FindPath(const int nStartX,	const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);

private:
	int SearchForShortestPath(const unsigned char* pMap, int* pOutBuffer);

	int GetIndex(int aXPos, int aYPos);
	Nick::Vector2 GetPosition(int aIndex);
	int GetDistance(int aIndexA, int aIndexB);

	bool myFoundTarget;
	int myStartX;
	int myStartY;
	int myTargetX;
	int myTargetY;
	int myStartTileIndex;
	int myTargetTileIndex;

	int myMapHeight;
	int myMapWidth;
	int myBufferSize;
	int myTileAmount;
	int myCurrentNodeIndex;

	int* myLocalNodeValues;
	int* myGlobalNodeValues;
	int* myParentNodeValues;
	int* myTileXPositions;
	int* myTileYPositions;
	CustomBitSet* myNodeExistsIncheckList;

	void AddNodeToCheckList(int aNode);
	void RemoveCurrentNodeFromCheckList();
	void SetShortestDistFirstInChecklist();

	int* myNodeCheckList;
	unsigned int myCheckListSize;
};