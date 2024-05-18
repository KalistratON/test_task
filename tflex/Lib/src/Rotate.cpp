#include "Rotate.h"
#include <utility>

namespace figure {
	
	Rotate::Rotate(const double _angle) noexcept :
		angle(_angle)
	{};

	Rotate& Rotate::operator = (const Rotate& _rtt) noexcept
	{
		if (this == &_rtt)
			return *this;
		angle = _rtt.angle;
		return *this;
	}

	Rotate& Rotate::operator = (Rotate&& _rtt) noexcept
	{
		if (this == &_rtt)
			return *this;
		angle = std::move(_rtt.angle);
		return *this;
	}

	double Rotate::get_rotate() const noexcept
	{
		return angle;
	}

}