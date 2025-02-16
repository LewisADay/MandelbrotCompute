
#include "Renderer.h"

#include <SDL3/SDL_events.h>
//#include <SDL3/SDL_surface.h>

namespace MBC {

	static SDL_Window* s_Window = nullptr;
	static SDL_Renderer* s_Renderer = nullptr;
	static SDL_Surface* s_WindowSurface = nullptr;

	constexpr int c_WindowWidth = 640;
	constexpr int c_WindowHeight = 480;

	static bool ResizingEventWatcher(void* data, SDL_Event* event) {
		if (event->type == SDL_EVENT_WINDOW_RESIZED) {
			SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
			if (win == (SDL_Window*)data) {
				ResizeWindow(event->window.data1, event->window.data2);
			}
		}
		return false;
	}

	bool InitRenderer() {

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("Could not initialise SDL. Error: %s\n", SDL_GetError());
			return false;
		}

		s_Window = SDL_CreateWindow("Mandelbrot Set Compute Test App", c_WindowWidth, c_WindowHeight,
			SDL_WINDOW_RESIZABLE
		);

		s_Renderer = SDL_CreateRenderer(s_Window, nullptr);

		if (!s_Window) {
			SDL_Log("Could not create window. Error: %s\n", SDL_GetError());
			return false;
		}

		s_WindowSurface = SDL_GetWindowSurface(s_Window);

		return true;
	}

	void RenderColourData(const std::vector<Colour>& data, int width, int height) {

		// We start withb a blank grey canvas
		SDL_SetRenderDrawColor(s_Renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(s_Renderer);

		// The data is rgb pixel data from top left to bottom right windowspace, left to right
		for (size_t i = 0; i < data.size(); ++i) {
			const Colour& colour = data[i];
			SDL_SetRenderDrawColor(s_Renderer, colour.r, colour.g, colour.b, SDL_ALPHA_OPAQUE);
			SDL_RenderPoint(s_Renderer, i % width, i / width); // Probably a better way to do this
		}

		SDL_RenderPresent(s_Renderer);
	}

	SDL_Window* GetSDLWindow() {
		return s_Window;
	}

	void ResizeWindow(int width, int height) {
		
		if (!SDL_SetWindowSize(s_Window, width, height)) {
			SDL_Log("Failed to set window size to: %i x %i. Error: %s\n", width, height, SDL_GetError());
		}
	}

	void DestroyRenderer() {

		// Destroying the window also destroys it's surface
		SDL_DestroyWindow(s_Window);

		SDL_Quit();
	}
	
} // MBC
