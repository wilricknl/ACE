/**
 * @file Vec.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Math.h"
#include "Vec.h"

namespace math
{
	Vec3& Vec3::operator+=(Vec3 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3 Vec3::operator+(Vec3 const& rhs) const
	{
		return Vec3(*this) += rhs;
	}

	Vec3& Vec3::operator-=(Vec3 const& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3 Vec3::operator-(Vec3 const& rhs) const
	{
		return Vec3(*this) -= rhs;
	}

	/**
	 * @param other The end point of the distance
	 *
	 * @return The distance
	 */
	float Vec3::Distance(Vec3 const& other) const
	{
		return (float)std::sqrt(std::pow(other.x - x, 2) 
			+ std::pow(other.y - y, 2) 
			+ std::pow(other.z - z, 2));
	}

	/**
	 * @param other The end point of the distance
	 *
	 * @return The squared distance
	 */
	double Vec3::DistanceSquared(Vec3 const& other) const
	{
		return std::pow(other.x - x, 2)
			+ std::pow(other.y - y, 2)
			+ std::pow(other.z - z, 2);
	}

	/**
	 * @param other Another Vec3
	 *
	 * @return The angles stored in a Vec3
	 */
	Vec3 Vec3::Angle(Vec3 const& other) const
	{
		Vec3 diff{ other - *this };
		return Vec3{
			RadiansToDegrees(atan2(diff.y, diff.x)) + 90.f,
			RadiansToDegrees(atan2(diff.z, sqrt(diff.x * diff.x + diff.y * diff.y)))
		};
	}
} // namespace math
