// Elvin Latifi, ella2817

#include <SDL.h>
#include "GameEngine.h"
#include "Sprite.h"
#include "System.h"
#include <string>
#include <random>
#include <time.h>


std::string resPath = "INSERT PATH TO /resources folder";

GameEngine engine;

class Alien : public Sprite {
public:
	static Alien* getInstance(int x) {
		return new Alien(x);
	}

	void draw() const {
		const SDL_Rect& rect = getRect();
		SDL_RenderCopy(sys.getRen(), texture, NULL, &rect); 
	}

	void tick(std::vector<Sprite*> activeSprites) {
		counter++;
		if (rect.y >= 1000)
			engine.remove(this);
		else if (counter % 20 == 0)
			rect.y++;
	}

private:
	Alien(int x) : Sprite(x, 100, 100, 50) {
		SDL_Surface* alienSurf = SDL_LoadBMP((resPath + "images/aliensprite.bmp").c_str());
		//Här skapar vi en vit färg
		Uint32 white = SDL_MapRGB(alienSurf->format, 255, 255, 255);
		// Här sätter vi så att alla pixlar med färgen vit kommer vara genomskinliga
		SDL_SetColorKey(alienSurf, true, white);
		// Skapa textur
		texture = SDL_CreateTextureFromSurface(sys.getRen(), alienSurf);
		// Fria surface
		SDL_FreeSurface(alienSurf);
	}

	~Alien() {
		SDL_DestroyTexture(texture);
	}

	SDL_Texture* texture;
	int counter = 0;
};

class AlienShip : public Sprite {
public:
	static AlienShip* getInstance() {
		return new AlienShip();
	}

	void draw() const {
		const SDL_Rect& rect = getRect();
		SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
	}

	void tick(std::vector<Sprite*> activeSprites) {
		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distr(1, 3);
		switch (distr(gen)) {
		case 1:
			if (rect.x > 200 && counter % 10 == 0) {
				rect.x-=30;
			}
			break;
		case 2:
			if (rect.x < 1000 && counter % 10 == 0) {
				rect.x+=30;
			}
			break;
		case 3:
			counter++;
			if (counter % 500 == 0) {
				Alien* alien = Alien::getInstance(rect.x + 100);
				engine.add(alien);
			}
			break;
		}
	}

	void decreaseHP() {
		healthPoints--;
		if (healthPoints == 0)
			engine.remove(this);
	}

private:
	AlienShip() : Sprite(600, 100, 200, 100) {
		SDL_Surface* alienSurf = SDL_LoadBMP((resPath + "images/alienship.bmp").c_str());
		//Här skapar vi en vit färg
		Uint32 white = SDL_MapRGB(alienSurf->format, 255, 255, 255);
		// Här sätter vi så att alla pixlar med färgen vit kommer vara genomskinliga
		SDL_SetColorKey(alienSurf, true, white);
		// Skapa textur
		texture = SDL_CreateTextureFromSurface(sys.getRen(), alienSurf);
		// Fria surface
		SDL_FreeSurface(alienSurf);
	}
	~AlienShip() {
		SDL_DestroyTexture(texture);
	}
	SDL_Texture* texture;
	int counter = 0;
	int healthPoints = 10;
};

class LaserShot : public Sprite {
public:
	static LaserShot* getInstance(int x) {
		return new LaserShot(x);
	}

	void draw() const {
		const SDL_Rect& rect = getRect();
		SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
	}

	void tick(std::vector<Sprite*> activeSprites) {
		detectCollision(activeSprites);
		counter++;
		if (rect.y <= 0)
			engine.remove(this);
		else if (counter % 2 == 0)
			rect.y--;
	}

	void detectCollision(std::vector<Sprite*> activeSprites) {
		SDL_Point p = { rect.x, rect.y };
		for (Sprite* sprite : activeSprites) {
			const SDL_Rect& spriteRect = sprite->getRect();
			if (sprite != this && SDL_PointInRect(&p, &spriteRect)) {
				if (AlienShip* alienShip = dynamic_cast<AlienShip*>(sprite)) {
					alienShip->decreaseHP();
					engine.remove(this);
				}
				else {
					engine.remove(sprite);
					engine.remove(this);
				}
			}
		}
	}

private:
	LaserShot(int x) : Sprite(x, 600, 10, 50) {
		SDL_Surface* shotSurf = SDL_LoadBMP((resPath + "images/lasershot.bmp").c_str());
		// Skapa textur
		texture = SDL_CreateTextureFromSurface(sys.getRen(), shotSurf);
		// Fria surface
		SDL_FreeSurface(shotSurf);
	}
	~LaserShot() {
		SDL_DestroyTexture(texture);
	}
	SDL_Texture* texture;
	int counter = 0;
};

class SpaceShip : public Sprite {
public:
	static SpaceShip* getInstance() {
		return new SpaceShip();
	}

	void draw() const {
		const SDL_Rect& rect = getRect();
		SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
	}

	void keyDown(SDL_Event event) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			if (rect.x < 1100)
				rect.x += 20;
			break;
		case SDLK_LEFT:
			if (rect.x > 100)
				rect.x -= 20;
			break;
		case SDLK_UP:
			LaserShot* shot = LaserShot::getInstance(rect.x + 70);
			engine.add(shot);
			break;
		}
	}

	void tick(std::vector<Sprite*> activeSprites) {
		detectCollision(activeSprites);
	}

	void detectCollision(std::vector<Sprite*> activeSprites) {
		SDL_Point p = { rect.x + 70, rect.y + 40 };
		for (Sprite* sprite : activeSprites) {
			const SDL_Rect& spriteRect = sprite->getRect();
			if (sprite != this && SDL_PointInRect(&p, &spriteRect)) {
				engine.remove(this);
			}
		}
	}

private:
	SpaceShip() : Sprite(600, 700, 150, 150) {
		SDL_Surface* shipSurf = SDL_LoadBMP((resPath + "images/spaceship.bmp").c_str());
		// Skapa textur
		texture = SDL_CreateTextureFromSurface(sys.getRen(), shipSurf);
		// Fria surface
		SDL_FreeSurface(shipSurf);
	}
	~SpaceShip() {
		SDL_DestroyTexture(texture);
	}
	SDL_Texture* texture;
};



int main(int argc, char** argv) {
	SpaceShip* ship = SpaceShip::getInstance();
	engine.add(ship);
	AlienShip* alienShip = AlienShip::getInstance();
	engine.add(alienShip);
	engine.run();

	return 0;
}

