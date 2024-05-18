#include "Ellipse.h"

#include <cmath>
#include <vector>
#include <algorithm>

namespace figure {

	Ellipse::Ellipse(const Point& _cnt, const Rotate& _rtt, double _x_axis, double _y_axis) :
		Figure(_cnt, _rtt),
		x_axis(_x_axis),
		y_axis(_y_axis)
	{
		if (_x_axis < .0 || _y_axis < 0)
			throw std::invalid_argument("Negative axis(-es) : x_axis < 0 OR (AND) y_axis < 0");
	
	};

	std::vector<Point> Ellipse::interpolation() const
	{
		std::vector<Point> interPoints;
		interPoints.reserve(N + 1);
		auto iter = std::back_inserter(interPoints);
		size_t i = -1;

		std::generate_n(iter, N, [&]() {

			return ++i,
					Point(x_axis * std::cos(2 * phi * i / N),
						y_axis * std::sin(2 * phi * i / N)).transform(m_rtt) + m_cnt;

			});
		interPoints.insert(interPoints.begin(), m_cnt);

		return interPoints;
	}

	void Ellipse::printIntoStream(std::ostream& os) const
	{
		const auto interPoints = interpolation();

		for (size_t j = 0; j < N + 1; j++)
			os << '(' << interPoints.at(j).get_x() << ';' << interPoints.at(j).get_y() << ')' << std::endl;
	}
}
