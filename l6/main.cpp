// Base headers
#include <iostream>
#include <string>
using namespace std;

// Graphic library header files
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Header files from me
#include "res_path.h"
#include "DestroySdlObjects.h"
#include "settings.h"
#include "errors.h"
#include "splash.h"
#include "sdl_utils.h"
#include "config.h"


int main(int argc, char** argv) {
	Splash image("chrono.png", "l5");
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printSDLErrorToTerminal("Couldn't Initialize SDL", SDL_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Chrono walking", 0, 0, screen_width, screen_height, SDL_WINDOW_SHOWN);

	if (win == nullptr) {
		printSDLErrorToTerminal("Error creating sdl window", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	image.setSDLWindow(win);

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (ren == nullptr) {
		printSDLErrorToTerminal("Erro creating sdl renderer", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	image.setSDLRenderer(ren);

	image.setSplashImageTexture();

	if (image.getSDLTexture() == NULL) {
		printSDLErrorToTerminal("Error setting image texture", SDL_GetError());
		cleanup(image.getSDLTexture(), ren, win);
		SDL_Quit();
		return 1;
	}

	bool quit = false;
	SDL_Event e;

	int cW = 20;
	int cH = 50;
	int windowX = screen_width/2 - cW/2;
	int windowY = screen_height/2 - cH/2;

	SDL_Rect clips[4];

	for (int i = 0; i < 4; i++) {
		clips[i].x = i*50;
		clips[i].y = i*11 % 2 * cH;
		clips[i].w = cW;
		clips[i].h = cH;
	}

	int useClip = 0;

	while (!quit) {
		
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_1:
						useClip = 0;
						break;
					case SDLK_2:
						useClip = 1;
						break;
					case SDLK_3:
						useClip = 2;
						break;
					case SDLK_4:
						useClip = 3;
						break;
				}
			} 
		}
			SDL_RenderClear(ren);

			renderTexture(image.getSDLTexture(), ren, windowX, windowY, &clips[useClip]);
			SDL_RenderPresent(ren);
	}
	cleanup(image.getSDLTexture(), ren, win);
	SDL_Quit();
	return 0;
}