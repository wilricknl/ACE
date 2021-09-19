#include "../pch.h"
#include "gl/GL.h"
#include "Draw.h"

namespace draw
{
	void Draw::Setup2D()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, viewport[2], viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
	}

	void Draw::Restore2D()
	{
		glPopMatrix();
		glPopAttrib();
		glEnable(GL_DEPTH_TEST);
	}

	/**
	 * @p x1 The x-value of point 1
	 * @p y1 The y-value of point 1
	 * @p x2 The x-value of point 2
	 * @p y2 The y-value of point 2
	 * @p lineWidth The width of the line
	 * @p color The color of the line
	 */
	void Draw::Line2D(float x1, float y1, float x2, float y2, float lineWidth, Color const& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(color.r, color.g, color.b, color.a);
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
		glDisable(GL_BLEND);
	}

	/**
	 * @p x Top left x-coordinate
	 * @p y Top left y-coordinate
	 * @p width The width of the rectangle
	 * @p height The height of the rectangle
	 * @p color The color of the rectangle
	 */
	void Draw::Rectangle2D(float x, float y, float width, float height, Color const& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
		glEnd();
		glDisable(GL_BLEND);
	}

	/**
	 * @p x Top left x-coordinate
	 * @p y Top left y-coordinate
	 * @p width The width of the rectangle
	 * @p height The height of the rectangle
	 * @p lineWidth The width of the line
	 * @p lineOffset The offset outside the triangle
	 * @p color The color of the rectangle
	 */
	void Draw::RectangleOutline2D(float x, float y, float width, float height, float lineWidth, float lineOffset, Color const& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINE_STRIP);
		glLineWidth(lineWidth);
		glVertex2f(x - lineOffset, y - lineOffset);
		glVertex2f(x + width + lineOffset, y - lineOffset);
		glVertex2f(x + width + lineOffset, y + height + lineOffset);
		glVertex2f(x - lineOffset, y + height + lineOffset);
		glVertex2f(x - lineOffset, y - lineOffset);
		glEnd();
		glDisable(GL_BLEND);
	}

	/**
	 * @p x Top left x-coordinate of the bar
	 * @p y Top left y-coordinate of the bar
	 * @p width The width of the bar
	 * @p height The height of the bar
	 * @p value The value of the bar
	 * @p maximum The maximum value of the bar
	 * @p foreground The foreground color of the slider
	 * @p background The background color of the slider
	 */
	void Draw::Bar2D(float x, float y, float width, float height, float value, float maximum, Color const& foreground, Color const& background)
	{
		Rectangle2D(x, y, width, height, background);
		float valueHeight{ height * (value / maximum) };
		Rectangle2D(x, y + height - valueHeight, width, valueHeight, foreground);
	}

	/**
	 * @p height The height of the text
	 *
	 * @post The text can be drawn to the screen
	 */
	void Draw::SetupText(int height)
	{
		hdc = wglGetCurrentDC();
		base = glGenLists(96);
		auto hFont = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, 
			FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
		auto hOldFont = (HFONT)SelectObject(hdc, hFont);
		wglUseFontBitmaps(hdc, 32, 96, base);
		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);
		bFontBuilt = true;
	}

	/**
	 * @pre The font is built using @ref SetupText
	 *
	 * @p x The x coordinate where the text should be drawn
	 * @p y The y coordinate where the text should be drawn
	 * @p text The text that should be drawn
	 * @p color The color of the text
	 */
	void Draw::Text(float x, float y, std::string const& text, Color const& color) const
	{
		glColor4f(color.r, color.g, color.b, color.a);
		glRasterPos2f(x, y);
		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(text.size(), GL_UNSIGNED_BYTE, text.c_str());
		glPopAttrib();
	}

	/**
	 * Find the center where the text should be drawn, such that it's
	 * centered in relation to a rectangle.
	 *
	 * @p x Top left x of the rectangle
	 * @p y Top left y of the rectangle
	 * @p width The width of the rectangle
	 * @p height The height of the rectangle
	 * @p textWidth The width of the text
	 * @p textHeight The height of the text
	 *
	 * @return The position where the text should be drawn.
	 */
	math::Vec3 Draw::CenterText(float x, float y, float width, float height, float textWidth, float textHeight)
	{
		return math::Vec3{
			CenterTextAxis(x, width, textWidth),
			CenterTextAxis(y, height, textHeight)
		};
	}

	/**
	 * @p axis The axis value
	 * @p axisSize The size of the axis
	 * @p textSize The text axis' size
	 *
	 * @return The value where the text is centered compared to the axis.
	 */
	float Draw::CenterTextAxis(float axis, float axisSize, float textSize)
	{
		if (axisSize > textSize)
		{
			return axis + (axisSize - textSize) / 2.f;
		}
		return axis - (textSize - axisSize) / 2.f;
	}

	/**
	 * @return `true` if the text is built, else `false`
	 */
	bool Draw::IsFontBuilt() const
	{
		return bFontBuilt;
	}

	/**
	 * @return The currently known `HDC`
	 */
	HDC Draw::GetHDC() const
	{
		return hdc;
	}
} // namespace draw