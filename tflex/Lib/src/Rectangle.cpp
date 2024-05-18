#include <vector>
#include <algorithm>
#include "Rectangle.h"


namespace figure {

	Rectangle::Rectangle(const Point& _cnt, const Rotate& _rtt, double _height, double _width) :
		Figure(_cnt, _rtt),
		height(_height),
		width(_width)
	{
		if (_height < .0 || _width < 0)
			throw std::invalid_argument("Negative length(-es) : _height < 0 OR (AND) _width < 0");
	};

	std::vector<Point> Rectangle::interpolation() const
	{
		std::vector<Point> interPoints;
		const size_t N = 4;
		interPoints.reserve(N + 1);
		auto iter = std::back_inserter(interPoints);
		size_t i = -1;
		
		std::generate_n(iter, N, [&]() {
				++i;
				switch (i)
				{
				case 0:
					return Point(width / 2, - height / 2).transform(m_rtt) + m_cnt;
				case 1:
					return Point(width / 2,height / 2).transform(m_rtt) + m_cnt;
				case 2:
					return Point(-width / 2, +height / 2).transform(m_rtt) + m_cnt;
				case 3:
					return Point(-width / 2, -height / 2).transform(m_rtt) + m_cnt;
				}
			});
		interPoints.insert(interPoints.begin(), m_cnt);
		return interPoints;
	}

	void Rectangle::printIntoStream(std::ostream& os) const
	{
		const auto interPoints = interpolation();
		const size_t N = 5;

		for (size_t j = 0; j < N; j++)
			os << '(' << interPoints.at(j).get_x() << ';' << interPoints.at(j).get_y() << ')' << std::endl;
	}
}
