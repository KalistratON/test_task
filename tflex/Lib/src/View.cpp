#include <iostream>
#include "View.h"

View::View()
{
	SelectObject(device_context, pen);
};

View::~View()
{
	ReleaseDC(GetConsoleWindow(), device_context);
}

void View::drawByTri(const std::unique_ptr<figure::Figure>& _fgr)
{
	auto fgrPoints = _fgr->interpolation();
	const size_t N = fgrPoints.size();

	
	for (size_t j = 1; j < N; j++)
	{
		MoveToEx(device_context, fgrPoints.at(0).get_x(), fgrPoints.at(0).get_y(), nullptr);
		LineTo(device_context, fgrPoints.at(j).get_x(), fgrPoints.at(j).get_y());
	}
		
	for (size_t j = 2; j < N; j++)
	{
		MoveToEx(device_context, fgrPoints.at(j - 1).get_x(), fgrPoints.at(j - 1).get_y(), nullptr);
		LineTo(device_context, fgrPoints.at(j).get_x(), fgrPoints.at(j).get_y());
	}
	MoveToEx(device_context, fgrPoints.at(N - 1).get_x(), fgrPoints.at(N - 1).get_y(), nullptr);
	LineTo(device_context, fgrPoints.at(1).get_x(), fgrPoints.at(1).get_y());
}
