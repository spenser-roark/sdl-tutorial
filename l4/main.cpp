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
	Splash background("background.png", "l3");
	Splash image("image.png", "l3");
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printSDLErrorToTerminal("Couldn't Initialize SDL", SDL_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Lesson 2", 100, 100, screen_width, screen_height, SDL_WINDOW_SHOWN);

	if (win == nullptr) {
		printSDLErrorToTerminal("Error creating sdl window", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	background.setSDLWindow(win);
	image.setSDLWindow(win);

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (ren == nullptr) {
		printSDLErrorToTerminal("Erro creating sdl renderer", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	background.setSDLRenderer(ren);
	image.setSDLRenderer(ren);

	background.setSplashImageTexture();
	image.setSplashImageTexture();

	if (background.getSDLTexture() == NULL || image.getSDLTexture() == NULL) {
		printSDLErrorToTerminal("Error setting image texture", SDL_GetError());
		cleanup(background.getSDLTexture(), image.getSDLTexture(), ren, win);
		SDL_Quit();
		return 1;
	}

	bool quit = false;
	SDL_Event e;
	int iW;
	int iH;
	SDL_QueryTexture(image.getSDLTexture(), NULL, NULL, &iW, &iH);

	int windowX = screen_width/2 - iW/2;
	int windowY = screen_height/2 - iH/2;

	while (!quit) {
		
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				} else if (e.key.keysym.sym == SDLK_LEFT) {
					windowX -= 10;
				} else if (e.key.keysym.sym == SDLK_DOWN) {
					windowY += 10;
				} else if (e.key.keysym.sym == SDLK_RIGHT) {
					windowX += 10;
				} else if (e.key.keysym.sym == SDLK_UP) {
					windowY -= 10;
				}
			} 
		}
			SDL_RenderClear(ren);

			// int xTiles = screen_width / tile_size;
			// int yTiles = screen_height / tile_size;

			// for (int i = 0; i < xTiles * yTiles; i++) {
			// 	int x = i % xTiles;
			// 	int y = i / xTiles;

			// 	renderTexture(background.getSDLTexture(), ren, x * tile_size, y * tile_size, tile_size, tile_size);
			// }


			renderTexture(image.getSDLTexture(), ren, windowX, windowY);

			SDL_RenderPresent(ren);
	}
	cleanup(background.getSDLTexture(), image.getSDLTexture(), ren, win);
	SDL_Quit();
	return 0;
}