#include "Triangle.h"
#include <cmath>
#include <vector>
#include <algorithm>

namespace figure {
	Triangle::Triangle(const Point& _cnt, const Rotate& _rtt, double _a, double _b, double _c) :
		Figure(_cnt, _rtt),
		a(_a),
		b(_b),
		c(_c)
	{
		if (_a <= .0 || _b <= .0 || _c <= .0)
			throw std::invalid_argument("Negative length(-es) : a < 0 OR (AND) b < 0 OR (AND) c < 0");
		if (_c > _a + _b || _a > _c + _b || _b > _c + _a)
			throw std::invalid_argument("Triangle rule is fails");
	};

	std::vector<Point> Triangle::interpolation() const
	{		
		double _x = (a * a + b * b - c * c) / (2 * a);
		double _y = std::sqrt((b - _x) * (b + _x));

		return std::vector<Point>	{
										m_cnt,
										Point(a, .0).transform(m_rtt) + m_cnt,
										Point(_x, _y).transform(m_rtt) + m_cnt
									};
	}

	void Triangle::printIntoStream(std::ostream& os) const
	{
		const auto interPoints = interpolation();
		const size_t N = 3;

		for (size_t j = 0; j < N; j++)
			os << '(' << interPoints.at(j).get_x() << ';' << interPoints.at(j).get_y() << ')' << std::endl;
	}
}
