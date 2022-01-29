// Elvin Latifi, ella2817
#include "GameEngine.h"
#include <SDL.h>
#include "Sprite.h"
#include "System.h"

using namespace std;

void GameEngine::run() {
	// Main loop
	bool continueLoop = true;
	while (continueLoop) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				continueLoop = false;
				break;
			case SDL_KEYDOWN:
				for (Sprite* sprite : activeSprites)
					sprite->keyDown(event);
				break;
			} // switch
		} // inre while

		// Tick för alla sprites
		for (Sprite* sprite : activeSprites)
			sprite->tick(activeSprites);

		// Ta bort sprites
		for (Sprite* sprite : removed) {
			for (vector<Sprite*>::iterator i = activeSprites.begin(); i != activeSprites.end();) {
				if (*i == sprite) {
					delete* i;
					i = activeSprites.erase(i);
				}
				else
					i++;
			}
		}
		removed.clear();

		// Lägg till nya sprites
		for (Sprite* sprite : added)
			activeSprites.push_back(sprite);
		added.clear();

		// Rendera bild
		SDL_RenderClear(sys.getRen());
		for (Sprite* sprite : activeSprites) {
			sprite->draw();
		}
		SDL_RenderPresent(sys.getRen());

	} //yttre while
	
}

void GameEngine::add(Sprite* sprite) {
	added.push_back(sprite);
}

void GameEngine::remove(Sprite* sprite) {
	removed.push_back(sprite);
}


