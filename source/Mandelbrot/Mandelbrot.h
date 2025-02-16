
#pragma once

#include <vector>

#include "Colour.h"

namespace MBC {

	void ComputeMandelbrotSetCPU(
		std::vector<Colour>& outVector,
		double xMin, double xMax,
		double yMin, double yMax,
		int displayWidth, int displayHeight,
		const std::vector<Colour>& colourScale,
		int maxIteration = 1000
	);

	void ComputeMandelbrotSetGPU(
		std::vector<Colour>& outVector,
		double xMin, double xMax,
		double yMin, double yMax,
		int displayWidth, int displayHeight,
		const std::vector<Colour>& colourScale,
		int maxIteration = 1000
	);

} // MBC
