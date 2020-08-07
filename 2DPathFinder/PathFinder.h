#pragma once
#include "structs.h"
#include "CustomBitSet.h"
#include <iostream>

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	int FindPath(Nick::Vector2 aStart, Nick::Vector2 aTarget, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);

private:
	int SearchForShortestPath(const unsigned char* pMap, int* pOutBuffer);

	int FillBufferAndReturnPathLength(int* pOutBuffer)
	{
		int pathLength = 0;
		int indexToSave = GetIndex(myTargetPosition.xPos, myTargetPosition.yPos);
		int* tempBuffer = new int[myBufferSize];

		while (indexToSave < myTileAmount)
		{
			if (pathLength < myBufferSize)
			{
				tempBuffer[pathLength] = indexToSave;
			}
			indexToSave = myIntList[myParentNodeOffset + indexToSave];
			pathLength++;
		}
		pathLength--;

		//Det behovs inte "speglas" nar man laser pathen
		if (pathLength < myBufferSize && pOutBuffer != nullptr)
		{
			for (int bufferIndex = 0; bufferIndex < pathLength; bufferIndex++)
			{
				pOutBuffer[bufferIndex] = tempBuffer[pathLength - bufferIndex - 1];
			}
		}

		delete[]tempBuffer;

		return pathLength;
	}

	/*
	* Returns true if aNeighbourTileIndex is:
	* 1. a walkable tile
	* 2. not in the checklist
	* 3. the new local value is smaller than the local value currently in the tile
	*/
	bool CheckTileValidity(const unsigned char * pMap, int aNeighbourTileIndex)
	{
		bool isWalkable = pMap[aNeighbourTileIndex] == 1;
		bool isNotInChecklist = !myNodeExistsIncheckList->Test(aNeighbourTileIndex);
		bool isShorterDistanceToStart = myCurrLocNodeValPlusOne < myIntList[myLocalNodeOffset + aNeighbourTileIndex];

#ifdef coutingatstuff
std::cout << "Tile <" << aNeighbourTileIndex << "> isWalkable: " << isWalkable << " - isNotInChecklist: " << isNotInChecklist << " - isShorterDistanceToStart:" << isShorterDistanceToStart << std::endl;
#endif

		bool result = isWalkable && isNotInChecklist && isShorterDistanceToStart;

		return  result;
	}

	void inline UpdateNeighbourTileAndAddToChecklist(int aNeighbourIndex, int aCurrentTileIndex, int aCurrLocNodeValPlusOne)
	{
		myIntList[myParentNodeOffset + aNeighbourIndex] = aCurrentTileIndex;
		myIntList[myLocalNodeOffset + aNeighbourIndex] = aCurrLocNodeValPlusOne;
		myIntList[myGlobalNodeOffset + aNeighbourIndex] = myIntList[myLocalNodeOffset + aNeighbourIndex] + GetDistance(aNeighbourIndex, myTargetTileIndex);
		
#ifdef coutingatstuff
		std::cout << " is updated, ";
#endif
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


	Nick::Vector2 myStartPosition;
	Nick::Vector2 myTargetPosition;
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
	int myCurrLocNodeValPlusOne;
	CustomBitSet* myNodeExistsIncheckList;

	void AddNodeToCheckList(int aNode);

	void UpdateChecklistIfNewNodeIsCloserToTarget();
	

	void RemoveCurrentNodeFromCheckList();
	void SetShortestDistFirstInChecklist();

	int* myNodeCheckList;
	unsigned int myCheckListSize;
};