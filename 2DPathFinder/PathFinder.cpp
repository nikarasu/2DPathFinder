#include "pch.h"
#include "PathFinder.h"

//#define coutingatstuff

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

	myParentNodeOffset = 0;
	myLocalNodeOffset = 0;
	myGlobalNodeOffset = 0;

	myTargetPosition = { 0,0 };
	myStartPosition = { 0,0 };
	myCurrLocNodeValPlusOne = 0;
	myTileXPositionOffset = 0;
	myTileYPositionOffset = 0;
}

PathFinder::~PathFinder()
{

}

int PathFinder::FindPath(Nick::Vector2 aStart, Nick::Vector2 aTarget, const unsigned char * pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
	if (pMap == nullptr)
	{
		return -1;
	}

	if(aStart == aTarget)
	{
		return 0;
	}

	myMapHeight = nMapHeight;
	myMapWidth = nMapWidth;
	myBufferSize = nOutBufferSize;
	myTileAmount = myMapHeight * myMapWidth;

	myStartPosition = aStart;
	myStartTileIndex = GetIndex(aStart.xPos, aStart.yPos);

	myTargetPosition = aTarget;
	myTargetTileIndex = GetIndex(aTarget.xPos, aTarget.yPos);

	myNodeExistsIncheckList = new CustomBitSet(myTileAmount);

	myIntList = new int[myTileAmount * 5];
	std::fill_n(myIntList, myTileAmount * 5, INT_MAX);

	myLocalNodeOffset = 0;
	myGlobalNodeOffset = myTileAmount;
	myParentNodeOffset = myTileAmount * 2;
	myTileXPositionOffset = myTileAmount * 3;
	myTileYPositionOffset = myTileAmount * 4;

	for (int index = 0; index < myTileAmount; ++index)
	{
		myIntList[myTileXPositionOffset + index] = index % myMapWidth;
		myIntList[myTileYPositionOffset + index] = index / myMapWidth;
	}

	myNodeCheckList = new int[myTileAmount] {0};

	AddNodeToCheckList(myStartTileIndex);

#ifdef coutingatstuff	
	std::cout << "Start  position: " << myStartPosition.xPos << ", " << myStartPosition.yPos << " - Index: " << myStartTileIndex << std::endl;
	std::cout << "Target position: " << myTargetPosition.xPos << ", " << myTargetPosition.yPos << " - Index: " << myTargetTileIndex << std::endl << "--------------" << std::endl;
#endif

	signed int pathLength = SearchForShortestPath(pMap, pOutBuffer);

	delete[] myNodeCheckList;
	delete[] myIntList;
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

#ifdef coutingatstuff
	std::cout << "Starting pathfinding... \n" << std::endl;
#endif

	while (currentTileIndex != myTargetTileIndex && myCheckListSize > 0)
	{

#ifdef coutingatstuff
		std::cout << "Current tile <" << currentTileIndex << "> - Position: " << GetPosition(currentTileIndex).xPos << ", " << GetPosition(currentTileIndex).yPos << std::endl;
#endif

		int check1 = myIntList[currentTileIndex + myTileXPositionOffset];
		int check2 = myIntList[currentTileIndex + myTileYPositionOffset];

		if (check1 == myTileAmount || check2 == myTileAmount)
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

		myCurrLocNodeValPlusOne = myIntList[currentTileIndex + myLocalNodeOffset] + 1;

		rTileIndex = ((XPos + 1) + YPos * myMapWidth);
		uTileIndex = (XPos + (YPos - 1) * myMapWidth);
		lTileIndex = ((XPos - 1) + YPos * myMapWidth);
		dTileIndex = (XPos + (YPos + 1) * myMapWidth);

		//Svårlästa if statements, knepiga uträkningar
		//Istället för att kolla -1 eller +1 i y-led, sub eller add mapwidth 

		if (XPos + 1 < myMapWidth && CheckTileValidity(pMap, rTileIndex))
		{

#ifdef coutingatstuff
			std::cout << "Right neighbour <" << rTileIndex << "> ";
#endif
			UpdateNeighbourTileAndAddToChecklist(rTileIndex, currentTileIndex, myCurrLocNodeValPlusOne);
		}

		if (YPos - 1 >= 0 && CheckTileValidity(pMap, uTileIndex))
		{

#ifdef coutingatstuff
			std::cout << "Up neighbour <" << uTileIndex << "> ";
#endif
			UpdateNeighbourTileAndAddToChecklist(uTileIndex, currentTileIndex, myCurrLocNodeValPlusOne);
		}

		if (XPos - 1 >= 0 &&CheckTileValidity(pMap, lTileIndex))
		{

#ifdef coutingatstuff
			std::cout << "Left neighbour <" << lTileIndex << "> ";
#endif
			UpdateNeighbourTileAndAddToChecklist(lTileIndex, currentTileIndex, myCurrLocNodeValPlusOne);
		}

		if (YPos + 1 < myMapHeight && CheckTileValidity(pMap, dTileIndex))
		{

#ifdef coutingatstuff
			std::cout << "Down neighbour <" << dTileIndex << "> ";
#endif

			UpdateNeighbourTileAndAddToChecklist(dTileIndex, currentTileIndex, myCurrLocNodeValPlusOne);
		}
		
#ifdef coutingatstuff
		std::cout << "Tiles in checklist (size " << myCheckListSize << "): ";

		for (int i = 0; i < myCheckListSize; ++i)
		{
			std::cout << myNodeCheckList[i] << "  ";
		}

		std::cout << "" << std::endl;
#endif

		RemoveCurrentNodeFromCheckList();


#ifdef coutingatstuff
		std::cout << "Checklist size: " << myCheckListSize << std::endl;
#endif

		if (myCheckListSize > 0)
		{

#ifdef coutingatstuff
			std::cout << "Updating current tile from <" << currentTileIndex << "> ";
#endif
			currentTileIndex = myNodeCheckList[0];

			
#ifdef coutingatstuff
			std::cout << " to <" << currentTileIndex << "> " << std::endl;
#endif
		}

		
#ifdef coutingatstuff
		std::cout << "-------------------------------\n" << std::endl;
#endif
	}


	if (currentTileIndex != myTargetTileIndex)
	{
		return -1;
	}

	return FillBufferAndReturnPathLength(pOutBuffer);
}

