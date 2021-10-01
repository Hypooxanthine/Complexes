#include "Mandelbrot/Mandelbrot.h"

int main()
{
	std::cout << "----- Mandelbrot fractal -----\n";
	std::cout << "Commands :\nLeft click to zoom in somewhere.\nRight click to zoom out.\nMouse wheel to modify the iterations number.\n";
	std::cout << "The \"Render\" button will generate a set of 150 png images while zooming in into a point in the Sea Horse Valley I found interesting.\n";
	std::cout << "Have fun :)\n\n";
	Mandelbrot app;
	app.run();

	std::cin.get();
}