// Elvin Latifi, ella2817
#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <vector>
class Sprite {
public:
	virtual void draw() const = 0;
	virtual void tick(std::vector<Sprite*> activeSprites) = 0;
	virtual void keyDown(SDL_Event event) {}
	virtual void detectCollision(std::vector<Sprite*> activeSprites) {}
	SDL_Rect getRect() const {
		return rect;
	}
	virtual ~Sprite() {}
	Sprite(const Sprite&) = delete;
	const Sprite& operator=(const Sprite&) = delete; 

protected:
	Sprite(int x, int y, int w, int h) : rect{ x, y, w, h } {}
	SDL_Rect rect;
};

#endif

