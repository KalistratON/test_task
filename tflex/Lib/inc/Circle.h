#pragma once
#include "Figure.h"

namespace figure {
	class Circle : public Figure
	{
		double R;

		static const size_t N = 100;

	public:
		Circle() = delete;
		explicit Circle(const Point&, const Rotate&, double);

		Circle(const Circle&) = delete;
		Circle(Circle&&) = delete;

		Circle& operator = (const Circle&) = delete;
		Circle& operator = (Circle&&) = delete;

		std::vector<Point> interpolation() const override;
		void printIntoStream(std::ostream& os) const override;
	};
}

