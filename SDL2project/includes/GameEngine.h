// Elvin Latifi, ella2817
#ifndef GAMEENNGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include <vector>

class GameEngine {
public:
	void run();
	void add(Sprite* sprite);
	void remove(Sprite* sprite);
private:
	std::vector<Sprite*> activeSprites;
	std::vector<Sprite*> added;
	std::vector<Sprite*> removed;
};
#endif
