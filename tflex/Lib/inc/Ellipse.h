#pragma once
#include "Figure.h"

namespace figure {
	class Ellipse : public Figure
	{
		double x_axis;
		double y_axis;

		static const size_t N = 100;

	public:
		Ellipse() = delete;
		explicit Ellipse(const Point&, const Rotate&, double, double);

		Ellipse(const Ellipse&) = delete;
		Ellipse(Ellipse&&) = delete;

		Ellipse& operator = (const Ellipse&) = delete;
		Ellipse& operator = (Ellipse&&) = delete;

		std::vector<Point> interpolation() const override;
		void printIntoStream(std::ostream& os) const override;
	};
}

