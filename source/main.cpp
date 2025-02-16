
#include "Renderer/Renderer.h"

int main() {

	if (!MBC::InitRenderer()) {
		SDL_Log("Failed to initialise renderer.\n");
		return 1;
	}

	// Main loop
	bool shouldQuit = false;
	SDL_Event currentEvent;
	SDL_zero(currentEvent);

	std::vector<Colour> colourData(4);
	colourData[0].r = 255;
	colourData[0].g = 0;
	colourData[0].b = 0;

	colourData[1].r = 0;
	colourData[1].g = 255;
	colourData[1].b = 0;

	colourData[2].r = 0;
	colourData[2].g = 0;
	colourData[2].b = 255;

	colourData[3].r = 255;
	colourData[3].g = 255;
	colourData[3].b = 255;


	while (!shouldQuit) {
		while (SDL_PollEvent(&currentEvent)) {
			if (currentEvent.type == SDL_EVENT_QUIT) {
				shouldQuit = true;
			}
		}
		MBC::RenderColourData(colourData, 2, 2);
	}

	MBC::DestroyRenderer();
}
