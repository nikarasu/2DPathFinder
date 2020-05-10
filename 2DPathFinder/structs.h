#pragma once

namespace Nick
{
	struct Vector2
	{
		inline Vector2& operator=(const Vector2& aVec)
		{
			this->xPos = aVec.xPos;
			this->yPos = aVec.yPos;
			return *this;
		}

		int xPos;
		int yPos;
	};

	const bool operator==(const Vector2& aVec0, const Vector2& aVec1)
	{
		return(aVec0.xPos == aVec1.xPos && aVec0.yPos == aVec1.yPos);
	}
}