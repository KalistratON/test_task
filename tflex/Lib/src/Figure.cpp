#include "Figure.h"

namespace figure {
	
	const double phi = 3.14159265358979323846;

	Figure::Figure(const Point& _cnt, const Rotate& _rtt) noexcept :
		m_cnt(_cnt),
		m_rtt(_rtt)
	{}

	void Figure::setCenter(const Point& _cnt) noexcept
	{
		m_cnt = _cnt;
	}

	void Figure::setRotate(const Rotate& _rtt) noexcept
	{
		m_rtt = _rtt;
	}
}
