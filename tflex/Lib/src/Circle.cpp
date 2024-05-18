#include "Circle.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace figure {
	Circle::Circle(const Point& _cnt, const Rotate& _rtt, double _R) :
		Figure(_cnt, _rtt),
		R(_R)
	{
		if (_R < .0)
			throw std::invalid_argument("Negative radius : R < 0");
	};

	std::vector<Point> Circle::interpolation() const
	{
		std::vector<Point> interPoints;
		interPoints.reserve(N + 1);
		auto iter = std::back_inserter(interPoints);
		size_t i = -1;
		
		std::generate_n(iter, N, [&]() {

			//transform is ignored for circle
			return ++i, 
					Point(R * std::cos(2 * phi * i / N),
						R * std::sin(2 * phi * i / N)).transform(m_rtt) + m_cnt;
			
			});
		interPoints.insert(interPoints.begin(), m_cnt);
		
		return interPoints;
	}

	void Circle::printIntoStream(std::ostream& os) const
	{
		const auto interPoints = interpolation();

		for (size_t j = 0; j < N + 1; j++)
			os << '(' << interPoints.at(j).get_x() << ';' << interPoints.at(j).get_y() << ')' << std::endl;
	}
}