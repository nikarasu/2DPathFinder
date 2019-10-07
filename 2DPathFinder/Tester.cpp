#include "pch.h"
#include "Tester.h"
#include <iostream>
#include <assert.h>
#include <future>
#include <stdlib.h>

#define SHOULD_PRINT true

Tester::Tester()
{
	
}


Tester::~Tester()
{
}

int Tester::Working()
{
	printf("Default working test: 10x10\n");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 50;
	int* pOutBuffer[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 9, 8, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	return result;
}

int Tester::LargeEmptyMap()
{
	printf("Large empty map: 30x30\n");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	PathFinder largeMap;
	const int bufferSize = 20;
	int* pOutBuffer[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 29, 29, pMap10x10AllAccess, 30, 30, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	return result;
}

int Tester::DefaultEmptyMap()
{
	printf("default empty map: 10x10\n");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1
		
	};

	PathFinder largeMap;
	const int bufferSize = 20;
	int* pOutBuffer[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 9, 9, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	return result;
}

int Tester::ZeroBuffer()
{
	printf("Zero buffer test\n");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 0;
	int* pOutBuffer = nullptr;

	int result = largeMap.FindPath(0, 0, 9, 8, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::BordersTooLong()
{
	printf("Borders too long test");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 0;
	int* pOutBuffer = nullptr;

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			std::cout << pMap10x10AllAccess[x + y * 20] << "  ";
		}
		std::cout << std::endl;
	}

	int result = largeMap.FindPath(0, 0, 9, 8, pMap10x10AllAccess, 20, 20, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::RandomPositionThreadedSharedMap()
{
	printf("Threaded 20x20 map (10 threads)");

	unsigned char pMap20x20AllAccess[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0

	};

	PathFinder largeMap;
	int bufferSize = 15;

	srand((unsigned int)time(NULL));

	const int threadAmount = 10;
	Nick::Vector2 randomStart[threadAmount];
	Nick::Vector2 randomTarget[threadAmount];

	for (int index = 0; index < threadAmount; ++index)
	{
		bool foundStart = false;
		while (!foundStart)
		{
			randomStart[index] = { rand() % 20, rand() % 20 };
			if (pMap20x20AllAccess[randomStart[index].xPos + randomStart[index].yPos * 20] == 1)
			{
				foundStart = true;
			}
		}

		bool foundTarget = false;
		while (!foundTarget)
		{
			randomTarget[index] = { rand() % 20, rand() % 20 };
			if (pMap20x20AllAccess[randomTarget[index].xPos + randomTarget[index].yPos * 20] == 1)
			{
				foundTarget = true;
			}
		}
	}

	int* pOutBuffer[threadAmount];
	for (int bufferIndex = 0; bufferIndex < threadAmount; ++bufferIndex)
	{
		int* bufferArray = new int[bufferSize] {0};
		pOutBuffer[bufferIndex] = &bufferArray[0];
	}

	for (int y = 0; y <= 20; y++)
	{
		for (int x = 0; x <= 20; x++)
		{
			if (x != 0)
			{
				if (y == 0)
				{
					if (x < 10)
					{
						std::cout << x << "  ";
					}
					else
					{
						std::cout << x << " ";
					}
				}
				else
				{
					int r = pMap20x20AllAccess[(x - 1) + (y - 1) * 20];
					std::cout << r << "  ";
				}
			}
			else
			{
				if (y < 10)
				{
					std::cout << y << "   ";
				}
				else
				{
					std::cout << y << "  ";
				}
			}
		}
		std::cout << std::endl;
	}

	std::future<int> t1[threadAmount];
	int result[threadAmount];
	for (int i = 0; i < threadAmount; ++i)
	{
		t1[i] = std::async(std::launch::async, &PathFinder::FindPath, &largeMap, randomStart[i].xPos, randomStart[i].yPos, randomTarget[i].xPos, randomTarget[i].yPos, pMap20x20AllAccess, 20, 20, pOutBuffer[i], 12);
	}

	for (int bufferIndex = 0; bufferIndex < threadAmount; ++bufferIndex)
	{
		t1[bufferIndex].wait();
		result[bufferIndex] = t1[bufferIndex].get();
		std::cout << "Start position: " << randomStart[bufferIndex].xPos << ", " << randomStart[bufferIndex].yPos << std::endl;
		std::cout << "Target position: " << randomTarget[bufferIndex].xPos << ", " << randomTarget[bufferIndex].yPos << std::endl;
		std::cout << "Steps: " << result[bufferIndex] << "(" << bufferSize << ")" << std::endl;
		std::cout << "----------------------" << std::endl;

		PrintBuffer(pOutBuffer[bufferIndex], bufferSize);
	}

	return result[0];
}

int Tester::OutBufferNullPtr()
{
	std::cout << std::endl << "OutBuffer is NullPtr test" << std::endl;

	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 50;

	int* pOutBuffer = nullptr;

	int result = largeMap.FindPath(0, 0, 9, 8, pMap10x10AllAccess, 10, 10, nullptr, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::MapNullPtr()
{
	printf("Map nullptr test \n");
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 50;

	int* pOutBuffer[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 9, 8, nullptr, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	return result;
}

int Tester::StrangeCharInArray()
{
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,5,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,1,1,0,1,0,1,
		1,1,0,0,8,1,0,1,0,1,
		1,1,1,1,1,1,0,1,0,1,
		1,1,0,4,0,0,0,0,0,1,
		1,1,1,1,3,1,1,1,1,1,
		0,0,0,0,2,0,1,0,0,0
	};

	PathFinder largeMap;
	const int bufferSize = 50;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 9, 8, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::NoPath()
{
	std::cout << std::endl << "No map path" << std::endl;
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,0,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	int bufferSize = 17;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(3, 4, 6, 9, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::RandomPositionGiganticMap()
{
	std::cout << std::endl << "40x20 map" << std::endl;

	unsigned char pMap40x20AllAccess[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0

	};

	PathFinder largeMap;
	int bufferSize = 30;
	int* pOutBuffer = new int[bufferSize] {0};
	int width = 30;
	int height = 20;

	Nick::Vector2 start;
	Nick::Vector2 target;

	bool foundValidPos = false;

	while (!foundValidPos)
	{
		start.xPos = rand() % width;
		target.xPos = rand() % width;

		start.yPos = rand() % height;
		target.yPos = rand() % height;

		if (pMap40x20AllAccess[start.xPos + start.yPos*width] == 1 && pMap40x20AllAccess[target.xPos + target.yPos*width] == 1)
		{
			foundValidPos = true;
		}
	}

	int result = largeMap.FindPath(start.xPos, start.yPos, target.xPos, target.yPos, pMap40x20AllAccess, width, height, pOutBuffer, bufferSize);

	PrintData(largeMap, pMap40x20AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::StartTargetSamePos()
{
	std::cout << std::endl << "Same start and target position" << std::endl;
	unsigned char pMap10x10AllAccess[] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,1,0,1,0,1,0,1,
		1,1,0,0,0,1,0,1,0,1,
		1,1,0,1,1,1,0,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,0,0,0
	};

	PathFinder largeMap;
	int bufferSize = 17;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(6, 9, 6, 9, pMap10x10AllAccess, 10, 10, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap10x10AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::ThinMapWorking()
{
	std::cout << std::endl << "Thin map path" << std::endl;

	unsigned char pMap30x4AllAccess[] =
	{
		1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,
		1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1
	};

	PathFinder largeMap;
	int bufferSize = 42;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 23, 1, pMap30x4AllAccess, 30, 4, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap30x4AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::NarrowMapWorking()
{
	unsigned char pMap5x24AllAccess[] =
	{
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,0,0,0,
		1,1,0,1,1,
		1,1,0,0,1,
		1,1,1,1,1,
		1,1,0,0,0,
		1,1,1,1,1,
		1,1,0,0,0,
		1,1,1,1,1,
		1,1,0,0,0,
		1,1,1,1,1,
		0,0,1,1,0,
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1,
		0,0,1,0,1,
		1,1,1,0,1,
		0,0,0,0,1,
		1,1,1,1,1,
		0,0,0,1,1,
		1,1,1,1,1
	};

	PathFinder largeMap;
	std::cout << "Narrow map path" << std::endl;
	int bufferSize = 31;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 0, 23, pMap5x24AllAccess, 5, 24, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap5x24AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

int Tester::SmallMapWorking()
{
	unsigned char pMap5x24AllAccess[] =
	{
		1,1,
		0,1
	};

	PathFinder largeMap;
	std::cout << "Small map path" << std::endl;
	int bufferSize = 4;
	int* pOutBuffer = new int[bufferSize] {0};

	int result = largeMap.FindPath(0, 0, 1, 1, pMap5x24AllAccess, 2, 2, pOutBuffer, bufferSize);
	PrintData(largeMap, pMap5x24AllAccess);

	PrintBuffer(pOutBuffer, bufferSize);

	delete pOutBuffer;
	return result;
}

void Tester::PrintData(PathFinder& aPF, unsigned char* pMap)
{
	/*
	if (SHOULD_PRINT)
	{
		Nick::Vector2 mapSize{ aPF.GetMapWidth(), aPF.GetMapHeight() };
		Nick::Vector2 startPos = aPF.GetStartPos();
		Nick::Vector2 targetPos = aPF.GetTargetPos();

		std::cout << "MapWidth is larger or equal to 1:" << ((1 <= mapSize.xPos) ? "True " : "False ") << std::endl;
		std::cout << "MapHeight is larger or equal to 1:" << ((1 <= mapSize.yPos) ? "True " : "False ") << std::endl;
		std::cout << "Start position X is between 0 and map Width:" << ((0 <= startPos.xPos <= mapSize.xPos) ? "True " : "False ") << std::endl;
		std::cout << "Start position Y is between 0 and map Height:" << ((0 <= startPos.yPos <= mapSize.yPos) ? "True " : "False ") << std::endl;
		std::cout << "Target position X is between 0 and map Width:" << ((0 <= targetPos.xPos <= mapSize.xPos) ? "True " : "False ") << std::endl;
		std::cout << "Target position Y is between 0 and map Height:" << ((0 <= targetPos.yPos <= mapSize.yPos) ? "True " : "False ") << std::endl;
		std::cout << "nOutBufferSize is larger or equal to 0: " << ((aPF.GetBufferSize() >= 0) ? "True " : "False ") << std::endl;

		if (pMap != nullptr)
		{
			std::cout << "Start position is in an empty location: " << startPos.xPos << ", " << startPos.yPos << " -- " << ((pMap[startPos.xPos + mapSize.xPos * startPos.yPos] == 1) ? "True " : "False ") << std::endl;
			std::cout << "Target position is in an empty location: " << targetPos.xPos << ", " << targetPos.yPos << " -- " << ((pMap[targetPos.xPos + mapSize.xPos * targetPos.yPos] == 1) ? "True " : "False ") << std::endl;

			bool arrayIsClean = true;

			for (int index = 0; index < (mapSize.xPos * mapSize.yPos); ++index)
			{
				if (!(pMap[index] == 1 || pMap[index] == 0))
				{
					std::cout << "Found strange char at index " << index << ": " << (int)pMap[index] << std::endl;
					arrayIsClean = false;
				}
			}

			std::cout << "pMap is clean: " << (arrayIsClean ? "True " : "False ") << std::endl;
		}

		std::cout << "Start Pos:" << startPos.xPos << ", " << startPos.yPos << std::endl;
		std::cout << "Target Pos:" << targetPos.xPos << ", " << targetPos.yPos << std::endl;

		std::cout << "---pMap--" << std::endl;
		for (int y = 0; y < mapSize.yPos; ++y)
		{
			for (int x = 0; x < mapSize.xPos; ++x)
			{
				if (x == startPos.xPos && y == startPos.yPos)
				{
					std::cout << "S  ";
				}
				else if (x == targetPos.xPos && y == targetPos.yPos)
				{
					std::cout << "T  ";
				}
				else
				{
					std::cout << pMap[x + y * mapSize.xPos] << "  ";
				}
			}
			std::cout << std::endl;
		}

		std::cout << std::endl << "---DistanceMap--" << std::endl;
		for (int y = 0; y < mapSize.yPos; ++y)
		{
			for (int x = 0; x < mapSize.xPos; ++x)
			{
				int index = x + y * mapSize.xPos;
				if ((startPos.xPos + startPos.yPos * mapSize.xPos) == index)
				{
					std::cout << "S   ";
				}
				else if (targetPos.xPos == x && targetPos.yPos == y)
				{
					std::cout << "T   ";
				}
				else
				{
					if (aPF.GetDistMap()[index] < 10)
					{
						if (aPF.GetDistMap()[index] == 0)
						{
							std::cout << "W   ";
						}
						else
						{
							std::cout << aPF.GetDistMap()[index] << "   ";
						}
					}
					else if (aPF.GetDistMap()[index] < 100)
					{
						std::cout << aPF.GetDistMap()[index] << "  ";
					}
					else
					{
						std::cout << aPF.GetDistMap()[index] << " ";
					}
				}
			}
			std::cout << std::endl;
		}

		std::cout << std::endl << "---visited Map--" << std::endl;
		for (int y = 0; y < mapSize.yPos; ++y)
		{
			for (int x = 0; x < mapSize.xPos; ++x)
			{
				if (aPF.GetVisitedTiles()[x + y * mapSize.xPos])
				{
					std::cout << "." << " ";
				}
				else
				{
					std::cout << "X" << " ";
				}
			}
			std::cout << std::endl;
		}
	}
	*/
}

void Tester::PrintBuffer(const int* aBuffer, int aBuffersize)
{
	if (aBuffer != nullptr)
	{
		std::cout << "{ ";
		for (int index = 0; index < aBuffersize; ++index)
		{
			std::cout << aBuffer[index] << " ";
		}
		std::cout << "}" << std::endl;
	}
}

void Tester::SampleTests()
{
	PathFinder pf;

	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[12]{ 0 };
	int bufferSize = 12;
	assert(pf.FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, bufferSize) == 3);
	printf("\nPRINTING SAMPLE MAP 1\n");
	PrintData(pf, pMap);

	printf("1. Should be 1: %d\n", pOutBuffer[0]);
	printf("2. Should be 5: %d\n", pOutBuffer[1]);
	printf("3. Should be 9: %d\n", pOutBuffer[2]);
	assert(pOutBuffer[0] == 1);
	assert(pOutBuffer[1] == 5);
	assert(pOutBuffer[2] == 9);

	PrintBuffer(pOutBuffer, bufferSize);

	PathFinder pf2;
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	const int bufferSize2 = 7;
	int pOutBuffer2[bufferSize2]{ 0 };
	int result = pf2.FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, bufferSize2);
	printf("\nPRINTING SAMPLE MAP 2\n");
	PrintData(pf2, pMap2);
	assert(result == -1);
	PrintBuffer(pOutBuffer2, bufferSize2);

}

int Tester::RunWorkingTests()
{
	SampleTests();

	int result = 0;


	result = StartTargetSamePos();
	printf("Test 3: %i - Should be 0 \n", result);
	assert(result == 0);

	result = ThinMapWorking();
	printf("Test 4: %i - Should be 42 \n", result);
	assert(result == 42);

	result = NarrowMapWorking();
	printf("Test 5: %i - Should be 31 \n", result);
	assert(result == 31);

	result = SmallMapWorking();
	printf("Test 6: %i - Should be 2 \n", result);
	assert(result == 2);

	//printf("Test 7: %i - Cannot assert random positions\n", RandomPositionGiganticMap());

	return result;
}

int Tester::RunBrokenTests()
{
	//printf("BROKEN TESTS ------\n");
	//printf("Running test Zero Buffer----------------\n");
	//printf("Test 1: %i\n", ZeroBuffer());
	//printf("Running test StrangeCharInArray----------------\n");
	//printf("Test 2: %i\n", StrangeCharInArray());
	//printf("Running test OutBufferNullPtr----------------\n");
	//printf("Test 3: %i\n", OutBufferNullPtr());
	//printf("Running test mapNullPtr----------------\n");
	//printf("Test 3: %i\n", MapNullPtr());
	

	return DefaultEmptyMap();
}

int Tester::RunThreadedTests()
{
	return RandomPositionThreadedSharedMap();
}

