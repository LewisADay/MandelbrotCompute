
#include "Mandelbrot.h"

#include <iostream>
#include <complex>

namespace MBC {

	static Colour InterpolateColour(const std::vector<Colour>& colourScale, int num, int numMax) {

		if (num >= numMax) {
			return colourScale[colourScale.size() - 1];
		}

		// Need location in terms of colourScale index but not int as we want to interpolate
		double colourIndex = (static_cast<double>(num) / static_cast<double>(numMax)) * static_cast<double>(colourScale.size() - 1);

		const size_t firstIndex = static_cast<size_t>(std::floor(colourIndex));
		const size_t secondIndex = firstIndex + 1; // Guarenteed to be <= numMax
		Colour firstColour = colourScale[firstIndex];
		Colour secondColour = colourScale[secondIndex];

		Colour outColour{ 0, 0, 0 };
		outColour.r = firstColour.r + ((secondColour.r - firstColour.r) * (colourIndex - firstIndex));
		outColour.g = firstColour.g + ((secondColour.g - firstColour.g) * (colourIndex - firstIndex));
		outColour.b = firstColour.b + ((secondColour.b - firstColour.b) * (colourIndex - firstIndex));

		return outColour;
	}

	void ComputeMandelbrotSetCPU(
		std::vector<Colour>& outVector,
		double xMin, double xMax,
		double yMin, double yMax,
		int displayWidth, int displayHeight,
		const std::vector<Colour>& colourScale,
		int maxIteration
	)
	{
		// Tweak for fun
		const int power = 2;
		const int bound = 2;

		// Mandelbrot core function
		auto iterationFunc = [](std::complex<double> iter, int power, std::complex<double> seedCoord) {
			return std::pow(iter, power) + seedCoord;
		};

		// Iterate over domain for pixels in screen space
		double xIter = (xMax - xMin) / displayWidth;
		double yIter = (yMax - yMin) / displayHeight;

		for (double yCurrent = yMin; yCurrent < yMax; yCurrent += yIter) {
			for (double xCurrent = xMin; xCurrent < xMax; xCurrent += xIter) {

				std::complex<double> z_old{0, 0}; // Init at 0 + 0i
				std::complex<double> z_new{0, 0}; // Init at 0 + 0i
				std::complex<double> seed{xCurrent, yCurrent}; // x + yi
				bool set = false;

				for (int iter = 0; iter < maxIteration; ++iter) {

					// If we've left the bounds add the appropriate colour
					if (std::abs(z_old) >= bound) {
						outVector.push_back(InterpolateColour(colourScale, iter, maxIteration));
						set = true;
						break;
					}
					z_new = iterationFunc(z_old, power, seed);
					if (z_new == z_old) {
						outVector.push_back(colourScale[colourScale.size() - 1]);
						set = true;
						break;
					}
					z_old = z_new;
				}

				if (!set) {
					outVector.push_back(colourScale[colourScale.size() - 1]);
				}
			}
		}
	}

} // MBC
