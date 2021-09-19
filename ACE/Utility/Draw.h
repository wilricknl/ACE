#pragma once
#include <string>
#include "Vec.h"

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

		const float r; ///< Red
		const float g; ///< Green
		const float b; ///< Blue
		const float a; ///< Alpha
	};

	/**
	 * @brief Draw provides OpenGL drawing operations
	 */
	class Draw
	{
	public:
		Draw() = default;
		virtual ~Draw() = default;

		/** @brief Setup OpenGL for 2D drawing
		 */
		void Setup2D();
		/** @brief Restore OpenGL after 2D drawing 
		 */
		void Restore2D();
		/** @brief Draw a 2D line
		 */
		void Line2D(float x1, float y1, float x2, float y2, float width, Color const& color);
		/** @brief Draw a 2D rectangle
		 */
		void Rectangle2D(float x, float y, float width, float height, Color const& color);
		/** @brief Draw a 2D outline
		 */
		void RectangleOutline2D(float x, float y, float width, float height, float lineWidth, float lineOffset, Color const& color);
		/** @brief Draw a 2D bar
		 */
		void Bar2D(float x, float y, float width, float height, float value, float maximum, Color const& foreground, Color const& background);
		/** @brief Prepare the font for drawing text on the screen
		 */
		void SetupText(int height);
		/** @brief Draw text onto the screen
		 */
		void Text(float x, float y, std::string const& text, Color const& color) const;
		/** @brief Center the text along a rectangle
		 */
		math::Vec3 CenterText(float x, float y, float width, float height, float textWidth, float textHeight);
		/** @brief Center the text around an axis
		 */
		float CenterTextAxis(float axis, float axisSize, float textSize);
		/** @brief Check if the font is already built 
		 */
		bool IsFontBuilt() const;
		/** @brief Get the current known HDC
		 */
		HDC GetHDC() const;
	private:
		bool bFontBuilt = false; ///< Font build status
		unsigned int base; ///< Font base
		HDC hdc; ///< Last known hdc
		int viewport[4]{ 0 }; ///< Viewport
	};
} // namespace draw
