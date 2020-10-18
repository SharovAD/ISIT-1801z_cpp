

#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>
#include <cmath>

#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 800, HEIGHT = 600;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"SINC",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 255, 255, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(ren.get(), 50, 20, 255, 255);


		    auto GetX = [&](double x) { return int(x / 60 * WIDTH); };
		    auto GetY = [&](double y) { return int((-y / 1 + 1) * (HEIGHT / 2)); };

		    for(double i = 0; i < 60; i += 0.002)
		        {
		           double X = GetX(i);
		           double Y = GetY(sin(i)/i);
		           SDL_RenderDrawPoint(ren.get(), X, Y);

		        }
		SDL_RenderPresent(ren.get());
	}


	return 0;
}

