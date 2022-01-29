// Elvin Latifi, ella2817
#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>

class System
{
public: 
	System();
	~System();
	SDL_Renderer* getRen() const {
		return ren;
	}
private:
	SDL_Renderer* ren;
	SDL_Window* win;
};

extern System sys; 

#endif

