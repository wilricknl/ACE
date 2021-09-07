/**
 * @file Vec.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Vec.h"

namespace math
{
	Vec3 Vec3::operator+(Vec3 const& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3 Vec3::operator-(Vec3 const& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	/**
	 * @return The distance
	 */
	float Vec3::Distance(Vec3 const& other) const
	{
		return (float)std::sqrt(std::pow(other.x - x, 2) 
			+ std::pow(other.y - y, 2) 
			+ std::pow(other.z - z, 2));
	}

	/**
	 * @param other Another Vec3
	 *
	 * @return The angles stored in a Vec3
	 */
	Vec3 Vec3::Angle(Vec3 const& other) const
	{
		constexpr float conversion{ 180.f / 3.1415926535897922328f };
		Vec3 diff{ other - *this };
		Vec3 angles{
			atan2(diff.y, diff.x) * conversion + 90.f,
			atan2(diff.z, sqrt(diff.x * diff.x + diff.y * diff.y)) * conversion
		};

		return angles;
	}
} // namespace math
