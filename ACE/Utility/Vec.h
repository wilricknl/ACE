/**
 * @file Vec.h
 * @brief Custom vector classes.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace math
{
	/** Vec3 is a 3 dimensional vector class
	 */
	class Vec3
	{
	public:
		Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: x(x), y(y), z(z)
		{}

		Vec3& operator+=(Vec3 const& rhs);
		Vec3 operator+(Vec3 const& rhs) const;
		Vec3& operator-=(Vec3 const& rhs);
		Vec3 operator-(Vec3 const& rhs) const;

		/** @brief Calculate the distance between this and @p other
		 */
		float Distance(Vec3 const& other) const;
		/** @brief Calculate the distance squared between this and @p other
		 */
		double DistanceSquared(Vec3 const& other) const;
		/** @brief Calculate pitch and yaw to @p other
		 */
		Vec3 Angle(Vec3 const& other) const;

		float x, y, z;
	};
} // namespace math
