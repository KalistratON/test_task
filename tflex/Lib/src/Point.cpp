#include <utility>
#include <cmath>
#include "Point.h"

namespace figure {
	Point::Point(const double _x, const double _y) noexcept :
		x(_x),
		y(_y)
	{};

	Point& Point::operator = (const Point& _ctr) noexcept
	{
		if (this == &_ctr)
			return *this;
		x = _ctr.x;
		y = _ctr.y;
		return *this;
	}

	Point& Point::operator = (Point&& _ctr) noexcept
	{
		if (this == &_ctr)
			return *this;
		x = std::move(_ctr.x);
		y = std::move(_ctr.y);
		return *this;
	}

	Point Point::operator + (const Point& _ctr)
	{
		return Point(x + _ctr.get_x(), y + _ctr.get_y());
	}

	Point Point::operator - (const Point& _ctr)
	{
		return Point(x - _ctr.get_x(), y - _ctr.get_y());
	}

	double Point::get_x() const noexcept
	{
		return x;
	}

	double Point::get_y() const noexcept
	{
		return y;
	}

	Point Point::transform(const Rotate& _rtt) const noexcept
	{
		return Point(x * std::cos(_rtt.get_rotate()) + y * std::sin(_rtt.get_rotate()),
			-x * std::sin(_rtt.get_rotate()) + y * std::cos(_rtt.get_rotate()));
	}
}