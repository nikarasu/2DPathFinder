﻿#include "pch.h"
#include "PathFinder.h"

PathFinder::PathFinder()
{
	myMapHeight = 0;
	myMapWidth = 0;
	myBufferSize = 0;
	myLocalNodeValues = nullptr;
	myGlobalNodeValues = nullptr;
	myParentNodeValues = nullptr;
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

	//TODO: lower amount of allocations, move everything into one single list
	//Consider what happens if the lists are on different caches
	//Vad händer om arrays hamnar på olika cache?

	myLocalNodeValues = new int[myTileAmount];
	std::fill_n(myLocalNodeValues, myTileAmount, myTileAmount);

	myGlobalNodeValues = new int[myTileAmount];
	std::fill_n(myGlobalNodeValues, myTileAmount, myTileAmount);

	myParentNodeValues = new int[myTileAmount];
	std::fill_n(myParentNodeValues, myTileAmount, myTileAmount);

	myTileXPositions = new int[myTileAmount];
	std::fill_n(myTileXPositions, myTileAmount, myTileAmount);

	myTileYPositions = new int[myTileAmount];
	std::fill_n(myTileYPositions, myTileAmount, myTileAmount);

	myNodeCheckList = new int[myTileAmount] {0};

	AddNodeToCheckList(myStartTileIndex);

	signed int pathLength = SearchForShortestPath(pMap, pOutBuffer);

	delete[] myLocalNodeValues;
	delete[] myGlobalNodeValues;
	delete[] myParentNodeValues;
	delete[] myNodeCheckList;
	delete myNodeExistsIncheckList;
	delete[] myTileXPositions;
	delete[] myTileYPositions;

	return pathLength;
}

int PathFinder::SearchForShortestPath(const unsigned char * pMap, int* pOutBuffer)
{
	int currentTileIndex = myStartTileIndex;
	myLocalNodeValues[myStartTileIndex] = 0;
	myGlobalNodeValues[myStartTileIndex] = GetDistance(myStartTileIndex, myTargetTileIndex);

	int rTileIndex;
	int uTileIndex;
	int lTileIndex;
	int dTileIndex;
	int XPos;
	int YPos;
	int currLocNodeValPlusOne;

	while (currentTileIndex != myTargetTileIndex && myCheckListSize > 0)
	{
		if (myTileXPositions[currentTileIndex] == myTileAmount)
		{
			//Slå ihop GetPOisiton uträkningar
			myTileXPositions[currentTileIndex] = GetPosition(currentTileIndex).xPos;
			myTileYPositions[currentTileIndex] = GetPosition(currentTileIndex).yPos;
		}

		//Skippa myTileXPositions och myTileYPositions för att, 1. slippa onödig allokering, samt det är lättare att använda GetPosition(currentTileIndex)
		XPos = myTileXPositions[currentTileIndex];
		YPos = myTileYPositions[currentTileIndex];

		if (myGlobalNodeValues[currentTileIndex] == myTileAmount)
		{
			myGlobalNodeValues[currentTileIndex] = GetDistance(currentTileIndex, myTargetTileIndex);
		}

		currLocNodeValPlusOne = myLocalNodeValues[currentTileIndex] + 1;

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
			currLocNodeValPlusOne < myLocalNodeValues[rTileIndex]
			)
		{
			//Extrahera allt i if statement till egen inline funktion fär att slippa repetition
			myParentNodeValues[rTileIndex] = currentTileIndex;
			myLocalNodeValues[rTileIndex] = currLocNodeValPlusOne;
			myGlobalNodeValues[rTileIndex] = myLocalNodeValues[rTileIndex] + GetDistance(rTileIndex, myTargetTileIndex);
			AddNodeToCheckList(rTileIndex);
		}

		if (
			YPos - 1 >= 0 &&
			pMap[uTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(uTileIndex) &&
			currLocNodeValPlusOne < myLocalNodeValues[uTileIndex]
			)
		{
			myParentNodeValues[uTileIndex] = currentTileIndex;
			myLocalNodeValues[uTileIndex] = currLocNodeValPlusOne;
			myGlobalNodeValues[uTileIndex] = myLocalNodeValues[uTileIndex] + GetDistance(uTileIndex, myTargetTileIndex);
			AddNodeToCheckList(uTileIndex);
		}

		if (
			XPos - 1 >= 0 &&
			pMap[lTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(lTileIndex) &&
			currLocNodeValPlusOne < myLocalNodeValues[lTileIndex]
			)
		{
			myParentNodeValues[lTileIndex] = currentTileIndex;
			myLocalNodeValues[lTileIndex] = currLocNodeValPlusOne;
			myGlobalNodeValues[lTileIndex] = myLocalNodeValues[lTileIndex] + GetDistance(lTileIndex, myTargetTileIndex);
			AddNodeToCheckList(lTileIndex);
		}

		if (
			YPos + 1 < myTileAmount &&
			pMap[dTileIndex] == 1 &&
			!myNodeExistsIncheckList->Test(dTileIndex) &&
			currLocNodeValPlusOne < myLocalNodeValues[dTileIndex]
			)
		{
			myParentNodeValues[dTileIndex] = currentTileIndex;
			myLocalNodeValues[dTileIndex] = currLocNodeValPlusOne;
			myGlobalNodeValues[dTileIndex] = myLocalNodeValues[dTileIndex] + GetDistance(dTileIndex, myTargetTileIndex);
			AddNodeToCheckList(dTileIndex);
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
		indexToSave = myParentNodeValues[indexToSave];
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
	//FATTAR JAG VAD DETTA ÄR ???? myGlobalNodeValues[myNodeCheckList[0]] >= myGlobalNodeValues[myNodeCheckList[myCheckListSize - 1]])
	if (myCheckListSize > 0)
	{
		if (myGlobalNodeValues[myNodeCheckList[0]] >= myGlobalNodeValues[myNodeCheckList[myCheckListSize - 1]])
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
		if (myGlobalNodeValues[myNodeCheckList[index]] < myGlobalNodeValues[myNodeCheckList[smallestIndex]])
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