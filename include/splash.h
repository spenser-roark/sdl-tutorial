#ifndef SPLASH_H
#define SPLASH_H

#include <SDL2/SDL.h>

class Splash {
private:
	string fileName;
	string lesson;
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture* tex;
public:
	Splash();
	Splash(string, string);
	SDL_Texture* setSplashImageTexture();
	void setFileName(string newFileName);
	void setSDLWindow(SDL_Window* newWin);
	void setLesson(string newLesson);
	void setSDLRenderer(SDL_Renderer* newRen);
	SDL_Texture* getSDLTexture();
};

#endif