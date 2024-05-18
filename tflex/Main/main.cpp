#define _WIN32_WINNT 0x601

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>

#include <windows.h>

#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "View.h"

using Shape = std::unique_ptr<figure::Figure>;

int main(int argc, char* argv[])
{
	try {

		const int windowWidth = GetSystemMetrics(SM_CXSCREEN);
		const int windowHeight = GetSystemMetrics(SM_CYSCREEN);
				
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		const size_t N = 20;
		std::vector<Shape> figures;
		View view;

		const figure::Point globalCenter(	static_cast<double>(windowWidth / 2),
											static_cast<double>(windowHeight / 2));
		
		auto generateType = [&globalCenter]() -> Shape
		{
			figure::Rotate _rrt(std::rand() % 360 * figure::phi / 180.0);

			int atom = globalCenter.get_y() < globalCenter.get_x() ? static_cast<int>(globalCenter.get_y()) : static_cast<int>(globalCenter.get_x());

			int radius = std::rand() % atom;

			int x_axis = (std::rand() % atom + std::rand() % atom) / 2;
			int y_axis = (std::rand() % atom + std::rand() % atom) / 2;

			int height = (std::rand() % atom + std::rand() % atom) / 2;
			int width = (std::rand() % atom + std::rand() % atom) / 2;

			int a = (std::rand() % atom + std::rand() % atom) / 2;
			int b = (std::rand() % atom + std::rand() % atom) / 2;
			int c = a > b ? b / 2 + a : a / 2 + b;

			switch (std::rand() % 4)
			{
			case 0:
				return std::make_unique<figure::Circle>(globalCenter, _rrt, radius);
				break;
			case 1:
				return std::make_unique<figure::Ellipse>(globalCenter, _rrt, x_axis, y_axis);
				break;
			case 2:
				return std::make_unique<figure::Rectangle>(globalCenter, _rrt, height, width);
				break;
			default:
				return std::make_unique<figure::Triangle>(globalCenter, _rrt, a, b, c);
			}
		};

		auto iter = std::back_inserter(figures);
		std::generate_n(iter, N, generateType);

		std::for_each(figures.begin(), figures.end(), [&view](const Shape& shape) {
			
			system("cls");
			view.drawByTri(shape);
			
			std::this_thread::sleep_for(std::chrono::seconds(1ll));
			
		});

		system("cls");
		std::cout << "Output into stream" << std::endl;

		std::for_each(figures.begin(), figures.end(), [&view](const Shape& shape) {

			system("cls");
			shape->printIntoStream(std::cout);

			std::this_thread::sleep_for(std::chrono::seconds(1ll));

		});
		
		return 0;
	}
	catch (const std::invalid_argument& exc) {

		std::cerr << exc.what() << std::endl;
	}
	catch (const std::exception&)
	{
		std::cerr << "Standart exception" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Non - standart exception" << std::endl;
	}
}