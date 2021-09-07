/**
 * @file Math.h
 * @brief Math helper functions
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace math
{
	/** @brief Check if two floats are nearly equal
	 */
	bool IsNearlyEqual(float a, float b, float tolerance = 0.00001f);

	/** @brief Check if a float is nearly zero
	 */
	bool IsNearlyZero(float a, float tolerance = 0.00001f);
} // namespace math