void PathFinder::AddNodeToCheckList(int aNode)
{
	myNodeCheckList[myCheckListSize++] = aNode;
	myNodeExistsIncheckList->Set(aNode, true);
	
#ifdef coutingatstuff
std::cout << " added to checklist ";
#endif

	UpdateChecklistIfNewNodeIsCloserToTarget();
}

void PathFinder::UpdateChecklistIfNewNodeIsCloserToTarget()
{
	//Bryta ut if statement till bools sa man forstar vad allt gor
	//https://stackoverflow.com/questions/15843525/how-do-you-insert-the-value-in-a-sorted-vector/25524075#25524075
	int firstNodeDistanceToTarget = myIntList[myGlobalNodeOffset + myNodeCheckList[0]];
	int recentlyAddedNodeDistanceToTarget = myIntList[myGlobalNodeOffset + myNodeCheckList[myCheckListSize - 1]];

	//TODO: Do I really need to check is size is > 0 ? Redundant?
	if (myCheckListSize > 0 && firstNodeDistanceToTarget >= recentlyAddedNodeDistanceToTarget)
	{
		int tempIndex = myNodeCheckList[0];
		myNodeCheckList[0] = myNodeCheckList[myCheckListSize - 1];
		myNodeCheckList[myCheckListSize - 1] = tempIndex;

		if (myCurrentNodeIndex == 0)
		{
			myCurrentNodeIndex = myCheckListSize - 1;
		}
	
#ifdef coutingatstuff
std::cout << "and ";
	}

	else
	{
		std::cout << "but not ";
#endif
	}

	#ifdef coutingatstuff
std::cout << "closer to target <" << myTargetTileIndex << "> " << std::endl;
#endif
}

void PathFinder::RemoveCurrentNodeFromCheckList()
{

#ifdef coutingatstuff
	std::cout << "Remove node <" << myCurrentNodeIndex << "> from checklist" << std::endl;
#endif

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
	//TODO: Remove this for loop wit h a mysecondsmallestindex
	//Maybe a BST would sort this out?

	int smallestIndex = 0;
	for (unsigned index = myCheckListSize; index--; )
	{
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
