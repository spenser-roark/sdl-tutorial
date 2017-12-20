#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "res_path.h"
#include "DestroySdlObjects.h"
#include "splash.h"
#include "errors.h"
#include "config.h"

Splash::Splash() {
	lesson = "l1";
	fileName = "doomguy4.jpg";
}

Splash::Splash(string newFileName, string newLesson) {
	lesson = newLesson;
	fileName = newFileName;
}

void Splash::setFileName(string newFileName) {
	fileName = newFileName;
}

void Splash::setSDLWindow(SDL_Window* newWin) {
	win = newWin;
}

void Splash::setSDLRenderer(SDL_Renderer* newRen) {
	ren = newRen;
}

void Splash::setLesson(string newLesson) {
	lesson = newLesson;
}

SDL_Texture* Splash::getSDLTexture() {
	return tex;
}

SDL_Texture* Splash::setSplashImageTexture() {
	try {
		string image;
		// SDL_Surface* surfaceImage;
		image = getResourcePath(lesson) + fileName;
		
		// Deprecated code
		/* surfaceImage = IMG_Load(image.c_str());

		if (surfaceImage == nullptr) {
		 	throw 0;
		}
		*/
		tex = IMG_LoadTexture(ren, image.c_str());
		// cleanup(surfaceImage);

		if (tex == nullptr) {
			throw 1;
		}
	} catch (int e) {
		cleanup(ren, win);
		printSDLErrorToTerminal(errorMessages.find(e)->second, SDL_GetError());
		SDL_Quit();
		return NULL;
	}
}