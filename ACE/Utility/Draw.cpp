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
} // namespace draw