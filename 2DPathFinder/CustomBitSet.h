#pragma once
#include <bitset>
#include <vector>

class CustomBitSet
{
public:
	CustomBitSet(int aBitAmount)
	{
		int numChunks = aBitAmount / myTypeBitAmount + 1;
		myData.resize(numChunks);
	};

	inline bool Test(int index) const
	{
		const int64_t& chunk = myData[index / myTypeBitAmount];

		const int64_t bit = int64_t(1) << (index % myTypeBitAmount);
		return (chunk & bit) != 0;
	}

	inline void Set(int aIndex, bool aValue)
	{
		int64_t& chunk = myData[aIndex / myTypeBitAmount];
		const int64_t bit = int64_t(1) << (aIndex % myTypeBitAmount);
		if (aValue)
		{
			chunk |= bit;
		}
		else
		{
			chunk &= ~bit;
		}
	}

	~CustomBitSet()
	{
	};

private:
	int myTypeBitAmount = 64;
	std::vector<int64_t> myData;
};
