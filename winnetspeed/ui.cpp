#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "ui.h"

void UI::uithreadfunc()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("title", 50, 50, 560, 380, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetWindowBordered(window, SDL_FALSE);
	SDL_SetWindowResizable(window, SDL_FALSE);
	SDL_SetWindowOpacity(window, 0.9);

	int beginx = -1, beginy = -1, beginwinx = -1, beginwiny = -1, m = 0;
	bool quit = false;
	while (!quit) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetWindowPosition(window, &beginwinx, &beginwiny);
				beginx = e.button.x + beginwinx;
				beginy = e.button.y + beginwiny;
				m = 1;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				beginx = -1, beginy = -1, beginwinx = -1, beginwiny = -1, m = 0;
			}
			else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_LEAVE) {
				beginx = -1, beginy = -1, beginwinx = -1, beginwiny = -1, m = 0;
			}
			else if (e.type == SDL_MOUSEMOTION && m) {
				int x, y;
				SDL_GetWindowPosition(window, &x, &y);
				x = e.motion.x + x - beginx + beginwinx;
				y = e.motion.y + y - beginy + beginwiny;
				SDL_SetWindowPosition(window, x, y);
			}
		}


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xff);
		SDL_RenderClear(renderer);

		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xff);
		SDL_Rect rect;
		// rect.x = 20;
		// rect.y = 30;
		// rect.w = 100;
		// rect.h = 130;
		// SDL_RenderFillRect(renderer, &rect);

		SDL_Color White = { 255, 255, 255 };
		SDL_Color Black = { 0, 0, 0 };
		std::string font_path;
		font_path += SDL_GetBasePath();
		font_path += "simkai.ttf";
		auto font_ptr = TTF_OpenFont(font_path.c_str(), 20);
		if (!font_ptr) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			// handle error
		}
		std::string text(u8"网速:");
		text += std::to_string(this->in_speed / 1024);
		text += u8"kb/s";
		auto text_surface = TTF_RenderUTF8_Solid(font_ptr, text.c_str(), Black);
		auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		rect.x = 20;
		rect.y = 30;
		rect.w = text_surface->w;
		rect.h = text_surface->h;
		SDL_RenderCopy(renderer, text_texture, nullptr, &rect);

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}



	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
}

UI::UI(/* args */)
{
	this->uithread.reset(new std::thread(&UI::uithreadfunc, this));
}

void UI::set_speed(int& in, int& out)
{
	this->in_speed = in;
	this->out_speed = out;
}

UI::~UI()
{
	this->uithread->join();
}
    