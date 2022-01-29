// Elvin Latifi, ella2817
#include "System.h"
#include <SDL.h>
#include <iostream>

using namespace std;

System::System() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cerr << "SDL_Init fel: " << SDL_GetError() << endl;
		exit(-1);
	}
	win = SDL_CreateWindow("SpaceGame", 30, 30, 1300, 900, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
}

System::~System() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

System sys;