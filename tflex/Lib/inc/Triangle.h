#pragma once

#include "Figure.h"

namespace figure {
	class Triangle : public Figure
	{
		double a;
		double b;
		double c;

	public:
		Triangle() = delete;
		explicit Triangle(const Point&, const Rotate&, double, double, double);

		Triangle(const Triangle&) = delete;
		Triangle(Triangle&&) = delete;

		Triangle& operator = (const Triangle&) = delete;
		Triangle& operator = (Triangle&&) = delete;

		std::vector<Point> interpolation() const override;
		void printIntoStream(std::ostream& os) const override;
	};
}

