﻿#pragma once
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

	void inline CheckNeigbourTile(int aNeighbourIndex, int aCurrentTileIndex, int aCurrLocNodeValPlusOne)
	{
		myIntList[myParentNodeOffset + aNeighbourIndex] = aCurrentTileIndex;
		myIntList[myLocalNodeOffset + aNeighbourIndex] = aCurrLocNodeValPlusOne;
		myIntList[myGlobalNodeOffset + aNeighbourIndex] = myIntList[myLocalNodeOffset + aNeighbourIndex] + GetDistance(aNeighbourIndex, myTargetTileIndex);
		AddNodeToCheckList(aNeighbourIndex);
	}

	inline const int GetIndex(const int aXPos, const int aYPos) const
	{
		return (aXPos % myMapWidth + aYPos * myMapWidth);
	}

	const Nick::Vector2 GetPosition(const int aIndex) const
	{
		return { aIndex % myMapWidth, aIndex / myMapWidth };
	}

	const int GetDistance(const int aIndexA, const int aIndexB) const
	//First const makes the return variable const
	//aIndexA is set to const, so it can't be changed inside the function, same for aIndexB
	//Last const makes it so you cannot change the member variables of the pathfinder object that runs the function
	//You may not Man får inte heller kalla på icke constade medlemsfunktioner
	{
		const Nick::Vector2 aPos = GetPosition(aIndexA);
		const Nick::Vector2 bPos = GetPosition(aIndexB);
		const int a = aPos.xPos - bPos.xPos;
		const int b = aPos.yPos - bPos.yPos;
		return a * a + b * b;
	}

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

	int* myIntList;
	int myLocalNodeOffset;
	int myGlobalNodeOffset;
	int myParentNodeOffset;
	int myTileXPositionOffset;
	int myTileYPositionOffset;
	CustomBitSet* myNodeExistsIncheckList;

	void AddNodeToCheckList(int aNode);
	void RemoveCurrentNodeFromCheckList();
	void SetShortestDistFirstInChecklist();

	int* myNodeCheckList;
	unsigned int myCheckListSize;
};