#pragma once

namespace Nick
{
	struct Vector2
	{
		int xPos;
		int yPos;
	};

	struct Node
	{
		//Konstruktor och destruktor kan vara dyra SE CLASS
		~Node() 
		{
			delete[] myNeighbors;
		}
		Node* myParent;
		int myIndex;
		int myXPos;
		int myYPos;
		int myDistToTarget;
		int myDistToStart;
		Node* myNeighbors;
	};
}