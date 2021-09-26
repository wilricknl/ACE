#pragma once
#include <string>
#include "../ReClass/Entity.h"
#include "Color.h"
#include "Vec.h"

namespace mvc
{
	class Model;
}

namespace draw
{
	/**
	 * @brief Draw provides OpenGL drawing operations
	 */
	class Draw
	{
	public:
		Draw(mvc::Model& model);
		virtual ~Draw() = default;

		/** @brief Setup OpenGL for 2D drawing
		 */
		void Setup2D();
		/** @brief Restore OpenGL after 2D drawing 
		 */
		void Restore2D();
		/** @brief Draw a 2D line
		 */
		void Line2D(
			float x1, 
			float y1, 
			float x2, 
			float y2, 
			float width, 
			Color const& color) const;
		/** @brief Draw a 2D rectangle
		 */
		void Rectangle2D(
			float x, 
			float y, 
			float width, 
			float height, 
			Color const& color) const;
		/** @brief Draw a 2D outline
		 */
		void RectangleOutline2D(
			float x, 
			float y, 
			float width, 
			float height, 
			float lineWidth, 
			float lineOffset, 
			Color const& color) const;
		/** @brief Draw a 2D bar
		 */
		void Bar2D(
			float x, 
			float y, 
			float width, 
			float height, 
			float value, 
			float maximum, 
			Color const& foreground, 
			Color const& background) const;
		/** @brief Prepare the font for drawing text on the screen
		 */
		void SetupText(int height);
		/** @brief Draw text onto the screen
		 */
		void Text(float x, float y, std::string const& text, Color const& color) const;
		/** @brief Center the text along a rectangle
		 */
		math::Vec3 CenterText(float x, float y, float width, float height, float textWidth, float textHeight) const;
		/** @brief Center the text around an axis
		 */
		float CenterTextAxis(float axis, float axisSize, float textSize) const;
		/** @brief Check if the font is already built 
		 */
		bool IsFontBuilt() const;
		/** @brief Get the current known HDC
		 */
		HDC GetHDC() const;
		/** @brief Convert world position to screen coordinate
		 */
		bool WorldToScreen(
			math::Vec3 position, 
			math::Vec2& outScreenCoordinates,
			int windowWidth, 
			int windowHeight) const;
	private:
		mvc::Model& model; ///< Reference to model
		bool bFontBuilt = false; ///< Font build status
		unsigned int base; ///< Font base
		HDC hdc; ///< Last known hdc
		int viewport[4]{ 0 }; ///< Viewport
	};
} // namespace draw
