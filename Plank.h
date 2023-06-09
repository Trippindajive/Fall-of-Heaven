#ifndef PLANK_H_INCLUDED
#define PLANK_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "TextureWrapper.h"

class Plank
{
public:
	static const int PLANK_WIDTH = 80;
	static const int PLANK_HEIGHT = 20;
	static constexpr int PLANK_MAX_AXIS_VEL = 10;
	static constexpr int GFORCE = -1;

	Plank();

	void handleKeyPresses(SDL_Event&);

	void move(SDL_Rect&, const int, const int);

	bool checkCollision(SDL_Rect, SDL_Rect);

	void render(LTexture*, SDL_Renderer*);

	int getPosX();
	int getPosY();
	int getScore();
	SDL_Rect* getCollider();
	void setVelY(int);
	void addScore(int);

private:
	int plankPosX, plankPosY;
	int plankVelX, plankVelY;
	int score;
	SDL_Rect plankCollider;
};

#endif /* PLANK_H_INCLUDED */