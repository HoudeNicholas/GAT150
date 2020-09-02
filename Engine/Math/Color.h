#pragma once
#include "pch.h"
#include <Windows.h>
#include "SDL.h"
#include <iostream>
#include <string>

namespace nc 
{
	struct Color 
	{
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 }{};
		Color(float r, float g, float b, float a = 1.0f) : r{ r }, g{ g }, b{ b }, a{ a } {};

		inline SDL_Color pack888() const {

			SDL_Color color;
			color.r = static_cast<BYTE>(r * 255);
			color.g = static_cast<BYTE>(g * 255);
			color.b = static_cast<BYTE>(b * 255);
			color.a = static_cast<BYTE>(a * 255);

			return color;
		}


		friend std::ostream& operator<<(std::ostream& stream, Color& c) {
			stream << c.r << " " << c.g << " " << c.b << " " << c.a;
			return stream;
		}

		operator SDL_Color() const {
			return pack888();
		}

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }

		Color operator -= (const Color& c) { return Color{ r -= c.r, g -= c.g, b -= c.b }; }
		Color operator += (const Color& c) { return Color{ r += c.r, g += c.g, b += c.b }; }
		Color operator *= (const Color& c) { return Color{ r *= c.r, g *= c.g, b *= c.b }; }
		Color operator /= (const Color& c) { return Color{ r /= c.r, g /= c.g, b /= c.b }; }

		Color operator += (float s) { return Color{ r += s, g += s, b += s }; }
		Color operator -= (float s) { return Color{ r -= s, g -= s, b -= s }; }
		Color operator *= (float s) { return Color{ r *= s, g *= s, b *= s }; }
		Color operator /= (float s) { return Color{ r /= s, g /= s, b /= s }; }

		friend std::istream& operator >> (std::istream& stream, Color& c)
		{
			std::string line;
			std::getline(stream, line);

			if (line.find("{") != std::string::npos)
			{
				std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{"));
				c.r = std::stof(cr);

				line = line.substr(line.find(",") + 1, line.find("}") - line.find(","));

				std::string cg = line.substr(0, line.find(","));
				c.g = std::stof(cg);

				std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
				c.b = std::stof(cb);

				
			}
			return stream;
		}

	};
}