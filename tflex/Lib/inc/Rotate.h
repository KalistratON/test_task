#pragma once

namespace figure {
	class Rotate
	{
		double angle;

	public:
		Rotate() = delete;
		explicit Rotate(const double) noexcept;

		Rotate(const Rotate&) = default;
		Rotate(Rotate&&) = default;
		~Rotate() = default;

		Rotate& operator = (const Rotate&) noexcept;
		Rotate& operator = (Rotate&&) noexcept;

		double get_rotate() const noexcept;
	};
}

