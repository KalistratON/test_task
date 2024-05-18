#pragma once
#include <windows.h>
#include <memory>

#include "Figure.h"

class View
{
	HDC device_context = GetDC(GetConsoleWindow());
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

public:
	View();
	View(const View&) = delete;
	View(View&&) = delete;
	~View();

	View& operator = (const View&) = delete;
	View& operator = (View&&) = delete;

	void drawByTri(const std::unique_ptr<figure::Figure>&);
};

