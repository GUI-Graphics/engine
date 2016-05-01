#pragma once

namespace engine
{
	class Color {
	public:
		Color()
		{ }

		Color::Color(float r, float g, float b) : r(r), g(g), b(b)
		{ }

		Color::Color(unsigned int hex)
		{
			set(hex);
		}

		Color& Color::set(float r, float g, float b)
		{
			this->r = r;
			this->g = g;
			this->b = b;

			return *this;
		}

		Color& Color::set(unsigned int hex)
		{
			float k = 1 / 255.0f;

			r = (hex >> 16 & 0xff) * k;
			g = (hex >> 8 & 0xff) * k;
			b = (hex & 0xff) * k;

			return *this;
		}

		unsigned int Color::getHex() const
		{
			return (unsigned int)(r * 255.0f) << 16
				^ (unsigned int)(g * 255.0f) << 8
				^ (unsigned int)(b * 255.0f);
		}

		bool Color::operator==(const Color& color) const
		{
			return r == color.r && g == color.g && b == color.b;
		}

		bool Color::operator!=(const Color& color) const
		{
			return r != color.r || g != color.g || b != color.b;
		}

	public:
		float r;
		float g;
		float b;
	};
}
