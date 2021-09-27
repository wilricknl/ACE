/**
 * @file Math.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Math.h"

namespace math
{
	/**
	 * @return `true` if is nearly equal, else `false`
	 */
	bool IsNearlyEqual(float a, float b, float tolerance)
	{
		return std::abs(a - b) <= tolerance;
	}

	/**
	 * @return `true` if is nearly 0, else `false`
	 */
	bool IsNearlyZero(float a, float tolerance)
	{
		return std::abs(a) <= tolerance;
	}

	/**
	 * @return Degrees
	 */
	float RadiansToDegrees(float radians)
	{
		constexpr float conversion{ 180.f / 3.1415926535897922328f };
		return radians * conversion;
	}

	/**
	 * @return Radians
	 */
	float DegreesToRadians(float degrees)
	{
		constexpr float conversion{ 3.1415926535897922328f / 180.f };
		return degrees * conversion;
	}
} // namespace math