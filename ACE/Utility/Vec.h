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

		/** @brief Calculate the distance between this and @p other
		 */
		float Distance(Vec3 const& other) const;

		float x, y, z;
	};
} // namespace math
