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
	private:
		int viewport[4]{ 0 }; ///< Viewport
	};
} // namespace draw
