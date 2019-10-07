#pragma once
#include "PathFinder.h"


class Tester
{
public:
	Tester();
	~Tester();

	int RunWorkingTests();
	int RunBrokenTests();
	int RunThreadedTests();

private:
	int Working();
	int LargeEmptyMap();
	int DefaultEmptyMap();
	int NoPath();
	int RandomPositionGiganticMap();
	int StartTargetSamePos();
	int ThinMapWorking();
	int NarrowMapWorking();
	int SmallMapWorking();
	int BordersTooLong();
	int RandomPositionThreadedSharedMap();
	int OutBufferNullPtr();
	int MapNullPtr();
	void PrintData(PathFinder& aPF, unsigned char* pMap);

	void PrintBuffer(const int* aBuffer, int aBuffersize);


	void SampleTests();

	int ZeroBuffer();
	int StrangeCharInArray();
};

