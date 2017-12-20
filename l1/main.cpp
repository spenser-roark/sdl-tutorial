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
	Splash doomGuy("CronosHouse.png", "l1");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		printSDLErrorToTerminal("SDL Init Error", SDL_GetError());
		return 1;
	}
	int imgFlags = IMG_INIT_JPG;
	int imgInit = IMG_Init(imgFlags);

	if (imgInit&imgFlags != imgFlags) {
		printSDLErrorToTerminal("Img Init: Failed to initialize jpeg support", IMG_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (!win) {
		printSDLErrorToTerminal("SDL Create Window Error", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	doomGuy.setSDLWindow(win);

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (ren == nullptr) {
		cleanup(win);
		printSDLErrorToTerminal("SDL create renderer error", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	doomGuy.setSDLRenderer(ren);

	doomGuy.setSplashImageTexture();
	
	if (doomGuy.getSDLTexture() == NULL) {
		return 1;
	}

	// quits when x button is hit
	// while(1){
	// 	SDL_Event e;
	// 	if (SDL_PollEvent(&e)) {
	// 		cout << "e key " << (char)e.key.keysym.scancode << endl;
	// 		if (e.type == SDL_QUIT) {
	// 			break;
	// 		}
	// 	}

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i){
		//First clear the renderer
		SDL_RenderClear(ren);
		//Draw the texture
		SDL_RenderCopy(ren, doomGuy.getSDLTexture(), NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	// change this to a destructor
	cleanup(doomGuy.getSDLTexture(), ren, win);
	SDL_Quit();

	hello();
	return 0;
}