#pragma once
#include <ostream>
#include <vector>

#include "Point.h"
#include "Rotate.h"

namespace figure {

	extern const double phi;

	class Figure
	{

	protected:
		Point m_cnt;
		Rotate m_rtt;

	public:
		Figure() = delete;
		Figure(const Point&, const Rotate&) noexcept;
		
		virtual ~Figure() = default;

		void setCenter(const Point&) noexcept;
		void setRotate(const Rotate&) noexcept;

		virtual std::vector<Point> interpolation() const = 0;
		virtual void printIntoStream(std::ostream& os) const = 0;
	};
}

