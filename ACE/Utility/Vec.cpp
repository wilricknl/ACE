/**
 * @file Vec.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Vec.h"

namespace math
{
	/**
	 * @return The distance
	 */
	float Vec3::Distance(Vec3 const& other) const
	{
		return (float)std::sqrt(std::pow(other.x - x, 2) 
			+ std::pow(other.y - y, 2) 
			+ std::pow(other.z - z, 2));
	}
} // namespace math
