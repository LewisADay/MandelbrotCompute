
#include "Renderer/Renderer.h"
#include "Mandelbrot/Mandelbrot.h"

int main() {

	if (!MBC::InitRenderer()) {
		SDL_Log("Failed to initialise renderer.\n");
		return 1;
	}

	std::vector<Colour> colourScale;
	colourScale.emplace_back(255, 255, 255);
	colourScale.emplace_back(0, 0, 255);
	colourScale.emplace_back(0, 255, 0);
	colourScale.emplace_back(255, 0, 0);
	colourScale.emplace_back(0, 0, 0);

	int initWindowWidth = 0;
	int initWindowHeight = 0;
	SDL_GetWindowSize(MBC::GetSDLWindow(), &initWindowWidth, &initWindowHeight);

	std::vector<Colour> colourData;
	colourData.reserve(initWindowWidth * initWindowHeight);

	MBC::ComputeMandelbrotSetCPU(
		colourData,
		-2, 2,
		-2, 2,
		initWindowWidth, initWindowHeight,
		colourScale
	);

	MBC::RenderColourData(colourData, initWindowWidth, initWindowHeight);

	// Main loop
	bool shouldQuit = false;
	SDL_Event currentEvent;
	SDL_zero(currentEvent);
	while (!shouldQuit) {
		while (SDL_PollEvent(&currentEvent)) {
			if (currentEvent.type == SDL_EVENT_QUIT) {
				shouldQuit = true;
			}
		}
	}

	MBC::DestroyRenderer();
}
