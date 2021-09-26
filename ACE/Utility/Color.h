#pragma once

namespace draw
{
	/**
	 * @brief Color can be used to easily pass RGBA values
	 */
	struct Color
	{
		Color(float r, float g, float b, float a = 1.0f)
			: r(r), g(g), b(b), a(a)
		{}

		Color SetR(float r) const;
		Color SetG(float g) const;
		Color SetB(float b) const;
		Color SetA(float a) const;

		const float r; ///< Red
		const float g; ///< Green
		const float b; ///< Blue
		const float a; ///< Alpha
	};

	/** @brief Predefined colors
	 */
	namespace colors
	{
		const Color white{ 1.f, 1.f, 1.f, 1.f }; ///< White
		const Color red{ 1.f, 0.f, 0.f, 1.f }; ///< Red
		const Color yellow{ 1.f, 1.f, 0.f, 1.f }; ///< Yellow
		const Color green{ 0.f, 1.f, 0.f, 1.f }; ///< Green
		const Color cyan{ 0.f, 1.f, 1.f, 1.f }; ///< Cyan
		const Color blue{ 0.f, 0.f, 1.f, 1.f }; ///< Blue
		const Color magenta{ 1.f, 0.f, 1.f, 1.f }; ///< Magenta
		const Color black{ 0.f, 0.f, 0.f, 1.f }; ///< Black
		const Color friendly{ 1.f, 0.2f, 0.2f, 1.f }; ///< Friendly
		const Color enemy{ 0.2f, 1.f, 0.2f, 1.f }; ///< Enemy
	} // namespace colors
} // namespace draw