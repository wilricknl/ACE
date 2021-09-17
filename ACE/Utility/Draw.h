#pragma once

namespace draw
{
	struct Color
	{
		Color(float r, float g, float b, float a = 1.0f)
			: r(r), g(g), b(b), a(a)
		{}

		const float r;
		const float g;
		const float b;
		const float a;
	};

	class Draw
	{
	public:
		Draw() = default;
		virtual ~Draw() = default;

		void Setup();
		void Restore();
		void Line(float x1, float y1, float x2, float y2, float width, Color const& color);
		void Rect(float x, float y, float width, float height, Color const& color);
		void Outline(float x, float y, float width, float height, float lineWidth, float lineOffset, Color const& color);
	private:
		int viewport[4]{ 0 };
	};
} // namespace draw
