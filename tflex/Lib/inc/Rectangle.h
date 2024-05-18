#pragma once

#include "Figure.h"

namespace figure {
	class Rectangle : public Figure
	{
		double height;
		double width;

	public:
		Rectangle() = delete;
		explicit Rectangle(const Point&, const Rotate&, double, double);

		Rectangle(const Rectangle&) = delete;
		Rectangle(Rectangle&&) = delete;

		Rectangle& operator = (const Rectangle&) = delete;
		Rectangle& operator = (Rectangle&&) = delete;

		std::vector<Point> interpolation() const override;
		void printIntoStream(std::ostream& os) const override;
	};
}

