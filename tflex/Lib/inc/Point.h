#pragma once
#include "Rotate.h"

namespace figure {
	class Point
	{
		double x;
		double y;

	public:
		Point() = delete;
		explicit Point(const double, const double) noexcept;

		Point(const Point&) = default;
		Point(Point&&) = default;
		~Point() = default;

		Point& operator = (const Point&) noexcept;
		Point& operator = (Point&&) noexcept;

		Point operator + (const Point&);
		Point operator - (const Point&);

		double get_x() const noexcept;
		double get_y() const noexcept;

		Point transform(const Rotate&) const noexcept;
	};
}

