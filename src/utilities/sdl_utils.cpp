#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_utils.h"
#include "DestroySdlObjects.h"
#include "config.h"
#include "errors.h"

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip = nullptr){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	} else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);	
}


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect* clip = nullptr){
	SDL_RenderCopy(ren, tex, clip, &dst);
}


SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer) {
	try {
		SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());

		if (texture == nullptr) {
			throw 1;
		}

		return texture;
	} catch (int e) {
		cleanup(renderer);
		printSDLErrorToTerminal(errorMessages.find(e)->second, SDL_GetError());
		SDL_Quit();
		return NULL;
	}
}