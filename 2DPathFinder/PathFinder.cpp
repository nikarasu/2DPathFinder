#include "pch.h"
#include "PathFinder.h"

PathFinder::PathFinder()
{
	myMapHeight = 0;
	myMapWidth = 0;
	myBufferSize = 0;
	myNodeCheckList = nullptr;
	myNodeExistsIncheckList = nullptr;
	myCheckListSize = 0;
	myCurrentNodeIndex = 0;
	myStartTileIndex = 0;
}

PathFinder::~PathFinder()
{

}

int PathFinder::FindPath(const int nStartX,	const int nStartY, const int nTargetX, const int nTargetY, const unsigned char * pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{

	if (pMap == nullptr)
	{
		return -1;
	}

	if((nStartX == nTargetX) && (nStartY == nTargetY))
	{
		return 0;
	}

	myMapHeight = nMapHeight;
	myMapWidth = nMapWidth;
	myBufferSize = nOutBufferSize;
	myTileAmount = myMapHeight * myMapWidth;

	myStartX = nStartX;
	myStartY = nStartY;
	myStartTileIndex = GetIndex(myStartX, myStartY);
	myTargetX = nTargetX;
	myTargetY = nTargetY;
	myTargetTileIndex = GetIndex(myTargetX, myTargetY);

	myNodeExistsIncheckList = new CustomBitSet(myTileAmount);

	myIntList = new int[myTileAmount * 5];
	std::fill_n(myIntList, myTileAmount * 5, INT_MAX);

	myLocalNodeOffset = 0;
	myGlobalNodeOffset = myTileAmount;
	myParentNodeOffset = myTileAmount * 2;
	myTileXPositionOffset = myTileAmount * 3;
	myTileYPositionOffset = myTileAmount * 4;

	myNodeCheckList = new int[myTileAmount] {0};

	AddNodeToCheckList(myStartTileIndex);

	signed int pathLength = SearchForShortestPath(pMap, pOutBuffer);

	delete[] myNodeCheckList;
	delete myNodeExistsIncheckList;

	return pathLength;
}

int PathFinder::SearchForShortestPath(const unsigned char * pMap, int* pOutBuffer)
{
	int currentTileIndex = myStartTileIndex;
	myIntList[myStartTileIndex + myLocalNodeOffset] = 0;
	myIntList[myStartTileIndex + myGlobalNodeOffset] = GetDistance(myStartTileIndex, myTargetTileIndex);

	int rTileIndex;
	int uTileIndex;
	int lTileIndex;
	int dTileIndex;
	int XPos;
	int YPos;
	int currLocNodeValPlusOne;

	while (currentTileIndex != myTargetTileIndex && myCheckListSize > 0)
	{
		if (myIntList[currentTileIndex + myTileXPositionOffset] == myTileAmount)
		{
			//Slå ihop GetPOisiton uträkningar
			myIntList[currentTileIndex + myTileXPositionOffset] = GetPosition(currentTileIndex).xPos;
			myIntList[currentTileIndex + myTileYPositionOffset] = GetPosition(currentTileIndex).yPos;
		}

		//Skippa myTileXPositions och myTileYPositions för att, 1. slippa onödig allokering, samt det är lättare att använda GetPosition(currentTileIndex)
		XPos = myIntList[currentTileIndex + myTileXPositionOffset];
		YPos = myIntList[currentTileIndex + myTileYPositionOffset];

		if (myIntList[currentTileIndex + myGlobalNodeOffset] == myTileAmount)
		{
			myIntList[currentTileIndex + myGlobalNodeOffset] = GetDistance(currentTileIndex, myTargetTileIndex);
		}

		currLocNodeValPlusOne = myIntList[currentTileIndex + myLocalNodeOffset] + 1;

		rTileIndex = ((XPos + 1) + YPos * myMapWidth);
		uTileIndex = (XPos + (YPos - 1) * myMapWidth);
		lTileIndex = ((XPos - 1) + YPos * myMapWidth);
		dTileIndex = (XPos + (YPos + 1) * myMapWidth);

		//Svårlästa if statements, knepiga uträkningar
		//Istället för att kolla -1 eller +1 i y-led, sub eller add mapwidth 

		if (
			XPos + 1 < myMapWidth &&
			pMap[rTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(rTileIndex) &&
			currLocNodeValPlusOne < myIntList[myLocalNodeOffset + rTileIndex]
			)
		{
			CheckNeigbourTile(rTileIndex, currentTileIndex, currLocNodeValPlusOne);
		}

		if (
			YPos - 1 >= 0 &&
			pMap[uTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(uTileIndex) &&
			currLocNodeValPlusOne < myIntList[myLocalNodeOffset + uTileIndex]
			)
		{
			CheckNeigbourTile(uTileIndex, currentTileIndex, currLocNodeValPlusOne);
		}

		if (
			XPos - 1 >= 0 &&
			pMap[lTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(lTileIndex) &&
			currLocNodeValPlusOne < myIntList[myLocalNodeOffset + lTileIndex]
			)
		{
			CheckNeigbourTile(lTileIndex, currentTileIndex, currLocNodeValPlusOne);
		}

		if (
			YPos + 1 < myTileAmount &&
			pMap[dTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(dTileIndex) &&
			currLocNodeValPlusOne < myIntList[myLocalNodeOffset + dTileIndex]
			)
		{
			CheckNeigbourTile(dTileIndex, currentTileIndex, currLocNodeValPlusOne);
		}

		RemoveCurrentNodeFromCheckList();

		if (myCheckListSize > 0)
		{
			currentTileIndex = myNodeCheckList[0];
		}
	}


	if (currentTileIndex != myTargetTileIndex)
	{
		return -1;
	}

	int pathLength = 0;
	int indexToSave = GetIndex(myTargetX, myTargetY);
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

	//Det behövs inte "speglas" när man läser pathen
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

void PathFinder::AddNodeToCheckList(int aNode)
{
	myNodeCheckList[myCheckListSize++] = aNode;
	myNodeExistsIncheckList->Set(aNode, true);
	
	//Bryta ut ut if statement till bools så man förstår vad allt gör
	//FATTAR JAG VAD DETTA ÄR ???? myIntList[myGlobalNodeOffset + myNodeCheckList[0]] >= myIntList[myGlobalNodeOffset + myNodeCheckList[myCheckListSize - 1]])
	if (myCheckListSize > 0)
	{
		if (myIntList[myGlobalNodeOffset + myNodeCheckList[0]] >= myIntList[myGlobalNodeOffset + myNodeCheckList[myCheckListSize - 1]])
		{
			int tempIndex = myNodeCheckList[0];
			myNodeCheckList[0] = myNodeCheckList[myCheckListSize - 1];
			myNodeCheckList[myCheckListSize - 1] = tempIndex;

			if (myCurrentNodeIndex == 0)
			{
				myCurrentNodeIndex = myCheckListSize - 1;
			}
		}
	}
}

void PathFinder::RemoveCurrentNodeFromCheckList()
{
	myNodeExistsIncheckList->Set(myNodeCheckList[myCurrentNodeIndex], false);
	myNodeCheckList[myCurrentNodeIndex] = myNodeCheckList[myCheckListSize - 1];
	myNodeCheckList[myCheckListSize - 1] = 0;
	myCheckListSize--;

	if (myCurrentNodeIndex != 0)
	{
		myCurrentNodeIndex = 0;
	}
	else
	{
		SetShortestDistFirstInChecklist();
	}
}

void PathFinder::SetShortestDistFirstInChecklist()
{
	int smallestIndex = 0;
	for (unsigned index = myCheckListSize; index--; )
	{
		//TODO: Remove this for loop wit h a mysecondsmallestindex
		if (myIntList[myGlobalNodeOffset + myNodeCheckList[index]] < myIntList[myGlobalNodeOffset + myNodeCheckList[smallestIndex]])
		{
			smallestIndex = index;
		}
	}
	if (smallestIndex != 0)
	{
		int temp = myNodeCheckList[0];
		myNodeCheckList[0] = myNodeCheckList[smallestIndex];
		myNodeCheckList[smallestIndex] = temp;
	}
}