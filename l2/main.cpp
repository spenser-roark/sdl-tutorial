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
	Splash background("background.bmp", "l2");
	Splash image("image.bmp", "l2");
	
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

	for (int i = 0; i < 3; i++) {
		SDL_RenderClear(ren);

		int bW;
			int bH;
		SDL_QueryTexture(background.getSDLTexture(), NULL, NULL, &bW, &bH);

		// Bottom right corner
		renderTexture(background.getSDLTexture(), ren, bW*2.2, bH*2.2);

		// fill the rest of the window
		for (int j = 0; j < 3; j++) {
			renderTexture(background.getSDLTexture(), ren, 0, bH*j);
			renderTexture(background.getSDLTexture(), ren, bW, bH*j);
			renderTexture(background.getSDLTexture(), ren, bW*j, bH*2.2);
			renderTexture(background.getSDLTexture(), ren, bW*2, bH*j);
			renderTexture(background.getSDLTexture(), ren, bW*2.2, bH*j);
		}

		int iW;
		int iH;
		SDL_QueryTexture(image.getSDLTexture(), NULL, NULL, &iW, &iH);
		int windowX = screen_width/2 - iW/2;
		int windowY = screen_height/2 - iH/2;

		renderTexture(image.getSDLTexture(), ren, windowX, windowY);

		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}

	cleanup(background.getSDLTexture(), image.getSDLTexture(), ren, win);
	SDL_Quit();
	return 0;
}