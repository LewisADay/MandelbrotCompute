
#pragma once

#include <vector>
#include <SDL3/SDL.h>

#include "Colour.h"

namespace MBC {

	bool InitRenderer();
	void RenderColourData(const std::vector<Colour>& data, int width, int height);
	SDL_Window* GetSDLWindow();
	void ResizeWindow(int width, int height);
	void DestroyRenderer();

} // MBC
